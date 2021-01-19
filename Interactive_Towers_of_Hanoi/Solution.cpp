#include "Solution.h"

//destructor
Solution::~Solution()
{
	winning=0, flag=0;

	moveNum=0, diskNum=0,
	arrOne[8]={0}, arrTwo[8]={0}, arrThree[8]={0},
	retOne=0, retTwo=0, retThree=0,
	topOfT1=0, topOfT2=0,
	userMoves=0, fromTower=0, toTower=0, retDisk=0,
	bottomSpace=0, index=0, counter=0, space=0,
	diffSpaceOne=0, diffSpaceTwo=0, diffSpaceThree=0, diffSpaceFour=0,
	arrSize=8, base=0, bigSpace=0;
}

//this section is responsible for drawing towers that have less than or equal 8 disks
/**************************************************************************************/
void Solution::drawingTowers(StackLinked<int> &t1,StackLinked<int> &t2,StackLinked<int> &t3,int disks)
{
	t1.convertToArr(arrOne);
	t2.convertToArr(arrTwo);
	t3.convertToArr(arrThree);

	//temp lines between to comments to display arrays sent to draw function
	/*--------------------------------------------------------------------------
	printLine();
	cout<<"Array one: \n";
	for(index=0;index<8;index++)
	cout<<arrOne[index]<<"\t";
	cout<<endl;

	cout<<"Array two: \n";
	for(index=0;index<8;index++)
	cout<<arrTwo[index]<<"\t";
	cout<<endl;

	cout<<"Array three: \n";
	for(index=0;index<8;index++)
	cout<<arrThree[index]<<"\t";
	cout<<endl;
	printLine();
	--------------------------------------------------------------------------*/
	draw(arrOne,arrTwo,arrThree,disks);
	for (index=0;index<8;index++)
	{
		arrOne[index]=0;
		arrTwo[index]=0;
		arrThree[index]=0;
	}
}

//this section is responsible for displaying towers that have more than 8 disks
/**************************************************************************************/
void Solution::displayStep(int fromTower,int toTower)
{
	cout<<"\n"<<++moveNum<<
	"- Move disk from tower "<<fromTower<<" to tower "<<toTower<<"\n";
}

//this section is responsible for checking rules and end of game
/**************************************************************************************/
bool Solution::checkMove(StackLinked<int> &t1,StackLinked<int> &t2) //return true if movement valid
{
	//topOfT1 represent pop element
	//topOfT2 represent push element
	topOfT1=0, topOfT2=0;
	t1.getTop(topOfT1);
	t2.getTop(topOfT2);

	//special cases
	if(topOfT1==0) return 0; //you can't push zero
	else if(topOfT1>=1&&topOfT2==0) return 1; //push large disk over small disk

	else if(topOfT1<topOfT2) return 1; //element (pop) less than element that will (push) over it
	else if(topOfT1>=topOfT2) return 0;
	return 0;
}

bool Solution::checkEmpty(StackLinked<int> &t1,StackLinked<int> &t2)
{
	return(t1.isEmpty()&&t2.isEmpty());
}

//this section is responsible for algorithms of solving
/**************************************************************************************/
void Solution::fromAToB(StackLinked<int> &t1,StackLinked<int> &t2)
{
	retOne=0, retTwo=0;
	t1.getTop(retOne);
	t2.getTop(retTwo);

	if(checkMove(t1,t2))
	{
		t1.pop(retOne);
		t2.push(retOne);
		fromTower=1;
		toTower=2;
	}

	else if(checkMove(t2,t1))
	{
		t2.pop(retTwo);
		t1.push(retTwo);
		fromTower=2;
		toTower=1;
	}
}

void Solution::fromAToC(StackLinked<int> &t1,StackLinked<int> &t3)
{
	retOne=0, retThree=0;
	t1.getTop(retOne);
	t3.getTop(retThree);

	if(checkMove(t1,t3))
	{
		t1.pop(retOne);
		t3.push(retOne);
		fromTower=1;
		toTower=3;
	}

	else if (checkMove(t3,t1))
	{
		t3.pop(retThree);
		t1.push(retThree);
		fromTower=3;
		toTower=1;
	}
}

