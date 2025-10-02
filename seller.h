#pragma once
#include "buyer.h"
#include "item.h"
#include <string>
#include <vector>
#include <iostream>

class Seller : public Buyer {
private:
    vector<Item> items;

public:
    Seller(int id, const string& name, const string& address, const string& phone, BankCustomer &account)
        : Buyer(id, name, address, phone, account) {}

    void addNewItem(int newId, const std::string& newName, int newQuantity, double newPrice) {
        Item newItem(newId, newName, newQuantity, newPrice);
        items.push_back(newItem);
    }

    void displayDetails() const override {
        cout << "--- Seller Details ---" << endl;
        cout << "User ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "--- Bank Account Info ---" << endl;
        account.printInfo();
        cout << "--- Items in Stock: " << items.size() << " ---" << endl;
        for (const auto& item : items) {
            cout << "  - Item ID: " << item.getId() << ", Name: " << item.getName() << ", Qty: " << item.getQuantity() << ", Price: " << item.getPrice() << endl;
        }
        cout << "------------------------" << endl;
    }
};