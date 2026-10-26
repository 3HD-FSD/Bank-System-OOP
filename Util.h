#pragma once

#include <iostream>
#include <string>

using namespace std;

class Util
{
public:
	static void Srand()
	{
		srand((unsigned)time(NULL));
	}

	static int randomInteger(int from, int to)
	{
		return rand() % (to - from + 1) + from;
	}

	enum enCharType { SmallLetter = 1, CapitalLetter = 2, SpecialCharacter = 3, Digit = 4, MixChars = 5 };

	static char randomChar(enCharType charType)
	{
		if (charType == enCharType::MixChars)
		{
			charType = (enCharType)randomInteger(1, 3);
		}
		switch (charType)
		{
		case enCharType::SmallLetter:
			return (char)randomInteger(97, 122);
			break;

		case enCharType::CapitalLetter:

			return (char)randomInteger(65, 90);
			break;

		case enCharType::SpecialCharacter:
			return (char)randomInteger(33, 47);
			break;

		case enCharType::Digit:
			return (char)randomInteger(48, 57);
			break;
		default:
			return (char)randomInteger(65, 90);
			break;
		}
	}

	static string generateWord(enCharType charType, int length)
	{
		string word = "";
		for (int i = 1; i <= length; i++)
		{
			word += randomChar(charType);
		}
		return word;
	}

	static string generateKey(enCharType charType = CapitalLetter, string delimiter = "-", int charactersNumber = 4, int piecesNumber = 4)
	{
		string key = "";
		for (int i = 1; i <= piecesNumber; i++)
		{
			key += generateWord(charType, charactersNumber) + delimiter;
		}
		return key.substr(0, key.length() - delimiter.length());
	}

	static string generateKeys(int keysNumber, enCharType charType = CapitalLetter, string delimiter = "-", int charactersNumber = 4, int piecesNumber = 4)
	{
		string keys = "";
		for (int i = 1; i <= keysNumber; i++)
		{
			if (i == keysNumber)
			{
				keys += generateKey(charType, delimiter, charactersNumber, piecesNumber);
				break;
			}
			keys += generateKey(charType, delimiter, charactersNumber, piecesNumber) + "\n";
		}
		return keys;
	}

	static void swap(short& number1, short& number2)
	{
		short temp = number1;
		number1 = number2;
		number2 = temp;
	}

	static void swap(int& number1, int& number2)
	{
		int temp = number1;
		number1 = number2;
		number2 = temp;
	}

	static void swap(double& number1, double& number2)
	{
		double temp = number1;
		number1 = number2;
		number2 = temp;
	}

	static void swap(float& number1, float& number2)
	{
		float temp = number1;
		number1 = number2;
		number2 = temp;
	}

	static void swap(string& str1, string& str2)
	{
		string temp = str1;
		str1 = str2;
		str2 = temp;
	}

	static void swap(char& character1, char& character2)
	{
		char temp = character1;
		character1 = character2;
		character2 = temp;
	}

	static void shuffle(int arr[], int n)
	{
		for (int i = 0; i < n; i++)
		{
			swap(arr[randomInteger(1, n - 1)], arr[randomInteger(1, n - 1)]);
		}
	}

	static void shuffle(string arr[], int n)
	{
		for (int i = 0; i < n; i++)
		{
			swap(arr[randomInteger(1, n - 1)], arr[randomInteger(1, n - 1)]);
		}
	}

	static string encrypt(string str, short key)
	{
		for (int i = 0; i < str.length(); i++)
		{
			str[i] = char((int)str[i] + key);
		}
		return str;
	}

	static string decrypt(string str, short key)
	{
		for (int i = 0; i < str.length(); i++)
		{
			str[i] = char((int)str[i] - key);
		}
		return str;
	}

	enum enAlign
	{
		LEFT,
		CENTER,
		RIGHT
	};

	static string tabs(short numberOfTabs)
	{
		string tabs = "";
		for (int i = 1; i <= numberOfTabs; i++)
		{
			tabs += "\t";
		}
		return tabs;
	}

	static string lines(short numberOfLines)
	{
		string lines = "";
		for (int i = 1; i <= numberOfLines; i++)
		{
			lines += "\t";
		}
		return lines;
	}

	static string characters(char character, short numberOfCharacters)
	{
		string characters = "";
		for (int i = 1; i <= numberOfCharacters; i++)
		{
			characters += character;
		}
		return characters;
	}

	static string formatString(short width, string str, enAlign align = LEFT, char fillChar = ' ')
	{
		if (str.length() >= width)
		{
			return str;
		}
		short space = width - str.length();
		string result;
		switch (align)
		{
		case LEFT:
			result = str + string(space, fillChar);
			break;
		case RIGHT:
			result = string(space, fillChar) + str;
			break;
		case CENTER:
		{
			short left = space / 2;
			short right = space - left;
			result = string(left, fillChar) + str + string(right, fillChar);
			break;
		}
		}
		return result;
	}

	static void printHeader(short width, string header, enAlign align = CENTER)
	{
		cout << Util::tabs(5) << characters('-', width) << endl;
		cout << Util::tabs(5) << "|" << formatString(width - 2, header, align) << "|" << endl;
		cout << Util::tabs(5) << characters('-', width) << endl;
	}

	static void printFooter(short width, string footer, enAlign align = CENTER)
	{
		cout << Util::tabs(5) << characters('-', width) << endl;
		cout << Util::tabs(5) << "|" << formatString(width - 2, footer, align) << "|" << endl;
		cout << Util::tabs(5) << characters('-', width) << endl;
	}

	static void insertionSort(int arr[], int n)
	{
		for (int i = 1; i < n; i++)
		{
			int key = arr[i];
			int j = i - 1;
			while (j >= 0 && arr[j] > key)
			{
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = key;
		}
	}

	static void bubbleSort(int arr[], int n)
	{
		bool swapped;
		for (int i = 0; i < n - 1; i++)
		{
			swapped = false;
			for (int j = 0; j < n - i - 1; j++)
			{
				if (arr[j] > arr[j + 1])
				{
					int temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
					swapped = true;
				}
			}
			if (!swapped)
			{
				break;
			}
		}
	}

	static void selectionSort(int arr[], int n)
	{
		int min;
		for (int i = 0; i < n - 1; i++)
		{
			min = i;
			for (int j = i + 1; j < n; j++)
			{
				if (arr[j] < arr[min])
				{
					min = j;
				}
			}
			if (min != i)
			{
				int temp = arr[i];
				arr[i] = arr[min];
				arr[min] = temp;
			}
		}
	}

	//static void mergeSort(int arr[], int n)
	//{

	//}

	//static void quickSort(int arr[], int n)
	//{

	//}

	static int binarySearch(int arr[], int n, int value)
	{
		int start = 0;
		int end = n - 1;
		while (start <= end)
		{
			int middle = start + (end - start) / 2;
			if (value == arr[middle])
			{
				return middle;
			}
			else if (value < arr[middle])
			{
				end = middle - 1;
			}
			else
			{
				start = middle + 1;
			}
		}
		return -1;
	}

	static int linearSearch(int arr[], int n, int value)
	{
		for (int i = 0; i < n; i++)
		{
			if (value == arr[i])
			{
				return i;
			}
		}
		return -1;
	}
};

