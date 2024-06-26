#include <string>
using std::string;

#include <iostream>

#include <cctype> // for isalpha
#include <vector>
#include <stack>

#include "algebraic_expressions.hpp"

bool isoperator(char ch)
{
  return ((ch == '+') || (ch == '-') || (ch == '/') || (ch == '*'));
}

int endPost(string s, int last)
{
  int first = 0;

  if ((first > last))
  {
    return -1;
  }

  char ch = s[last];
  if (isalpha(ch))
  {
    return last;
  }
  else
  {
    if (isoperator(ch))
    {
      int lastEnd = endPost(s, last - 1);
      if (lastEnd > -1)
      {
        return endPost(s, lastEnd - 1);
      }
      else
      {
        return -1;
      }
    }
    else
    {
      return -1;
    }
  }
}

bool isPost(string s)
{
  int firstChar = endPost(s, s.size() - 1);

  return (firstChar == 0);
}

void convert(string &postfix, string &prefix)
{
  std::stack<std::string, std::vector<std::string>> my_stack;

  for (char my_char : postfix)
  {
    if (isalpha(my_char))
    {
      my_stack.push(std::string(1, my_char));
    }
    else if (isoperator(my_char))
    {
      std::string temp = my_stack.top();
      my_stack.pop();
      std::string other_temp = my_stack.top();
      my_stack.pop();
      std::string result = my_char + other_temp + temp;
      my_stack.push(result);
    }
  }
  if (!my_stack.empty())
  {
    prefix = my_stack.top();
  }
}
