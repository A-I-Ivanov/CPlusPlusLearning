// Functionality_Checker.cpp : Defines the entry point for the console application.
//
#define _CRTDBG_MAP_ALLOC
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <crtdbg.h>
#include <queue> 
#include <string>
#include <stdexcept>



class node
{
	//Data memvbers 
public:
	double value;
	node *next = nullptr;

};

class llist
{
	node headNode;

public : 
	llist(double firstValue);
	void pushback(double value);
	void changeVal(int location, double value);
	double access(int location);
	void remove(int location);
	void removeAll();

};

llist::llist(double firstValue)
{
	headNode.value = firstValue;
}

void llist::pushback(double value)
{
	node *lastNode = &headNode;
	while ((*lastNode).next!= nullptr)
		lastNode = (*lastNode).next;

	node *newNode = new node();

	(*lastNode).next = newNode;
	(*newNode).value = value;
	(*newNode).next = nullptr;


}

void llist::changeVal(int location, double value)
{
	node *nodeWeWant = &headNode;
	for (int i = 0; i < location; i++)
	{
		if ((*nodeWeWant).next != nullptr)
			nodeWeWant = (*nodeWeWant).next;
		else
		{
			throw - 1;
		}
	}

	(*nodeWeWant).value = value;
}

double llist::access(int location)
{
	node *nodeWeWant = &headNode;
	for (int i = 0; i < location; i++)
	{
		if ((*nodeWeWant).next != nullptr)
			nodeWeWant = (*nodeWeWant).next;
		else
		{
			throw - 1;
		}
	}

	return (*nodeWeWant).value;

}

void llist::remove(int location)
{
	node *nodeWeWant = &headNode;
	node *previousNode = nullptr; 
	for (int i = 0; i < location; i++)
	{
		if ((*nodeWeWant).next != nullptr)
		{
			previousNode = nodeWeWant;
			nodeWeWant = (*nodeWeWant).next;
		}
			
		else
		{
			throw - 1;
		}
	}
	//First we reassign the pointer of the previous node
	(*previousNode).next = (*nodeWeWant).next;
	//Now we get rid of the dynamically allocated node to prevent a memory leak
	delete nodeWeWant;
}

void llist::removeAll()
{

	node *nodeWeWant = &headNode;
	node *nextNode = headNode.next;
	while (nextNode != nullptr)
	{
		nodeWeWant = nextNode;
		nextNode = (*nodeWeWant).next;
		delete nodeWeWant;
	}

	headNode.next = nullptr;
}

//Begin Palindrome problem 

struct centers
{
public:
	int leftCenter;
	int rightCenter;
};

class palinFinder
{
	//Data Members 
	int largestSize = 0;
	int indexOfLargest = -1;
	std::queue<int> stackOfPotentials;
	std::string inputString;

public:
	palinFinder(std::string inputString);

private:
	std::pair<int, centers> itterate(centers startPosition, int currentSize);
public:
	std::string getLargest();
};

palinFinder::palinFinder(std::string inputString)
{
	
	if (inputString.size() > 0)
	{
		this->inputString = inputString;
		largestSize = 0;
		indexOfLargest = inputString.size() - 1;

		//If the string is even in size, place both central elements in the stack
		if (inputString.size() % 2 == 0)
		{
			stackOfPotentials.push(inputString.size() / 2);
			stackOfPotentials.push(inputString.size() / 2 - 1);
		}
		else //Place the central element in the stack
		{
			stackOfPotentials.push((inputString.size()/ 2));
		}


	}


}


