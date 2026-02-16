
#include "grid.h"
#include <iostream>
#include <cctype>
#include <string>
#include <cassert>
using namespace std;








//hasCorrectForm returns true if the parameter is a plan//
bool hasCorrectForm(string plan)
{
	if (plan == "") //if the string is empty (plan size 0) return true
	{
		return true; 
	}


	for (int i = 0; i < plan.size(); i++) //increments through plan
	{
		if ( !((plan.at(i) == 'r') || (plan.at(i) == 'R') || 
			(plan.at(i) == 'l') || (plan.at(i) == 'L') ||                        
			(isdigit(plan.at(i)))) )                           //this tests if the string has characters other than r,l,R,L or digits
		{
			return false; 
		}                                
	}

	
	for (int i = 0; i < plan.size(); i++) //increments through plan
	{

		if ((plan.size() >= 3) && (i <= plan.size() - 3)) // proceed if plan size is at least 3 characters long or if the program is not looking at the last three characters 
		{
			
			if (isdigit(plan.at(i)) && isdigit(plan.at(i + 1)) && isdigit(plan.at(i + 2))) //return false if there are three nums in a row
			{
				return false;
			}
		}
	}	

	if (isdigit(plan.at(plan.size() - 1))) //return false if last character is a digit
	{
		return false; 
	}

	return true;   //return true if the program makes it this far without returning false 

}












int determineSafeDistance(int r, int c, char dir, int maxSteps)
{
	if (!((dir == 'n') || (dir == 'N') || (dir == 's') || (dir == 'S')
		|| (dir == 'e') || (dir == 'E') || (dir == 'w') || (dir == 'W')))  //check that dir is a valid direction letter 
	{
		cerr << "not correct direction letter " << endl; 
		return -1; 
	}

	if (maxSteps < 0)                                                     //check that maxSteps is not negative
	{
		cerr << "max steps is negative" << endl; 
		return -1; 
	}

	if (r <= 0 || r > getRows() || c <= 0 || c > getCols())                 //checks that (r,c) position is on the grid
	{
		cerr << "you are outside the grip" << endl; 
		return -1; 
	}

	if (isWall(r, c))                                                     //if there is a wall at the starting position return -1
	{
		cerr << "you have run into a wall" << endl; 
		return -1; 
	}


	//check how many steps the car can travel without falling off edge or crashing into wall 
	int rChange = 0;     //variables that hold the change in r and c values, set to 0 at first 
	int cChange = 0; 
	 
	int newR = r;        //variables that will any hold new r,c values; first set to original r,c values
	int newC = c; 


	for (int i = 1; i <= maxSteps; i++)
	{
		if (dir == 'n' || dir == 'N')    //when dir is north, move position up a row
		{
			rChange = -1;
		}

		if (dir == 's' || dir == 'S')    //when dir is south, move position down a row
		{
			rChange = 1;
		}

		if (dir == 'e' || dir == 'E')    //when dir is east, move position down a column 
		{
			cChange = 1;
		}

		if (dir == 'w' || dir == 'W')    //when dir is west, move position up a column 
		{
			cChange = -1;
		}

		newR += rChange;                //set new r,c values 
		newC += cChange;


		if (newR <= 0 || newR > getRows()
			|| newC <= 0 || newC > getCols())                      //if new position is off the grid, return the steps traveled safely 
		{
			return i - 1;
		}

		if (isWall(newR, newC))                                    //if new position contains a wall, return the steps traveled safely 
		{
			return i - 1; 
		}
	}

	return maxSteps;   //if the program runs to the end of the function without returning a value, return the maxSteps traveled 
}











