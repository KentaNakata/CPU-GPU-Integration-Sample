CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

project("Common" CXX)
set(module_names "Core" "Test")



# CoreとTestモジュールを作成
# Coreは簡易的なデータコンテナとデータビューワーを持つ
# TestはHelloWorld関数のみを持つ

add_library("Core" SHARED
    "DataContainer.cpp"
    "DataViewer.cpp"
)

add_library("Test" SHARED
    "test.cpp"
)

foreach(module ${module_names})
    target_include_directories(${module} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )

    # ビルド時はBUILD_Commonマクロを定義。これによりビルド時は、シンボルがエクスポート設定になる (api.h)
    target_compile_definitions(${module} PRIVATE
        $<$<PLATFORM_ID:Windows>:__WINDOWS__>
        $<$<PLATFORM_ID:Linux>:__LINUX__>
        $<BUILD_INTERFACE:BUILD_${PROJECT_NAME}>
    )

    # インストール時はUSE_Commonマクロを定義。これにより外部からdllが参照された時は、シンボルがインポート設定になる (api.h)
    target_compile_definitions(${module} PUBLIC
        $<INSTALL_INTERFACE:USE_${PROJECT_NAME}>
    )
endforeach()



# 下記インストール時の設定。利用先であるMainプロジェクトのCmakeLists.txtで、モダンなCMake記法を可能にしている

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
