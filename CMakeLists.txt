cmake_minimum_required(VERSION 3.22)
project(sagan)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#add cmake script to downlad conan-cmake integrations
include(cmake/conan_config.cmake)
include(cmake/PreventInSourceBuilds.cmake)
include(cmake/coverage.cmake)
#setup conditional compilation of advanced compiler features
INCLUDE (CheckIncludeFiles)
CHECK_INCLUDE_FILES("stacktrace" USE_STACKTRACES LANGUAGE CXX)
if(USE_STACKTRACES)
	message("Using stacktraces")
	add_definitions(-DUSE_STACKTRACES)
else()	
	message("Not using stacktraces")
endif()

conan_cmake_configure(REQUIRES 
	yaml-cpp/0.8.0
	vsg/1.0.5
    catch2/3.4.0
    entt/3.11.1
    nlohmann_json/3.11.2
    GENERATORS CMakeDeps CMakeToolchain
)

conan_cmake_autodetect(settings)
conan_cmake_install(PATH_OR_REFERENCE .
                    BUILD missing
                    REMOTE conancenter
				    SETTINGS ${settings})
enable_testing()
add_subdirectory(src)
add_subdirectory(test)

install(DIRECTORY
		data/
	DESTINATION
		${CMAKE_INSTALL_BINDIR}/data
	COMPONENT
		${RUNTIME_COMPONENT}
)