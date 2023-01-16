#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
using namespace std;

class customer      //  |   This is the customer class, that holds all customer attributes.
{
private:
    string fName;   //  |   Variable for customer first name.
    string lName;   //  |   Variable for cusomter last name.
    string ssn;     //  |   Variable for customer social security number.

public:
    customer()      //  |   Initializes variables.
    {
        ssn = "000-00-0000";
        fName = "Chris";
        lName = "Ciobanu";
    }

    customer(string ssn, string name1, string name2)        //  |   Allows for variables to be updated.
    {
        fName = name1;
        lName = name2;
        ssn = ssn;
        
    }

    void setFirstName(string name) { fName = name; }    //  |   Sets the first name.
    void setLastName(string name) { lName = name; }     //  |   Sets the last name.
    void setSSN(string ssn) { ssn = ssn; }              //  |   Sets the social security number.


    string getFirstName() { return fName; }     //  |   Returns the first name.
    string getLastName() { return lName; }      //  |   Returns the last name.
    string getSSN() { return ssn; }             //  |   Returns the social security number.


};

#endif