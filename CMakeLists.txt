cmake_minimum_required(VERSION 4.0)

project(MySnippets)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(wxWidgets_ROOT_DIR "E:/wxWidgets_3.3.1")
set(wxWidgets_LIB_DIR "E:/wxWidgets_3.3.1/lib/gcc_dll")


find_package(wxWidgets REQUIRED COMPONENTS core base stc)

include(${wxWidgets_USE_FILE})

set(SOURCES
    src/MyApp.cpp
    src/MainFrame.cpp
    wx.rc
)

add_executable(MySnippets WIN32 ${SOURCES})

target_link_libraries(MySnippets ${wxWidgets_LIBRARIES})

target_include_directories(MySnippets PRIVATE include)