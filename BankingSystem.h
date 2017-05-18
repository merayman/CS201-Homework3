//
// Created by musab on 5/12/17.
//

#ifndef HW3_BANKINGSYSTEM_H
#define HW3_BANKINGSYSTEM_H

#include <iostream>
#include <string.h>
#include "Customer.h"

using namespace std;
class BankingSystem{
public:
    //Default Constructor
    BankingSystem();
    //Destructor
    ~BankingSystem();
    //add a customer
    void addCustomer( const int customerId, const string firstName, const string lastName );
    //delete a customer
    void deleteCustomer( const int customerId );
    //add an account for a customer and returns account id
    int addAccount( const int id, const double deposit );
    //delete an account for a customer
    void deleteAccount( const int accountId );
    //Show the list of all accounts
    void showAllAccounts();
    //Show the list of all customers
    void showAllCustomers();
    //Show detailed information about a particular customer
    void showCustomer( const int customerId );

private:

    struct CustNode{
        //item of linked list
        Customer* customer;
        CustNode* next;
    };

    CustNode *headCust;
    Customer* findCustomer(const int customerId, bool &found) const;
    int accounts;
    void helperDeleteCustomer(const int customerId);
};
#endif //HW3_BANKINGSYSTEM_H