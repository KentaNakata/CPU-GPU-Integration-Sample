CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

project("Main" CXX)



add_executable(${PROJECT_NAME}
	"main.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<PLATFORM_ID:Windows>:__WINDOWS__>
    $<$<PLATFORM_ID:Linux>:__LINUX__>
    BUILD_${PROJECT_NAME}
)



install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "bin"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
)



set(Common_PATH "${CMAKE_CURRENT_BINARY_DIR}/../../src/Common")
add_dependencies(${PROJECT_NAME} Common::Core)

target_link_libraries(${PROJECT_NAME} PRIVATE
	Common::Core
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<$<PLATFORM_ID:Windows>:${Common_PATH}/Common_Core.dll>
    $<$<PLATFORM_ID:Linux>:${Common_PATH}/Common_Core.so>
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

set(CudaCommon_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../cuda/out/install/local-release")
set(CMAKE_PREFIX_PATH "${CudaCommon_PATH}")
find_package(CudaCommon REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    CudaCommon::CudaCore
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<$<PLATFORM_ID:Windows>:${CudaCommon_PATH}/bin/CudaCommon_CudaCore.dll>
    $<$<PLATFORM_ID:Linux>:${CudaCommon_PATH}/lib/CudaCommon_CudaCore.so>
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)



find_package(OpenMP REQUIRED)

target_compile_options(${PROJECT_NAME} PRIVATE 
    "${OpenMP_CXX_FLAGS}"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenMP::OpenMP_CXX
)
