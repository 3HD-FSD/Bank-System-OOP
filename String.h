#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class String
{
private:
	string _value;
public:
	String()
	{
		_value = "";
	}

	String(string value)
	{
		_value = value;
	}

	void setValue(string value)
	{
		_value = value;
	}

	string getValue()
	{
		return _value;
	}

	__declspec(property(get = getValue, put = setValue)) string value;




	static vector <string> split(string str, string delimiter)
	{
		vector<string> vWords;
		string word;
		size_t pos;
		while ((pos = str.find(delimiter)) != std::string::npos)
		{
			word = str.substr(0, pos);

			if (word != "")
			{
				vWords.push_back(word);
			}

			str.erase(0, pos + delimiter.length());
		}
		if (str != "")
		{
			vWords.push_back(str);
		}
		return vWords;
	}

	vector <string> split(string delimiter)
	{
		return split(_value, delimiter);
	}

	static string join(vector<string> words, string delimiter)
	{
		string str = "";
		for (string word : words)
		{
			str = str + word + delimiter;
		}
		return str.substr(0, str.length() - delimiter.length());
	}

	void clear()
	{
		_value = "";
	}

	static int length(string str)
	{
		int length = 0;
		for (int i = 0; i < str.length(); i++)
		{
			length++;
		}
		return length;
	}

	int length()
	{
		return length(_value);
	}

	static string rightTrim(string str)
	{
		for (size_t i = str.length() - 1; i >= 0; i--)
		{
			if (str[i] != ' ')
			{
				return str.substr(0, i + 1);
			}
		}
	}

	string rightTrim()
	{
		return rightTrim(_value);
	}

	static string leftTrim(string str)
	{
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] != ' ')
			{
				return str.substr(i, str.length() - 1);
			}
		}
	}

	string leftTrim()
	{
		return leftTrim(_value);
	}

	static string trim(string str)
	{
		return leftTrim(rightTrim(str));
	}

	string trim()
	{
		return leftTrim(rightTrim(_value));
	}

	static void printFirstLetterInEachWord(string str)
	{
		bool isFirstLetter = true;
		for (int i = 0; i < str.length(); i++)
		{
			if (isFirstLetter && str[i] != ' ')
			{
				cout << str[i] << endl;
			}
			isFirstLetter = str[i] == ' ' ? true : false;
		}
	}

	void printFirstLetterInEachWord()
	{
		printFirstLetterInEachWord(_value);
	}

	static string upperFirstLetterInEachWord(string str)
	{
		bool isFirstLetter = true;
		for (int i = 0; i < str.length(); i++)
		{
			if (isFirstLetter && str[i] != ' ')
			{
				str[i] = toupper(str[i]);
			}
			isFirstLetter = str[i] == ' ' ? true : false;
		}
		return str;
	}

	string upperFirstLetterInEachWord()
	{
		return upperFirstLetterInEachWord(_value);
	}

	static string lowerFirstLetterInEachWord(string str)
	{
		bool isFirstLetter = true;
		for (int i = 0; i < str.length(); i++)
		{
			if (isFirstLetter && str[i] != ' ')
			{
				str[i] = tolower(str[i]);
			}
			isFirstLetter = str[i] == ' ' ? true : false;
		}
		return str;
	}

	string lowerFirstLetterInEachWord()
	{
		return lowerFirstLetterInEachWord(_value);
	}

	static string upperAllLetters(string str)
	{
		for (int i = 0; i < str.length(); i++)
		{
			if (islower(str[i]))
			{
				str[i] = toupper(str[i]);
			}
		}
		return str;
	}

	string upperAllLetters()
	{
		return upperAllLetters(_value);
	}

	static string lowerAllLetters(string str)
	{
		for (int i = 0; i < str.length(); i++)
		{
			if (isupper(str[i]))
			{
				str[i] = tolower(str[i]);
			}
		}
		return str;
	}

	string lowerAllLetters()
	{
		return lowerAllLetters(_value);
	}

	static char invertLetter(char letter)
	{
		return isupper(letter) ? tolower(letter) : toupper(letter);
	}

	static string invertAllLetters(string str)
	{
		for (int i = 0; i < str.length(); i++)
		{
			str[i] = invertLetter(str[i]);
		}
		return str;
	}

	string invertAllLetters()
	{
		return invertAllLetters(_value);
	}

	static int countCapitalLetters(string str)
	{
		int count = 0;
		for (int i = 0; i < str.length(); i++)
		{
			if (isupper(str[i]))
			{
				count++;
			}
		}
		return count;
	}

	int countCapitalLetters()
	{
		return countCapitalLetters(_value);
	}

	static int countSmallLetters(string str)
	{
		int count = 0;
		for (int i = 0; i < str.length(); i++)
		{
			if (islower(str[i]))
			{
				count++;
			}
		}
		return count;
	}

	int countSmallLetters()
	{
		return countSmallLetters(_value);
	}

	static int countLetter(char letter, string str)
	{
		int count = 0;
		for (int i = 0; i < str.length(); i++)
		{
			if (letter == str[i])
			{
				count++;
			}
		}
		return count;
	}

	int countLetter(char letter)
	{
		return countLetter(letter, _value);
	}

	static int countLetter(string str, char letter, bool ignoreCase = false)
	{
		int count = 0;
		for (int i = 0; i < str.length(); i++)
		{
			if (ignoreCase)
			{
				if (tolower(letter) == tolower(str[i]))
				{
					count++;
				}
			}
			else
			{
				if (letter == str[i])
				{
					count++;
				}
			}
		}
		return count;
	}

	int countLetter(char letter, bool ignoreCase = false)
	{
		return countLetter(_value, letter, ignoreCase);
	}

	static bool isVowel(char letter)
	{
		letter = tolower(letter);
		return letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u';
	}

	static int countVowelLetters(string str)
	{
		int count = 0;
		for (int i = 0; i < str.length(); i++)
		{
			if (isVowel(str[i]))
			{
				count++;
			}
		}
		return count;
	}

	int countVowelLetters()
	{
		return countVowelLetters(_value);
	}

	static int countWords(string str, string delimiter)
	{
		int count = 0;
		string word;
		size_t pos;
		while ((pos = str.find(" ")) != std::string::npos)
		{
			word = str.substr(0, pos);

			if (word != "")
			{
				count++;
			}

			str.erase(0, pos + delimiter.length());
		}
		if (str != "")
		{
			count++;
		}
		return count;
	}

	int countWords(string delimiter)
	{
		return countWords(_value, delimiter);
	}

	static string reverseWords(string str)
	{
		vector<string> vWords = split(str, " ");

		str = "";

		vector<string>::iterator iter = vWords.end();

		while (iter != vWords.begin())
		{
			--iter;
			str += *iter + " ";
		}

		return str.substr(0, str.length() - 1);
	}

	string reverseWords()
	{
		return reverseWords(_value);
	}

	static string replace(string str, string wordToReplace, string wordReplaceTo, bool ignoreCase = false)
	{
		vector <string> vWords = split(str, " ");

		for (string& word : vWords)
		{
			if (ignoreCase)
			{
				if (lowerAllLetters(word) == lowerAllLetters(wordToReplace))
				{
					word = wordReplaceTo;
				}
			}
			else
			{
				if (word == wordToReplace)
				{
					word = wordReplaceTo;
				}
			}
		}

		return join(vWords, " ");
	}

	string replace(string wordToReplace, string wordReplaceTo, bool ignoreCase = false)
	{
		return replace(_value, wordToReplace, wordReplaceTo, ignoreCase);
	};

	static string smartReplace(string str, string wordToReplace, string wordReplaceTo)
	{
		size_t pos;
		while ((pos = str.find(wordToReplace)) != std::string::npos)
		{
			str = str.replace(pos, wordToReplace.length(), wordReplaceTo);
			pos = str.find(wordToReplace);
		}
		return str;
	}

	string smartReplace(string wordToReplace, string wordReplaceTo)
	{
		return smartReplace(_value, wordToReplace, wordReplaceTo);
	}
};