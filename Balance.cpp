#include <iostream>
#include <sstream>
#include <ctime>
#include <unistd.h>
#include <curl/curl.h>
#include "Balance.h"

using namespace std;

Balance::Balance() {}
Balance::~Balance() {
    node *tmp = new node();
    tmp = head;
    while (tmp->next != NULL) {
        node *toDelete = tmp;
        tmp = tmp->next;
        delete toDelete;
    }
}
void Balance::setLoginInfo() {
    cout << "Enter IdentiKey: ";
    string name;
    getline(cin, name);
    string pass = getpass("Enter Password: ");
    username = name;
    password = pass;
}
void Balance::logIn() {
    string postData =
    "name="+username+
    "&pass="+password+
    "&form_build_id=form-s7kSHZ9fLpU7xXn3ZxDC79ZfEcAkU0168N161pNZRu8"
    "&form_id=user_login"
    "&op=Log in";
    cout << "\nLogging in and fetching data from oncampus.colorado.edu...\n" << endl;

    curl_global_init(CURL_GLOBAL_ALL);
    CURL * myHandle = curl_easy_init();
    string readBuffer;

    curl_easy_setopt(myHandle, CURLOPT_USERAGENT, "Mozilla/4.0");
    curl_easy_setopt(myHandle, CURLOPT_AUTOREFERER, 1 );
    curl_easy_setopt(myHandle, CURLOPT_FOLLOWLOCATION, 1 );
    curl_easy_setopt(myHandle, CURLOPT_COOKIEFILE, "");

    curl_easy_setopt(myHandle, CURLOPT_URL,
        "https://oncampus.colorado.edu/user/login");
    curl_easy_setopt(myHandle, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(myHandle, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_perform( myHandle );

    curl_easy_setopt(myHandle, CURLOPT_REFERER,
        "https://oncampus.colorado.edu/user/login");
    char *data=&postData[0]; //
    curl_easy_setopt(myHandle, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(myHandle, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(myHandle, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_perform( myHandle );
    curl_easy_cleanup( myHandle );
    html = readBuffer;
    buildLinkedList();
}
size_t Balance::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
void Balance::setMealPlan() {

    string command;
    while (command != "19" && command != "15") {
        cout << "Do you have the 19 or 15 meal per week Plan? (Enter: 19 or 15): ";
        getline(cin, command);
    }
    if (command == "19") {
        meal19Plan = true;
    }
    else {
        meal19Plan = false;
    }
}
void Balance::setMealPlan(int size) {
    bool meal19Plan = true;
}
void Balance::buildLinkedList() {
    string i;
    stringstream ss(html);
    node *current = new node();
    head = current;
    while (ss>>i) {
        node *insert = new node();
        current->word = i;
        current->next = insert;
        current = insert;
    }
}
bool Balance::loginError() {
    node *tmp = new node();
    tmp = head;
    bool found = false;
    while (tmp->next != NULL && !found) {
        if (tmp->word == "<title>OnCampus</title>") {
            found = true;
        }
        tmp = tmp->next;
    }
    return !found;
}
int Balance::getSwipes() {
    node *tmp = new node();
    tmp = head;
    while (tmp->word != "Plan") {
        tmp = tmp->next;
    }
    string swipeStr = tmp->next->next->word;
    swipeStr = swipeStr.substr(0,(swipeStr.length()-3));
    return stoi(swipeStr);
}
float Balance::getMunch() {
    node *tmp = new node();
    tmp = head;
    while (tmp->word != "Money") {
        tmp = tmp->next;
    }
    string munchStr = tmp->next->next->word;
    munchStr = munchStr.substr(1, (munchStr.length()-6));
    return stof(munchStr);
}
float Balance::getCampus() {
    node *tmp = new node();
    tmp = head;
    while (tmp->word != "Cash") {
        tmp = tmp->next;
    }
    string campusStr = tmp->next->next->word;
    campusStr = campusStr.substr(1,(campusStr.length()-3));
    return stof(campusStr);
}
string Balance::getName() {
    node *tmp = new node();
    tmp = head;
    while (tmp->word != "views-field-field-first-name\">") {
        tmp = tmp->next;
    }
    string first = tmp->next->next->word;
    first = first.substr(22, first.length());
    string last = tmp->next->next->next->word;
    last = last.substr(0, last.length()-6);
    return first + " " + last;
}
int Balance::daysLeft() {
    time_t currentUnix = time(nullptr);
    int endSemesterUnix = 1462406400;
    int diffUnix = endSemesterUnix-currentUnix;
    int numDays = diffUnix/60/60/24;
    return numDays;
}
float Balance::munchPerDay() {
    float munchPerDay = getMunch()/(daysLeft()*1.0);
    return munchPerDay;
}
float Balance::munchPerDayPast() {
    time_t currentUnix = time(nullptr);
    int startSemesterUnix = 1452470400;
    int diffUnix = currentUnix - startSemesterUnix;
    float munchPast = 0;
    if (meal19Plan == true) {
        munchPast = 150.00-getMunch();
    }
    else {
        munchPast = 200.00-getMunch();
    }
    float munchPerDayPast = munchPast/(diffUnix/60/60/24);
    return munchPerDayPast;
}
float Balance::ratioMunchPerDay() {
    float ratio = munchPerDayPast()/munchPerDay();
    return ratio;
}
void Balance::reset() {
    node *tmp = new node();
    tmp = head;
    while (tmp->next != NULL) {
        node *toDelete = tmp;
        tmp = tmp->next;
        delete toDelete;
    }
    head = NULL;
    username = "";
    password = "";
    html = "";
}
void Balance::setHtml(string _html) {
    html = _html;
}
