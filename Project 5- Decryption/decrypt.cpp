
//compiler instructions 
#pragma warning(disable:6262)
#define _CRT_SECURE_NO_DEPRECATE 

//headers for importing libraries 
#include <cstring>
#include <iostream>
#include <cctype>
#include <cassert>
using namespace std;



//check if crib has no words
bool checkCribNoWords(const char crib[])
{
	int cribLength = 0; 

	//count how many letters are in crib 
	for (int i = 0; i < strlen(crib); i++)
	{
		if (isalpha(crib[i]))
		{
			cribLength++;
		}
	}

	//if crib is empty return true 
	if (cribLength == 0)    
	{
		return true;
	}

	return false;
}



//check if crib contains an end line character
bool checkCribEndLine(const char crib[])
{
	for (int i = 0; i < strlen(crib); i++)
	{
		if (crib[i] == '\n')
		{
			return true; 
		}
	}

	return false; 
}



//turns non letters into spaces + upper case to lower case 
//also strip spaces at begining and end 
//only one space between each word
const char* returnRefinedCString(const char oldString[])
{
	char newString1[10000] = "";
	char newString2[10000] = " ";
	const int HIGHEST_POS = 10000;
	int posOfFirstLetter = HIGHEST_POS;


	for (int i = 0; i < strlen(oldString); i++)
	{

		newString1[i] = oldString[i];

		if (isupper(oldString[i]))  //change upper case to lower case
		{
			newString1[i] = tolower(oldString[i]);
		}

		if (isalpha(oldString[i]) == false && oldString[i] != '\n')  //replace all non letters excpet for new line with a space character
		{
			newString1[i] = ' ';
		}

		if (newString1[i] == '\n')
		{
			// cerr << "end line at " << i << endl; 
		}

		// cerr << " STRING1: " << newString1[i] << endl;
	}

	bool addCharacter = true;
	bool noMoreLetters = true;
	int counter = 0;

	for (int i = 0; i < strlen(newString1); i++)
	{
		addCharacter = true;

		//identify position of first letter character 
		if (isalpha(newString1[i]) && posOfFirstLetter == HIGHEST_POS)
		{
			posOfFirstLetter = i;
		}

		//if the spaces are in the front, you do not want to add these characters 
		if (newString1[i] == ' ' && i < posOfFirstLetter)
		{
			addCharacter = false;
		}

		//remove extra spaces from in between words
		//if a character is a space, is after the first letter, is not at the end of the c string, and does not have a letter in front of it: 
		if ((newString1[i] == ' ') && (i > posOfFirstLetter) && (i != strlen(newString1) - 1) && !(isalpha(newString1[i + 1])))
		{
			addCharacter = false;
		}

		//remove extra spaces at the end of the c string
		noMoreLetters = true;
		for (int j = i; j < strlen(newString1); j++)
		{
			if (isalpha(newString1[j]))
			{
				noMoreLetters = false;
			}
		}

		//add character to new string if permitted 
		if (addCharacter == true && noMoreLetters == false)
		{
			newString2[counter] = newString1[i];
			counter++;

		}
	}

	const char* newString3 = newString2;

	//cerr << "Old String: " << oldString << endl;
	//cerr << "New String: |||" << newString3 << "|||" << endl;
	return newString3;
}





//checks if crib message is too long
//with all letters and valid spaces it cannot be over 90
bool cribOver90(const char crib[])
{
	int validCharInCrib = 0; 
	bool firstLetterDetected = false; 
	bool lastLetterDetected = false; 
	int lastPos = strlen(crib) - 1; 

	//cerr <<  "check 90 valid: |||"; 

	//count how many valid characters are in crib
	for (int i = 0; i < strlen(crib); i++)
	{
		if (isalpha(crib[i]))
		{
			lastLetterDetected = true; 

			//check if this is the first letter
			if (validCharInCrib == 0)
			{
				firstLetterDetected = true; 
			}

			//check if this is the last letter 
			if (i != lastPos)
			{
				for (int j = i + 1; j < strlen(crib); j++)
				{
					if (isalpha(crib[j]))
					{
						lastLetterDetected = false; 
					} 
				}
			}


			//icremement 
			//cerr << crib[i]; 
			validCharInCrib++;
		}
		else
		{
			//if the following is true, we know a non letter char is not at the begginging or end of letters
			if (firstLetterDetected && lastLetterDetected == false)
			{
				if (isalpha(crib[i - 1]))
				{
					//cerr << crib[i]; 
					validCharInCrib++; 
				}
			}
		}
	}

	//cerr << "|||" << endl << "Length of Valid: " << validCharInCrib << endl;

	//if there are more than 90 letter characters in crib -> return true 
	if (validCharInCrib > 90)
	{
		return true; 
	}

	return false;
}

