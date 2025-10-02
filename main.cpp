#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>

#include "bank.h"
#include "bank_customer.h"
#include "buyer.h"
#include "seller.h"

using namespace std;

enum PrimaryPrompt{LOGIN, REGISTER, EXIT, ADMIN_LOGIN};
enum RegisterPrompt{CREATE_BUYER, CREATE_SELLER, BACK};
enum AdminPrompt{VIEW_ALL_USERS=1, VIEW_USER_DETAILS, SEARCH_USER, CREATE_USER, REMOVE_USER, ADMIN_LOGOUT};

// --- Deklarasi Fungsi Helper Admin ---
void handleAdminMenu(vector<Buyer*>& users, Bank& bank);
void viewAllUsers(const vector<Buyer*>& users);
void viewUserDetails(const vector<Buyer*>& users);
void searchUser(const vector<Buyer*>& users);
void createUser(vector<Buyer*>& users, Bank& bank);
void removeUser(vector<Buyer*>& users, Bank& bank);
void clearInputBuffer();

Bank globalBank("World Digital Bank");
vector<Buyer*> allUsers;
int nextUserId = 1;
int nextBankId = 1;

int main() {
    PrimaryPrompt prompt = LOGIN;
    const string ADMIN_USERNAME = "root";
    const string ADMIN_PASSWORD = "toor";
    string username, password;

    BankCustomer& acc1 = globalBank.addAccount(nextBankId++, "Indra", 1000.0);
    allUsers.push_back(new Buyer(nextUserId++, "Indra", "123 Maple St", "555-0101", acc1));

    BankCustomer& acc2 = globalBank.addAccount(nextBankId++, "Andri", 5000.0);
    allUsers.push_back(new Seller(nextUserId++, "Andri", "456 Oak Ave", "555-0102", acc2));
    
    while (prompt != EXIT) {
        cout << "\n===== MAIN MENU =====\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cout << "4. Admin Login\n";
        cout << "Select an option: ";
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            clearInputBuffer();
            choice = -1; // Opsi tidak valid
        }

        prompt = static_cast<PrimaryPrompt>(choice - 1);
        switch (prompt) {
            case LOGIN:
                cout << "Login selected (Not Implemented)." << endl;
                break;
            case REGISTER:
                cout << "Register selected (Not Implemented)." << endl;
                break;
            case EXIT:
                cout << "Exiting." << endl;
                break;
            case ADMIN_LOGIN:
                cout << "--- Admin Login ---\n";
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;

                if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
                    cout << "Admin login successful!" << endl;
                    handleAdminMenu(allUsers, globalBank);
                } else {
                    cout << "Invalid username or password." << endl;
                }
                break;
            default:
                cout << "Invalid option." << endl;
                break;
        }
    }

    cout << "Cleaning up resources..." << endl;
    for (auto* user : allUsers) {
        delete user;
    }
    allUsers.clear();
    cout << "Cleanup complete. Goodbye!" << endl;

    return 0;
}


