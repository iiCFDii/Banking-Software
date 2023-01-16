#ifndef SUB_H
#define SUB_H
#include <iostream>
#include <string>
using namespace std;

class subAcc        //  |   This is the sub account class, it is used in the savings and checking accounts classes.
{


protected:
    int balance;        //  |   Variable for the balance in the sub account.
    string accNum;      //  |   Variable for the account number associated with the sub account.


public:

    subAcc()        //  |   default constructor
    {
        balance = 0;
        accNum = "N/A";
    }

    subAcc(string name, int bal)        //  |    This allows the variables to be updated.
    {
        balance = bal;
        accNum = name;
    }

    void setNum(string name) { accNum = name; }     //  |   sets the account number.
    void setBal(int bal) { balance = bal; }         //  |   sets the balance.   

    string getNum() { return accNum; }      //  |   returns the account number.
    int getBal() { return balance; }        //  |   returns the balance.

    void printSubAcc()      //  | prints the sub account at its base form.
    {
       
        cout << endl << endl << setfill(' ') << setw(27) << "| Sub-account number: " << accNum << endl << setfill(' ') << setw(16) << "| Balance: " << balance << endl << endl;
        
    }

    void error() {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "Error! Bad input! Please Try again!" << endl;
        cin.clear();
        cin.ignore(128, '\n');
    }
   
};

#endif