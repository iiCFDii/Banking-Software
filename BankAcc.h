#pragma once
#ifndef BANKACC_H		//	|	
#define BANKACC_H		//	|	
#include <string>		//	|	All the libraries needed for the program to work.
#include <vector>		//	|	

#include "sub.h"		//	|
#include "checking.h"	//	|	All the header files that the program references back to in the code.
#include "saving.h"		//	|
#include "customer.h"	//	|
using namespace std;

static unsigned int savNum = 1000;		//	| Saving accounts starting number.
static unsigned int checkingNum = 6000;	//	| Checking accounts starting number.

class bankAcc		//	| This is the class that defines what a bank account is.
{

private:
	string accountNum;					//	|	This is the variable for the account number of the bank accounts.
	checking tempCheck;					//	|	This variable is used when creating a new checking account. 
	savings tempSave;					//	|	This variable is used when creating a new savings account.
	customer user1;						//	|	This variable is used when creating a new bank account, specifically to hold the customers info.
	vector <checking> checkingSubV;		//	|	This vector is used to hold all the checking sub accounts.
	vector <savings> savingSubV;		//	|	This vector is used to hold all the saving sub accounts.
	int tempbal;						//	|	This variable is used when calculatung the total balance of the sub accounts later on
        


public:

    bankAcc()		//	|	Initializes account Num.
    {
		accountNum = "BNK1000";
    }

    bankAcc(unsigned int num)		//	|	Sets the account number to have the letters BNK in front of the numbers every time.
    {
		accountNum = "BNK" + to_string(num);
    }

    string getAccNum()		//	|	Returns the account number.
    {
        return accountNum;
    }

    int getSubAmount()		//	|	Returns how many sub accounts their are total.
    {
        int sub = 0;
        sub += checkingSubV.size();
        sub += savingSubV.size();
        return sub;
    }

	int getSubAccBal()		//	|	Returns the total amount of money in all sub accounts.

	{
		int bal = 0;
		for (int i = 0; i < checkingSubV.size(); ++i)
		{
			bal += checkingSubV[i].getBal();
		}
		for (int i = 0; i < savingSubV.size(); ++i)
		{
			bal += savingSubV[i].getBal();
		}
		return bal;
	}

	int getSavAccSize()		//	|	Returns the number of individual saving accounts.
	{
		return savingSubV.size();
	}

	int getCheckAccSize()		//	|	Returns the number of checking accounts.
	{
		return checkingSubV.size();
	}

	void closeSubAcc()		//	|	closes all sub accounts within the bank account.
	{
		checkingSubV.clear();
		savingSubV.clear();
	}

    void createNewAcc(unsigned int num)		//	| This function creates a new bank account.
    {
        customer user;		//	|	variable to hold customer info.
        string fname, lname, ssn;	//	|	variable to hold first name,last name, and social security number.

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << endl;
        cout << setfill(' ') << setw(49) << "Enter the first name of the account holder: ";		//	|	Gets the users first name.
        getline(cin, fname);
       

        cout << setfill(' ') << setw(48) << "Enter the last name of the account holder: ";		//	|	Get the users last name.
        getline(cin, lname);
        

        cout << setfill(' ') << setw(42) << "Enter the SSN of the account holder: ";			//	|	gets the users social security number.
        getline(cin, ssn);
        cout << endl;


        user = customer(fname,lname,ssn);		//	|	Puts the customer info into the user variable.
        accountNum = "BNK" + to_string(num);	//	|	Sets the account number to have BNK before it.
        user1 = user;		// sets the customer infor to user1 variable so it can be used later in the program, outside of this function.

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << setfill(' ') << setw(26) << "| A new Bank Account " << accountNum << " was successfully created." << endl << endl;
    }



	void printAccInfo()		//	|	This function prints all the account info associated with the bank account.
	{
		int tempBal = 0;
		for (int i = 0; i < savingSubV.size(); ++i) 
		{
			tempBal += savingSubV[i].getBal();
		}
		for (int i = 0; i < checkingSubV.size(); ++i)
		{
			tempBal += checkingSubV[i].getBal();
		}

		//	|	Lists out the acount info 
		cout << endl << endl << "| Bank Account Number: " << accountNum << endl << "| Account Holder Full Name: " << user1.getFirstName() << " " << user1.getLastName() << endl << "| Account Holder SSN: " << user1.getSSN() << endl << "| Aggregated Balance: " << tempBal << endl << "| Consists of " << savingSubV.size() + checkingSubV.size() << " Sub-Accounts" << endl << endl;


		for (int i = 0; i < savingSubV.size(); ++i)
		{
			savingSubV[i].printSave();		//	|	Prints the saving account information.
		}

		for (int i = 0; i < checkingSubV.size(); ++i)
		{
			checkingSubV[i].printSubCAccount();		//	|	Prints the checking account info.
		}
	}

