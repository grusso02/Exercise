#include <iostream>
#include <map>
#include <string>

//A map is an associative array, where a value correspond to a key
//	map<char, int> mp = {   < key, value >
//		{'A', 1},
//		{'B', 2},
//		{'C', 3}
//	};

//This exercise count the occurrences of all letter in a phrase and store their in a map

int main()
{
	std::string str = "Hello world my name is Gabriele! And I love study coding!";
	std::map<char, int> freq;

	for (int i = 0; i < str.length(); i++)
	{
		char letter = str[i];

		if (freq.find(letter) == freq.end())
			freq[letter] = 0;
		freq[letter]++; // equivalent to freq[letter] += 1 or freq[letter] = freq[letter] + 1;
	}

	for (std::map<char, int>::iterator it = freq.begin(); it != freq.end(); it++)
		std::cout << it->first << ": " << it->second << std::endl;
	
}