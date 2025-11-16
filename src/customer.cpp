#include <iostream>
#include "tlist.h"
#include"inventory.h"
#include "item.h"
#include "customer.h"



// Default Constructor
customer::customer():_customer_name(""){};

// Create a temporary Item with the given ID and search in shoppingCart
Item* customer::findByID(int const id){
    Item other(id, "", 0,0);
    return shoppingCart.search(other);
}

// Create a temporary Item with the given name and search in shoppingCart
// Return Pointer to the item
Item* customer::findByName(const std::string item_name){
    Item other(0, item_name, 0,0);
    return shoppingCart.search(other);
}

// Update quantity method
// Updates the quanitity of the item in the chart.
// return pointer to the item if found. Otherwise returns nullptr
Item* customer::updateQuantity(std::string item_name, int quantity, Inventory& inv) {
    Item* cartItem = findByName(item_name); // Create a temp Item
    if(cartItem) { // Check if the Item exist in the Chart
        Item* invItem = inv.searchByName(item_name); // Check if the Item exist in the inventory
        if(invItem) {
            int totalAvailable = invItem->getQuantity() + cartItem->getQuantity();
            if(quantity <= totalAvailable) { // if there is enough quantity
                invItem->setQuantity(invItem->getQuantity() + cartItem->getQuantity());
                cartItem->setQuantity(quantity);
                invItem->setQuantity(invItem->getQuantity() - quantity);
            } else {
                std::cout << "Not enough stock in inventory.\n"; 
            }
        }
    } else {
        std::cout << "Item not found in cart.\n";
    }
    return cartItem;
}


// add by name method
// Adds a given quantity of an item from inventory to the customer's cart
// If item already exists in cart, increases quantity
// Decreases inventory quantity accordingly
Item* customer::addByName(Inventory& inv, const std::string item_name, int quantity) {
    Item* cartItem = findByName(item_name); // Create a temp Cart Item
    Item* invItem = inv.searchByName(item_name); // Create a temp inv Item
    if (!invItem) { // check if item exists in the inv
        std::cout << "Item \"" << item_name << "\" not found in inventory.\n";
        return nullptr; // Return nullptr if the item does not exist
    }

    if (quantity > invItem->getQuantity()) { // if item exists but no enough stock available
        std::cout << "Not enough stock in inventory.\n";
        return cartItem; // return pointer to the CartItem
    }

    if (cartItem) { 
              // Item already in cart, increase its quantity
        cartItem->setQuantity(cartItem->getQuantity() + quantity);
    } else {
    
        Item newItem = *invItem;
        newItem.setQuantity(quantity);
        shoppingCart.insertInOrder(newItem);
    }

    // Reduce inventory by quantity added to cart
    invItem->setQuantity(invItem->getQuantity() - quantity); 

    return cartItem;
}


// Returns total cost of all items in shopping cart
double customer::total(){
    double total=0.0;
    for (int i=0; i<shoppingCart.getCount(); i++){
        total+=shoppingCart.findAt(i).total();
    }
    return total;
}


// Removes an item from cart and returns it to inventory
void customer::remove(std::string item_name, Inventory& inv){
    Item* item = findByName(item_name);
    if (item==nullptr) return;
    else {
        inv.addToInventory(*item);
        shoppingCart.removeByPointer(item);
    
    }
}

// Set customer name
void customer::setCustomerName(std::string name){
    _customer_name=name;
}

// Get customer name
std::string customer::getCustomerName(){
    return _customer_name;
}

// Prints customer name, cart items, and total in formatted way
std::ostream& operator<<(std::ostream& out, customer& custmr){
        out<<"------------------------------------"<<std::endl;
        out<< "Customer Name: "<< custmr._customer_name<<"\n\n";
        for(int i=0;i<custmr.shoppingCart.getCount();i++){
            out<<custmr.shoppingCart.findAt(i);
        }
        out<<"----------------------------------"<<std::endl;
         out <<std::setw(50) <<std::right << "Total $ " <<std::setprecision(2) <<custmr.total()<<std::endl;
        return out; 
    }

// returns the number of the items in the chart
int customer::getCount(){
    return shoppingCart.getCount();
}