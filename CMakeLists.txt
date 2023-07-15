cmake_minimum_required(VERSION 3.5)

set(project_name Qt-Firebase-Client)  # Jarvis
set(project_version_major 0)
set(project_version_minor 1)
set(project_version_patch 0)
set(project_version ${project_version_major}.${project_version_minor}.${project_version_patch})
project(${project_name} VERSION ${project_version} LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin") # qtcreator + msvc 可执行文件的输出目录
set(CMAKE_BINARY_DIR "${EXECUTABLE_OUTPUT_PATH}")             # visual studio 2022 可执行的输出目录

set(qt_moduls Widgets Network) # Network Multimedia WebSockets
set(qt_version_moduls)
foreach(it ${qt_moduls})
    list(APPEND qt_version_moduls Qt${QT_VERSION_MAJOR}::${it})
    message("--->qt_moduls:" Qt${QT_VERSION_MAJOR}::${it})
endforeach()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS ${qt_moduls})
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS ${qt_moduls} ) # LinguistTools No link

set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
        widget.ui
)

set(src_root_path ${CMAKE_CURRENT_SOURCE_DIR})                                              # default root path curr path （CMakeList.txt）
file(GLOB_RECURSE source_lists LIST_DIRECTORIES false "${src_root_path}/*.cpp" "${src_root_path}/*.h")

source_group(TREE ${src_root_path} FILES ${source_lists})                                   # will be organized according to the actual directory structure, .h.cpp is put together
#include_directories(${PROJECT_SOURCE_DIR}/widgets)  # 修复 Qt Design 使用提升自定义控件后， MinGW 找不到而编译失败

#***************************************************通用参数的定义 开始**********************************************
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(architecture_bit "x86")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(architecture_bit "x64")
endif()

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR})     # 创建输出目录
message("--->" ${architecture_bit})

#***************************************************使用第三方库 firebase *.lib 开始**********************************************
# 设置 Firebase 相关的目录
set(firebase_lib_dir "${CMAKE_CURRENT_SOURCE_DIR}/tripartite/firebase/libs/windows/VS2019/MD/${architecture_bit}/Release")
#set(firebase_include_dir "${CMAKE_CURRENT_SOURCE_DIR}/tripartite/firebase/include") # 当有多个的时候，请使用 foreach + include_directories 加入
set(firebase_lib_copy_dir ${CMAKE_BINARY_DIR})

# 添加头文件目录
#include_directories(${firebase_include_dir})
#include_directories("${firebase_include_dir}/firebase")
#include_directories("${firebase_include_dir}/google_play_services")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/tripartite/firebase/include")
#include_directories("${firebase_include_dir}/firebase")
#include_directories("${firebase_include_dir}/google_play_services")

# 拷贝整套的 lib 和 dll
#    file(GLOB firebase_lib_flies "${firebase_lib_dir}/*.lib")  # 不必，所有模块

set(firebase_lib_flies "${firebase_lib_dir}/firebase_analytics.lib"
                       "${firebase_lib_dir}/firebase_app.lib"
                   )


file(COPY ${firebase_lib_flies} DESTINATION ${firebase_lib_copy_dir})

set(firebase_flies_names "")
foreach(it ${firebase_lib_flies})
    get_filename_component(FILE_NAME ${it} NAME)     # 带后缀
#    get_filename_component(FILE_NAME_WE ${it} NAME_WE)  # 不带后缀
    set(firebase_flies_names ${firebase_flies_names} "${firebase_lib_copy_dir}/${FILE_NAME}")
endforeach()

foreach(it ${firebase_flies_names})
    message("firebase_flies_names:" ${it})
endforeach()
foreach(it ${firebase_lib_flies})
    message("firebase_lib_flies:" ${it})
endforeach()
#foreach(it ${firebase_lib_dir})
#    message("firebase_lib_dir:" ${it})
#endforeach()

# 最后在 target_link_libraries链接时候加上此 dll:only dll name; lib: lib complete absolute path  的名字
#***************************************************使用第三方库 结束**********************************************

add_executable(${project_name}
    ${PROJECT_SOURCES}
)

target_link_libraries(${project_name} PRIVATE ${qt_version_moduls}
    "${firebase_lib_dir}/firebase_analytics.lib"
    "${firebase_lib_dir}/firebase_app.lib"
#    ${firebase_flies_names}
)

set_target_properties(${project_name} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ${project_name}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${project_name})
endif()
