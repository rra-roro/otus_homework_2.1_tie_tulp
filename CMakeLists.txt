cmake_minimum_required(VERSION 3.2)

project(tie_tulp_lib VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.12")
    message(STATUS "CMake version ${CMAKE_VERSION}")
    cmake_policy(SET CMP0074 NEW)
endif ()

configure_file("./include/version.h.in" version.h)

add_library(tie_tulp_lib ./src_lib/lib.cpp)
add_executable(tie_tulp_cli ./src/main.cpp)
add_executable(test_tie_tulp ./src_test/test_tie_tulp.cpp)

target_include_directories(tie_tulp_lib PUBLIC "include/" "${CMAKE_CURRENT_BINARY_DIR}" )
target_include_directories(tie_tulp_cli PUBLIC "include/" "${CMAKE_CURRENT_BINARY_DIR}")
target_include_directories(test_tie_tulp PUBLIC "include/" "${CMAKE_CURRENT_BINARY_DIR}" $ENV{gtest_INCLUDE_DIR})

if (MSVC)

    message(STATUS "MSVC")

	set_target_properties(tie_tulp_cli tie_tulp_lib test_tie_tulp PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED ON
     # COMPILE_OPTIONS "-Wall;/permissive-;/Zc:wchar_t"
    )

else()

	set_target_properties(tie_tulp_cli tie_tulp_lib test_tie_tulp PROPERTIES
		  CXX_STANDARD 14
		  CXX_STANDARD_REQUIRED ON
		  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
	)

endif ()
   
target_link_libraries(tie_tulp_cli tie_tulp_lib)

set(GTEST_INCLUDE_DIR  $ENV{gtest_INCLUDE_DIR})

enable_testing()
find_package(GTest REQUIRED)

target_link_libraries(test_tie_tulp "${GTEST_BOTH_LIBRARIES}" tie_tulp_lib)

install(TARGETS tie_tulp_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT rra.roro@gmail.com)

include(CPack)

enable_testing()

add_test(test_tie_tulp test_tie_tulp)