
//osition that would require looking at the contents of an element past the last element we're interested in
// or less than 0 

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;


//print array//
void printArray(string a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cerr << a[i] << endl; 
	}
}

//duplicates each string in an array//
int reduplicate(string a[], int n)
{
	
	//check if array size is negative
	if (n < 0)
	{
		return -1;
	}
	 

	//print first array
	cerr << "First array:" << endl;
	for (int i = 0; i < n; i++)
	{
		cerr << a[i] << "|";
	}

	cerr << endl << "Second array: " << endl;
	for (int i = 0; i < n; i++)
	{
		a[i] += a[i];        //duplicate string in each element of the array
		cerr << a[i] << "|"; //print second version of array 
	}

	cerr << endl << "n value: " << n << endl;  //print n value 
	return n;                                  //return array length value 
}




//return position of first stirng that matches the target input//
int locate(const string a[], int n, string target)
{
	// check for negative array length 
	if (n < 0)
	{
		return -1; 
	}

	//loop through array 
	for (int i = 0; i < n; i++)
	{
		//if the element of the array equals the target return the position
		if (a[i] == target) 
		{
			return i; 
		}
	}

	//return -1 if the program makes it here
	return -1; 
}


//return smallest pos num of string that is >= to every other string in an array//
int locationOfMax(const string a[], int n)
{
	//check if n is negative 
	if (n < 0)
	{
		return -1; 
	}


	int counter = 0; 
	for (int i = 0; i < n; i++)  //loop through array
	{
		counter = 0;  //reset counter 
		for (int j = 0; j < n; j++)  //loop through array again
		{
			if (a[i] >= a[j]) //when string at i is >= to string at j
			{
				cerr << a[i] << " is >= to " << a[j] << endl;
				counter++; 
			}
		}

		cerr << "Counter is " << counter << " of " << n << endl << endl;

		//if the string was >= to all other strings (n number of times) return position
		if (counter == n)
		{
			return i; 
			
		}
	}
	return -1;
}



int circleLeft(string a[], int n, int pos)
{

	//check if n is negative, or if pos is outside the range of the array 
	if (n < 0 || pos < 0 || pos >= n)
	{
		return -1; 
	}


	printArray(a, n); 
	
	//hold the value that will move to the end of the array
	string tempStringHolder = a[pos];

	//loop through strings between pos and end of array
	for (int i = pos; i < n - 1; i++)
	{
		a[i] = a[i + 1];  //move strings back one 
	}
	
	//add string at position pos to end of the array 
	a[n-1] = tempStringHolder;

	cerr << endl; 
	printArray(a, n);
	return pos; 
}


//return number of sequences of one or more consecutive identical items in a//
int enumerateRuns(const string a[], int n)
{
	//check if n is negative
	if (n < 0)
	{
		return -1;
	}

	int counter = 0; 
	
	//cycle through string
	for (int i = 0; i < n; i++)
	{
		//if the next sting is different than the one we are looking at
		//or if we are at the end of the array
		if (i == (n - 1) || a[i] != a[i + 1])
		{
			counter++;  //add to counter
		}
	}

	cerr << "counter: " << counter << endl; 
	return counter;
}




//reverse order of elements int the array//
int flip(string a[], int n)
{
	//check if n is negative 
	if (n < 0)
	{
		return -1;
	}

	//testing
	cerr << "a Array: " << endl;
	printArray(a, n);
	cerr << "--------" << endl;

	//switch each value with the value that is at the other end of the array
	//and is an equal distance from the midpoint
	string stringHolder = " ";
	for (int i = 0; i < n / 2; i++)
	{
		stringHolder = a[i];             //assign first string to a StringHolder
		a[i] = a[n - 1 - i];             //then switch with string at opposite end of the array
		a[n - 1 - i] = stringHolder;     //then assign the stringHolder 
		                                 //to the string at end of the array
	}

	//testing 
	cerr << "a Array: " << endl;
	printArray(a, n);

	return n;
}



//return the position of the first corresponding elements of a1 and a2 that are not equal//
int locateDifference(const string a1[], int n1, const string a2[], int n2)
{
	
	//check that n1 and n2 are not negative 
	if (n1 < 0 || n2 < 0)
	{
		return -1; 
	}

	//cycle through the first array
	for (int i = 0; i < n1; i++)
	{
		//check that we are not leaving the bounds of the second array
		if (i < n2)
		{
			//are the values in the same position of each string different
			if (a1[i] != a2[i])
			{
				//return the position where the corresponding elements 
				//are not equal 
				return i; 
			}
		}
	}

	//if all elements are equal:
	//return which ever value is smaller-n1 or n2
	if (n1 <= n2)
	{
		return n1;
	}
	else
	{
		return n2;
	}
}


