//
// Created by musab on 5/13/17.
//
#include <iostream>
#include <string.h>
#include "Customer.h"
using namespace std;
Customer::Customer(int id, string f, string l) {
    firstName = f;
    lastName = l;
    this->id = id;
    accountCounter = 0;
    headAcc = NULL;
}
Customer::~Customer() {
    AccountNode *cur = headAcc;
    while(cur!=NULL){
        AccountNode *temp = cur;
        cur = cur->next;
        delete temp;
        headAcc = cur;
    }
}
Customer::Customer(const Customer &c) {
    this->accountCounter = c.accountCounter;
    this->id = c.id;
    this->firstName = c.firstName;
    this->lastName = c.lastName;
    if (c.headAcc == NULL)
        headAcc = NULL;  // original list is empty
    else {
        // copy first node
        headAcc = new AccountNode;
        headAcc->item = c.headAcc->item;
        headAcc->accountId = c.headAcc->accountId;
        // copy rest of list
        AccountNode *newPtr = headAcc;  // new list ptr

        for (AccountNode *origPtr = c.headAcc->next;
             origPtr != NULL;
             origPtr = origPtr->next){
            newPtr->next = new AccountNode;
            newPtr = newPtr->next;
            newPtr->item = origPtr->item;
            newPtr->accountId = origPtr->accountId;
        }
        newPtr->next = NULL;
    }
}
void Customer::operator=(const Customer &c) {
    this->accountCounter = c.accountCounter;
    this->id = c.id;
    this->firstName = c.firstName;
    this->lastName = c.lastName;
    if (c.headAcc == NULL)
        headAcc = NULL;  // original list is empty
    else {
        // copy first node
        headAcc = new AccountNode;
        headAcc->item = c.headAcc->item;
        headAcc->accountId = c.headAcc->accountId;
        // copy rest of list
        AccountNode *newPtr = headAcc;  // new list ptr

        for (AccountNode *origPtr = c.headAcc->next;
             origPtr != NULL;
             origPtr = origPtr->next){
            newPtr->next = new AccountNode;
            newPtr = newPtr->next;
            newPtr->item = origPtr->item;
            newPtr->accountId = origPtr->accountId;
        }
        newPtr->next = NULL;
    }
}
bool Customer::isSame(const Customer *c) const {
    if(c->lastName != this->lastName)
        return false;
    else {
        if (c->firstName == this->firstName)
            return true;
        else
            return false;
    }
}
bool Customer::isEmpty() const {
    return (headAcc==NULL);
}
//add an account to customer
void Customer::addAccount(const double deposit, int &accountId){
    AccountNode *cur = headAcc;
    AccountNode* newAcc = new AccountNode;
    //newAcc->accountId=++accountCounter;
    newAcc->item = deposit;
    //if list is empty:
    if(cur==NULL){
        headAcc = newAcc;
        newAcc->next = NULL;
        newAcc->accountId = accountId;
        accountCounter++;
        return;
    }
    //else if list is not empty:
    else{
        while(cur!=NULL){
            if(cur->next==NULL){//end of the list
                cur->next = newAcc;
                newAcc->next = NULL;
                newAcc->accountId = accountId;
                accountCounter++;
                //cout<<"Account "<<newAcc->accountId<<" added for customer "<< this->id<<endl;
                return;
            }
            else{
                cur = cur->next;
            }
        }
    }
}
//delete account from customer
void Customer::deleteAccount(const int accountId, bool &success){
    AccountNode *cur = headAcc;
    AccountNode *prev = NULL;
    //find account:
    while(cur!=NULL){
        if(cur->accountId==accountId){
            AccountNode* temp = cur;
            if(cur==headAcc){
                cur = cur->next;
                headAcc = cur;
                delete temp;
                success = true;
                accountCounter--;
                return;
            }
            else{
                prev -> next= cur -> next;
                cur = cur->next;
                delete temp;
                success = true;
                accountCounter--;
                return;
            }
        }
        else{
            prev = cur;
            cur = cur->next;
        }
    }
    success = false;
}
void Customer::showAccounts(bool &exist) const{
    AccountNode *cur = headAcc;
    if(cur==NULL) exist = false;
    else exist = true;
    while(cur != NULL){
        cout<<cur->accountId<<"\t\t"<< this->id<<"\t\t\t"<< this->firstName<<" "<<this->lastName<<"\t\t\t"<<cur->item<<endl;
        cur = cur->next;
    }
}
void Customer::showAccounts2() const {
    AccountNode *cur = headAcc;
    while(cur != NULL){
        cout<<cur->accountId<<"\t\t"<<cur->item<<endl;
        cur = cur->next;
    }
}