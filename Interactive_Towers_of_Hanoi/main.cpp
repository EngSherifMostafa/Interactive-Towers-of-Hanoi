#include "Solution.h"

int main()
{
	char mode='0', again='0';
	int disks=0, delayTime=0;
	Solution sol; //object from Solution class
	sol.startingScreen();

	do
	{
		cout<<"\n1- Automated solving\n"<<"2- User solving\n"<<"Select mode: ";
		cin>>mode;
		sol.printLine('-');

		switch (mode)
		{
            case '1':
                cout<<"Enter number of disks: ";
                cin>>disks;
                if(disks>15||disks<=0)
                {
                    cout<<"Invalid disk number\n";
                    fflush(stdin); //clear buffer
                    cin.clear();
                    break;
                }

                cout<<"Enter delay time between every step (by sec): ";
                cin>>delayTime;
                if(delayTime>15||delayTime<0)
                {
                    cout<<"Invalid time\n";
                    fflush(stdin); //clear buffer
                    cin.clear();
                    break;
                }

                if(disks<=8)
                {
                    cout<<"Minimum moves = "<<(pow(2,disks)-1)<<endl;
                    sol.printLine('-');
                    sol.machineSolve(disks,delayTime);
                    break;
                }

                else if(disks>8&&disks<=15)
                {
                    cout<<"Minimum moves = "<<(pow(2,disks)-1)<<endl;
                    sol.printLine('-');
                    sol.machineSolve(disks,delayTime);
                    break;
                }

            case '2':
                cout<<"Enter number of disks: ";
                cin>>disks;
                if(disks>8||disks<=0)
                {
                    cout<<"Invalid disk number\n";
                    fflush(stdin); //clear buffer
                    cin.clear();
                    break;
                }

                else
                {
                    cout<<"Minimum moves = "<<(pow(2,disks)-1)<<endl;
                    sol.printLine('-');
                    sol.userSolve(disks);
                    break;
                }

            default:
            {
                cout<<"Invalid selection mode\n";
                fflush(stdin); //clear buffer
                cin.clear();
            }
		}

		sol.printLine('-');
		cout<<"Do you want to try again Y/N: ";
		cin>>again;
		sol.printLine('-');
		sol.~Solution();  //reset all class attributes
	} while(again=='Y'||again=='y');

	system("pause");
	return 0;
}
