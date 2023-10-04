project(sandbox)

find_package(yaml-cpp CONFIG REQUIRED)

add_executable(${PROJECT_NAME})


target_sources(${PROJECT_NAME}
    PRIVATE
       main.cpp
)
target_link_libraries(
${PROJECT_NAME}
	PRIVATE
		renderer
        foundation
		yaml-cpp::yaml-cpp
)

enable_coverage(${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}
        #RUNTIME DESTINATION bin
        #LIBRARY DESTINATION lib
        #ARCHIVE DESTINATION lib/static
)