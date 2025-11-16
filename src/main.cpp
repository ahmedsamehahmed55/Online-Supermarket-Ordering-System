// Name: Ahmed Ahmed
// Problem Statement: Supermarket Online Ordering System.


//---------- Libraries ------------//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>  // Required for string comparision
#include <string>
#include <limits>

//-------- Header Files---------//

#include "inventory.h"
#include "customer.h"
#include "item.h"
#include "tvector.h"
#include "tlist.h"



using namespace std;

void printMenu() {
    cout << "\n=== Supermarket Menu ===\n";
    cout << "1. Create a Shopping Cart\n";
    cout << "2. Search Inventory\n";
    cout << "3. Add Item to Shopping Cart\n";
    cout << "4. List Shopping Cart\n";
    cout << "5. Update Item in Shopping Cart\n";
    cout << "6. Remove Item from Shopping Cart\n";
    cout << "7. Print Inventory\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

void printCat(string fname) {
    cout << "All Categories \n\n";
    ifstream in(fname);
    string id, name;
    cout << "ID              Category Name\n";
    while (in >> id >> name) {
        cout << id << "          " << name << endl;
    }
}


int inputValidation(){
    int value=0;
    string input;
    while (true) {
    cin >> input;  // read as string
    stringstream ss(input);
    if (ss >> value && ss.eof()) {  // check if entire input is an integer
        return value;               // valid integer
    } 
    else {
        cout << "Invalid input. Please enter an integer: ";
        cin.clear();
    }
    } 
} 


int main() {
    Inventory inv;
    customer cus;
    cus.setCustomerName("Ahmed Ahmed");
    inv.loadInventory("inventory.txt");

    int choice = -1;
    while (choice!=0) {
        printMenu();
        choice=inputValidation();

        switch (choice) {

        case 1: {
            cout << "Enter Your Name: ";
            cin.ignore();
            string name;
            getline(cin, name);
            cus.setCustomerName(name);
            cout << "Shopping Cart for " << cus.getCustomerName()
                 << " has been created!\n";
            break;
        }
        case 2: {
            cout << "Press 1 to search by Category\n"
                 << "Press 2 to search by Name\n";

            int userChoice;
            cin >> userChoice;

            while (userChoice != 1 && userChoice != 2) {
                cout << "Invalid choice. Try again.\n";
                cin >> userChoice;
            }

            // Search by category ID
            if (userChoice == 1) {
                printCat("cat.txt");
                cout << "Enter Category ID: ";
                int id;
                cin >> id;

                tvector<Item*> items = inv.searchByID(id);

                if (items.getCount() == 0) {
                    cout << "No items found for category ID: " << id << endl;
                } else {
                    cout << "\nItems Found:\n";
                    for (int i = 0; i < items.getCount(); i++) {
                        cout << **items.elemAt(i);
                    }
                }
            }

            // Search by name
            if (userChoice == 2) {
                cout << "Enter Item Name: ";
                cin.ignore();
                string name;
                getline(cin, name);
                if (!inv.searchByName(name)) {
                    cout << "Item Not Found.\n";
                } else {
                    cout << "Item Found:\n" << *inv.searchByName(name);
                }
            }

            break;
        }
        // Add Item By Name
        case 3: {
            cout << "Enter Item Name to Add: ";
            cin.ignore();
            string name;
            getline(cin, name);

            cout << "Enter Quantity: ";
            int qty=inputValidation();

            if(cus.addByName(inv, name, qty)){
            cout << "\nItem Added!\n";
            }
            break;
        }
        // Show the shopping cart
        case 4: {
            cout << "\n=== Shopping Cart ===\n";
            cout << cus;
            break;
        }
        // Update the shopping cart
        case 5: {
            cout << "Enter Item Name to Update: ";
            cin.ignore();
            string name;
            getline(cin, name);

            cout << "Enter NEW Quantity: ";
            int qty=inputValidation();

            cus.updateQuantity(name, qty, inv);
            break;
        }
        // Remove from the shopping cart
        case 6: {
            cout << "Enter Item Name to Remove: ";
            cin.ignore();
            string name;
            getline(cin, name);
            if(!cus.findByName(name)) cout<< "Item Name: "<< name<<" was not found !"<<endl;
            cus.remove(name, inv);
            break;
        }
        // Show Inventory
        case 7: {
            cout << "\n=== Inventory ===\n";
            cout << inv; 
            break;
        }
        case 0:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}