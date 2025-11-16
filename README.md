# Online SuperMarket Ordering System

It is a console-based Online Ordering System built completely in C++ that allows the customers to browse, select, and
purchase products. It also allows the the owner to manage the content of the inventory and keep track of it.
This project demonstrates object-oriented programming, efficient data structures, and modular design. It includes 
template libraries for Linked Lists and Dynamic Array or Vector with extended feature that allow better control of the content of each one.

---
## Features

- **Customer Management**  
  - Create and manage customer accounts  
  - Maintain a dynamic shopping cart with add, remove, and update item functionality  

- **Inventory Management**  
  - Add, remove, and search items by ID or category  
  - Track stock quantities and automatically update inventory after orders  

- **Order Processing**  
  - Calculate totals and display structured invoices  
  - Update inventory in real time after checkout  

- **User-Friendly Output**  
  - Organized display of product listings, cart contents, and order summaries using formatted tables and numeric precision  

- **Modular and Extensible Design**  
  - Classes for `Customer`, `Item`, and `Inventory` ensure maintainable and scalable code  
  - Easily extendable to GUI, web, or mobile platforms  

---


## Classes

- **`Customer`**  
  Handles customer information, login credentials, and shopping cart management. Supports adding/removing items from the cart.
It uses Linked List of Item for this management called tlist.h.   

- **`Item`**  
  Represents a product with properties such as ID, name, quantity, and retail price.  

- **`Inventory`**  
  Manages all available items, including searching by ID or category, adding/removing items, and tracking stock. It uses Dynamic Vector called tvector.h. 

---


## Folder Structure
- `src/` → C++ source files
- `include/` → Header files
- `data/` → Text/data files

## How to Compile
```bash
g++ src/*.cpp -Iinclude -o OnlineSuperMarket
./OnlineSuperMarket
