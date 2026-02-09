# CMakeList.txt : CMake project for MoloneySnake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Dependencies
include(FetchContent)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("MoloneySnake")

set(RAYLIB_VERSION 4.5.0)

FetchContent_Declare(
	raylib
	URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
	FIND_PACKAGE_ARGS ${RAYLIB_VERSION}
)
	
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(raylib)



# Add source to this project's executable.
add_executable (MoloneySnake "src/MoloneySnake.cpp" "src/Game.cpp" "include/Game.h" "include/Globals.h" "include/GameObject.h" "include/Food.h" "src/GameObject.cpp" "src/Food.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MoloneySnake PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

target_link_libraries(${PROJECT_NAME} raylib)
include_directories("include")

# Define source and destination
set(ASSET_SRC "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set(ASSET_DST "${CMAKE_CURRENT_BINARY_DIR}/assets")

# Create a command to copy the directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSET_SRC}" "${ASSET_DST}"
    COMMENT "Copying game assets to build directory..." )