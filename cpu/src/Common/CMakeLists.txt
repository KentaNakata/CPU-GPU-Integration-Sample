CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

project("Common" CXX)
set(module_names "Core")



add_library("Core" SHARED
	"core.cpp"
)

target_include_directories(${module_names} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_definitions(${module_names} PRIVATE
    $<$<PLATFORM_ID:Windows>:__WINDOWS__>
    $<$<PLATFORM_ID:Linux>:__LINUX__>
    $<BUILD_INTERFACE:BUILD_${PROJECT_NAME}>
)
target_compile_definitions(${module_names} PUBLIC
    $<INSTALL_INTERFACE:USE_${PROJECT_NAME}>
)



install(TARGETS ${module_names}
    EXPORT "${PROJECT_NAME}Targets"
    RUNTIME DESTINATION "bin"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
)

install(DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION "include"
)

install(EXPORT "${PROJECT_NAME}Targets"
    DESTINATION "lib/cmake/${PROJECT_NAME}"
    NAMESPACE "${PROJECT_NAME}::"
)

install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake"
    DESTINATION "lib/cmake/${PROJECT_NAME}"
)

foreach(module IN LISTS module_names)
    add_library("${PROJECT_NAME}::${module}" ALIAS "${module}")

    set_target_properties("${module}" PROPERTIES
        OUTPUT_NAME_DEBUG "${PROJECT_NAME}_${module}"
        OUTPUT_NAME_RELEASE "${PROJECT_NAME}_${module}"
    )
endforeach()
