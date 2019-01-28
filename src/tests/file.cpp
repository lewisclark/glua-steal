/* Copyright (C) 2019 Lewis Clark

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>. */


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
