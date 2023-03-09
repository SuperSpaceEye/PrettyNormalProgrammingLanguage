cmake_minimum_required(VERSION 3.24)
project(PrettyNormalProgrammingLanguage)
set(${PROJECT_NAME} PrettyNormalProgrammingLanguage)

set(CMAKE_CXX_STANDARD 20)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

include_directories("Source/Misc")
include_directories("Source/Compiler")

add_executable(${PROJECT_NAME} main.cpp Source/Compiler/Transpiler/Tokens.h Source/Misc/ConstMap.h)

llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(${PROJECT_NAME} ${llvm_libs})