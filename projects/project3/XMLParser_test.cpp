#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include <iostream>
#include "catch.hpp"
#include "XMLParser.hpp"

using namespace std;

// TODO Implement tests of your Stack class and XMLParser class here

TEST_CASE( "Test Bag add", "[ADT Bag]" )
{
	   INFO("Hint: testing Bag add()");
		// Create a Bag to hold ints
		Bag<int> intBag;
		int testSize = 2;
		int bagSize;
		bool success;
		for (int i=0; i<testSize; i++) {
			success = intBag.add(i);
			REQUIRE(success);
			bagSize = intBag.size();
			success = (bagSize == (i+1));
			REQUIRE(success);
		}
}

TEST_CASE( "Test Stack push and size", "[ADT Stack]" )
{
	   INFO("Hint: testing Stack push()");
		// Create a Stack to hold ints
		Stack<int> intStack;
		int testSize = 3;
		int stackSize;
		bool success;
		for (int i=0; i<testSize; i++) {
			success = intStack.push(i);
			REQUIRE(success);
			stackSize = intStack.size();
			success = (stackSize == (i+1));
			REQUIRE(success);
		}
}

TEST_CASE( "Test Stack peek", "[ADT Stack]" )
{
	   INFO("Hint: testing Stack peek()");
		// Create a Stack to hold ints
		Stack<int> intStack;
		int testSize = 10;
		int stackSize;
		bool success;
		for (int i=0; i<testSize; i++) {
			success = intStack.push(i);
			REQUIRE(success);
			stackSize = intStack.size();
			success = (stackSize == (i+1));
			REQUIRE(success);
			REQUIRE(intStack.peek() == i);
		}
}

TEST_CASE( "Test Stack pop", "[ADT Stack]" )
{
	   INFO("Hint: testing Stack pop()");
		// Create a Stack to hold ints
		Stack<int> intStack;
		int testSize = 10;
		int stackSize;
		bool success;
		for (int i=0; i<testSize; i++) {
			success = intStack.push(i);
			REQUIRE(success);
			stackSize = intStack.size();
			success = (stackSize == (i+1));
			REQUIRE(success);
			REQUIRE(intStack.peek() == i);
		}
		for(int i = 0; i < testSize; i++){
		REQUIRE(intStack.pop());
		}
		//fail on empty stack
		REQUIRE_FALSE(intStack.pop());
}

TEST_CASE( "Test XMLParser tokenizeInputString Valid Strings", "[XMLParser]" )
{
	   INFO("Hint: tokenize single element test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test>stuff</test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		REQUIRE(myXMLParser.tokenizeInputString("</tag>reversed<tag>"));
		REQUIRE(myXMLParser.tokenizeInputString(" <tag /> "));
		REQUIRE(myXMLParser.tokenizeInputString("stuff"));
		REQUIRE(myXMLParser.tokenizeInputString("<tag><test>stuff</test><tag>"));
}

TEST_CASE( "Test XMLParser tokenizeInputString Each Case", "[XMLParser]" )
{
	   INFO("Hint: check case filter");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><test><empty/>stuff</test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		std::vector<TokenStruct> result = { TokenStruct{StringTokenType::DECLARATION, std::string("xml version=\"1.0\" encoding=\"UTF-8\"")},
											TokenStruct{StringTokenType::START_TAG, std::string("test")},
											TokenStruct{StringTokenType::EMPTY_TAG, std::string("empty")},
											TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
											TokenStruct{StringTokenType::END_TAG, std::string("test")},
											};
		std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		for (int i = 0; i < result.size(); i++) {
			REQUIRE(result[i].tokenType == output[i].tokenType);
			REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
		}
}

TEST_CASE( "Test XMLParser tokenizeInputString Empty Strings", "[XMLParser]" )
{
	   INFO("Hint: check empty condition");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test>stuff</test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		REQUIRE_FALSE(myXMLParser.tokenizeInputString(""));
		REQUIRE_FALSE(myXMLParser.tokenizeInputString("   "));
		REQUIRE_FALSE(myXMLParser.tokenizeInputString("  "));
		REQUIRE_FALSE(myXMLParser.tokenizeInputString(" \n "));
		REQUIRE_FALSE(myXMLParser.tokenizeInputString(" \n\n "));
		REQUIRE_FALSE(myXMLParser.tokenizeInputString(" \r\n\n "));				
}

TEST_CASE( "Test XMLParser tokenizeInputString Invalid Strings", "[XMLParser]" )
{
	   INFO("Hint: check that conditions for invalid are being met");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test>stuff</test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);

		//incomplete tags
		REQUIRE_FALSE(myXMLParser.tokenizeInputString("<teststuff"));
		REQUIRE_FALSE(myXMLParser.tokenizeInputString("test>stuff"));
		REQUIRE_FALSE(myXMLParser.tokenizeInputString("</teststuff"));
		REQUIRE_FALSE(myXMLParser.tokenizeInputString("/test>stuff"));
		REQUIRE_FALSE(myXMLParser.tokenizeInputString("<"));
		REQUIRE_FALSE(myXMLParser.tokenizeInputString(">"));	
		REQUIRE_FALSE(myXMLParser.tokenizeInputString("<test <tag>>stuff</test>"));
		REQUIRE_FALSE(myXMLParser.tokenizeInputString("<test <tag>>stuff<<tag>/test>"));
}

