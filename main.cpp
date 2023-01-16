/* 
Christopher Ciobanu
Professor Yousefi
Comp 53 Data Structures
2/22/20

Project 1 - Bank

***** Make sure to expand the window to see all comments, some are pushed back to look neater*****
*/

#include <iostream>			//	|
#include <string>			//	|
#include <limits>			//	| 	All the libraries needed for the program to work.
#include <iomanip>			//	|	
#include <windows.h>		//	| 

#include "BankAcc.h"		//	|
#include "saving.h"			//	|	All the header files that the program references back to in the code.
#include "checking.h"		//	|
#include "customer.h"		//	|
using namespace std;

string name;				//	|
string address;				//	|	The variables used to set up the Banks' name, address and working hours.
string hours;				//	|


static unsigned int bankAccNum = 10000;		//	variable for the bank account number, starts at 10000.

void BankInfo()															//	|	Collects the information to set up the Bank, using the variables defined earlier.
{																		//	|
	system("color B1");													//	|	This line sets the background of the console to blue.
																		//	|					
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);		//	|	This speicifc line, and all lines similar to it set the color of the outputed text after it to a certain color.
    cout << "Enter the name of the bank: ";								//	|	
    getline(cin, name);													//	|
    cout << "Enter the address of the bank: ";							//	|			
    getline(cin, address);												//	|
    cout << "Enter the working hours of the bank: ";					//	|
    getline(cin, hours);												//	|
	cout << endl << endl;												//	|
}

char Menu()		//	|	This is the main menu for the Bank, allows the user to traverse various functions.
{
	subAcc error1;
    char choice;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "Eligible services for " << name << endl << setfill( ' ' ) << setw(35) << "A -- Number of Bank-Accounts" << endl << setfill(' ') << setw(37) <<"S -- Number of Saving-Accounts" << endl << setfill(' ') << setw(39) << "H -- Number of Checking-Accounts" << endl
		<< setfill(' ') << setw(29) <<"O -- Open Bank-Account" << endl << setfill(' ') << setw(31) << "C -- Close Bank Account "<< endl << setfill(' ') << setw(31) << "M -- Modify Bank-Account" << endl << setfill(' ') << setw(34) <<  "D -- Detailed Bank-Accounts" << endl
		<< setfill(' ') << setw(72) << "B -- Brief Bank-Accounts Info Sorted Based on Aggregated Balances" << endl << setfill(' ') << setw(16) << "X -- Exit" << endl  << "Please enter your selection:";

    cin >> choice;

    while (cin.fail() || ((choice != 'A') && (choice != 'a') && (choice != 'S') && (choice != 's') && (choice != 'H') && (choice != 'h') && (choice != 'O') && (choice != 'o') && (choice != 'C') && (choice != 'c') && (choice != 'M') && (choice != 'm') && (choice != 'D') && (choice != 'd') && (choice != 'B') && (choice != 'b') && (choice != 'X') && (choice != 'x')))
    {
		error1.error();				//	|  This sections validates the users input, and if the user inputs an incorrect menu choice, then they are prompted as such.
        cin >> choice;														
    }	

    return choice;
}

