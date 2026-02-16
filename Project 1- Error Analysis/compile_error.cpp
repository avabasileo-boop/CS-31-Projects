// Code for compile_error.cpp
	// syntax errror line 24 -- removed semicolon
	// syntax error line 30 -- removed insertion operator
   //MISSING SEMI COLON 
    

#include <iostream>
using namespace std;

int main()
{
	int numberSurveyed;
	int likeInPerson;
	int likeAtHome;

	cout << "How many students were surveyed? ";
	cin >> numberSurveyed;
	cout << "How many of them prefer being at school in person? ";
	cin >> likeInPerson;
	cout << "How many of them would rather do school from home? ";
	cin >> likeAtHome;

	double pctLikeInPerson = 100.0 * likeInPerson / numberSurveyed;
	double pctLikeAtHome = 100.0 * likeAtHome / numberSurveyed            //I took away a semi colon

	cout.setf(ios::fixed);
	cout.precision(1);

	cout << endl;
	cout  pctLikeInPerson << "% prefer being at school in person." << endl; //I removed insertion operator
	cout << pctLikeAtHome << "% prefer doing school from home." << endl;

	if (likeInPerson > likeAtHome)
		cout << "More students like being at school in person than doing school at home." << endl;
	else
		cout << "More students like doing school from home than being at school in person." << endl;
}