//test when all n2 elements of a2 appear in a1, return pos in a1 where it starts//
int subsequence(const string a1[], int n1, const string a2[], int n2)
{
	//check if n1 or n2 is negative
	if (n1 < 0 || n2 < 0)
	{
		return -1; 
	}

	//check if the subsequence has 0 elements
	if (n2 == 0)
	{
		return 0; 
	}

	int hasSubsequence = 0; 
	for (int i = 0; i < n1; i++) //loop through first array
	{
		if (a1[i] == a2[0] && n1 - i  >= n2) //if the first element of the second array matches an element in 
											    //in the first array and there is and n2 amount of elements left in the first array proceed
		{
			for (int j = 0; j < n2; j++) //loop through second array
			{

				if (a2[j] == a1[i + j]) //check if the elements match 
				{
					hasSubsequence++; //each time the elements match add to the counter
				}
			}

			if (hasSubsequence == n2) //if there are n2 number of matching elements, 
									   //return the pos of the first matching element in the first array 
			{
				return i; 
			}
		}
	}

	//return -1 if the a2 elements do not appear (in the same order) in the a1 array
	return -1;  
}



//locate when any string from a2 appears in a1//
int locateAny(const string a1[], int n1, const string a2[], int n2)
{
	//check if n1 or n2 is negative
	if (n1 < 0 || n2 < 0)
	{
		return -1;
	}


	for (int i = 0; i < n1; i++) //cycle through a1 array
	{
		for (int j = 0; j < n2; j++) //cycle through a2 array
		{
			if (a1[i] == a2[j]) //check if the elements are the same 
			{
				return i;  //return position of the element from a1 array 
			}
		}
	}

	//if there are no elements from a2 in a1:
	return -1; 
}


int separate(string a[], int n, string separator)
{
	//check if n is negative
	if (n < 0)
	{
		return -1; 
	}

	printArray(a, n); 
	cerr << endl; 

	//alphabetize array
	string temp; 
	for (int i = 0; i < n; i++) //cycle through array
	{
		for (int j = i; j < n; j++) //compare each element to the rest of the array
		{
			if (a[j] < a[i])
			{
				//switch elements
				temp = a[j]; 
				a[j] = a[i]; 
				a[i] = temp; 
			}
		}
	}

	printArray(a, n); 
	cerr << endl;

	//find first elements greater than or equal to separator 
	for (int i = 0; i < n; i++)
	{
		if (a[i] >= separator)
		{
			return i; 
		}
	}

	return n; 

}

int main()
{
	string h[7] = { "moana", "mulan", "ariel", "tiana", "", "belle", "elsa" };
	assert(locate(h, 7, "belle") == 5);
	assert(locate(h, 7, "ariel") == 2);
	assert(locate(h, 2, "ariel") == -1);
	assert(locationOfMax(h, 7) == 3);

	string g[4] = { "moana", "mulan", "belle", "raya" };
	assert(locateDifference(h, 4, g, 4) == 2);
	assert(circleLeft(g, 4, 1) == 1 && g[1] == "belle" && g[3] == "mulan");

	string c[4] = { "ma", "can", "tu", "do" };
	assert(reduplicate(c, 4) == 4 && c[0] == "mama" && c[3] == "dodo");

	string e[4] = { "ariel", "tiana", "", "belle" };
	assert(subsequence(h, 7, e, 4) == 2);

	string d[5] = { "mulan", "mulan", "mulan", "belle", "belle" };
	assert(enumerateRuns(d, 5) == 2);

	string f[3] = { "tiana", "ariel", "raya" };
	assert(locateAny(h, 7, f, 3) == 2);
	assert(flip(f, 3) == 3 && f[0] == "raya" && f[2] == "tiana");

	assert(separate(h, 7, "elsa") == 3);

	cout << "All tests succeeded" << endl;
}