TEST_CASE( "Test XMLParser parseTokenizedInput Valid Strings", "[XMLParser]" )
{
	   INFO("Hint: check for proper closing of tags");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test>stuff</test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		REQUIRE(myXMLParser.parseTokenizedInput());

		REQUIRE(myXMLParser.tokenizeInputString("<?xml version =\"1.0\"?><html><head>Content here</head><body>Content here<empty src=\"f\"/></body></html>"));
		REQUIRE(myXMLParser.parseTokenizedInput());
		REQUIRE(myXMLParser.tokenizeInputString("<tag>content<empty/></tag>"));
		REQUIRE(myXMLParser.parseTokenizedInput());
		REQUIRE(myXMLParser.tokenizeInputString("<tag2><tag>content<empty/></tag></tag2>"));
		REQUIRE(myXMLParser.parseTokenizedInput());
		REQUIRE(myXMLParser.tokenizeInputString("<empty/>"));
		REQUIRE(myXMLParser.parseTokenizedInput());
}

TEST_CASE( "Test XMLParser parseTokenizedInput Invalid Strings", "[XMLParser]" )
{
	   INFO("Hint: check for roots");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test>stuff</test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		REQUIRE(myXMLParser.parseTokenizedInput());

		REQUIRE(myXMLParser.tokenizeInputString("</tag>reversed tag<empty/><tag>"));
		REQUIRE_FALSE(myXMLParser.parseTokenizedInput());
		REQUIRE(myXMLParser.tokenizeInputString("<tag>"));
		REQUIRE_FALSE(myXMLParser.parseTokenizedInput());
		REQUIRE(myXMLParser.tokenizeInputString("</tag>"));
		REQUIRE_FALSE(myXMLParser.parseTokenizedInput());
		REQUIRE(myXMLParser.tokenizeInputString("</tag>reversed tag<empty/><tag>"));
		REQUIRE_FALSE(myXMLParser.parseTokenizedInput());
		REQUIRE(myXMLParser.tokenizeInputString("<tagA>different tags<empty/></tagB>"));
		REQUIRE_FALSE(myXMLParser.parseTokenizedInput());
		REQUIRE(myXMLParser.tokenizeInputString("<?xml?><head>sometext</head>\n<body>sometext</body>"));
		REQUIRE_FALSE(myXMLParser.parseTokenizedInput());
		REQUIRE(myXMLParser.tokenizeInputString("<?xml version =\"1.0\"?><html><head>Content here<?xml version =\"1.0\"?></head><body>Content here<empty src=\"f\"/></body></html>"));
		REQUIRE_FALSE(myXMLParser.parseTokenizedInput());
}

