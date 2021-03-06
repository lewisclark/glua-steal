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


#include "catch2/catch.hpp"

#include "file/file.hpp"
#include "file/sanitization.hpp"
#include "os.hpp"

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
	REQUIRE(SanitizeLuaFilePath("...") == "noname.lua");
	REQUIRE(SanitizeLuaFilePath("...@") == "noname.lua");
	REQUIRE(SanitizeLuaFilePath("@...@") == "noname.lua");
	REQUIRE(SanitizeLuaFilePath("-") == "-.lua");
	REQUIRE(SanitizeLuaFilePath(".a.") == "noname.lua");
	REQUIRE(SanitizeLuaFilePath("_._.") == "_.lua");
	REQUIRE(SanitizeLuaFilePath("..././test.lua") == "test.lua");
	REQUIRE(SanitizeLuaFilePath("..././dir/.../.../../dir2/test.lua") == "dir/dir2/test.lua");
	REQUIRE(SanitizeLuaFilePath("..\xc1\x1c./test.lua") == "test.lua");
	REQUIRE(SanitizeLuaFilePath("..\xc0\xaf./test.lua") == "test.lua");
	REQUIRE(SanitizeLuaFilePath("dir1/..\xc1\x1c./dir2/test.lua") == "dir1/dir2/test.lua");
	REQUIRE(SanitizeLuaFilePath("dir1/..\xc0\xaf./dir2/test.lua") == "dir1/dir2/test.lua");

#if (defined(OS_LINUX) || defined(OS_MAC))
	REQUIRE(SanitizeLuaFilePath("/tmp/file.lua") == "tmp/file.lua");
	REQUIRE(SanitizeLuaFilePath("..//tmp/file.lua") == "tmp/file.lua");
	REQUIRE(SanitizeLuaFilePath("./tmp/file.lua") == "tmp/file.lua");
	REQUIRE(SanitizeLuaFilePath("./tmp/./file.lua") == "tmp/file.lua");
#elif (defined(OS_WINDOWS))
	REQUIRE(SanitizeLuaFilePath("C:/test/file.lua") == "test/file.lua");
	REQUIRE(SanitizeLuaFilePath("con/lpt8/nultest/nul/aux.lua") == "_con/_lpt8/nultest/_nul/_aux.lua");
	REQUIRE(SanitizeLuaFilePath("dir/com9") == "dir/_com9.lua");
	REQUIRE(SanitizeLuaFilePath("dir/com9.lua") == "dir/_com9.lua");
	REQUIRE(SanitizeLuaFilePath("dir/Com9.lua") == "dir/_Com9.lua");
	REQUIRE(SanitizeLuaFilePath("dir/Com9") == "dir/_Com9.lua");
	REQUIRE(SanitizeLuaFilePath("dir2/Com9/AuX.aUx") == "dir2/_Com9/_AuX.lua");
	REQUIRE(SanitizeLuaFilePath("a@u@x.lua") == "_aux.lua");
	REQUIRE(SanitizeLuaFilePath("c;o;n.lua") == "_con.lua");
	REQUIRE(SanitizeLuaFilePath("...\\.\\test.lua") == "test.lua");
#endif
}