int accountPartiton(vector <bankAcc>& cityVec, int i, int k) {			//	| This is the account parition, which is used in the quick sort algorithm for the account vector
	int l = 0;															//	| This function is a quick sort algorithm, similar to the one we did in the lab, used to order the accounts from smallest balance to largest.
	int h = 0;
	int  midpoint = 0;
	bankAcc pivot;
	bankAcc temp;
	bool done = false;
	midpoint = i + (k - i) / 2;
	pivot = cityVec[midpoint];
	l = i;
	h = k;
	while (!done) {

		while (cityVec[l].getSubAccBal() < pivot.getSubAccBal())
		{
			++l;
		}
		while (pivot.getSubAccBal() < cityVec[h].getSubAccBal())
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
void accQuickSort(vector <bankAcc>& cityVec, int l, int u) {		//	| This uses the accountPartition above to actually sort the vector from smallest balance to largest balance.
	int j = 0;
	if (l >= u)
	{
		return;
	}
	j = accountPartiton(cityVec, l, u);
	accQuickSort(cityVec, l, j);
	accQuickSort(cityVec, j + 1, u);
}


	int main()					//	|  Main functions that ties together all the headers and functions
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		cout << "Welcome to the wonderful Bank Program, steadily crafted by none other than the great Chris Ciobanu!" << endl << "Prepare yourself to really feel the coding prowess and a wonderful, immersive, envornoment created in none other than c++!   ;)" << endl << "Click any button to Dive in!" << endl << "**Colors used in this program are VIBRANT**" << endl << endl;
		system("pause");

		BankInfo();				//	|  Calls the bankInfo function from above in order to set up the Bank.

		char choice = 'N';			//	|	This variable will be used for the users choice when using the menu.
		bool invalid = false;		//	|	This variable will be used to check if the user input is correct or not	.
		int totBal = 0;				//	|	This variable will be used later on to calculate the totla balance of the bank .
		int numCheck;				//	|	This variable will be used later on output how many total checking accounts their are.
		int numSave;				//	|	This variable will be used to output how many total saving accounts their are.
		bool found;					//	|	This variable will be used to tell if an account has been found or not when searching in the menu.
		string close;				//	|	This variable will be used to search for accounts that are being requested for close.
		string modify;				//	|	This variable will be used to search for accounts being requested for modification.
		vector <bankAcc> account;	//	|	This vector will be used to hold all bank accounts
		bankAcc BankAccount;		//	|	This variable will be used when creating a new Bank account
		

		do							//	|	This whole loop is what loops the main menu until the user opts to exit.
		{

			choice = Menu();		//	|	assings choice equal to the choice that is returned from the menu function above.
			
			cin.clear();			
			cin.ignore(128, '\n');

			switch (choice)			//	|	The switch that allows the user to pick between different menu options.
			{
			case 'A': case 'a':		//	|	First case, tells the user how manu banks accounts have been created.

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				cout << endl << "| The number of Bank Accounts are " << account.size() << endl << endl;
				
				break;



			case 'S': case 's':		//	|	Second case, tells the user the number of saving account created.

				numSave = 0;
				for (int i = 0; i < account.size(); ++i)
				{
					numSave += account[i].getSavAccSize();
				}

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				cout << endl << "| The number of Saving-Accounts is " << numSave << endl << endl;
				
				break;





			case 'H': case 'h':		//	|	Third case, tells the user the number of checking accounts created.

				numCheck = 0;
				for (int i = 0; i < account.size(); ++i)
				{
					numCheck += account[i].getCheckAccSize();
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				cout << endl << "| The number of Checking-Accounts is " << numCheck << endl << endl;
				
				break;



			case 'O': case 'o':		//	|	Fourth case, this case creates a new bank account.

				BankAccount.createNewAcc(bankAccNum);		//	|	Calls the function that creates a new bank account.
				bankAccNum += 1;							//	|	Adds 1 to the total number of bank accounts.
				account.push_back(BankAccount);				//	|	Adds the new bank account to the vector that stores all the bank accounts.
				account.back().bankAccMenu();				//	|	Calls the function that puts the menu for bank accounts on the console, specifically for the account that was just created.
				
				break;



			case 'C': case 'c':		//	|	Fifth case, this case closes bank accounts.

				found = false;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				cout << endl << "| Enter the bank account number to be closed: ";
				cin >> close;

				for (int i = 0; i < account.size(); ++i)		//	|	This for loop searches through the vector that holds all the banks accounts
				{												//	|
					if (close == account[i].getAccNum())		//	|	Once the name that user inputed matches a bank account in the vector...
					{											//	|	
						found = true;							//	|	...the found variable is set to true
						account[i].closeSubAcc();				//	|	and all the sub accounts associated with it are cleared.
						account.erase(account.begin() + i);		//	|	Then the account itself is erased from the vector.
					}
				}

				if (found)		//	| This if statement will state to the user if the bank account was successfully closed or not.
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout << endl << "| Bank Account " << close << " successfully closed." << endl;
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout << endl << "| Bank Account " << close << " not found. Please try again." << endl;
				}
				
				break;



			case 'M': case 'm':		//	|	Sixth case, this case allows the user to modify existing bank accounts.

				found = false;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				cout << endl << " Enter the bank account number to be modified: ";
				cin >> modify;

				for (int i = 0; i < account.size(); ++i)		//	|	Thi for loop searches through all the bank accounts
				{												
					if (modify == account[i].getAccNum())		//	|
					{											//	|	If the bank account is found then the menu for that bank account is displayed
						found = true;							//	|
						account[i].bankAccMenu();				//	|
					}
				}


				if (!found)		//	|	If the bank account is not found then a message is displayed to the user telling so.
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout << endl << "| Bank Account " << close << " not found. Please try again." << endl;	
				}
				
				break;



			case 'D': case 'd':		//	|	Seventh case, this case gives detailed information on the bank and all the accounts within the bank.

				accQuickSort(account, 0, account.size() - 1);	//	| Calls to the quit sort function and organizes the accounts by their balance from smallest to greatest.
				for (int i = 0; i < account.size(); ++i)		//	|	This for loop gets the total balance for all sub accounts.
				{
					totBal += account[i].getSubAccBal();
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				//	|	The line below lists all the details of the bank.
				cout << endl << "| Bank Name: " << name << endl << "| Bank Address: " << address << endl << "| Bank Working Address: " << hours << endl << "| Aggregated Balance: " << totBal << endl << "| Consists of " << account.size() << " Bank Accounts" << endl << endl;

				for (int i = 0; i < account.size(); ++i)		//	|	This for loop prints out all the accounts and their associated info.
				{
					account[i].printAccInfo();
				}
			
				break;



			case 'B': case 'b':		//	|	Eigth case, this case gives brief info on all the accounts in the bank, and is sorted by their aggregated balance.
				
				accQuickSort(account, 0, account.size() - 1);	//	|	Calls to the quit sort function and organizes the accounts by their balance from smallest to greatest.
				
				cout << endl << "| Bank Name: " << name << endl << "| Bank Address: " << address << endl << "| Bank Working Address: " << hours << endl << "| Aggregated Balance: " << totBal << endl << "| Consists of " << account.size() << " Bank Accounts" << endl << endl;
				
				for (int i = 0; i < account.size(); ++i)		//	|	This for loop simply prints out the account number and it's total balance in the order of smallest to largest balance.
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					cout << endl << "| Account Number : " << account[i].getAccNum() << " with " << account[i].getSubAmount() << " Sub-accounts, has an" << " Aggregated Balance of: " << account[i].getSubAccBal() << endl << endl;
				}
				

				break;



			case 'X': case 'x':		//	|	Ninth case, this case exits the program lets the user know
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << endl << "| End of service for bank " << name << endl;
				   
				break;


			default:		//	| The default case, does nothing except said the invalid vairable to true.
				invalid = true;
				break;
			}

		} while (!(choice == 'x' || choice == 'X'));		//	| While the user does not choose x, the menu will continue to loop



		system("Pause");		//	| Pauses the console
		return 0;				//	| Tells the program it can terminate.
	}