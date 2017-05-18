//
// Created by musab on 5/13/17.
//

//#ifndef HW3_CUSTOMER_H
#define HW3_CUSTOMER_H

#include <iostream>
#include <string.h>
using namespace std;
class Customer{
public:
    //Customer();

    Customer(int id, string firstName, string lastName);
    ~Customer();
    Customer( const Customer &c );
    void operator=(const Customer &c);
    int id;
    string firstName;
    string lastName;

    bool isSame(const Customer *c) const;
    bool isEmpty() const;


    int accountCounter;
    void addAccount(const double deposit,int &accountId);
    void deleteAccount(const int accountId, bool &success);
    void showAccounts(bool &exist) const;
    void showAccounts2() const;
    struct AccountNode{
        double item;
        int accountId;
        AccountNode *next;
    };
    AccountNode *headAcc;

};