int obeyPlan(int sr, int sc, int er, int ec, char dir, string plan, int& nsteps)
{


	//--if there is something wrong with the parameters return a 2--//
	if (er <= 0 || er > getRows() || ec <= 0 || ec > getCols())            //return 2 if er,ec is not valid grid position
	{
		cerr << "rows out of grid" << endl; 
		return 2;
	}

	if (isWall(er, ec))                                                    //return 2 if er,ev contains a wall 
	{
		cerr << "starts on wall" << endl; 
		return 2;
	}


	if (determineSafeDistance(sr, sc, dir, 1) == -1)                 //return 2 if determineSafeDistance fails
	{
		cerr << "determineSafeDistance returned -1 " << endl;
		return 2;
	}

	if (!hasCorrectForm(plan))                                            //return 2 if the plan string is not a plan 
	{
		cerr << "did not have correct form" << endl;
		return 2;
	}


	//--variables used during cycling through plan string--//
	int planPortionSteps = 0;                   //steps per planPortion 
	int stepsCompleted = 0;                     //steps the program managed to complete per plan portion without meeting an obstacle or falling off the grid 
	int numberHolder = 0;                       //this variable holds the value of the digit being looked at in the for loop 
	int determineSafeDistanceReturnValue = 0;   //return value for determineSafeDistance function 
	int distanceTraveled = 0;                   //distance traveled per plan portion
	int totalStepsCounter = 0;                         //total steps traveled over the course of the plan portion 



	//--cycle through each character in the plan, do different things to letters and digits--//
	for (int i = 0; i < plan.size(); i++)
	{
		cerr << endl << endl; 
		cerr << "plan i: " << i << endl;
		if (isalpha(plan.at(i)))  //change the dir if the plan character is a letter 
		{
			cerr << plan.at(i) << " is a Letter. " << endl;
			cerr << "initial direction: " << dir << endl;
			if (plan.at(i) == 'r' || plan.at(i) == 'R')  //if the character represents right, move the directions clockwise
			{
				if (dir == 'w' || dir == 'W')
				{
					dir = 'N';
				}

				else if (dir == 'n' || dir == 'N')
				{
					dir = 'E';
				}

				else if (dir == 'e' || dir == 'E')
				{
					dir = 'S';
				}

				else 
				{
					dir = 'W';
				}
			}

			if (plan.at(i) == 'l' || plan.at(i) == 'L') //if the character represents left, move the directions counter clockwise
			{
				if (dir == 'e' || dir == 'E')
				{
					dir = 'N';
				}

				else if (dir == 's' || dir == 'S')
				{
					dir = 'E';
				}

				else if (dir == 'w' || dir == 'W')
				{
					dir = 'S';
				}

				else 
				{
					dir = 'W';
				}
			}
		    
			cerr << "new direction: " << dir << endl;
		}


		
		if (isdigit(plan.at(i)))  //if the character is a digit act accordingly: 
		{
			
			//set numberHolder to whatever digit in plan is currently being looked at
			if (plan.at(i) == '0')
			{
				numberHolder = 0; 
			}

			if (plan.at(i) == '1')
			{
				numberHolder = 1;
			}

			if (plan.at(i) == '2')
			{
				numberHolder = 2;
			}

			if (plan.at(i) == '3')
			{
				numberHolder = 3;
			}

			if (plan.at(i) == '4')
			{
				numberHolder = 4;
			}

			if (plan.at(i) == '5')
			{
				numberHolder = 5;
			}

			if (plan.at(i) == '6')
			{
				numberHolder = 6;
			}

			if (plan.at(i) == '7')
			{
				numberHolder = 7;
			}

			if (plan.at(i) == '8')
			{
				numberHolder = 8;
			}

			if (plan.at(i) == '9')
			{
				numberHolder = 9;
			}

			cerr << " Number holder: " << numberHolder << endl;

			//if the number we are looking at in the ten's place of a number multiply 
			//numberHolder by 10 and add it to the planPortionSteps
			if (i != (plan.size() - 1) && isdigit(plan.at(i + 1)))          
			{
				planPortionSteps += numberHolder * 10 ;  
				                           
			}
			else
			{
				planPortionSteps += numberHolder; 
			}
	
			cerr << " planPortionSteps: " << planPortionSteps << endl;





			//Once we reach the end of the plan portion:  
			if (i == (plan.size()) - 1 || isalpha(plan.at(i+1)))
			{
				numberHolder = 0;                           //reset numberHolder variable for the next plan portion
		        

				//now use the determineSafeDistance function 
				distanceTraveled = determineSafeDistance(sr, sc, dir, planPortionSteps);
				totalStepsCounter += distanceTraveled;      //add the distanced traveled in one plan portion to the totalStepsCoutner

				cerr << " steps that could be completed: " << distanceTraveled;
				if (distanceTraveled < planPortionSteps)    //if the car cannot make it to the end of the plan portion 
				{
					nsteps = totalStepsCounter;
					return 3;
				}

				//reset planPortion variable 
				planPortionSteps = 0; 
				 
				cerr << endl << "distancetraveled: " << distanceTraveled << endl; 
				cerr << "dir: " << dir << endl; 
				cerr << endl << "(" << sr << "," << sc << ")" << endl;

				//reset starting coordinates (sr, sc)
				if (dir == 'N' || dir == 'n')
				{
					sr -= distanceTraveled;
				}

				if (dir == 'S' || dir == 's')
				{
					sr += distanceTraveled;
				}

				if (dir == 'E' || dir == 'e')
				{
					sc += distanceTraveled;
				}

				if (dir == 'W' || dir == 'w')
				{
					sc -= distanceTraveled;
				}

				cerr << "(" << sr << ", " << sc << ")" << endl;

			}				
		}
	}
	
	//change nsteps to the number of steps traveled 
	nsteps = totalStepsCounter;
	
	//check if you made it to your destination
	if (sc == ec && sr == er)  //if you did make it to the destination: 
	{
		cerr << "You go to your destination!" << endl;
		return 0; 
	}
	
	
	//if you did not make it to the destination: 
	return 1; 
}

















	
int main()
{
	setSize(3, 4);
	setWall(1, 4);
	setWall(2, 2);
	setWall(3, 2);
	assert(hasCorrectForm("2R1r"));
	assert(!hasCorrectForm("1Lx"));
	assert(determineSafeDistance(3, 1, 'N', 2) == 2);
	int len;
	len = -999;  // so we can detect whether obeyPlan sets len
	assert(obeyPlan(3, 1, 3, 4, 'S', "LL2R2r2L1R", len) == 0 && len == 7);
	len = -999;  // so we can detect whether obeyPlan sets len
	assert(obeyPlan(3, 1, 3, 4, 'N', "1Lx", len) == 2 && len == -999);
	len = -999;  // so we can detect whether obeyPlan sets len
	assert(obeyPlan(2, 4, 1, 1, 'w', "3R1L", len) == 3 && len == 1);
		cerr << "All tests succeeded" << endl;
}
