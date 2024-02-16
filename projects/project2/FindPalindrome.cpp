#include <string>
#include <vector>
#include <iostream>
#include "FindPalindrome.hpp"
#include <map>

//------------------- HELPER FUNCTIONS -----------------------------------------

// non-class helper functions go here, should be declared as "static" so that
// their scope is limited

// helper function to convert string to lower case
static void convertToLowerCase(std::string &value)
{
	std::locale loc;
	for (int i = 0; i < value.size(); i++)
	{
		value[i] = tolower(value[i]);
	}
}

static std::string stringVectorToString(const std::vector<std::string> string_vector)
{
	std::string new_string = "";
	for (std::string s : string_vector)
	{
		new_string += s; // adds a string at a time
	}
	return new_string;
}

//------------------- PRIVATE CLASS METHODS ------------------------------------

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(std::vector<std::string> candidateStringVector,
											  std::vector<std::string> currentStringVector)
{
	/* at first call, candidateStringVector is empty
	candidateStringVector, will be used to hold the permutated vector, while currentStringVector is original vector
	*/
	if (!cutTest2(candidateStringVector, currentStringVector))
	{
		return;
	}
	if (currentStringVector.empty()) // triggers after a full permutation vector is made
	{
		std::string temp_string = stringVectorToString(candidateStringVector);
		if (isPalindrome(temp_string))
		{
			my_palindromes.push_back(candidateStringVector); // creates a vector of string vectors, that contains all the permutations that are valid pallindromes
		}
		return;
	}
	else
	{
		for (int i = 0; i < currentStringVector.size(); i++)
		{
			candidateStringVector.push_back(currentStringVector.back()); // add to the back of the candidate
			currentStringVector.pop_back();								 // remove what was placed in candidate

			recursiveFindPalindromes(candidateStringVector, currentStringVector); // recursive call

			currentStringVector.insert(currentStringVector.begin(), candidateStringVector.back()); // add to the beginning what was originally removed, the back is now in the front
			candidateStringVector.pop_back();													   // remove what was placed in current
		}
	}
	return;
}

// private function to determine if a string is a palindrome (given, you
// may change this if you want)
bool FindPalindrome::isPalindrome(std::string currentString) const
{
	std::locale loc;
	// make sure that the string is lower case...
	convertToLowerCase(currentString);
	// see if the characters are symmetric...
	int stringLength = currentString.size();
	for (int i = 0; i < stringLength / 2; i++)
	{
		if (currentString[i] != currentString[stringLength - i - 1])
		{
			return false;
		}
	}
	return true;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
	// vectors are initialized when created, as vectors have their own constructor
}

FindPalindrome::~FindPalindrome()
{
	my_words.clear();
	my_palindromes.clear();
}

int FindPalindrome::number() const
{
	return toVector().size();
}

void FindPalindrome::clear()
{
	my_words.clear();
	my_palindromes.clear();
}

bool FindPalindrome::cutTest1(const std::vector<std::string> &stringVector)
{
	if (stringVector.size() == 0) // if empty case
	{
		return true;
	}
	std::map<char, int> my_map;				   // hashmap is set to the default of the type it's converting to, in this case 0
	for (std::string my_string : stringVector) // iterate through every string in the vector
	{
		convertToLowerCase(my_string);
		for (char my_character : my_string) // iterate through every character in the string
		{
			my_map[my_character]++; // go through the map with the lowercase characters as index, ihcrements if same character appears again
		}
	}
	std::string the_alphabet = "abcdefghijklmnopqrstuvwxyz";
	int odd_count = 0;
	for (char my_character : the_alphabet)
	{
		if (my_map[my_character] % 2 == 1) // check every character in the alphabet, faster than going through every character and string in the string vector again, most of the time
		{
			odd_count++;
		};
	}
	return odd_count <= 1;
}

bool FindPalindrome::cutTest2(const std::vector<std::string> &stringVector1,
							  const std::vector<std::string> &stringVector2)
{

	// fix sentence to string
	std::string first_string = stringVectorToString(stringVector1);
	std::string second_string = stringVectorToString(stringVector2);

	convertToLowerCase(first_string);
	convertToLowerCase(second_string);

	if (first_string.size() > second_string.size()) // first_string will be the smalller
	{
		std::swap(first_string, second_string);
	}

	for (char my_character : first_string)
	{
		if (second_string.find(my_character) == std::string::npos)
		{ // npos is a failure state
			return false;
		}
	}
	return true;
}

bool FindPalindrome::add(const std::string &value)
{
	for (char my_character : value)
	{
		if (!std::isalpha(my_character)) // check to make sure character is contained in the alphabet
		{
			return false;
		}
	}
	std::string lower_case_string = value; // don't alter value, but still want to only compare lowercases
	convertToLowerCase(lower_case_string);
	for (std::string my_string : my_words) // confirm no repetition
	{
		convertToLowerCase(my_string);
		if (my_string == lower_case_string)
		{
			return false;
		}
	}
	my_words.push_back(value);
	my_palindromes.clear();
	std::vector<std::string> temp;
	if (cutTest1(my_words)) // only needs to be called initially, as if it fails, not point in finding pallindromes
	{
		recursiveFindPalindromes(temp, my_words);
	}
	return true;
}

bool FindPalindrome::add(const std::vector<std::string> &stringVector)
{
	for (std::string my_string : stringVector)
	{
		for (char my_character : my_string)
		{
			if (!std::isalpha(my_character)) // check to make sure character is contained in the alphabet
			{
				return false;
			}
		}
		convertToLowerCase(my_string);
		for (std::string my_other_string : my_words) // confirm no repetition
		{
			convertToLowerCase(my_other_string);
			if (my_other_string == my_string)
			{
				return false;
			}
		}
	}
	for(std::string my_string : stringVector){
		my_words.push_back(my_string); // add the string, after checking no duplicates and valid characters
	}
	my_palindromes.clear();
	std::vector<std::string> temp;
	if (cutTest1(my_words)) // only needs to be called initially, as if it fails, not point in finding pallindromes
	{
		recursiveFindPalindromes(temp, my_words);
	}
	return true;
}

std::vector<std::vector<std::string>> FindPalindrome::toVector() const
{
	return my_palindromes;
}
