#ifndef SAVING_H
#define SAVING_H
#include <string>
#include "sub.h"
using namespace std;

class savings : public subAcc		//	|	This class defines the attributes for a saving sub account. Inherits the subAc class.
{


private:
    bool first;		//	|	The only variable that is exclusive to savings, check to see if its the first account or not.


public:
    savings()		//	| default constructor for variables.
    {
        balance = 0;
        accNum = "1000";
        first = false;
    }

    savings(string name, int bal, bool first1)		//	|	Allows variables to be updated.
    {
        balance = bal;
        accNum = name;
        first = first1;
    }


	void printSave()		//	|	Prints saving account information.
	{
		system("color B");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		printSubAcc();
	}


	void createSavAcc(unsigned int num, bool isFirst)		//	|	This function creates a new saving account.
	{
		int sav;
		do {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			cout << endl << setfill(' ') << setw(32) << "Enter the initial balance: ";
			cin >> sav;

			if (cin.fail() || sav < 0) {
				error();
			}

		} while (cin.fail() || sav < 0);

		if (isFirst)		//	|	Checks to see if the saving account being created is the first or not.
		{
			balance = sav + 100;		//	|	if the account is the first,a 100 dollar bonus is awarded.
		}
		else
		{
			balance = sav;
		}

		accNum = "SAV" + to_string(num);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout << setfill(' ') << setw(33) << "| A new Savings Sub-Account " << accNum << " was successfully created." << endl << endl;
	}



	void savMenu()		//	|	This is the menu for the saving accounts.
	{
		char choice = '0';		//	|	Variable used for user choice in menu.
		bool check = false;		//	|	Variable used to validate.
		int money;				//	|	Variable used to add all the money together.


		do		//	|	Do loop for the savings menu.

		{

			cin.clear();
			cin.ignore(128, '\n');

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			cout <<endl << endl << "Eligible services for sub-account " << accNum << endl << setfill(' ') << setw(17) << "D -- Deposit" << endl << setfill(' ') << setw(18) << "W -- Withdraw" << endl << setfill(' ') << setw(14) << "X -- Exit" << endl << "Please enter your selection: ";
			cin >> choice;

			while (cin.fail() || ((choice != 'D') && (choice != 'd') && (choice != 'W') && (choice != 'w') && (choice != 'X') && (choice != 'x')))
			{
				error();
				cin >> choice;
			}



			switch (choice)		//	|	Switch for all the menu options.
			{

			case 'd': case 'D':		//	|	First case, this case allows the user to deposit into the saving account.
				do 
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					cout << endl << endl << setfill(' ') << setw(34) << "Enter the amount to deposit: ";
					cin >> money;

					if (cin.fail() || money < 0) {
						error();
					}

				} while (cin.fail() || money < 0);

				balance += money;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << setfill(' ') << setw(30) << "| Deposit was successful." << endl << setfill(' ') << setw(26) << "| Current balance is " << balance << endl << endl;
				
				break;



			case 'w': case 'W':		//	|	Second case, this case allows the user to withdraw from the saving account.
				do
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					cout << endl << setfill(' ') << setw(35) << "Enter the amount to withdraw: ";
					cin >> money;

					if (cin.fail() || money > balance) {
						error();
					}

				} while (cin.fail() || money > balance);

				if (money <= balance)		//	|	Checks to see if the amount being withdrawed is less than the balance to avoid negative numbers.
				{
					balance -= money;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout << setfill(' ') << setw(31) << "| Withdraw was successful." << endl << setfill(' ') << setw(26) << "| Current balance is " << balance << endl << endl;
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout << setfill(' ') << setw(31) << "| Error, Not Enough Money!" << endl << setfill(' ') << setw(26) << "| Current balance is " << balance << endl << endl;
				}
				
				break;



			case 'x': case 'X':		//	|	Third case, this case allows the user to exit the savings menu.

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << endl << setfill(' ') << setw(38) << "| End of service for sub-account " << accNum << endl;
				break;


			default:
				check = true;
				break;
			}

		} while (!(choice == 'x' || choice == 'X'));
	}

};

#endif



