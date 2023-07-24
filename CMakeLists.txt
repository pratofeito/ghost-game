cmake_minimum_required(VERSION 3.21)
project(application LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build shared libraries (.dll/.so) instead of static ones (.lib/.a)" OFF)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

# Download Prato Engine
FetchContent_Declare(
  prato-engine
  GIT_REPOSITORY https://github.com/pratofeito/prato-engine.git
  GIT_TAG main
)
FetchContent_MakeAvailable(prato-engine)

# Add the prato-engine headers to the include directories
include_directories(${prato-engine_SOURCE_DIR}/include)

# Add the source files
file(GLOB_RECURSE SRC_FILES_PROJECT "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Add the include directories
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include")

# Add the executable target
add_executable(application ${SRC_FILES_ENGINE} ${SRC_FILES_PROJECT})

# Link prato-engine and SFML to the target
target_link_libraries(application PRIVATE sfml-audio sfml-graphics sfml-window sfml-system prato-engine)
target_compile_features(application PRIVATE cxx_std_17)

# Copy shared libraries on Windows
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET application POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:application> $<TARGET_FILE_DIR:application> COMMAND_EXPAND_LISTS)
endif()

# Install the target
install(TARGETS application)

