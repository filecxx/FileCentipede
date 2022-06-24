cmake_minimum_required(VERSION 3.2)
cmake_policy(SET CMP0063 NEW)
cmake_policy(SET CMP0065 NEW)

set(no_unity_build true)
#set(static_gcc_runtime true)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    #set(enable_sanitizer true)
else()
    set(optimize_file_size true)
endif()

project(fileu)
include(../CMakeHeader.txt)

set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(QT_PATH I:\\Librarys\\Qt\\5.15.2\\mingw81_64\\lib\\cmake)
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QT_PATH})
else()
    set(QT_DIR /opt/Qt5)
    #set(QT_DIR /opt/Qt5_GCC/5.15.2/gcc_64/)
    set(QT_PATH ${QT_DIR}/lib/cmake)
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QT_PATH})
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../bin/lib_debug/)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../bin/lib)
endif()
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto")

find_package(Qt5Widgets REQUIRED PATHS ${QT_PATH} NO_DEFAULT_PATH)
find_package(Qt5Svg REQUIRED PATHS ${QT_PATH} NO_DEFAULT_PATH)

file(GLOB_RECURSE project_files
    dialogs/*
    plugins/*
    tasks/*
    file_manager/*
    file_browser/*
    search_engine/*
    view/*
    tools/*
    settings/*
    help/*
    catalogs/*
    pro_global.cpp
    pro_global.h
    pro_methods.cpp
    pro_methods.h
    main_window.h
    main_window.cpp
    main.cpp
)

if(WIN32)
    #set(CMAKE_EXE_LINKER_FLAGS -Wl,-subsystem,windows)
    set(no_console WIN32)
    set(require_libs ${require_libs} Iphlpapi)
	set(project_files ${project_files} "resources_win32.rc")
endif()


#qt5_add_resources(QRC_FILES resources.qrc)
add_executable(${PROJECT_NAME} ${no_console} ${QRC_FILES} ${project_files})


if(WIN32)
    set(require_libs ${require_libs} iconv winmm wtsapi32 userenv iphlpapi)
endif()

target_precompile_headers(${PROJECT_NAME} PUBLIC pro_headers.h)
target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::Svg
    doom_ipdb
    doom_privilege
    ext_ui
    ext_net
    ext_uri
    ext_fs
    ext_archive
    ext_process
    ext_compressor
    ext_crypto
    ext_os
    ext_runtime
    wolfssl
    boost_locale
    boost_nowide
    #iconv
    ${require_libs}
)

