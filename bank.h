#ifndef BANK_H
#define BANK_H

#include "bank_customer.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 

using namespace std;

class Bank{
private:
    string name;
    vector<BankCustomer> accounts;

public:
    Bank(const string& name) : name(name) {}

    BankCustomer& addAccount(int id, const string& customerName, double initialBalance);

    BankCustomer* findAccountById(int id);

    bool removeAccountById(int id);

    const vector<BankCustomer>& getAllAccounts() const;
};

#endif 