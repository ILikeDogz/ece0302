// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
	@file XMLParser.cpp */

#include <string>
#include <assert.h>
#include "XMLParser.hpp"

// TODO: Implement the constructor here
XMLParser::XMLParser()
{
	elementNameBag = new Bag<std::string>;
	parseStack = new Stack<std::string>;
	// vector is not dynamic
	tokened_input = false;
	parsed_input = false;

} // end default constructor

// TODO: Implement the destructor here
XMLParser::~XMLParser()
{
	elementNameBag->~Bag();
	parseStack->~Stack();
	// vector is not dynamic

} // end destructor

// TODO: Implement the tokenizeInputString method
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	size_t tags = 0;
	size_t index = 0;
	std::string my_string = "";
	size_t space_remove = 0;
	// remove spaces at the
	for (space_remove = 0; space_remove < inputString.length(); space_remove++)
	{
		if (std::isspace(inputString[space_remove]))
		{ // locates space and creates a substring at point of space
		}
		else
		{
			break;
		}
	}
	my_string = inputString.substr(space_remove);
	if (my_string.empty())
	{
		return false;
	}
	while (index < my_string.length())
	{
		TokenStruct my_token;
		if (std::isspace(my_string[index]))
		{ // just move past spaces
			index++;
		}
		else if (my_string[index] == '<')
		{ // start of a tag
			size_t end_delimiter = my_string.find('>', index);
			if (end_delimiter == std::string::npos)
			{ // every < should have a matching closing >
				return false;
			}
			std::string my_tag = my_string.substr(index, (end_delimiter + 1) - index);
			size_t length = my_tag.length();
			// there are four cases to look out for, start-tag <element>, end-tag </element>, empty-tag </element>, and declaration <?  ?>
			bool start_slash = my_tag[1] == '/';
			bool end_slash = my_tag[length - 2] == '/';
			bool start_question = my_tag[1] == '?';
			bool end_question = my_tag[length - 2] == '?';
			if (!start_slash && !end_slash && !start_question && !end_question)
			{ // start tag
				my_token.tokenType = START_TAG;
			}
			else if (start_slash && !end_slash && !start_question && !end_question)
			{ // end tag
				my_token.tokenType = END_TAG;
			}
			else if (!start_slash && end_slash && !start_question && !end_question)
			{ // empty tag
				my_token.tokenType = EMPTY_TAG;
			}
			else if (!start_slash && !end_slash && start_question && end_question)
			{ // declaration
				my_token.tokenType = DECLARATION;
				my_token.tokenString = my_tag.substr(2, my_tag.length() - 4); // remove front and end
				tokenizedInputVector.push_back(my_token);
				index += my_tag.length();
				tags++;
				continue; //skip removing invalid chars
			}
			else
			{
				return false; // did not meet the four cases
			}

			// single out the name
			std::string my_name = "";
			if (my_tag[0] == '<' && my_tag[length - 1] == '>')
			{ // all valid tags should contain < >
				my_name = my_tag.substr(1, length - 2);
			}
			// delimiters are now removed, assuming tag contained < >, should not make it this far if it does not contain < >
			if (my_tag[1] == '/')
			{													   // end tag
				my_name = my_name.substr(1, my_name.length() - 1); // remove front
			}
			else if (my_tag[length - 2] == '/')
			{													   // empty tag
				my_name = my_name.substr(0, my_name.length() - 1); // remove end
			}
			// at this point, name has no end tags, or invalid
			size_t temp = my_name.length();
			for (size_t i = 0; i < temp; i++)
			{
				if (std::isspace(my_name[i]))
				{ // locates space and creates a substring at point of space
					my_name = my_name.substr(0, i);
					break;
				}
			}
			// check for invalid chars in the name
			std::string invalid_characters = "!\"#$%&'()*+,-/;<=?@[\\]^`{|}~ ";
			std::string invalid_start = "-.0123456789";
			if (my_name.empty())
			{ // invalid if empty
				return false;
			}
			// locate invalid characters
			for (char my_char : invalid_characters)
			{
				if (my_name.find(my_char) != std::string::npos)
				{ // invalid if any of the invalid chars are found
					return false;
				}
			}
			for (char my_char : invalid_start)
			{ // check for invalid first characters
				if (my_name[0] == my_char)
				{
					return false;
				}
			}
			my_token.tokenString = my_name;
			tokenizedInputVector.push_back(my_token);
			index += my_tag.length();
			tags++;
		}
		else
		{
			if (tags % 2 == 0)
			{
				return false;
			}
			my_token.tokenType = CONTENT;
			size_t next_delimiter = my_string.find('<', index);
			if (next_delimiter == string::npos)
			{
				next_delimiter = my_string.length(); // we hit an end
			}
			size_t i = index;
			for (i; i < next_delimiter; i++)
			{
				if (std::isspace(my_string[i]))
				{ // removes spaces from content
					my_token.tokenString = my_string.substr(index, i - index);
					break;
				}
			}
			my_token.tokenString = my_string.substr(index, i - index);
			size_t content_index = next_delimiter;
			index = next_delimiter;
			tokenizedInputVector.push_back(my_token);
		}
	}
	tokened_input = true;
	return true;
} // end

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput()
{
	return false;
}

// TODO: Implement the clear method here
void XMLParser::clear()
{
	elementNameBag->clear();
	parseStack->clear();
	tokenizedInputVector.clear();
	tokened_input = false;
	parsed_input = false;
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

// TODO: Implement the containsElementName method
bool XMLParser::containsElementName(const std::string &inputString) const
{
	if (tokened_input && parsed_input)
		return elementNameBag->contains(inputString);
	throw std::logic_error("did not call tokenizedInputString and parseTokenizedInput");
}

// TODO: Implement the frequencyElementName method
int XMLParser::frequencyElementName(const std::string &inputString) const
{
	if (tokened_input && parsed_input)
		return elementNameBag->getFrequencyOf(inputString);
	throw std::logic_error("did not call tokenizedInputString and parseTokenizedInput");
	return -1;
}
