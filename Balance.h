#ifndef BALANCE_H
#define BALANCE_H
#include <curl/curl.h>

struct node {
    std::string word;
    node *next;
};

class Balance {
    private:
        std::string username;
        std::string password;
        std::string html;
        node *head;
        bool meal19Plan;
        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
    public:
        std::string test;
        Balance();
        ~Balance();
        void setLoginInfo();
        void logIn();
        bool loginError();
        void setMealPlan();
        void setMealPlan(int size);
        void buildLinkedList();
        int getSwipes();
        float getMunch();
        float getCampus();
        std::string getName();
        int daysLeft();
        float munchPerDay();
        float munchPerDayPast();
        float ratioMunchPerDay();
        void reset();
        void setHtml(std::string _html);
};

#endif
