#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <iostream>
#include "tlist.h"
#include "item.h"
#include"inventory.h"

class customer{
    private:
    std::string _customer_name; // Name of the Customer
    tlist<Item> shoppingCart; 
    public:
    customer(); //default constructor
    
    // Add Quanitity of Item
    // Return Pointer to the Cart Item. Return nullptr if item is not found !
    Item* addByName(Inventory&, const std::string, int);

    // Update the Quantity of Existing item in the chart
    // Check if there is enough quantity in the inventory
    // return pointer to the Cart Item. Return nullptr if item is not found
    Item* updateQuantity(std::string, int, Inventory& );

    // Find by ID ---> Catogery
    // Return pointer to the element if found. Return nullptr if item is not found
    Item* findByID(const int);

    // Find by Name ---> Catogery
    // Return pointer to the element if found. Return nullptr if item is not found
    Item* findByName(std::string);

    // Remove an item from the cart and add it back to inventory
    void remove(std::string, Inventory&);

    // Set the customer's name
    void setCustomerName(std::string _customer_name);

    // Operator overloading to print the content of chart
    friend std::ostream& operator<<(std::ostream&, customer&);

    // Get the number of distinct items 
    int getCount();

    // Get Customer Name  
    std::string getCustomerName();

    // Get Total Price
    double total();
   
};


#endif