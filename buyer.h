#ifndef BUYER_H
#define BUYER_H

#include <string>
#include <iostream>
#include "bank_customer.h"

using namespace std;

class Buyer {
protected: 
    int id;
    string name;
    string address;
    string phoneNumber;
    BankCustomer &account; 

public:
    Buyer(int id, const string& name, const string& address, const string& phone, BankCustomer &account)
        : id(id), name(name), address(address), phoneNumber(phone), account(account) {}

    virtual ~Buyer() = default;

    int getId() const { return id; }
    string getName() const { return name; }
    string getAddress() const { return address; }
    string getPhoneNumber() const { return phoneNumber; }
    BankCustomer& getAccount() { return account; }
    int getBankAccountId() const { return account.getId(); }

    void setId(int newId) { id = newId; }
    void setName(const std::string& newName) { name = newName; }
    void setAddress(const std::string& newAddress) { address = newAddress; }
    void setPhoneNumber(const std::string& newPhone) { phoneNumber = newPhone; }

    // Fungsi virtual untuk menampilkan detail
    virtual void displayDetails() const {
        cout << "--- Buyer Details ---" << endl;
        cout << "User ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "--- Bank Account Info ---" << endl;
        account.printInfo();
        cout << "-----------------------" << endl;
    }
};

#endif 