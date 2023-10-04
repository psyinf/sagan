project(foundation LANGUAGES CXX)
include (CheckIncludeFiles)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME} 
INTERFACE
    Config.h
    ErrorTrace.h
PRIVATE
)

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(
    ${PROJECT_NAME}
    INTERFACE
        yaml-cpp::yaml-cpp
        nlohmann_json::nlohmann_json
)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    LINKER_LANGUAGE CXX
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    DEBUG_POSTFIX "d"
)