	template <typename T>												//	|	Since this function will be used by a two different kinds of classes, I made it arbitrary so it could be used by both
	int accountPartiton(vector <T>& cityVec, int i, int k) {			//	| This is the account parition, which is used in the quick sort algorithm for the account vector
		int l = 0;														//	| This function is a quick sort algorithm, similar to the one we did in the lab, used to order the accounts from smallest balance to largest.
		int h = 0;
		int  midpoint = 0;
		T pivot;
		T temp;
		bool done = false;
		midpoint = i + (k - i) / 2;
		pivot = cityVec[midpoint];
		l = i;
		h = k;
		while (!done) {

			while (cityVec[l].getBal() < pivot.getBal())
			{
				++l;
			}
			while (pivot.getBal() < cityVec[h].getBal())
			{
				--h;
			}
			if (l >= h)
			{
				done = true;
			}
			else {
				temp = cityVec[l];
				cityVec[l] = cityVec[h];
				cityVec[h] = temp;
				++l;
				--h;
			}
		}
		return h;
	}


	template <typename T>
	void accQuickSort(vector <T>& cityVec, int l, int u) {		//	| This uses the accountPartition above to actually sort the vector from smallest balance to largest balance.
		int j = 0;
		if (l >= u)
		{
			return;
		}
		j = accountPartiton(cityVec, l, u);
		accQuickSort(cityVec, l, j);
		accQuickSort(cityVec, j + 1, u);
	}




