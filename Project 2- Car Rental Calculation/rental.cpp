
//This project calculates the charge for renting a car 
#include <iostream>
#include <string>
using namespace std; 

int main()
{
	//declare the variables that will hold rental data 
	int odStart; 
	int odEnd; 
	int rentDays; 
	string customerName; 
	string carType; 
	int monthNum; 


	
	//START ODOMETER READING// 
	cout << "Odometer at start: "; 
	cin >> odStart; 

	if (odStart < 0)                           //error message if the starting od reading is negative
	{
		cout << "---" << endl; 
		cout << "The starting odometer reading must not be negative.";
		return 1;
	}




	//END ODOMETER READING//
	cout << "Odometer at end: "; 
	cin >> odEnd; 

	if (odEnd < odStart)                        //error message if the ending od reading is less than the starting reading
	{
		cout << "---" << endl; 
		cout << "The ending odometer reading must be at least as large as the starting reading.";
		return 1;
	}




	//RETAL DAYS//
	cout << "Rental days: "; 
	cin >> rentDays; 
	 
	if (rentDays <= 0)                           //error message If the number of rental days is not positive
	{
		cout << "---" << endl;
		cout << "The number of rental days must be positive.";
		return 1;
	}
	



	//CUSTOMER NAME// 
	cout << "Customer name: "; 
	cin.ignore(10000, '\n');

	getline(cin, customerName); 

	if (customerName == "")                         //error message If an empty string was provided for the customer name
	{
		cout << "---" << endl;
		cout << "You must enter a customer name."; 
		return 1; 
	}

	

	//CAR TYPE//
	cout << "Luxury car? (y/n): "; 
	getline(cin, carType); 


	if (carType != "y" && carType != "n")             //error message If the luxury status is not y or n (must be lower case)
	{
		cout << "---" << endl; 
		cout << "You must enter y or n.";
		return 1; 
	}




	//MONTH NUMBER//
	cout << "Month (1=Jan, 2=Feb, etc.): "; 
	cin >> monthNum;  
	
	if (!(monthNum == 1 || monthNum == 2 || monthNum == 3 || 
		monthNum == 4 || monthNum == 5 || monthNum == 6 ||
		monthNum == 7 || monthNum == 8 || monthNum == 9 || 
		monthNum == 10 || monthNum == 11 || monthNum == 12))           //error message If the month number is not an integer between 1 and 12 inclusive
	{
		cout << "---" << endl; 
		cout << "The month number must be in the range 1 through 12."; 
		return 1; 
	}




	//calculate rental charge//
	double rentalCharge = 0; 

	//calculate base charge
	if (carType == "y")    //luxury car, 71 per day
	{
		rentalCharge += (71 * rentDays); 
	}
	else                   //non luxury car, 43 per day
	{
		rentalCharge += (43 * rentDays);
	}

	//calculate charge per mile 
	int milesDriven = odEnd - odStart; 

	if (milesDriven <= 100)      //charge for the first 100 miles 
	{
		rentalCharge += milesDriven * 0.27; 
	}
	else
	{
		rentalCharge += 100 * 0.27; 
	}



	                             //charge for miles between 100 and 500
	int secondFeeCounter;        //this variable will hold the num of miles b/w 100 and 500
	if (milesDriven > 100)     
	{

		if (milesDriven <= 500)       
		{
			secondFeeCounter = milesDriven - 100; 
		}
		else
		{
			secondFeeCounter = 400; 
		}

		//charge for the winter months
		if (monthNum == 12 || monthNum == 1 || monthNum == 2 || monthNum == 3) 
		{
			rentalCharge += 0.27 * secondFeeCounter; 
		}
		else  //charge for non-winter months 
		{
			rentalCharge += 0.21 * secondFeeCounter; 
		}
	
	}

	//charge for miles over 500
	if (milesDriven > 500)
	{
		rentalCharge += ((milesDriven - 500) * 0.17); 
	}




	
	
	//display rental charge//
	cout << "---" << endl; 
	cout.setf(ios::fixed);     //setting precision
	cout.precision(2); 
	cout << "The rental charge for " << customerName << " is $" << rentalCharge;

}