bool cribLongerThanCipher(const char cipherText[], const char crib[])
{
	if (strlen(crib) > strlen(cipherText))
	{
		return true; 
	}

	return false; 
}


//check if the pattern of letter and space characters is the same between the cipher and the crib 
bool patternDetected(const char ciphertext[], const char crib[], int cipherPos)
{
	
	for (int i = 0; i < strlen(crib); i++)
	{
		//cerr << "( " << (char)ciphertext[cipherPos + i] << " , " << (char)crib[i] << " )  ";
		if (!isalpha(crib[i]) && isalpha(ciphertext[cipherPos + i]))
		{

			return false;
		}

		//if one is a letter and the other is not 
		if (isalpha(crib[i]) && !isalpha(ciphertext[cipherPos + i]))
		{
			//cerr << "not both letters" << endl;
			return false;
		}

		//if the potential crib match contains an endline 
		if (ciphertext[cipherPos + i] == '\n')
		{
			//cerr << "endl in the middle" << endl;
			return false;
		}
	}
	
	//cerr << endl; 
	//cerr << endl;
	return true; 
}


//check that the potential match to crib is not in the middle of the cipher text 
bool middleOfText(const char ciphertext[], const char crib[], int cipherPos)
{
	bool middleOfText = false; 

	//if the potential match is not at the begginging of the cipher text 
	//and there is a letter before the potential match 
	if (cipherPos > 0 && isalpha(ciphertext[cipherPos - 1]))
	{
		middleOfText = true; 
	}

	int lastPosOfText = strlen(ciphertext) - 1; 
	int lastPosOfPotentialMatch = cipherPos + strlen(crib) - 1; 

	//cerr << "last pos of cipher: " << lastPosOfText << " last pos of potential match: " << lastPosOfPotentialMatch << endl; 

	//if the potential match does not end the cipher text 
	//and there is a letter after potential match ends 
	if (lastPosOfText != lastPosOfPotentialMatch && isalpha(ciphertext[lastPosOfPotentialMatch + 1]))
	{
		middleOfText = true;
	}

	return middleOfText; 
}




//check if the crib and the potential match to the crib in the cipher text are one to one letter patterns 
bool oneToOne(const char ciphertext[], const char crib[], int cipherPos)
{
	//match string is the part of the string that we think matches the crib
	//check if the letter pattern matches the crib 
	bool isOneToOne = true;

	//cycle through the crin
	for (int i = 0; i < strlen(crib); i++)
	{
		for (int j = 0; j < strlen(crib); j++)
		{
			if (i != j && crib[i] == crib[j]) //if any two things in the crib match: 
			{
				//make sure that the corresponding things in the cipertext match as well 
				if (ciphertext[cipherPos + i] != ciphertext[cipherPos + j])
				{
					//cerr << "They do not match" << endl;
					return false;
				}
			}
		}
	}

	//check that the letters in the potential match 
	//are differnt from each other in the same way they are different form each other in the crib
	for (int i = 0; i < strlen(crib); i++)
	{
		for (int j = 0; j < strlen(crib); j++)
		{
			if (i != j && crib[i] != crib[j]) //if any two things in the crib match: 
			{
				if (ciphertext[cipherPos + i] == ciphertext[cipherPos + j])
				{
					//cerr << "They do not match" << endl;
					return false;
				}
			}
		}
	}
	

	//cerr << "They are the same." << endl;
	return true;
}




//check if crib exists in the ciphertext
//return string with corresponding characters in the cipher 
bool findCribInText(const char ciphertext[], const char crib[], int position)
{
	//cerr << "Position we are looking at: " << position << " character: ||" << ciphertext[position] << "||" << endl;

	if (patternDetected(ciphertext, crib, position))
	{
		//cerr << "Pattern is detected." << endl;

		if (middleOfText(ciphertext, crib, position) == false)
		{
			//cerr << "It is not in the middle of the text. " << endl;

			if (oneToOne(ciphertext, crib, position))
			{
				//cerr << "Match detected. " << endl; 
				return true;
			}
		}
	}

	return false; 
}




