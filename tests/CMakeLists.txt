# GoogleTestのダウンロード
include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG        release-1.12.1
)

# GoogleTestのビルド
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

# ソースファイル
set(SOURCE_FILES
	test.cpp
	)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCE_FILES})

# 実行ファイルを作成
add_executable(Puppy-tests ${SOURCE_FILES})

# ライブラリをリンク
target_link_libraries(Puppy-tests
	PRIVATE
	Puppy::Puppy
	GTest::gtest_main
	)

# インストール
install(TARGETS Puppy-tests RUNTIME DESTINATION bin)

# テスト実行
include(GoogleTest)
gtest_discover_tests(Puppy-tests)