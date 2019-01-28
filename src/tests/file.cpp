#include "catch.h"

#include "file/file.h"

using namespace glt::file;

TEST_CASE("Filename sanitization", "[file]") {
	REQUIRE(SanitizeLuaFilePath("../../../hello.lua") == "hello.lua");
	REQUIRE(SanitizeLuaFilePath("../../../dir/../../dir/../../../test.lua") == "dir/dir/test.lua");
	REQUIRE(SanitizeLuaFilePath("cat") == "cat.lua");
	REQUIRE(SanitizeLuaFilePath("") == "noname.lua");
	REQUIRE(SanitizeLuaFilePath(".") == "noname.lua");
	REQUIRE(SanitizeLuaFilePath("../dir/////test//./../././myfile.txt") == "dir/test/myfile.lua");
	REQUIRE(SanitizeLuaFilePath(".lua") == "noname.lua");
	REQUIRE(SanitizeLuaFilePath("@!;hi/[[[/test7&;,/file.lua") == "hi/test7/file.lua");
	REQUIRE(SanitizeLuaFilePath(std::string(300, 'a')).string().length() <= 200);
	REQUIRE(SanitizeLuaFilePath("test/hello" + std::string(300, 'a')).string().length() <= 200);
	REQUIRE(SanitizeLuaFilePath("dir/dir2/file.lua   ") == "dir/dir2/file.lua");
	REQUIRE(SanitizeLuaFilePath("dir/dir2/file.lua...") == "dir/dir2/file.lua");
	REQUIRE(SanitizeLuaFilePath("dir/dir2/file.lua   ...") == "dir/dir2/file.lua");
}