//Note, I was generating a recursive function call here starting from the center of the string. 
std::string palinFinder::getLargest()
{
	int processLocation = 0;
	centers largestCenters, currentCenters;
	std::pair<int, centers> currentSizeAndCenters;
	
	while (stackOfPotentials.size() > 0)
	{

		currentCenters.leftCenter = stackOfPotentials.front();
		currentCenters.rightCenter = currentCenters.leftCenter;
		stackOfPotentials.pop();

		currentSizeAndCenters = itterate(currentCenters, 0);
		if (currentSizeAndCenters.first >= largestSize)
		{
			//This if statement is to capture the expetion where the size is the same, but there is a double letter in one but not the other
			//in this case the double letter should win
			if ((currentSizeAndCenters.second.leftCenter != currentSizeAndCenters.second.leftCenter) || currentSizeAndCenters.first > largestSize)
				largestCenters = currentSizeAndCenters.second; //May be doing unintentional over write here
			largestSize = currentSizeAndCenters.first;
		}

		if ((processLocation + largestSize) <= inputString.size() / 2)
		{
			processLocation++;

			if (inputString.size() % 2 == 0)
			{
				stackOfPotentials.push((inputString.size() / 2) - processLocation);
				stackOfPotentials.push(inputString.size() / 2   + processLocation);
			}
			else //Place the central element in the stack
			{
				stackOfPotentials.push((inputString.size() + 1) / 2 + processLocation -1);
				stackOfPotentials.push((inputString.size() + 1) / 2 - processLocation -1);
			}

		}

	}

	bool isOdd = (largestCenters.leftCenter == largestCenters.rightCenter);
	indexOfLargest = largestCenters.leftCenter - largestSize;
	int palinLength = largestSize * 2 + (2 - isOdd); //if the palindrome is odd we add one, otherwise add 2

	return inputString.substr(indexOfLargest, palinLength);

}

//This function assumes that the input is in all caps or all lower case not mixed case letters
std::pair<int, centers> palinFinder::itterate(centers startPosition, int currentSize)
{
	char expandLeft, expandRight;
	char currentLeft, currentRight;
	bool noExpandL = false, noExpandR = false;


	//Check if the arguments are out of bounds. If so return the current size
	if (startPosition.rightCenter + currentSize + 1 < inputString.size())
		expandRight = inputString[startPosition.rightCenter + currentSize + 1];
	else
		noExpandR = true;

	if (startPosition.leftCenter - currentSize - 1< inputString.size())
		expandLeft = inputString[startPosition.leftCenter - currentSize -1];
	else
		noExpandL = true;

	//Everything is happy, we keep expanding
	if ( !(noExpandL || noExpandR) && expandLeft == expandRight)
		return itterate(startPosition, currentSize + 1);
	else //check to make sure we can't add one more letter at least 
	{
		currentLeft = inputString[startPosition.leftCenter - currentSize];
		currentRight = inputString[startPosition.rightCenter + currentSize];
		if (!noExpandR && (expandRight == currentLeft) && currentSize==0) //Check if we can expand only to the right
		{
			startPosition.rightCenter++; //not sure if I can do this
			return itterate(startPosition, currentSize);
		}

		else 
		{
			if (!noExpandL && (expandLeft == currentRight) && currentSize == 0) //Check to see if we can expand only to the left
			{
				startPosition.leftCenter--;
				return itterate(startPosition, currentSize);
			}
			else //we could not expand any further. Return our current centers and current size
			{
				return std::pair<int, centers>(currentSize, startPosition);
			}
		}
		
	}

	throw std::logic_error("The special case handling for palindromes is wrong");

}

using namespace std;

int main()
{
	//Testing the linked list
	/*
	llist newList(0.0);
	int studpid = 0;

	//Test the pushback 
	for (int i = 1; i < 100; i++)
	{
		newList.pushback(i);
	}

	//Test the access 
	for (int i = 0; i < 100; i++)
	{
		std::cout << newList.access(i) << std::endl;
	}

	//Test the change value 
	for (int i = 0; i < 100; i++)
	{

		newList.changeVal(i, 100 - i - 1);
	}

	//Test the access 
	for (int i = 0; i < 100; i++)
	{
		std::cout << newList.access(i) << std::endl;
	}

	//Test the change value 
	for (int i = 0; i < 100; i++)
	{
		
		newList.changeVal(i, i);
	}

	//Test the remove

	for (int j = 0; j < 1; j++)
	{
		for (int i = 99; i>0; i--)
		{

			newList.remove(i);
		}

		for (int i = 1; i < 100; i++)
		{
			newList.pushback(i);
		}

	}

	newList.removeAll();

	_CrtDumpMemoryLeaks();

	*/

	//testing the palindrome class

	palinFinder palFinder = { "afadadddaaaddd" };
	string answer = palFinder.getLargest();

	std::cout << answer << endl;
	cin >> answer;
	return 0;
}