void Solution::fromBToC(StackLinked<int> &t2,StackLinked<int> &t3)
{
	retTwo=0, retThree=0;
	t2.getTop(retTwo);
	t3.getTop(retThree);

	if (checkMove(t2,t3))
	{
		t2.pop(retTwo);
		t3.push(retTwo);
		fromTower=2;
		toTower=3;
	}

	else if(checkMove(t3,t2))
	{
		t3.pop(retThree);
		t2.push(retThree);
		fromTower=3;
		toTower=2;
	}
}

//this section is responsible for solving game using machine
/**************************************************************************************/
void Solution::machineSolve(int &disks,int &delayTime)
{
	diskNum=disks;
	delayTime*=1000; //because user send seconds and sleep use milliseconds

	if(disks>0)
	{
		while(diskNum>=1)
			t1.push(diskNum--);

		//drawing towers if disks less than or equal 8
		if(disks<=8)
		{
			drawingTowers(t1,t2,t3,disks);
			Sleep(delayTime);
		}

		while(!checkEmpty(t1,t2))
		{
			if(disks%2==0) //even number of disks
			{
				fromAToB(t1,t2);
				displayStep(fromTower,toTower);
				if(disks<=8)
					drawingTowers(t1,t2,t3,disks);
                Sleep(delayTime);

				if(checkEmpty(t1,t2)) break;
				fromAToC(t1,t3);
				displayStep(fromTower,toTower);
				if(disks<=8)
					drawingTowers(t1,t2,t3,disks);
                Sleep(delayTime);

				if(checkEmpty(t1,t2)) break;
				fromBToC(t2,t3);
				displayStep(fromTower,toTower);
				if(disks<=8)
					drawingTowers(t1,t2,t3,disks);
				Sleep(delayTime);
			}

			else if(disks%2==1) //even number of disks
			{
				fromAToC(t1,t3);
				displayStep(fromTower,toTower);
				if(disks<=8)
					drawingTowers(t1,t2,t3,disks);
				Sleep(delayTime);

				if(checkEmpty(t1,t2)) break;
				fromAToB(t1,t2);
				displayStep(fromTower,toTower);
				if(disks<=8)
					drawingTowers(t1,t2,t3,disks);
				Sleep(delayTime);

				if(checkEmpty(t1,t2)) break;
				fromBToC(t2,t3);
				displayStep(fromTower,toTower);
				if(disks<=8)
					drawingTowers(t1,t2,t3,disks);
				Sleep(delayTime);
			}
		}
	}

	else
		return;
}


//this section is responsible for solving game by user
/**************************************************************************************/
void Solution::userSolve(int &disks)
{
	winning=0, flag=0;
	diskNum=disks;

	cout<<"Please note that if you want to stop playing at any time enter 0\n";
	//create first tower and draw it
	while(diskNum>=1)
		t1.push(diskNum--);
	drawingTowers(t1,t2,t3,disks);

	while(!checkEmpty(t1,t2))
	{
		cout<<"Enter move as (FROM TO): ";
		cin>>fromTower>>toTower;
		if(!cin)
		{
			fflush(stdin); //clear buffer
			cin.clear();
			cout<<"No change occurred <typo>\n";
			flag=1;
		}

		//stop game
		else if(fromTower==0||toTower==0)
		{
			cout<<"You stop game\n";
			break;
		}

		else if(fromTower>3||toTower>3||fromTower<0||toTower<0)
		{
			cout<<"No change occurred <typo>\n";
			flag=1;
		}

		//checking validation of movement
		/*	probabilities
		(1,1)(2,2)(3,3)
		(1,2)	  (1,3)
		(2,1)	  (2,3)
		(3,1)	  (3,2) */

		else if(fromTower==toTower)
		{
			cout<<"No change occurred <invalid movement>\n";
			flag=1;
		}

		else if(fromTower==1&&toTower==2)
		{
			if(!checkMove(t1,t2))
			{
				cout<<"No change occurred <invalid movement>\n";
				flag=1;
			}
		}

		else if(fromTower==1&&toTower==3)
		{
			if(!checkMove(t1,t3))
			{
				cout<<"No change occurred <invalid movement>\n";
				flag=1;
			}
		}

		else if(fromTower==2&&toTower==1)
		{
			if(!checkMove(t2,t1))
			{
				cout<<"No change occurred <invalid movement>\n";
				flag=1;
			}
		}

		else if(fromTower==2&&toTower==3)
		{
			if(!checkMove(t2,t3))
			{
				cout<<"No change occurred <invalid movement>\n";
				flag=1;
			}
		}

		else if(fromTower==3&&toTower==1)
		{
			if(!checkMove(t3,t1))
			{
				cout<<"No change occurred <invalid movement>\n";
				flag=1;
			}
		}

		else if(fromTower==3&&toTower==2)
		{
			if(!checkMove(t3,t2))
			{
				cout<<"No change occurred <invalid movement>\n";
				flag=1;
			}
		}

		if(!flag)
		{
			if(fromTower==1) t1.pop(retDisk);
			else if(fromTower==2) t2.pop(retDisk);
			else if(fromTower==3) t3.pop(retDisk);

			if(toTower==1) t1.push(retDisk);
			else if(toTower==2) t2.push(retDisk);
			else if(toTower==3) t3.push(retDisk);

			userMoves++;
		}

		flag=0;
		retDisk=0;
		drawingTowers(t1,t2,t3,disks);
		if(checkEmpty(t1,t2)) winning=1;
	}

	if(winning)
	{
	    str="Congratulations! you solve TOWER OF HANOI";
        drawSpecialLine(str,' ');
        cout<<endl;

		str="Your movements = ";
		drawSpecialLine(str,' ');
		cout<<userMoves<<endl;

		if(userMoves==(pow(2,disks)-1))
		{
		    str="You done the best movements";
            drawSpecialLine(str,' ');
			cout<<endl;
		}

		else
		{
		    str="Difference between your movements and optimal movements = ";
            drawSpecialLine(str,' ');
			cout<<userMoves-(pow(2,disks)-1)<<endl;

			str="Keep trying to do the optimal movements";
            drawSpecialLine(str,' ');
			cout<<endl;
		}
	}
}

