#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

TEST_CASE("Test number", "[FindPalindrome]")
{
	FindPalindrome b;
	REQUIRE(b.number() == 0);
	std::vector<std::string> a = {"a", "aA", "aAA", "aAAA", "aAAAA"};
	REQUIRE(b.add(a));
	REQUIRE(b.number() == 120);
	b.clear();
	REQUIRE(b.number() == 0);
}

TEST_CASE("Test clear", "[FindPalindrome]")
{
	FindPalindrome b;
	REQUIRE(b.number() == 0);
	REQUIRE(b.add("a"));
	REQUIRE(b.add("AA"));
	REQUIRE(b.add("AaA"));
	REQUIRE(b.number() == 6);
	b.clear();
	REQUIRE(b.number() == 0);
}

TEST_CASE("Test add", "[FindPalindrome]")
{
	FindPalindrome b;

	REQUIRE(b.add("a"));
	REQUIRE(b.add("AA"));
	REQUIRE(b.add("AaA"));
	REQUIRE(b.number() == 6);
}

TEST_CASE("Test add (vector)", "[FindPalindrome]")
{
	FindPalindrome b;
	std::vector<std::string> a = {"a", "aA", "aAA", "aAAA"};
	REQUIRE(b.add(a));
	REQUIRE(b.number() == 24);
}

TEST_CASE("Test adding invalid words, add (string) and add(vector)", "[FindPalindrome]")
{
	FindPalindrome b;
	REQUIRE(b.add("kayak"));
	REQUIRE(!b.add("kayak1"));
	std::vector<std::string> valid = {"a", "aA", "aAA", "aAAA"};
	std::vector<std::string> invalid = {"b", "bB", "b1B", "bBBB"};
	std::vector<std::string> invalid2 = {"b", "bB", "b,B", "bBBB"};
	REQUIRE(b.add(valid));
	REQUIRE_FALSE(b.add(invalid));
	REQUIRE_FALSE(b.add(invalid2));
}

TEST_CASE("Test cutTest1", "[FindPalindrome]")
{
	FindPalindrome b;
	std::vector<std::string> empty = {};
	std::vector<std::string> valid = {"a", "aA", "aAA", "aAAA"};								 // no odd count
	std::vector<std::string> valid2 = {"JImmY", "TtiMMy", "bObS", "GgAaRYy", "Marshall", "Jom"}; // one odd count
	std::vector<std::string> invalid = {"ccc", "bbb", "dd"};									 // c and b both show up an odd number of times
	REQUIRE(b.cutTest1(empty));
	REQUIRE(b.cutTest1(valid));
	REQUIRE(b.cutTest1(valid2));
	REQUIRE_FALSE(b.cutTest1(invalid));
}

TEST_CASE("Test cutTest2", "[FindPalindrome]")
{
	FindPalindrome b;
	std::vector<std::string> empty = {};
	std::vector<std::string> valid1 = {"JImmY", "TtiMMy", "bObS", "GgAaRYy"}; // inside valid2
	std::vector<std::string> valid2 = {"JImmY", "TtiMMy", "bObS", "GgAaRYy", "Marshall", "Jom"};
	std::vector<std::string> invalid1 = {"ccc", "bbb"};		  // not inside invalid2
	std::vector<std::string> invalid2 = {"eee", "ggg", "hh"}; // not inside invalid1
	std::vector<std::string> same1 = {"aa", "aaa"};	
	std::vector<std::string> same2 = {"aa", "aaa"}; 
	REQUIRE(b.cutTest2(empty, empty));
	REQUIRE(b.cutTest2(valid1, valid2));
	REQUIRE(b.cutTest2(same1, same2));
	REQUIRE_FALSE(b.cutTest2(invalid1, invalid2));
}

TEST_CASE("Test toVector and recursiveFindPalindromes", "[FindPalindrome]")
{
	FindPalindrome b;
	std::vector<std::vector<std::string>> empty = {};
	REQUIRE(b.toVector() == empty);
	std::vector<std::string> a = {"timmy", "mmit", "timm", "ymmit"};
	REQUIRE(b.add(a)); //recursive find palindrome is called forming a list of palindromes
	REQUIRE(b.number() == 8);
	std::vector<std::vector<std::string>> c = {{"ymmit", "timm", "mmit", "timmy"}, {"ymmit", "mmit", "timm", "timmy"}, {"timm", "timmy", "ymmit", "mmit"}, {"timm", "ymmit", "timmy", "mmit"}, {"mmit", "timmy", "ymmit", "timm"}, {"mmit", "ymmit", "timmy", "timm"}, {"timmy", "timm", "mmit", "ymmit"}, {"timmy", "mmit", "timm", "ymmit"}};
	for(int i = 0; i < c.size(); i++){
		//check that all the palindromes in c, are found in the b vector
		REQUIRE(std::find(b.toVector().begin(), b.toVector().end(), c[i]) != b.toVector().end()); 
	}
}	
TEST_CASE("Test Single Letter Combination", "[FindPalindrome]")
{
	FindPalindrome b;
	std::vector<std::string> a = {"a", "b"};
	b.add(a);
	REQUIRE(b.number() == 0);
	b.clear();
	b.add("a");
	REQUIRE(b.number() == 1);
}	

