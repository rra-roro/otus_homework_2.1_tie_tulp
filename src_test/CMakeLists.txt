cmake_minimum_required(VERSION 3.2)

if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.12")
    message(STATUS "CMake version ${CMAKE_VERSION}")
    cmake_policy(SET CMP0074 NEW)
endif ()

add_executable(test_tie_tulp test_tie_tulp.cpp)
target_include_directories(test_tie_tulp PUBLIC "../include/" "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/.." ${GTEST_INCLUDE_DIR})

if (MSVC)

    message(STATUS "MSVC")

	set_target_properties(test_tie_tulp PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED ON
      COMPILE_OPTIONS "/permissive-;/Zc:wchar_t"
    )

else()

	set_target_properties(test_tie_tulp PROPERTIES
		  CXX_STANDARD 17
		  CXX_STANDARD_REQUIRED ON
		  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
	)

endif ()

message(STATUS "GTest include: ${GTEST_INCLUDE_DIR}")
message(STATUS "GTest root: ${GTEST_ROOT}")

enable_testing()
find_package(GTest REQUIRED)

target_link_libraries(test_tie_tulp GTest::GTest GTest::Main tie_tulp_lib)

