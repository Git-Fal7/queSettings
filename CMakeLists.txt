cmake_minimum_required (VERSION 2.8.12)
project (Qt5CMake)

find_package (Qt5Widgets)

set (queSettingsLib_src ${PROJECT_SOURCE_DIR}/src/mainwindow.cpp)
set (queSettingsLib_hdr ${PROJECT_SOURCE_DIR}/include/mainwindow.h)
set (queSettingsLib_ui  ${PROJECT_SOURCE_DIR}/UI/mainwindow.ui)
set (queSettingsBin_src ${PROJECT_SOURCE_DIR}/src/main.cpp)

qt5_wrap_cpp(queSettingsLib_hdr_moc ${queSettingsLib_hdr})
qt5_wrap_ui (queSettingsLib_ui_moc  ${queSettingsLib_ui})

include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_BINARY_DIR})

add_library (queSettingsLib SHARED 
    ${queSettingsLib_src}
    ${queSettingsLib_hdr_moc}
    ${queSettingsLib_ui_moc}
)
target_link_libraries (queSettingsLib Qt5::Widgets)

add_executable(queSettings ${queSettingsBin_src})
target_link_libraries (queSettings queSettingsLib)
