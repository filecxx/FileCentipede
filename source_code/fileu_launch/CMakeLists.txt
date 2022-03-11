cmake_minimum_required(VERSION 3.1)
cmake_policy(SET CMP0063 NEW)
cmake_policy(SET CMP0065 NEW)

set(optimize_file_size true)
set(static_gcc_runtime true)

project(fileu)

include(../CMakeHeader.txt)

if(WIN32)
    set(PROJECT_FILES ${PROJECT_FILES} "resources_win32.rc")
    set(CMAKE_EXE_LINKER_FLAGS -Wl,-subsystem,windows)

endif()

set(PROJECT_FILES main.cpp ${PROJECT_FILES})
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../bin/)

add_executable(${PROJECT_NAME} ${QRC_FILES} ${PROJECT_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "fileu")
target_link_libraries(${PROJECT_NAME} ${require_libs})