void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void handleAdminMenu(vector<Buyer*>& users, Bank& bank) {
    int choice = 0;
    while (choice != ADMIN_LOGOUT) {
        cout << "\n===== ADMIN MENU =====\n";
        cout << "1. View All Buyers & Sellers\n";
        cout << "2. View All Details of Buyers & Sellers\n";
        cout << "3. Search for a User\n";
        cout << "4. Create New User/Account\n";
        cout << "5. Remove User/Account\n";
        cout << "6. Logout\n";
        cout << "Select an option: ";
        cin >> choice;

        if (cin.fail()) {
            clearInputBuffer();
            choice = -1; // Opsi tidak valid
        }
        
        AdminPrompt adminChoice = static_cast<AdminPrompt>(choice);

        switch (adminChoice) {
            case VIEW_ALL_USERS:
                viewAllUsers(users);
                break;
            case VIEW_USER_DETAILS:
                viewUserDetails(users);
                break;
            case SEARCH_USER:
                searchUser(users);
                break;
            case CREATE_USER:
                createUser(users, bank);
                break;
            case REMOVE_USER:
                removeUser(users, bank);
                break;
            case ADMIN_LOGOUT:
                cout << "Logging out from admin panel." << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }
}

void viewAllUsers(const vector<Buyer*>& users) {
    cout << "\n--- List of All Users ---\n";
    if (users.empty()) {
        cout << "No users in the system." << endl;
        return;
    }
    for (const auto* user : users) {
        const Seller* seller = dynamic_cast<const Seller*>(user);
        string userType = (seller) ? "Seller" : "Buyer";
        cout << "ID: " << user->getId() << ", Name: " << user->getName() << ", Type: " << userType << endl;
    }
}

void viewUserDetails(const vector<Buyer*>& users) {
    cout << "\n--- Detailed Information of All Users ---\n";
    if (users.empty()) {
        cout << "No users in the system." << endl;
        return;
    }
    for (const auto* user : users) {
        user->displayDetails();
        cout << endl;
    }
}

void searchUser(const vector<Buyer*>& users) {
    cout << "\n--- Search for a User ---\n";
    cout << "Enter search term (ID, Name, Address, or Phone): ";
    string searchTerm;
    if (cin.peek() == '\n') {
        cin.ignore();
    }
    getline(cin, searchTerm);
    
    bool found = false;
    int searchId = 0;
    bool isNumeric = false;
    try {
        searchId = stoi(searchTerm);
        isNumeric = true;
    } catch (...) {
    }

    for (const auto* user : users) {
        if ((isNumeric && user->getId() == searchId) || // <-- PERBAIKAN ADA DI SINI
            user->getName().find(searchTerm) != string::npos ||
            user->getAddress().find(searchTerm) != string::npos ||
            user->getPhoneNumber().find(searchTerm) != string::npos)
        {
            cout << "\n--- User Found ---" << endl;
            user->displayDetails();
            found = true;
        }
    }
    if (!found) {
        cout << "No user found matching '" << searchTerm << "'." << endl;
    }
}

void createUser(vector<Buyer*>& users, Bank& bank) {
    cout << "\n--- Create New User ---\n";
    cout << "Select user type (1: Buyer, 2: Seller): ";
    int type;
    cin >> type;

    if (cin.fail() || (type != 1 && type != 2)) {
        clearInputBuffer();
        cout << "Invalid type selected." << endl;
        return;
    }

    string name, address, phone;
    double initialBalance;

    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Address: ";
    getline(cin, address);
    cout << "Enter Phone Number: ";
    getline(cin, phone);
    cout << "Enter Initial Bank Balance: ";
    cin >> initialBalance;
    
    if(cin.fail()){
        clearInputBuffer();
        cout << "Invalid balance input." << endl;
        return;
    }

    BankCustomer& newAccount = bank.addAccount(nextBankId++, name, initialBalance);
    
    if (type == 1) {
        users.push_back(new Buyer(nextUserId++, name, address, phone, newAccount));
        cout << "New Buyer created successfully!" << endl;
    } else {
        users.push_back(new Seller(nextUserId++, name, address, phone, newAccount));
        cout << "New Seller created successfully!" << endl;
    }
}

void removeUser(vector<Buyer*>& users, Bank& bank) {
    cout << "\n--- Remove User by ID ---\n";
    cout << "Enter User ID to remove: ";
    int idToRemove;
    cin >> idToRemove;
    
    if (cin.fail()) {
        clearInputBuffer();
        cout << "Invalid ID." << endl;
        return;
    }

    auto it = std::find_if(users.begin(), users.end(), 
        [idToRemove](const Buyer* user) {
            return user->getId() == idToRemove;
        });

    if (it != users.end()) {
        int bankAccountId = (*it)->getBankAccountId();

        delete *it;

        users.erase(it);

        bank.removeAccountById(bankAccountId);

        cout << "User with ID " << idToRemove << " and all related information have been removed." << endl;
    } else {
        cout << "User with ID " << idToRemove << " not found." << endl;
    }
}