#include <iostream>
#include <fstream>
#include <iomanip>
#include <curl/curl.h>
#include "Balance.h"

using namespace std;

int main(int argv, char *argc[]) {
    if (argv > 1 && strcmp(argc[1], "test") == 0) { // for those w/o proper account
        ifstream file;
        file.open("testHtml.txt");
        string tmp;
        string fileContents;
        if (file.good()) {
            while(getline(file, tmp)) {
                fileContents = fileContents + tmp;
            }
        }
        Balance balance = Balance();
        balance.setHtml(fileContents);
        balance.setMealPlan(19);
        balance.buildLinkedList();
        cout << fixed;
        cout << setprecision(2);
        cout << "-------------------------------------" << endl;
        cout << "Balances for : " << balance.getName() << endl;
        cout << "-------------------------------------" << endl;
        cout << "Number of meal swipes left: " << balance.getSwipes() << endl;
        cout << "Amount of munch money available: $" << balance.getMunch() << endl;
        cout << "Amount of campus cash available: $" << balance.getCampus() << endl;
        cout << "Number of days left in semester: " << balance.daysLeft() << endl;
        cout << "Munch money that can be used per day: $" << balance.munchPerDay() << endl;
        cout << "Munch money used per day in past: $" << balance.munchPerDayPast() << endl;
        cout << "Ratio of past munch per day and current: " << balance.ratioMunchPerDay() << endl;
        cout << "-------------------------------------" << endl;
    }
    else {
        Balance balance = Balance();
        balance.setMealPlan();
        balance.setLoginInfo();
        balance.logIn();
        while (balance.loginError() == true) {
            cout << "That IdentiKey/Password returned an invalid page.  Let's try again." << endl;
            cout << "~~~~~~~~~~~~~~~~~" << endl << endl;
            balance.reset();
            balance.setLoginInfo();
            balance.logIn();
        }
        cout << fixed;
        cout << setprecision(2);
        cout << "-------------------------------------" << endl;
        cout << "Balances for : " << balance.getName() << endl;
        cout << "-------------------------------------" << endl;
        cout << "Number of meal swipes left: " << balance.getSwipes() << endl;
        cout << "Amount of munch money available: $" << balance.getMunch() << endl;
        cout << "Amount of campus cash available: $" << balance.getCampus() << endl;
        cout << "Number of days left in semester: " << balance.daysLeft() << endl;
        cout << "Munch money that can be used per day: $" << balance.munchPerDay() << endl;
        cout << "Munch money used per day in past: $" << balance.munchPerDayPast() << endl;
        cout << "Ratio of past munch per day and current: " << balance.ratioMunchPerDay() << endl;
        cout << "-------------------------------------" << endl;
    }
    return 0;
}