//output the translated restult 
void newOutput(const char ciphertext[], const char newCiphertext[], const char crib[], int firstPosOfMatch)
{
	bool letterOutputted = false; 
	int posInCrib = 0; 
	
	//create array that holds the key 
	char cribKey[100] = "";
	char matchKey[100] = "";
	char tempChar = ' ';

	for (int i = 0; i < strlen(crib); i++)
	{
		cribKey[i] = crib[i];
	}

	for (int i = 0; i < strlen(crib); i++)
	{
		matchKey[i] = newCiphertext[firstPosOfMatch + i];
	}

	//print the key
	for (int i = 0; i < strlen(crib); i++)
	{
		//cerr << cribKey[i] << " -> " << matchKey[i] << endl;
	}


	//cycling through the original c string 
	for (int posInCipher = 0; posInCipher < strlen(ciphertext); posInCipher++)
	{

		//if the character is a letter proceed 
		if (isalpha(ciphertext[posInCipher]))
		{
			letterOutputted = false;
			for (int i = 0; i < strlen(crib); i++)
			{
				tempChar = tolower(ciphertext[posInCipher]);
				//cout << posInCipher << ": cipher- " << tempChar << " match- " << matchKey[i] << endl; 
				if (letterOutputted == false && tempChar == matchKey[i])
				{
					cout << (char)toupper(cribKey[i]);
					letterOutputted = true; 
				}
			}
			

			//if there is no corresponding letter, print the letter in lower case 
			if (letterOutputted == false)
			{
				cout << (char)tolower(ciphertext[posInCipher]); 
			}
		}
		else //if not a letter just display it 
		{
			cout << ciphertext[posInCipher]; 
		}
	}
	cout << endl; 
}



//main function calling all others: 
bool decrypt(const char ciphertext[], const char crib[])
{

	//if there is no matching crib: return false and don't print anything 
	//if the crib is empty OR too long 
	if (checkCribNoWords(crib))
	{
		//cerr << "FALSE: Crib has no words." << endl; 
		return false;
	}


	//return false if crib contains a new line characters
	if (checkCribEndLine(crib))
	{
		//cerr << "False: Crib has a new line in it. " << endl;
		return false;
	}


	//check if crib is over 90 characters in the new forom 
	// this is longer than any ciphertext message we will look at 
	//return false if crib is too long 
	if (cribOver90(crib))
	{
		//cerr << "FALSE: Crib has over 90 characters. " << endl;
		return false;
	}


	//remove extra spaces and non letter characters from crib 
	char newCrib[10000] = "";
	//cerr << "Crib change:" << endl; 
	strcpy(newCrib, returnRefinedCString(crib)); 
	
	
	//clean up the ciphertext: 
	//turn all upper case to lower case
	//remove all extra spaces
	//turn non letters into spaces
	//cerr << "Cipher text change:" << endl; 
	char newCipherText[10000] = " ";
	strcpy(newCipherText, returnRefinedCString(ciphertext));

	//check if crib is longer than cipher text
	if (cribLongerThanCipher(newCipherText, newCrib))
	{
		//cerr << "FALSE- crib is too long" << endl; 
		return false; 
	}


	//check if there is a match to crib in the ciphertext 
	bool matchFound = false; 
	for (int posInCipher = 0; posInCipher <= strlen(newCipherText) - strlen(newCrib); posInCipher++)  //cycle through cipher 
	{
		if (findCribInText(newCipherText, newCrib, posInCipher)) //if the match is found continue 
		{
			
			//cerr << endl << "Match found at pos: " << posInCipher << endl; 
			//cerr << "Match: "; 
			//display the match found for testing 
			for (int k = posInCipher; k < posInCipher + strlen(crib); k++)
			{
				//cerr << newCipherText[k]; 
			}
			//cerr << endl; 
			//cerr << "first position of match: " << posInCipher << endl; 
			//display translated version 
			newOutput(ciphertext, newCipherText, newCrib, posInCipher); 

			return true;
			
		}
	}

	//cerr << "FALSE: no match found. Peace out." << endl; 
	return false; 
}










