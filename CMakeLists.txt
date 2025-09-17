cmake_minimum_required(VERSION 3.20)
project(lldb_user_types)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(UNIX)
    add_compile_options(-fdiagnostics-color -g)
endif()

file(GLOB src_files src/*.cpp)

foreach(file IN LISTS src_files)
    get_filename_component(tgt ${file} NAME_WLE)
    add_executable(${tgt} ${file})
    target_include_directories(${tgt} PRIVATE include/)
endforeach()
