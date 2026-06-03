#include "catch2/catch.hpp"

#include "config.hpp"

TEST_CASE("Stealer write mode parsing", "[config]") {
	using glt::config::ParseStealerWriteMode;
	using glt::config::StealerWriteMode;

	REQUIRE(ParseStealerWriteMode("truncate") == StealerWriteMode::Truncate);
	REQUIRE(ParseStealerWriteMode("append") == StealerWriteMode::Append);
	REQUIRE(ParseStealerWriteMode("APPEND") == StealerWriteMode::Append);
	REQUIRE(ParseStealerWriteMode("once") == StealerWriteMode::Once);
	REQUIRE(ParseStealerWriteMode("invalid") == StealerWriteMode::Truncate);
}