int main()
{

	//cerr << endl << "Test Case 1: empty crib" << endl; 
	const char text1[10] = "asjdfk"; 
	const char crib1[10] = "";
	decrypt(text1, crib1);

	//cerr << endl << "Test Case 2: crib with no words, has new line and non letters" << endl;
	const char text2[10] = "asdf"; 
	const char crib2[100] = "   **89 \n 90";
	decrypt(text2, crib2); 

	//cerr << endl << "Test Case 3: crib is over 90 letters long" << endl;
	const char text3[100] = "asdf";
	const char crib3[101] = "aaaaaaaaataaaaaaaaataaaaaaaaataaaaaaaaataaaaaaaaataaaaaaaaataaaaaaaaataaaaaaaaataaaaaaaaataaaaaaaaat"; 
	decrypt(text3, crib3);
	
	//cerr << endl << "Test Case 4: crib is over 90 characters long, but less than 90 letters long" << endl;
	const char text4[10] = "aaa";
	const char crib4[200] = "     her00e ya go 012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"; 
	decrypt(text4, crib4); 

	//cerr << endl << "Test Case 5: crib contains a new line" << endl; 
	const char text5[10] = "hello";
	const char crib5[100] = "h \n h"; 
	decrypt(text5, crib5);

	//cerr << endl << "Test Case 6: crib and cipher text need to refined " << endl; 
	const char text6[100] = " Hello there 9999 \n MEOW w)9090o&^w!!   ";
	const char crib6[20] = "W9Wo)  ";
	decrypt(text6, crib6); 

	//cerr << endl << "Test Case 7: new line in cipher text" << endl; 
	const char text7[100] = "Hi \n sup"; 
	const char crib7[10] = "asd";
	decrypt(text7, crib7); 

	//cerr << endl << "Test Case 8: the crib does match something" << endl;
	const char text8[100] = "bhat is up everyXne. belcome. \n bXb";
	const char crib8[10] = "wow";
	decrypt(text8, crib8);

	//cerr << endl << "Test Case 9: multiple endlines" << endl;
	const char text10[100] = "xy naxe dad's naxe is steven. \nXg Xcx's name is xcx. \n ";
	const char crib10[100] = "My mom's";
	decrypt(text10, crib10);

	//cerr << endl << "Test Case 10: multiple endlines" << endl; 
	const char text9[100] = "xy naxe dad's naxe is steven. \nXg Xcx's name is xcx. \n Xarrg is cool.";
	const char crib9[100] = "My mom's"; 
	decrypt(text9, crib9); 

	//cerr << endl << "test Case 11: a lot of stuff" << endl; 
	const char text11[300] = "I was driving dywn tywn with the girl\n I knyw and I was like aaaaa aaa. \n The change in my\n pycket, it wasn't enyugh. \nI'm like xyrget yyu and xyrget her tyy. \n If I was richer, I'd still be with yyu,\n"; 
	const char crib11[100] = "forget you"; 
	decrypt(text11, crib11); 

	//cerr << endl << "Test Case 12: crib is spaces" << endl;
	const char text12[100] = "xy naxe dad's naxe is steven. \nXg Xcx's name is xcx. \n Xarrg is cool.";
	const char crib12[100] = "   "; 
	decrypt(text12, crib12);

	//cerr << endl << "Test Case 13: crib is only numbers" << endl;
	const char text13[100] = "xy naxe dad's naxe is steven. \nXg Xcx's name is xcx. \n Xarrg is cool.";
	const char crib13[100] = "123";
	decrypt(text13, crib13);

	//cerr << endl << "Test Case 14: there is an endl at the beginning and end of the messages" << endl; 
	const char text14[100] = "\nHxllj thxrx\nwxlcjmx to my trxx hjusx\nyju arx njw in a trxx hjusx\ngood byx\n.";
	const char crib14[100] = "tree house";
	decrypt(text14, crib14);

	//cerr << endl << "Test Case 15: section in cipher text matches crib in amount of letters and spaces but not one to one" << endl;
	const char text15[100] = "hey there"; 
	const char crib15[100] = "wwo ddjkl";
	decrypt(text15, crib15); 

	

}