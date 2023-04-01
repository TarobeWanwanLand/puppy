# ソースファイル
set(SOURCE_FILES
    main.cpp
)

# ソースファイルをグループ化
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCE_FILES})

# プロジェクトを作成
add_executable(string_example)

# ソースファイルを追加
target_sources(string_example PRIVATE ${SOURCE_FILES})

# 外部ライブラリを追加
target_link_libraries(string_example PRIVATE puppy::puppy)

# インストール
install(TARGETS string_example
    RUNTIME DESTINATION bin
)