TEST_CASE( "Test XMLParser clear and returnTokenizedInput", "[XMLParser]" )
{
	   INFO("Hint: check clear");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><test><empty/>stuff</test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		std::vector<TokenStruct> result = { TokenStruct{StringTokenType::DECLARATION, std::string("xml version=\"1.0\" encoding=\"UTF-8\"")},
											TokenStruct{StringTokenType::START_TAG, std::string("test")},
											TokenStruct{StringTokenType::EMPTY_TAG, std::string("empty")},
											TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
											TokenStruct{StringTokenType::END_TAG, std::string("test")},
											};
		std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		for (int i = 0; i < result.size(); i++) {
			REQUIRE(result[i].tokenType == output[i].tokenType);
			REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
		}

		myXMLParser.clear();
		string testString2 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><test2><empty/>morestuff</test2>";
		bool success2;
		success2 = myXMLParser.tokenizeInputString(testString2);
		REQUIRE(success2);
		std::vector<TokenStruct> result2 = { TokenStruct{StringTokenType::DECLARATION, std::string("xml version=\"1.0\" encoding=\"UTF-8\"")},
											TokenStruct{StringTokenType::START_TAG, std::string("test2")},
											TokenStruct{StringTokenType::EMPTY_TAG, std::string("empty")},
											TokenStruct{StringTokenType::CONTENT, std::string("morestuff")},
											TokenStruct{StringTokenType::END_TAG, std::string("test2")},
											};
		std::vector<TokenStruct> output2 = myXMLParser.returnTokenizedInput();
		REQUIRE(result2.size() == output2.size());
		for (int i = 0; i < result2.size(); i++) {
			REQUIRE(result2[i].tokenType == output2[i].tokenType);
			REQUIRE(result2[i].tokenString.compare(output2[i].tokenString) == 0);
		}
		
		myXMLParser.clear();

		string invalidString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><tag><empty/>evenmore</tag><test2><empty/>morestuff</test2>";
		bool fail;
		fail = myXMLParser.tokenizeInputString(invalidString);
		REQUIRE_FALSE(myXMLParser.parseTokenizedInput());
}

TEST_CASE( "Test XMLParser containsElement", "[XMLParser]" )
{
	   INFO("Hint: call tokenizeInputString and parseTokenizedInput");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><test><empty/>stuff</test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		REQUIRE_THROWS(myXMLParser.containsElementName("test"));
		REQUIRE_THROWS(myXMLParser.containsElementName("my_stuff"));
		REQUIRE(myXMLParser.parseTokenizedInput());
		REQUIRE(myXMLParser.containsElementName("test"));
		REQUIRE(myXMLParser.containsElementName("empty"));
		REQUIRE_FALSE(myXMLParser.containsElementName("stuff"));
		REQUIRE_FALSE(myXMLParser.containsElementName("my_stuff"));
		REQUIRE_FALSE(myXMLParser.containsElementName(""));
}

TEST_CASE( "Test XMLParser frequencyElementName", "[XMLParser]" )
{
	   INFO("Hint: call tokenizeInputString and parseTokenizedInput");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><tag><test><empty/>stuff</test><test description\"Medium\">stuff</test></tag>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		REQUIRE_THROWS(myXMLParser.frequencyElementName("test") == 0);
		REQUIRE_THROWS(myXMLParser.frequencyElementName("my_stuff") == 0);
		REQUIRE(myXMLParser.parseTokenizedInput());
		REQUIRE(myXMLParser.frequencyElementName("tag") == 1);
		REQUIRE(myXMLParser.frequencyElementName("test") == 2);
		REQUIRE(myXMLParser.frequencyElementName("empty") == 1);
		REQUIRE(myXMLParser.frequencyElementName("stuff") == 0);
		REQUIRE(myXMLParser.frequencyElementName("my_stuff") == 0);
		REQUIRE(myXMLParser.frequencyElementName("") == 0);
}

TEST_CASE( "Test Stack handout-0", "[XMLParser]" )
{
		// Create a Stack to hold ints
		Stack<int> intStack;
		int testSize = 10;
		int stackSize;
		bool success = false;
		for (int i=0; i<testSize; i++) {
			intStack.push(i);
			stackSize = intStack.size();
			success = (stackSize == (i+1));
			REQUIRE(success);
		}
		for (int i = testSize-1; i>=0; i--) {
			REQUIRE(intStack.isEmpty() == false);
            int elem = intStack.peek();
			REQUIRE(elem == i);
            REQUIRE(intStack.isEmpty() == false);
			intStack.pop();
		}
        REQUIRE(intStack.isEmpty() == true);
}

TEST_CASE( "Test Stack handout-1", "[XMLParser]" )
{
	   Stack<char> charStack;
       std::string s("Hello world");
       int i = 1;
       for (auto c:s) {
           charStack.push(c);
           REQUIRE(charStack.size() == i);
           i++;
       }
       for (i = 0; i < 5; i++) {
           REQUIRE(charStack.isEmpty() == false);
           char c = charStack.peek();
           REQUIRE(c == s[s.length()-1-i]);
           REQUIRE(charStack.isEmpty() == false);
           charStack.pop();
       }
       REQUIRE(charStack.size() == 6);
       charStack.clear();
       REQUIRE(charStack.isEmpty() == true);      
}


