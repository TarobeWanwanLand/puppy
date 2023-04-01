# ソースファイル
set(SOURCE_FILES
	test.cpp
	)

# ソースファイルをグループ化
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCE_FILES})

# 実行ファイルを作成
add_executable(puppy-tests)

# ソースファイルを追加
target_sources(puppy-tests PRIVATE ${SOURCE_FILES})

# ライブラリをリンク
find_package(GTest REQUIRED)
target_link_libraries(puppy-tests
	PRIVATE
	puppy::puppy
	GTest::gtest_main
	)

# インストール
install(TARGETS puppy-tests
	RUNTIME DESTINATION bin
	)

# テスト実行
include(GoogleTest)
gtest_discover_tests(puppy-tests)