void Solution::ascendingOrder(int *&arr,int arrSize)
{
	for(index=0;index<arrSize;index++)
		for(counter=index+1;counter<arrSize;counter++)
			if(arr[counter]<arr[index])
			{
				//swap without temp
				arr[counter]+=arr[index];
				arr[index]=arr[counter]-arr[index];
				arr[counter]-=arr[index];
			}
}

void Solution::drawPeaks(int &bigSpace)
{
	for(counter=0;counter<bigSpace;counter++)
		cout<<" ";
	cout<<"|";

	for(counter=0;counter<bigSpace;counter++)
		cout<<" ";
	cout<< "|";

	for(counter=0;counter<bigSpace;counter++)
		cout<<" ";
	cout<<"|";

	for (counter=0;counter<bigSpace;counter++)
		cout<<" ";
	cout<<endl;
}

void Solution::drawBottoms()
{
	bottomSpace=(screenWidth-(3 * 8))/4;

	diffSpaceOne=bottomSpace-underEveryBase;
	diffSpaceTwo=bottomSpace-(2*underEveryBase);
	diffSpaceThree=bottomSpace-(2*underEveryBase);
	diffSpaceFour=bottomSpace-underEveryBase;

	//draw first bottom
	for(counter=diffSpaceOne;counter>0;counter--)
		cout<<" ";

	for(counter=underEveryBase;counter>0;counter--)
		cout<<"-";
	cout<<"-";

	for(counter=underEveryBase;counter>0;counter--)
		cout<<"-";

	//draw second bottom
	for(counter=diffSpaceTwo;counter>0;counter--)
		cout<<" ";

	for(counter=underEveryBase;counter>0;counter--)
		cout<<"-";
	cout<<"-";

	for(counter=underEveryBase;counter>0;counter--)
		cout<<"-";

	//draw third bottom
	for(counter=diffSpaceThree;counter>0;counter--)
		cout<<" ";

	for(counter=underEveryBase;counter>0;counter--)
		cout<<"-";
	cout<<"-";

	for(counter=underEveryBase;counter>0;counter--)
		cout<<"-";

	for(counter=diffSpaceFour;counter>0;counter--)
		cout<<" ";
	cout<<endl;
}

