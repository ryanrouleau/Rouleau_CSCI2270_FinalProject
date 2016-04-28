#include <iostream>
#include <fstream>
#include <iomanip>
#include <curl/curl.h>
#include <cstring>
#include "Balance.h"

using namespace std;

int main(int argv, char *argc[]) {
    if (argv > 1 && argc[1]=="test") { // command line arg for those w/o proper account
        ifstream file;
        file.open("testHtml.txt");
        string tmp;
        string fileContents;
        if (file.good()) {
            while(getline(file, tmp)) {
                fileContents = fileContents + tmp; // adding file contents to string one line at a time
            }
        }
        Balance balance = Balance(); // creating new balance object
        balance.setHtml(fileContents); // placing the provided html file into the object and building a linked list
        balance.setMealPlan(19); // my meal plan has 19 per week, so we set it as 19
        cout << fixed; // cout << fixed; and cout << setprecision; sets the output of floats to two decimal places
        cout << setprecision(2);
        cout << "---------------------------------------------" << endl;
        cout << "Balances for : " << balance.getName() << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Number of meal swipes left: " << balance.getSwipes() << endl;
        cout << "Amount of munch money available: $" << balance.getMunch() << endl;
        cout << "Amount of campus cash available: $" << balance.getCampus() << endl;
        cout << "Number of days left in semester: " << balance.daysLeft() << endl;
        cout << "Munch money that can be used per day: $" << balance.munchPerDay() << endl;
        cout << "Munch money used per day in past: $" << balance.munchPerDayPast() << endl;
        cout << "Ratio of past munch per day and current: " << balance.ratioMunchPerDay() << endl;
        cout << "---------------------------------------------" << endl;
    }
    else {
        cout << "Note that absolutely no login information is stored and that all info is transfered over secure https" << endl;
        cout << "This program does not break any apparent rules set by OIT." << endl << endl << endl;
        Balance balance = Balance(); // creating balance object
        balance.setMealPlan(); // prompting user and getting their meal plan (15/19 swipes)
        balance.setLoginInfo(); // prompting for user's IdentiKey/Password
        balance.logIn(); // securely loggin into oncampus.colorado.edu and grabbing the html once logged in
        while (balance.loginError() == true) { // loops until the user provides credentials that work
            cout << "That IdentiKey/Password combination returned an invalid login page.  Let's try again." << endl;
            cout << "~~~~~~~~~~~~~~~~~" << endl << endl;
            balance.reset();
            balance.setLoginInfo();
            balance.logIn();
        }
        cout << fixed; // cout << fixed; and cout << setprecision; sets the output of floats to two decimal places
        cout << setprecision(2);
        cout << "---------------------------------------------" << endl;
        cout << "Balances for : " << balance.getName() << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Number of meal swipes left: " << balance.getSwipes() << endl;
        cout << "Amount of munch money available: $" << balance.getMunch() << endl;
        cout << "Amount of campus cash available: $" << balance.getCampus() << endl;
        cout << "Number of days left in semester: " << balance.daysLeft() << endl;
        cout << "Munch money that can be used per day: $" << balance.munchPerDay() << endl;
        cout << "Munch money used per day in past: $" << balance.munchPerDayPast() << endl;
        cout << "Ratio of past munch per day and current: " << balance.ratioMunchPerDay() << endl;
        cout << "---------------------------------------------" << endl;
    }
    return 0;
}
