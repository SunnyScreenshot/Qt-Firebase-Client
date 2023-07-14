cmake_minimum_required(VERSION 3.5)

set(_PROJECT_NAME Qt-Firebase-Client)  # Jarvis
set(MY_PROJECT_VERSION_MAJOR 0)
set(MY_PROJECT_VERSION_MINOR 1)
set(MY_PROJECT_VERSION_PATCH 0)
set(MY_PROJECT_VERSION ${MY_PROJECT_VERSION_MAJOR}.${MY_PROJECT_VERSION_MINOR}.${MY_PROJECT_VERSION_PATCH})
project(${_PROJECT_NAME} VERSION ${MY_PROJECT_VERSION} LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")



find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
        widget.ui
)

#***************************************************通用参数的定义 开始**********************************************
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(architecture_bit "x86")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(architecture_bit "x64")
endif()

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR})     # 创建输出目录
message("---->" ${architecture_bit})

#***************************************************使用第三方库 firebase *.lib 开始**********************************************
# 设置 Firebase 相关的目录
set(firebase_lib_dir "${CMAKE_CURRENT_SOURCE_DIR}/tripartite/firebase/libs/windows/VS2019/MD/${architecture_bit}/Release")
set(firebase_include_dir "${CMAKE_CURRENT_SOURCE_DIR}/tripartite/firebase/include") # 当有多个的时候，请使用 foreach + include_directories 加入
set(firebase_lib_copy_dir ${CMAKE_BINARY_DIR})

# 添加头文件目录
include_directories(${firebase_include_dir})
include_directories("${firebase_include_dir}/firebase")
include_directories("${firebase_include_dir}/google_play_services")

# 拷贝整套的 lib 和 dll
file(GLOB firebase_lib_flies "${firebase_lib_dir}/*.lib")
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
#foreach(it ${firebase_lib_flies})
#    message("firebase_lib_flies:" ${it})
#endforeach()
#foreach(it ${firebase_lib_dir})
#    message("firebase_lib_dir:" ${it})
#endforeach()

# 最后在 target_link_libraries链接时候加上此 dll:only dll name; lib: lib complete absolute path  的名字
#***************************************************使用第三方库 结束**********************************************


add_library(Qt-Firebase-Client SHARED
    ${PROJECT_SOURCES}
)


target_link_libraries(${_PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${firebase_flies_names})

set_target_properties(${_PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ${_PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Qt-Firebase-Client)
endif()
