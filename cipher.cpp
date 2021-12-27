#include <iostream>
#include <queue>
#include <locale>
#include <fstream> 

using namespace std;

int main(void)
{
	//Make an array of queues for the rails. There won't be more than 100 rails.
	queue<char> rails [101];
	
	//Set up our input file
	istream & in = cin;
	
	//For debug purposes, if the file is missing, it will print out something
	// and exit.
	if(!in)
	{
		cout << "Missing the file!" << endl;
		return 1;
	}
	
	int n, r;
	
	char line [105];
	
	
	//Read in the first pair of numbers
	in >> n;
	in >> r;
	
	//Loop until we find the terminating sequence
	while(n != 0 || r != 0)
	{	
		//Now we read in the entirety of the line, eating the blank
		// line at the end of the numbers. This will loop until
		// it reads a non-empty string.
		do
		{
			in.getline(line, 105);
		} while(line[0] == '\0');
		
		//Now we lay the letters on the rails,
		// where direction is 1 for going down, and -1 for going up
		// (in relation to the picture on the problem set)
		int dir  = 1;
		
		//If we only have one rail, then we won't switch rails, direction = 0
		if(n == 1)
			dir = 0;
		
		//For each letter in the input line
		for(int currRail = 0, stringPos = 0; ; stringPos++)
		{
			char currChar = line[stringPos];
			
			//If the char is the null character, we've reached the end
			// of the line, so quit
			if(currChar == '\0')
				break;
			else if(!isalnum(currChar))	//Ignore non-alphanumeric characters.
				continue;				// if we care only about alphabeticals,
										// we'd use isalpha(currChar)
			
			//Put the character on the correct rail
			rails[currRail].push(currChar);
			
			//Change the current rail based on the direction
			currRail += dir;
			
			//If we're on the last rail per a direction, change directions
			if((currRail == 0 && dir < 0) || (currRail == n-1 && dir > 0))
				dir = -dir;
		}
		
		//i is a counter for adding the spaces
		int i = 0;
		bool first = true;
		
		//Now we go through every rail (rr) start from the specified rail (r)
		// and print out the contents of the rail
		for(int rr = 0, currRail = r-1; rr < n; rr++, currRail = (currRail+1)%n)
		{
			while(!rails[currRail].empty())
			{				
				//If this is not the first set of 5, and the counter
				// reset to 0, then put a space before printing the next 
				// character.
				if(i == 0 && !first)
				{
					cout << " ";
				}
			
				//Remove a letter from the queue.
				cout << rails[currRail].front();
				rails[currRail].pop();
				
				//Update the space counters.
				i = (i + 1)%5;
				first = false;
			}
		}
		
		//Add the period and newline at the end of each case, and read in the
		// next inputs.
		cout << "." << endl;
		
		in >> n;
		in >> r;
	}
	
	return 0;
}
