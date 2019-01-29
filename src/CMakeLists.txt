cmake_minimum_required(VERSION 3.2)

add_executable(tie_tulp_cli main.cpp)
target_include_directories(tie_tulp_cli PUBLIC "../include/" "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/..")

if (MSVC)

    message(STATUS "MSVC")

	set_target_properties(tie_tulp_cli PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED ON
      COMPILE_OPTIONS "/permissive-;/Zc:wchar_t"
    )

else()

	set_target_properties(tie_tulp_cli PROPERTIES
		  CXX_STANDARD 17
		  CXX_STANDARD_REQUIRED ON
		  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
	)

endif ()


target_link_libraries(tie_tulp_cli tie_tulp_lib)