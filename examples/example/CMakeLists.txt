# ソースファイル
set(SOURCE_FILES
    main.cpp)

# ソースファイルをグループ化
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCE_FILES})

# プロジェクトを作成
add_executable(Example)

# ソースファイルを追加
target_sources(Example PRIVATE ${SOURCE_FILES})

# 外部ライブラリを追加
target_link_libraries(Example PRIVATE Puppy::Puppy)

# インストール
install(TARGETS Example
    RUNTIME DESTINATION bin)