/*
int main()
{

	string cast[6] = { "elsa", "ariel", "mulan", "belle", "tiana", "moana" };
	int x = separate(cast, 6, "merida");  //  returns 3

	cerr << x << endl;
		// cast must now be
		//      "belle"  "elsa"  "ariel"  "moana"  "tiana"  "mulan"
		// or   "elsa"  "ariel"  "belle"  "mulan"  "moana"  "tiana"
		// or one of several other orderings.
		// All elements < "merida" (i.e., "elsa", "ariel", and "belle")
		//   come before all others
		// All elements > "merida" (i.e., "tiana", "moana", and "mulan")
		//   come after all others
	string cast2[4] = { "mulan", "tiana", "ariel", "raya" };
	int y = separate(cast2, 4, "");  //  returns 2
	cerr << y << endl; 
		// cast2 must now be either
		//      "mulan"  "ariel"  "raya"  "tiana"
		// or   "ariel"  "mulan"  "raya"  "tiana"
		// All elements < "raya" (i.e., "ariel" and "mulan") come
			// before all others.
		// All elements > "raya" (i.e., "tiana") come after all others.

     /* 
	string names[10] = { "moana", "mulan", "raya", "tiana", "merida" };
	string set1[10] = { "elsa", "merida", "tiana", "mulan" };
	int v = locateAny(names, 6, set1, 4);  // returns 1 (a1 has "mulan" there)
	cerr << "1: " << v << endl;
	string set2[10] = { "belle", "ariel" };
	int w = locateAny(names, 6, set2, 2);  // returns -1 (a1 has none)
	cerr << "-1: " << w << endl;
	int hey = locateAny(names, -6, set1, 4);
	cerr << "-1: " << hey << endl;
	int hey1 = locateAny(names, 6, set1, -4);
	cerr << "-1: " << hey1 << endl;

	string steve1[10] = { "bunny", "rabbit", "lop" };
	string steve2[10] = { "hippo", "chicken" };
	cerr << "-1: " << locateAny(steve1, 3, steve2, 2) << endl;

	string ava12[10] = { "a", "b", "a", "b" };
	string ava13[10] = { "a", "b" };
	cerr << "0: " << locateAny(ava12, 4, ava13, 2) << endl;
	cerr << "-1: " << locateAny(ava12, 0, ava13, 2) << endl;
	cerr << "-1: " << locateAny(ava12, 4, ava13, 0) << endl;
	cerr << "-1: " << locateAny(ava12, 0, ava13, 0) << endl;

	string alexa1[10] = { "a", "b", "c", "d" };
	string alexa2[10] = { "c", "d" };
	string alexa3[10] = { "4", "b" };
	cerr << "2: " << locateAny(alexa1, 4, alexa2, 2) << endl;
	cerr << "1: " << locateAny(alexa1, 4, alexa3, 2) << endl;

	



	cerr << "Tests for subsequence: ***********************" << endl; 
	string test1[10] = { "ava", "steve", "tiffany", "alexa", "bighead", "monster baby" };
	string test2[10] = { "bighead", "monster baby", "fancy tail" };
	int a = subsequence(test1, 6, test2, 3);
	cerr << "is it -1: " << a << endl; 
	cerr << "**************************" << endl;


	string test3[10] = { "ava", "steve", "tiffany", "alexa", "bighead", "monster baby" };
	string test4[10] = { "bighead", "monster baby", "fancy tail" };
	int b = subsequence(test3, 6, test4, 0);
	cerr << "is it 0: " << b << endl; 
	cerr << "**************************" << endl;

	string test5[10] = { "ava", "steve", "tiffany", "alexa", "bighead", "monster baby" };
	string test6[10] = { "bighead", "monster baby", "fancy tail" };
	int c = subsequence(test5, 0, test6, 3);
	cerr << "is it -1: " << c << endl; 
	cerr << "**************************" << endl;

	string test7[10] = { "a", "b", "c", "d", "a", "b", "c" };
	string test8[10] = { "a", "b" };
	int d = subsequence(test7, 7, test8, 2);
	cerr << "is it 0: " << d << endl; 
	cerr << "**************************" << endl;

	string test9[10] = { "a", "b", "c", "d", "a", "b", "c" };
	string test10[10] = { "a", "b" };
	int e = subsequence(test9, 7, test10, 2);
	cerr << "is it 0: " << e << endl; 
	cerr << "**************************" << endl;

	string names[10] = { "moana", "mulan", "raya", "tiana", "merida" };
	string names1[10] = { "mulan", "raya", "tiana" };
	int t = subsequence(names, 5, names1, 3);
	cerr << "is it 1: " << t << endl; 
	cerr << "**************************" << endl; 

	string test11[10] = { "ava", "steve", "tiffany", "alexa", "bighead", "monster baby" };
	string test12[10] = { "bighead", "monster baby",};
	int f = subsequence(test11, 6, test12, 2);
	cerr << "is it 4: " << f << endl; 
	cerr << "**************************" << endl;

	string test13[10] = { "a", "b", "c", "d", "a", "x", "y" }; 
	string test14[10] = { "x", "y" }; 
	int g = subsequence(test13, 7, test14, 2);
	cerr << "is it 5: " << g << endl;
	cerr << "**************************" << endl;

	string test15[10] = { "a", "b", "c", "d", "a", "x", "y" };
	string test16[10] = { "x", "y" };
	int j = subsequence(test15, 7, test16, -2);
	cerr << "is it -1: " << j << endl;
	cerr << "**************************" << endl;

	string here[10] = { "a", "g", "d" };
	string here1[10] = { "d" };
	int here2 = subsequence(here, 3, here1, 1);
	cerr << "2: " << here2 << endl;
	cerr << "**************************" << endl;

	*/

//} 

