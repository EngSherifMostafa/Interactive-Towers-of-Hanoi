#ifndef SOLUTION_H
#define SOLUTION_H

#include <iostream>
#include <time.h> //sleep function
#include <windows.h> //screen calculations
#include <cmath> //power function
#include <string>
#include "StackLinked.h"
using namespace std;

class Solution
{
public:
	~Solution();
	void intro();
	void printLine(char);
	void startingScreen();
	void machineSolve(int&,int&);
	void userSolve(int&);

private:
	void fromAToB(StackLinked<int>&,StackLinked<int>&);
	void fromAToC(StackLinked<int>&,StackLinked<int>&);
	void fromBToC(StackLinked<int>&,StackLinked<int>&);

	bool checkEmpty(StackLinked<int>&,StackLinked<int>&);
	bool checkMove(StackLinked<int>&,StackLinked<int>&);
	void ascendingOrder(int*&,int);

	void displayStep(int,int);
	void drawingTowers(StackLinked<int>&,StackLinked<int>&,StackLinked<int>&,int);
	void drawPeaks(int&);
	void drawBottoms();
	void draw(int[],int[],int[],int);
	void drawSpecialLine(string,char);

	bool winning=0, flag=0;
	int arrOne[8]={0}, arrTwo[8]={0}, arrThree[8]={0},
		moveNum=0, diskNum=0,
		retOne=0, retTwo=0, retThree=0,
		topOfT1=0, topOfT2=0,
		userMoves=0, fromTower=0, toTower=0, retDisk=0,
		bottomSpace=0, index=0, counter=0, space=0,
		diffSpaceOne=0, diffSpaceTwo=0, diffSpaceThree=0, diffSpaceFour=0,
		arrSize=8, base=0, bigSpace=0,
		screenWidth=0, underEveryBase=10;
	string str;
	StackLinked<int> t1, t2, t3;
};

#endif