	void bankAccMenu()		//	|	This function is the menu for the bank account itself.
	{
		char choice = '0';		//	|	Variable for the user choice in the menu.
		bool invalid = false;	//	|	Variable to validate user input.
		bool found;				//	|	Variable used to check if an account was found or not later on.
		string closeAccNum, modAccNum;		//	|	Variables used when closing and modifying accounts.
		subAcc error1;		//	|	used for input validation
		
		do			//	|	This do loop, loops the menu.
		{

			//	|	Bank menu, that allows user to select various functions.
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			cout << endl << "Eligible services for Bank-Account " << accountNum << endl << setfill(' ') << setw(33) << "S -- Open Saving Sub-Account" << endl << setfill(' ') << setw(35) << "C -- Open Checking Sub-Account" << endl 
				<< setfill(' ') << setw(30) << "M -- Modify a Sub-Account" << endl << setfill(' ') << setw(29) << "E -- Close a Sub-Account" << endl << setfill(' ') << setw(77) << "D -- Detailed Bank Account Info Sorted Based on Balances of Sub-Accounts" << endl
				<< setfill(' ') << setw(33) << "B -- Brief Bank Account Info" << endl << setfill(' ') << setw(14) << "X -- Exit" << endl << "Please enter your selection: ";
			cin >> choice;
			
			//	|	Input validation for the menu.
			while (cin.fail() || ((choice != 'S') && (choice != 's') && (choice != 'E') && (choice != 'e') && (choice != 'C') && (choice != 'c') && (choice != 'M') && (choice != 'm') && (choice != 'D') && (choice != 'd') && (choice != 'B') && (choice != 'b') && (choice != 'X') && (choice != 'x'))) 
			{
				error1.error();
				cin >> choice;
			}


			switch (choice)		//	|	Switch function that allows user to choose function.
			{

			case 's': case 'S':		//	|	First case, this case creates a new saving account and adds it to the saving account vector.

				if (savingSubV.size() > 0)
				{
					tempSave.createSavAcc(savNum, false);	//	|	If it is not the first saving account made, first account is set to false.
				}
				else
				{
					tempSave.createSavAcc(savNum, true);	//	|	If this is the first account, first account is set to true.
				}
				savNum += 1;
				savingSubV.push_back(tempSave);		//	|	New saving account added to saving vector.

				break;




			case 'c': case 'C':		//	|	Second case, this case is similar to the last one, it just creates a new checking account.

				tempCheck.createCheckAcc(checkingNum);
				checkingNum += 1;
				checkingSubV.push_back(tempCheck);
				
				break;



			case 'm': case 'M':		//	|	Third case, allows the user to modify a sub account.

				found = false;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				cout << endl << setfill(' ') << setw(50) << "Enter the sub-account number to be modified: " ;
				cin >> modAccNum;

				for (int i = 0; i < checkingSubV.size(); ++i)		//	|	This for loop searches for a checking account within the vector.
				{
					if (modAccNum == checkingSubV[i].getNum())
					{
						found = true;						
						checkingSubV[i].checkMenu();		//	|	once found, brings up the menu for the checking account.
					}
				}

				for (int i = 0; i < savingSubV.size(); ++i)		//	|	This loops searches for a saving account within the vector.
				{
					if (modAccNum == savingSubV[i].getNum())
					{
						found = true;
						savingSubV[i].savMenu();		//	|	Once found displays the menu to the user for saving sub accounts.
					}
				}

				if (!found)		//	|	If the account is not found, displays a message to the user.
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout << endl << setfill(' ') << setw(19) << "| Sub-Account " << closeAccNum << " not found. Please try again." << endl;
				}
				
				break;



			case 'e': case 'E':		//	|	Fourth case, This case allows the user to close a sub account.

				found = false;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				cout << endl << setfill(' ') << setw(49) << "Enter the sub-account number to be closed: " ;
				cin >> closeAccNum;

				for (int i = 0; i < checkingSubV.size(); ++i)		//	|	This for loop searches the checking account vector.
				{
					if (closeAccNum == checkingSubV[i].getNum())
					{
						found = true;
						checkingSubV.erase(checkingSubV.begin() + i);		//	|	Once the checking account is found it is deleted.
					}
				}


				for (int i = 0; i < savingSubV.size(); ++i)		//	|	This for loop searches the saving account vector.
				{
					if (closeAccNum == savingSubV[i].getNum())
					{
						found = true;
						savingSubV.erase(savingSubV.begin() + i);		//	|	Once the saving account is found it is deleted.
					}
				}


				if (!found)		//	|	If the checking or saving account is not found, displays an error message to the user.
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout << endl << setfill(' ') << setw(19) << "| Sub-Account " << closeAccNum << " not found. Please try again." << endl;
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout << endl << setfill(' ') << setw(19) << "| Sub-Account " << closeAccNum << " successfully closed." << endl;
				}
				
				break;


			case 'd': case 'D':		//	|	Fifth case, Gives detailed information on the sub accounts, in the order of their balances.
				if (savingSubV.size() > 0) {
					cout << "| Saving Accounts: ";
				}
				
				if (savingSubV.size() == 0 && checkingSubV.size() == 0) {
					cout << "| No sub-accounts have been created " << endl << endl;
				}

				accQuickSort(savingSubV, 0, savingSubV.size() - 1);		//	|	Orders the saving accounts from smallest balance to largest.

				for (int i = 0; i < savingSubV.size(); ++i)
				{
					savingSubV[i].printSave();
				}

				if (checkingSubV.size() > 0) {
					cout << "| Checking Accounts: " << endl << endl;
				}

				accQuickSort(checkingSubV, 0,checkingSubV.size() - 1);		//	|	Orders the checking accounts from smallest balance to largest.

				for (int i = 0; i < checkingSubV.size(); ++i) 
				{
					checkingSubV[i].printSubCAccount();
				}
				
				break;



			case 'b': case 'B':		//	|	Sixth case, gives brief detail of the bank account.

				tempbal = 0;
				for (int i = 0; i < savingSubV.size(); ++i) 
				{
					tempbal += savingSubV[i].getBal();
				}

				for (int i = 0; i < checkingSubV.size(); ++i)
				{
					tempbal += checkingSubV[i].getBal();
				}

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				
				cout << endl << setfill(' ') << setw(47) << "| Aggregated balance of the bank account: " << accountNum << " with " << savingSubV.size() + checkingSubV.size() << " Sub-Accounts is " << tempbal << endl << endl;
				
				break;



			case 'x': case 'X':		//	|	Seventh case,this case allows the user to exit the bank account menu
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << endl << setfill(' ') << setw(38) << "| End of service for bank account " << accountNum << endl << endl;
				break;

			default:		//	| default case
				invalid = true;
				break;
			}


		} while (!(choice == 'x' || choice == 'X'));
	}


};

#endif