// You can assume that the beginning and the end of CONTENT will not be filled with whitespace
TEST_CASE( "Test XMLParser tokenizeInputString Handout-0", "[XMLParser]" )
{
	   INFO("Hint: tokenize single element test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test>stuff</test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		std::vector<TokenStruct> result = {TokenStruct{StringTokenType::START_TAG, std::string("test")},
											TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
											TokenStruct{StringTokenType::END_TAG, std::string("test")}};
		std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		for (int i = 0; i < result.size(); i++) {
			REQUIRE(result[i].tokenType == output[i].tokenType);
			REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
		}
}


// You can assume that the beginning and the end of CONTENT will not be filled with whitespace
TEST_CASE( "Test XMLParser tokenizeInputString Handout-1", "[XMLParser]" )
{
	   INFO("Hint: tokenize multiple elements test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><Note src='gmail'>  <From>Tom</From> <To>Alice</To> </Note>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		std::vector<TokenStruct> result = { TokenStruct{StringTokenType::DECLARATION, std::string("xml version=\"1.0\" encoding=\"UTF-8\"")},
									TokenStruct{StringTokenType::START_TAG, std::string("Note")},
									TokenStruct{StringTokenType::START_TAG, std::string("From")},
									TokenStruct{StringTokenType::CONTENT, std::string("Tom")},
									TokenStruct{StringTokenType::END_TAG, std::string("From")},
									TokenStruct{StringTokenType::START_TAG, std::string("To")},
									TokenStruct{StringTokenType::CONTENT, std::string("Alice")},
									TokenStruct{StringTokenType::END_TAG, std::string("To")},
									TokenStruct{StringTokenType::END_TAG, std::string("Note")}};
		std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		for (int i = 0; i < result.size(); i++) {
			REQUIRE(result[i].tokenType == output[i].tokenType);
			REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
		}
}

TEST_CASE( "Test XMLParser parseTokenizedInput Handout-0", "[XMLParser]" )
{
	   INFO("Hint: tokenize single element test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test myattr='abcdef'>stuff<this_is_empty_tag/></test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		std::vector<TokenStruct> result = {TokenStruct{StringTokenType::START_TAG, std::string("test")},
											TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
											TokenStruct{StringTokenType::EMPTY_TAG, std::string("this_is_empty_tag")},
											TokenStruct{StringTokenType::END_TAG, std::string("test")}};
		std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		success = myXMLParser.parseTokenizedInput();
		REQUIRE(success);
		output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		for (int i = 0; i < result.size(); i++) {
			REQUIRE(result[i].tokenType == output[i].tokenType);
			REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
		}
}

TEST_CASE( "Test XMLParser Final Handout-0", "[XMLParser]" )
{
	   INFO("Hint: TestFile");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		ifstream myfile ("./TestFile.txt");
		std::string inputString((std::istreambuf_iterator<char>(myfile) ), (std::istreambuf_iterator<char>()) );

		bool success;
		success = myXMLParser.tokenizeInputString(inputString);
		REQUIRE(success);
		success = myXMLParser.parseTokenizedInput();
		REQUIRE(success);
		REQUIRE(myXMLParser.containsElementName("catalog"));
		REQUIRE(myXMLParser.frequencyElementName("catalog") == 1);
		REQUIRE(myXMLParser.containsElementName("product"));
		REQUIRE(myXMLParser.frequencyElementName("product") == 1);
		REQUIRE(myXMLParser.containsElementName("catalog_item"));
		REQUIRE(myXMLParser.frequencyElementName("catalog_item") == 2);
		REQUIRE(myXMLParser.containsElementName("item_number"));
		REQUIRE(myXMLParser.frequencyElementName("item_number") == 2);
		REQUIRE(myXMLParser.containsElementName("size"));
		REQUIRE(myXMLParser.frequencyElementName("size") == 6);
		REQUIRE(myXMLParser.containsElementName("color_swatch"));
		REQUIRE(myXMLParser.frequencyElementName("color_swatch") == 15);
}
