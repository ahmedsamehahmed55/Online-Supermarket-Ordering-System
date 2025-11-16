#include <iostream>
#include "inventory.h"
#include "item.h"
#include "tvector.h"
#include <fstream>  
#include <iomanip> 


// ---------------------- Update methods ----------------------

// Update the price of an item in inventory by name
double Inventory::updatePrice(const double price, std::string item_name){
    Item temp(0, item_name, 0.0, 0); // temp Item for search
    int pos=_inventory.search(temp); // Find the index 
    if (pos==-1) return -1; // if item is not found
    else{
        _inventory.elemAt(pos)->setRPrice(price); // Update Price
        return price; 
    }
}

// Update the quantity of an item in inventory by name
int Inventory::updateQuantity(const int quantity, std::string  item_name){

    Item temp(0, item_name, 0.0, 0); // Temporary item for search
    int pos=_inventory.search(temp); // Search index
    if (pos==-1) return -1; // Item not found
    else{
        _inventory.elemAt(pos)->setQuantity(quantity); // Update quantity
        return _inventory.elemAt(pos)->getQuantity(); 
    }
}

// ---------------------- Remove/Search methods ----------------------


// Remove an item from inventory by name
Item* Inventory::remove(std::string item_name){
    Item temp(0, item_name, 0.0, 0);
    int pos=_inventory.search(temp);
    if (pos==-1) return nullptr;
    else{
       return _inventory.removeFrom(pos);
    }
}

// Search for an item by name
Item* Inventory::searchByName(std::string name){
    Item temp(0,name,0.0,0);
    _inventory.mergeSort();
    if (_inventory.search(temp)<0){     // Item is not found
        return nullptr;
    }
    return _inventory.elemAt(_inventory.search(temp));
}

// Search for an item by ID
tvector<Item*> Inventory::searchByID(const int id) {
    tvector<Item*> items;
    for (int i = 0; i < _inventory.getCount(); i++) {
        Item* current = _inventory.elemAt(i);
        if (current && current->getID() == id) {
            items.addToEnd(current);
        }
    }
    return items;
}



// ---------------------- Insertion ----------------------
// insert in order
void Inventory::_insertInOrder(Item& i){
    _inventory.insertInOrder(i, 1); // 1= ascending order 
}

// Add a new item to inventory
void Inventory::addToInventory(Item& i)
{
    Item* existing = searchByName(i.getName()); // Check if item exists
    if (existing) {
        // Item exists, increment its quantity
        existing->setQuantity(existing->getQuantity() + i.getQuantity());
    } else {
        // New item, insert in sorted order
        _inventory.insertInOrder(i, 1); 
    }
}


// ---------------------- Load inventory ----------------------

// Load inventory items from a file
void Inventory::loadInventory(std::string fname){
    std::ifstream in(fname);
    if (!in) {
        std::cerr<<"Error in filename: "<<fname<<std::endl;
        return;
    }
    Item temp;
    while (in >> temp) {  
       _inventory.addToEnd(temp);
    }
    
    _inventory.mergeSort(Inventory::compareByID); // choose sorting 
    /*_inventory.mergeSort(Inventory::compareByName);
    _inventory.mergeSort(Inventory::compareByPrice);
    
    _inventory.mergeSort();
    */
}


// Calculate total price of all items in inventorye
double Inventory::inventoryTotal()
{
    double TotalPrice=0.0;
    for (int i=0;i<_inventory.getCount();i++){
        TotalPrice=_inventory.elemAt(i)->total()+TotalPrice ; // pass specific objects 
}
    return TotalPrice;  // return total price
}


// Print inventory items and total
std::ostream& operator<<(std::ostream& out, Inventory& inv){

    if (inv._inventory.isEmpty()) { // base case
        out << "Inventory is empty" << std::endl;
        return out;}

    out<<"Inventory : "<<std::endl; 
    for (int i=0; i<inv._inventory.getCount();i++){
        out<<*inv._inventory.elemAt(i);
    }
    out<< "===================================================\n";
    out <<std::setw(45) <<std::right << "Total $" <<std::setprecision(2)<<inv.inventoryTotal()<<std::endl;
    return out;
    }





// ---------------------- Sorting methods ----------------------

void Inventory::SortByID(){
    _inventory.mergeSort(Inventory::compareByID);
}

void Inventory::SortByName(){
    _inventory.mergeSort(Inventory::compareByName);
}
void Inventory::SortByPrice(){
    _inventory.mergeSort(Inventory::compareByPrice);
}

void Inventory::SortByQuanitity(){
    _inventory.mergeSort(Inventory::compareByQuantity);
}


