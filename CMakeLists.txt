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
add_executable (MoloneySnake "src/MoloneySnake.cpp" "src/Game.cpp" "include/Snake.h" "include/Food.h" "include/Globals.h" "src/Game.cpp" "src/Food.cpp"  "src/Snake.cpp")

target_link_libraries(${PROJECT_NAME} raylib)
include_directories("include")

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(${PROJECT_NAME} copy_assets)

# Version of game where edges cause game over
# add_compile_definitions(EVIL_EDGES)