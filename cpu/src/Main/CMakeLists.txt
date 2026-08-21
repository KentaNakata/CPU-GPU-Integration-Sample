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



set(CudaCommon_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../cuda/out/install/local-release") # [TODO] CudaCommonプロジェクトのパスのハードコーディング解消
list(APPEND CMAKE_PREFIX_PATH "${CudaCommon_PATH}")

# 外部CMakeプロジェクト(CudaCommon)をfind_package
find_package(CudaCommon REQUIRED)

# 作成したCommonやCudaCommonプロジェクトは、モダンなCMake記法を可能にしている
target_link_libraries(${PROJECT_NAME} PRIVATE
    Common::Core
    Common::Test
    CudaCommon::CudaCore
    CudaCommon::CudaTest
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Common::Core>
        $<TARGET_FILE:Common::Test>
        $<TARGET_FILE:CudaCommon::CudaCore>
        $<TARGET_FILE:CudaCommon::CudaTest>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)



find_package(OpenMP REQUIRED)

target_compile_options(${PROJECT_NAME} PRIVATE 
    "${OpenMP_CXX_FLAGS}"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenMP::OpenMP_CXX
)
