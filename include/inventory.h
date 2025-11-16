// Name: Ahmed Ahmed
// Decleration of Iventory class

#ifndef INVENTORY_H_
#define INVENTORY_H_

#include <iostream>
#include <string>
#include "tvector.h"
#include "item.h"
#include <iomanip> 

class Inventory {
    private:

    tvector<Item> _inventory;


    // ---------------------- Private helper ----------------------
    // Inserts an item in the inventory in sorted order
    void _insertInOrder(Item&);

    // ---------------------- Comparison functions ----------------------
    // Used for sorting inventory by different fields
    // Used by tvector in the sorting functions
    static bool compareByName(const Item& a, const Item& b)  {
    return a.getName() < b.getName();
    }
    static bool compareByID(const Item& a, const Item& b)  {
    return a.getID() < b.getID();
    }   
    static bool compareByPrice(const Item& a, const Item& b)   {
    return a.getPrice() < b.getPrice();}
    static bool compareByQuantity(const Item& a, const Item& b)   {
    return a.getQuantity() < b.getQuantity();}

    public:

    // ------------------- Inventory management methods ----------------------
    
    // Load inventory data from a file
    // Uses Merge Sort after inputting the data
    void loadInventory(std::string);

    // Add Item to inventory   
    void addToInventory(Item& i);

    // Check if item exist
    bool itemInInventory(Item& i);

    // Remove Item
    // Returns pointer to the removed item
    Item* remove(std::string); 

    // Update Price of Item
    // Returns the new price
    double updatePrice(const double, std::string);

    // Updates the Quantity
    int updateQuantity(const int, std::string);
    
    // Search By name
    // Return Poiner to the Item if found
    Item* searchByName(std::string);
    
    tvector<Item*> searchByID(const int id);
    
    // Operator Overloading for printing
    friend std::ostream& operator<<(std::ostream& out, Inventory& inv);
    
    // Total Price of Items in Inventory
    double inventoryTotal ();


        // ---------------------- Sorting methods ----------------------
    void SortByID();
    void SortByName();
    void SortByPrice();
    void SortByQuanitity();



};

#endif
