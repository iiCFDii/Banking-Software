#ifndef CHECKING_H
#define CHECKING_H
#include <string>
#include "sub.h"
using namespace std;

class checking : public subAcc		//	|	This class defines the attributes for a checking sub account. Inherits the subAcc class.
{


private:
    bool locked;	//	|	Variable for locking the sub account.
    int max;		//	|	Variable for the max balance.

public:
    checking()			//	|	Initializes the variables
    {
        balance = 0;
        accNum = "1000";
        locked = false;
        max = 0;
    }

    checking(string name, int bal, bool lock, int max1)		//	|	Allows for updating the variables.
    {
        balance = bal;
        accNum = name;
        locked = lock;
        max = max1;
    }



    void createCheckAcc(unsigned int bankNum)		//	|	This function creates a new checking sub account.
    {
		int baltemp = 0;		//	|	This variable is used to find the balance of the checking account later on.
        int maxtemp = 0;		//	|	This variable is used to set the max capacity.
        string locktemp;		//	|	This variable is used to tell if the account is locked or not.

		do
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			cout << endl << setfill(' ') << setw(31) << "Enter the initial balance: ";		//	|	Gets the inital balance.
			cin >> baltemp;


			cout << setfill(' ') << setw(40) << "Enter the desired maximum capacity: ";		//	|	Gets the desired max capacity.
			cin >> maxtemp;


			cout << setfill(' ') << setw(61) << "Define initial state (L - Locked, Otherwise - Unlocked): ";		//	|	Gets if the user wants the account locked or not.
			cin >> locktemp;

			if (cin.fail() || baltemp < 0 || maxtemp < baltemp) {
				error();
			}
			
		} while (cin.fail() || baltemp < 0 || maxtemp < baltemp);

        balance = baltemp;		//	|	Sets the inital balance.
        accNum = "CHK" + to_string(bankNum);		//	|	Sets CHK before the account number.
        max = maxtemp;		//	|		Sets the max capacity.

        if (locktemp == "l" || locktemp == "L")	//	|	Sets if the account is locked or not.
        {
            locked = true;
        }
        else
        {
            locked = false;
        }

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << setfill(' ') << setw(34) << "| A new Checking Sub-Account " << accNum << " was successfully created." << endl << endl;
    }


    void printSubCAccount()		//	|	Prints the checking account information when called.
    {
		system("color B");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		printSubAcc();
		cout << setfill(' ') << setw(33) << "| The maximum capacity is: $" << max << endl;

        if (locked)		//	|	if the account is locked, display a message.
        {
            cout << setfill(' ') << setw(34) << "| The sub-account is locked. " << endl;
        }
        else
        {
            cout << setfill(' ') << setw(37) << "| The sub-account is not locked." << endl;
        }
       
    }

	void checkMenu()		//	|	This function is the checking account menu
	{
		char choice = '0';		//	|	Variable for the user hoice within the menu.
		bool valid = false;		//	|	Variable for user validation.
		int input = 0;			//	|	Variable for taking in user input
		int check = balance + input;		//	|	Variable to check if the balance and the new deposit is under the desired capacity.

		do		//	|	Do loop that loops the menu until exited.
		{

			cin.clear();
			cin.ignore(128, '\n');

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			cout <<endl << endl<< "Eligible services for sub-account " << accNum << endl << setfill(' ') << setw(17) << "D -- Deposit" << endl << setfill(' ') << setw(18) << "W -- Withdraw" << endl << setfill(' ') << setw(22) << "C -- Max Capacity" << endl << setfill(' ') << setw(26) << "L -- Lock Sub-Account" << endl << setfill(' ') << setw(28) << "U -- Unlock Sub-Account" << endl << setfill(' ') << setw(14) << "X -- Exit" << endl << "Please enter your selection: ";
			cin >> choice; 

			//	|	input validation.
			while (cin.fail() || ((choice != 'D') && (choice != 'd') && (choice != 'W') && (choice != 'w') && (choice != 'C') && (choice != 'c') && (choice != 'L') && (choice != 'l') && (choice != 'U') && (choice != 'u') && (choice != 'X') && (choice != 'x'))) 
			{
				error();
				cin >> choice;
			}

			switch (choice)		//	|	Switch that allows user to pick function.
			{
			
			case 'd': case 'D':		//	|	First case, this case allows the user to deposit into the checking account.
				do
				{

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				cout << endl << setfill(' ') << setw(34) << "Enter the amount to deposit: ";
				cin >> input;

				if (cin.fail() || input < 0) {
					error();
				}

				}while (cin.fail() || input < 0);

				if (!locked && ((check) <= max))		//	|	Checks to see if the account is locked or not before depositing.
				{
					balance += input;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout << endl << setfill(' ') << setw(30) << "| Deposit was successful." << endl << setfill(' ') << setw(26) << "| Current balance is " << balance << endl << endl;
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout << endl << setfill(' ') << setw(39) << "| The account is currently locked!" << endl << setfill(' ') << setw(37) << "| The deposit was unsuccessfull." << endl << endl;
				}
			
				break;



			case 'w': case 'W':		//	|	Second case, this case allows the user to withdraw money from the checking account

				do
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					cout << endl << endl << setfill(' ') << setw(35) << "Enter the amount to withdraw: ";
					cin >> input;

					if (cin.fail() || input > balance) {
						error();
					}

				} while (cin.fail() || input > balance);


				if (!locked && (input <= balance))		//	|	Checks to see if the account is locked or not before withdrawing.
				{
					balance -= input;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout << endl << setfill(' ') << setw(31) << "| Withdraw was successful." << endl << setfill(' ') << setw(26) << "| Current balance is " << balance << endl << endl;
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout << endl << setfill(' ') << setw(40) << "| The account is currently locked! " << endl  << setfill(' ') << setw(38) << "| The withdraw was unsuccessfull."<< endl << endl;
				}
				
				break;



			case 'c': case 'C':		//	|	Third case, this case allows the user to modify the maximum capacity.

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				cout << endl << setfill(' ') << setw(37) << "Enter the new maximum capacity: ";
				cin >> input;

				if (input >= balance)
				{
					max = input;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout << setfill(' ') << setw(41) << "| Max capacity successfully changed." << endl << endl;
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout << setfill(' ') << setw(41) << "| Max capacity failed to be changed." << endl << endl;
				}
				
				break;



			case 'l': case 'L':		//	|	Fourth case, this case will lock the account.

				locked = true;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << setfill(' ') << setw(35) <<  "| Account successfully locked." << endl << endl;
				
				break;



			case 'u': case 'U':		//	|	Fifth case, this case will unlock the account.

				locked = false;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout <<endl << endl << setfill(' ') << setw(23) << "| The sub-account " << accNum << " is unlocked now! " << endl << endl;
				
				break;



			case 'x': case 'X':		//	|	This case will exit the checking account menu.

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << endl << setfill(' ') << setw(38) << "| End of service for sub-account " << accNum << endl;
				break;

			default:
				valid = true;
				break;
			}

		} while (!(choice == 'x' || choice == 'X'));
	}

};

#endif