void Solution::draw(int towerOne[],int towerTwo[],int towerThree[],int diskNumbers)
{
	base=diskNumbers*2,
	bigSpace=(screenWidth-(3*8))/4;

	ascendingOrder(towerOne,diskNumbers);
	ascendingOrder(towerTwo,diskNumbers);
	ascendingOrder(towerThree,diskNumbers);

	drawPeaks(bigSpace);
	drawPeaks(bigSpace);

	/*
	line equation
	bigSpace + diffSpaceOne + towerOne[index] + "|" + towerOne[index] +
	bigSpace + diffSpaceTwo + towerTwo[index] + "|" + towerTwo[index] +
	bigSpace + diffSpaceThree + towerThree[index] + "|" + towerThree[index] +
	bigSpace + diffSpaceFour + newLine
	*/

	for(index=0;index<diskNumbers;index++)
	{
		diffSpaceOne=bigSpace-towerOne[index];
		diffSpaceTwo=bigSpace-(towerOne[index]+towerTwo[index]);
		diffSpaceThree=bigSpace-(towerTwo[index]+towerThree[index]);
		diffSpaceFour=bigSpace-towerThree[index];

		if(towerOne[index]==0&&towerTwo[index]==0&&towerThree[index]==0)
		{
			drawPeaks(bigSpace);
			continue;
		}

		for(counter=0;counter<diffSpaceOne;counter++)
			cout<<" ";

		for(counter=0;counter<towerOne[index];counter++)
			cout<<"*";
		cout<<"|";

		for(counter=0;counter<towerOne[index];counter++)
			cout<<"*";

		for(counter=0;counter<diffSpaceTwo;counter++)
			cout<<" ";

		for(counter=0;counter<towerTwo[index];counter++)
			cout<<"*";
		cout<<"|";

		for(counter=0;counter<towerTwo[index];counter++)
			cout<<"*";

		for(counter=0;counter<diffSpaceThree;counter++)
			cout<<" ";

		for(counter=0;counter<towerThree[index];counter++)
			cout<<"*";
		cout<<"|";

		for(counter=0;counter<towerThree[index];counter++)
			cout<<"*";

		for(counter=0;counter<diffSpaceFour;counter++)
			cout<<" ";
		cout<<endl;
	}
	drawBottoms();
}


//this section is responsible for screen size
/**************************************************************************************/
void Solution::startingScreen()
{
	//make screen full
	HWND consoleWindow=GetConsoleWindow();
	ShowWindow(consoleWindow,SW_MAXIMIZE);

	//get cmd width
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
	screenWidth=csbi.srWindow.Right-csbi.srWindow.Left+1;

	intro();
}

//this section is responsible for make intro screen
/**************************************************************************************/
void Solution::intro()
{
	//draw 2 lines
    printLine('*');
    printLine('*');

	str=" ";
	drawSpecialLine(str,'*');

	str="WELCOME TO TOWER OF HANOI GAME";
	drawSpecialLine(str,'*');

	str="DESIGNED BY:";
	drawSpecialLine(str,'*');

	str="1- MOHAMED SAYED HEMED";
	drawSpecialLine(str,'*');

	str="2- SHERIF MOSTAFA SAMY";
	drawSpecialLine(str,'*');

	str="CAIRO UNIVERSITY";
	drawSpecialLine(str,'*');

	str=" ";
	drawSpecialLine(str,'*');

	//draw 2 lines
    printLine('*');
    printLine('*');
}

void Solution::drawSpecialLine(string str,char ch)
{
	//calculate remainder space after print string
	space=(screenWidth/3)-str.length();

	//counter = char + space before string + string length + space after string + char
	counter=(screenWidth/3)+(space/2)+str.length()+(space/2)+(screenWidth/3);

	//draw 1/3 line of char
	for(index=0;index<(screenWidth/3);index++)
		cout<<ch;

	//draw 1/2 remainder spaces before string
	for(index=0;index<(space/2);index++)
		cout<<" ";

	//print string
	cout<<str;

    if(ch==' ') return; //stop function when write string and variable

	//draw 1/2 remainder spaces after string
	for(index=0;index<(space/2);index++)
		cout<<" ";

	//check if spaces + char = screenWidth or less
	while(counter<screenWidth)
	{
		cout<<" ";
		counter++;
	}

	//draw 1/3 line of char
	for(index=0;index<(screenWidth/3);index++)
		cout<<ch;
}

void Solution::printLine(char ch)
{
	for(counter=0;counter<screenWidth;counter++)
		cout<<ch;
}
