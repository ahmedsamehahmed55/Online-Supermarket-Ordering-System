// Name: Ahmed Ahmed
// Declaration of Item class
#ifndef ITEM_H_
#define ITEM_H_

#include <iostream>
#include <string>
#include <iomanip>  // Required for setw and setfill in formatting
#include <fstream>  // Required for file I/O
#include <cctype>  // Required for string comparision

class Item {
private:
    int _id;              // Unique ID for the item
    std::string _name;    // Name of the item
    double _rPrice;       // Retail price of the item
    int _quantity;        // Quantity available in inventory
    static std::string toLower(const std::string&); // Helper function for the string comparision

public:

    // ---------------------- Constructors ----------------------

    // Default constructor: initializes item with default values
    Item();

    // Parameterized constructor: initializes item with given values
    Item(int id, std::string name, double price, int quantity);

    // ---------------------- Methods ----------------------

    // Calculate total price for this item (quantity * price)
    double total() const;

    // Set the quantity of the item
    int setQuantity(int quantity);

    // ---------------------- Getters ----------------------

    std::string getName() const;   // Return item name
    int getQuantity() const;       // Return item quantity
    double getPrice() const;       // Return item price
    int getID() const;             // Return item ID

    // ---------------------- Setters ----------------------

    void setRPrice(double price);          // Set retail price
    void setData(int id, std::string name); // Set ID and name

    // ---------------------- Operator overloads ----------------------

    // Equality: two items are equal if either name or ID matches
    bool operator==(Item& item) const {
        return this->toLower(_name) == toLower( item._name) || this->_id == item._id;
    }

    // Comparison operators based on name (used for sorting/searching)
    bool operator<(const Item& item) const {
        return toLower(_name) <toLower( item._name);
    }

    bool operator>(const Item& item) const {
        return toLower(_name)>toLower( item._name);
    }

    bool operator<=(const Item& item) const {
        return toLower(_name) <= toLower( item._name);
    }

    bool operator>=(const Item& item) const {
        return toLower(_name) >= toLower( item._name);
    }

    // ---------------------- Friend functions ----------------------

    // Overload input operator to read item from stream (cin or file)
    friend std::istream& operator>>(std::istream& in, Item& item);

    // Overload output operator to print item to stream (cout or file)
    friend std::ostream& operator<<(std::ostream& out, const Item& item);
};

#endif
