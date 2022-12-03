cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "3" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(ipfilter VERSION ${PROJECT_VERSION})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(GTest REQUIRED)

configure_file(version.h.in version.h)

#Main target 
add_executable(ip_filter main.cpp file_funcs.cpp print.cpp)
add_library(lib_ipfilter lib.cpp print.cpp)

#Test target
add_executable(test_version test_version.cpp)
add_executable(g_test_version gtest_version.cpp file_funcs.cpp)

set_target_properties(ip_filter lib_ipfilter test_version g_test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_include_directories(lib_ipfilter
    PRIVATE "${CMAKE_BINARY_DIR}"
)

# Add src to the include directories for the test target
target_include_directories(g_test_version
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

# Add googletest to the include directories for the test target
target_include_directories(g_test_version
    PRIVATE ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(ip_filter PRIVATE
    lib_ipfilter
)

target_link_libraries(test_version
    ${Boost_LIBRARIES}
    lib_ipfilter
)

# Link test target against gtest libraries
if (MSVC)
    target_link_libraries(g_test_version PRIVATE
    	${GTEST_BOTH_LIBRARIES}
    	lib_ipfilter
    )
else ()
    target_link_libraries(g_test_version PRIVATE
    	${GTEST_BOTH_LIBRARIES}
		pthread
    	lib_ipfilter
    )
endif()

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(lib_ipfilter PRIVATE
        /W4
    )
    target_compile_options(test_version PRIVATE
        /W4
    )
    target_compile_options(
        g_test_version PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(lib_ipfilter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
     target_compile_options(
        g_test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(test_version test_version)