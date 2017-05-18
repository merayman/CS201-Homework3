//
// Created by musab on 5/14/17.
//

#include <iostream>
#include <string.h>
#include "BankingSystem.h"

using namespace std;

BankingSystem::BankingSystem() {
    headCust = NULL;
    accounts = 1;
}
BankingSystem::~BankingSystem() {
    CustNode *cur= headCust;
    while(cur!=NULL){
        helperDeleteCustomer(cur->customer->id);
        cur = cur->next;
    }
}
void BankingSystem::addCustomer(const int customerId, const string firstName, const string lastName) {
    Customer *newCustomer = new Customer(customerId, firstName, lastName);
    //if head is NULL:
    if(headCust == NULL){
        CustNode *newNode = new CustNode;
        newNode->customer = newCustomer;
        headCust = newNode;
        newNode->next = NULL;
        cout<<"Customer "<<customerId<<" has been added"<<endl;
    }
    else{
        //if customer already exists:
        CustNode *cur = headCust;
        //CustNode *prev = NULL;

        while (cur!=NULL){
            if(cur->customer->isSame(newCustomer)||cur->customer->id==customerId){
                if(cur->customer->isSame(newCustomer))
                    cout<<"Customer "<<newCustomer->firstName<<" "<< newCustomer->lastName<<" already exists."<<endl;
                else
                    cout<<"Customer "<< customerId<<" "<<" already exists."<<endl;


                delete newCustomer;
                newCustomer = NULL;
                return;
            }
                cur = cur->next;
        }
        cur = headCust;
        //if customer does not already exist:
        while(cur!=NULL){

            //insert into middle or head:
            if(lastName > cur->customer->lastName && (cur->next != NULL) &&lastName < cur->next->customer->lastName){
                CustNode *newNode = new CustNode;
                newNode->customer = newCustomer;
                newNode->next = cur->next;
                cur->next = newNode;
                cout<<"Customer "<<customerId<<" has been added"<<endl;
                return;
            }
            //insert into last
            else if( cur->next == NULL && lastName > cur->customer->lastName ){
                CustNode *newNode = new CustNode;
                newNode->customer = newCustomer;
                cur->next = newNode;
                newNode->next = NULL;
                cout<<"Customer "<<customerId<<" has been added"<<endl;
                return;
            }
            //insert into before head with 1 noded ll
            else if(cur == headCust && lastName<cur->customer->lastName){
                CustNode *newNode = new CustNode;
                newNode->customer = newCustomer;
                newNode->next = headCust;
                headCust = newNode;
                cout<<"Customer "<<customerId<<" has been added"<<endl;
                return;
            }
            else
                cur = cur->next;
        }

    }
}
void BankingSystem::deleteCustomer(const int customerId) {
    CustNode *cur = headCust;
    CustNode *prev = NULL;
    while(cur!=NULL){
        if(cur->customer->id==customerId){
            CustNode *temp = cur;
            //delete all accounts of customer
            while(cur->customer->headAcc!=NULL) {
                bool dummy;
                int tempAccId = cur->customer->headAcc->accountId;
                cur->customer->deleteAccount(tempAccId,dummy);
            }
            if(cur == headCust){
                cur = cur->next;
                headCust = cur;
                delete temp->customer;
                delete temp;
                cout<<"Customer "<<customerId<<" has been deleted."<<endl;
                return;
            }
            else{
                prev->next =cur->next;
                delete temp->customer;
                delete temp;
                cout<<"Customer "<<customerId<<" has been deleted."<<endl;
                return;
            }
        }
        else {
            prev = cur;
            cur = cur->next;
        }
    }
    cout<<"Customer "<<customerId<<" does not exist."<<endl;
}
int BankingSystem::addAccount(const int customerId, const double deposit) {
    bool found;
    Customer* customer = findCustomer(customerId,found);
    //if customer does not exist
    if(!found) {
        cout<<"Customer "<<customerId<<" does not exist"<<endl;
        return -1;
    }
    //else customer exists:
    else{
        customer->addAccount(deposit,accounts);
        cout<<"Account "<<accounts<<" added for customer "<< customerId <<endl;
        return accounts++;
    }
}
void BankingSystem::deleteAccount(const int accountId){
    CustNode* cur = headCust;
    bool success;
    while(cur != NULL) {
        cur->customer->deleteAccount(accountId,success);
        if(success){
            cout<<"Account "<<accountId<<" has been deleted."<<endl;
            return;
        }
        else
            cur = cur->next;
    }
    cout<<"Account "<<accountId<<" does not exist."<<endl;
}
void BankingSystem::showAllAccounts() {
    CustNode *cur = headCust;
    bool exist = true;
    cout<<"Account id"<<"\t";
    cout<<"Customer id"<<"\t\t";
    cout<<"Customer name"<<"\t\t\t";
    cout<<"Balance"<<endl;
    while(cur!= NULL){
        cur->customer->showAccounts(exist);
        cur = cur->next;
    }
    if(!exist)
        cout<<"There is no account to show."<<endl;
}
void BankingSystem::showAllCustomers() {
    CustNode *cur = headCust;
    if(cur==NULL)
        cout<<"There is no customer to show!"<<endl;
    else{
        cout<<"Customer id"<< "\t\t";
        cout<<"Customer name"<<endl;
        while(cur!=NULL){
            cout<<cur->customer->id<<"\t\t\t";
            cout<<cur->customer->firstName<<" ";
            cout<<cur->customer->lastName<<endl;
            cur = cur->next;
        }
    }
}
void BankingSystem::showCustomer(const int customerId) {
    bool found;
    bool exist;
    Customer *c = findCustomer(customerId,found);
    if(found){
        cout<<"Customer id: "<< c->id<<"\t\t";
        cout<<"Customer name: "<<c->firstName<<" "<<c->lastName<<"\t";
        cout<<"Number of accounts: "<<c->accountCounter<<endl;
        if(c->headAcc!=NULL){
            cout<<"Accounts of this customer: "<<endl;
            cout<<"Account id"<<"\t";
            cout<<"Balance"<<endl;
            c->showAccounts2();
        }
    }
    else{
        cout<<"Customer "<<customerId<<" does not exist."<<endl;
    }
}
//returns Customer pointer and whether is found or not
Customer* BankingSystem::findCustomer(const int customerId,bool &found) const {
    CustNode *cur = headCust;
    found = false;
    while(cur!=NULL && !found){
        if(cur->customer->id==customerId) {
            found = true;
            return (cur->customer);
        }
        cur=cur->next;
    }
    return NULL;
}
void BankingSystem::helperDeleteCustomer(const int customerId) {

        CustNode *cur = headCust;
        CustNode *prev = NULL;
        while(cur!=NULL){
            if(cur->customer->id==customerId){
                CustNode *temp = cur;
                //delete all accounts of customer
                while(cur->customer->headAcc!=NULL) {
                    bool dummy;
                    int tempAccId = cur->customer->headAcc->accountId;
                    cur->customer->deleteAccount(tempAccId,dummy);
                }
                if(cur == headCust){
                    cur = cur->next;
                    headCust = cur;
                    delete temp->customer;
                    delete temp;
                    return;
                }
                else{
                    prev->next =cur->next;
                    cur = cur->next;
                    delete temp->customer;
                    delete temp;
                    return;
                }
            }
            else {
                prev = cur;
                cur = cur->next;
            }
        }
        cout<<"Customer "<<customerId<<" does not exist."<<endl;
}
