project(renderer LANGUAGES CXX)
include(GNUInstallDirs)

find_package(EnTT CONFIG REQUIRED)
find_package(vsg CONFIG REQUIRED)


add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} 
PUBLIC
    ViewerCore.h
    SceneEntity.h
    SceneFactory.h
    LoadOperation.h>  
PRIVATE
    ViewerCore.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        EnTT::EnTT
        vsg::vsg
)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    LINKER_LANGUAGE CXX
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    DEBUG_POSTFIX "d"
)
