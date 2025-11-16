// Name: Ahmed Ahmed
// Implementation of Item class

#include "item.h"
#include <iomanip>
#include <cctype>  // Required for string comparision

using namespace std;

// ---------------------- Constructors ----------------------

// Default constructor: initializes all members to default values
Item::Item(): _id(0), _name(""), _rPrice(0.0), _quantity(0) {}

// Parameterized constructor: initializes the item with given values
Item::Item(int i, string n, double rP, int qu)
    : _id(i), _name(n), _rPrice(rP), _quantity(qu) {}

// ---------------------- Methods ----------------------

// Calculate total price of this item (quantity * unit price)
double Item::total() const {
    return _quantity * _rPrice;
}

// Set the quantity of the item
int Item::setQuantity(int q){
    _quantity = q;
    return q;
}

// Get the quantity of the item
int Item::getQuantity() const {
    return _quantity;
}

// Set the retail price of the item
void Item::setRPrice(double r){
    _rPrice = r;
}

// Set ID and name of the item
void Item::setData(int id, string name){
    _id = id;
    _name = name;
}

// Get the name of the item
std::string Item::getName() const{
    return _name;
}

// Get the ID of the item
int Item::getID() const{
    return _id;
}

// Get the retail price of the item
double Item::getPrice() const{
    return _rPrice; 
}

// ---------------------- Operator Overloads ----------------------

// Output operator: prints the item in a formatted way
std::ostream& operator<<(std::ostream& out, const Item& item) {
    out << std::setw(5) << std::setfill('0') << item._id << " "          
        << std::left << std::setw(25) << std::setfill(' ') << item._name << " " 
        << std::left << std::setw(3) << item._quantity << " @ "       
        << "$" << std::fixed << std::setprecision(2) << std::setw(5) << item._rPrice << " = $ " 
        << std::fixed << std::setprecision(2) << std::setw(4) << item.total() 
        << std::endl;
    return out;
}

// Input operator: reads item data from a stream (cin or file)
std::istream& operator>>(std::istream& in, Item& item) {
    in >> item._id >> item._name >> item._quantity >> item._rPrice;
    return in;
}

// Helper function to lower case the string
std::string Item::toLower(const std::string& s) {
    std::string result;
    for(int i=0;i<s.size(); i++){
        if(!std::isspace(s[i])) result.push_back(std::tolower(s[i]));
    }
    return result;
}