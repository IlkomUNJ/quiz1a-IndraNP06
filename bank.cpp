#include "bank.h"

BankCustomer& Bank::addAccount(int id, const string& customerName, double initialBalance) {
    accounts.emplace_back(id, customerName, initialBalance);
    return accounts.back();
}

BankCustomer* Bank::findAccountById(int id) {
    for (auto& account : accounts) {
        if (account.getId() == id) {
            return &account;
        }
    }
    return nullptr; // Mengembalikan null jika tidak ditemukan
}

bool Bank::removeAccountById(int id) {
    auto it = std::remove_if(accounts.begin(), accounts.end(), 
        [id](const BankCustomer& acc) {
            return acc.getId() == id;
        });

    if (it != accounts.end()) {
        accounts.erase(it, accounts.end());
        cout << "Bank account with ID " << id << " successfully removed." << endl;
        return true;
    }
    
    cout << "Failed to remove. Bank account with ID " << id << " not found." << endl;
    return false;
}

const vector<BankCustomer>& Bank::getAllAccounts() const {
    return accounts;
}