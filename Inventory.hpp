/* 
Ayush karki
CSCI-23500 Fall 2023
project 7 - Implement the Inventory class as a subclass of BinarySearchTree that stores Items
Inventory.hpp

In this project, an Inventory Management System is implemented using a Binary Search Tree (BST) structure to organize and manage items. The project is divided into several tasks:
- Inventory Class Implementation: The Inventory class is created, inheriting from a BinarySearchTree of Item pointers. Items are organized in the BST based on alphabetical order of their names.
= addItem Function: The addItem function is implemented to add items to the inventory while preserving the BST structure. Special handling is included for consumable items, updating quantities if the same item is added multiple times.
- removeItem Function: The removeItem function removes items from the inventory, considering different cases for consumable and non-consumable items.
- findItem Function: The findItem function is implemented to search for items in the inventory based on their names.
- getTotalGoldValue Function: Calculates and returns the total gold value of all items in the inventory.
- printInventoryInOrder Function: Prints the details of all items in the inventory in ascending order based on their names. Special formatting is applied for consumable items, displaying their quantities.
- printInventory Function: Prints the items in the inventory in a specified order (name, type, level, value, or time). Allows for ascending or descending order.
= Additional Helper Functions: Several helper functions are implemented to support the main functionalities, such as recursive search, vector filling, and sorting */
#ifndef INVENTORY_H
#define INVENTORY_H
#include <vector>
#include <string>
#include "BinarySearchTree.hpp"
#include "Item.hpp"

//Implement the Inventory class as a subclass of BinarySearchTree that stores POINTERS to Items.
class Inventory : public BinarySearchTree<Item*> {

public:

// Constructor (no need for destructor)
/**
 * @brief   : Default constructor for the Inventory class.
 * @details : Initializes an empty inventory by calling the default constructor of the BinarySearchTree<Item*> base class.
 * @post    : An instance of the Inventory class is created with an empty binary search tree.
 * @return  : None.
 */
    Inventory();


//Task 1: Implement the Inventory class as a subclass of BinarySearchTree that stores POINTERS to Items
/*In addition to any necessary constructs and destructors, the Inventory class must additionally define the following member functions. */
// Additional Methods-

/**
 * @param : A Pointer to the Item object to be added to the inventory.
 * @post  : The Item is added to the inventory, preserving the BST structure. The BST property is based on (ascending) alphabetical order of the item's name.
 *          If the item is type UNKNOWN, WEAPON, or ARMOR and is already in the inventory, it is not added.
      However, if another instance of an Item of type CONSUMABLE is being added (an item with the same name), its quantity is updated to the sum of the quantities of the two objects, and the time_picked_up_ variable is updated to that of the latest instance of the item being added.
 * @return true if the item was added to the inventory or updated, false otherwise.
 */
    bool addItem(Item* item);

/**
 * @param   : A reference to string name of the item to be removed from the inventory.
 * @return  : True if the item was found and removed or updated successfully, false otherwise.
 * @post    : If the item is found in the inventory, it is removed while preserving the BST structure.
              If a CONSUMABLE is removed, its quantity is decremented by one, but its time_picked_up_ remains the same. However, if it is the last item (it's quantity is 1 and is being removed), the item should be removed. Non-CONSUMABLE items should always be removed when they are found.
 */
    bool removeItem(const std::string& name);

/**
 * @param   : A reference to string name of the item to be found.
 * @return  : An Item pointer to the found item, or nullptr if the item is not in the inventory.
 */
    Item* findItem(const std::string& name) const; 

/**
 * @return    : The total sum of gold values of all items in the inventory.
                Note: consumable items may have quantity >1 and gold value must be
                      added for each item
 */
    int getTotalGoldValue() const;

/**
 * @post    : The names of all items in the Inventory are printed in ascending order.
 *            This function performs an in-order traversal of the binary search tree and prints the details of each item in the following format. 
        NOTE: QUANTITY ONLY NEEDS TO BE DISPLAYED FOR CONSUMABLE ITEMS.

 *            [NAME] ([TYPE])
              Level: [LEVEL]
              Value: [VALUE]
              Quantity: [QUANTITY]
   
              Example:
              TIRED GAUNTLETS (ARMOR)
              Level: 3
              Value: 25
        
              SMALL HEALTH POTION (CONSUMABLE)
              Level: 1
              Value: 10
              Quantity: 2
 * 
 */
    void printInventoryInOrder(); 

/**
 * @param   : a reference to bool if the items are to be printed in ascending order. 
 * @param   : a reference to string attribute which defines the order by which the items are to be printed. You may assume that the given parameter will be in one of the following forms: ["NAME"/"TYPE"/"LEVEL"/"VALUE"/"TIME"]
 * @post    : All items in the Inventory are printed in the order specified by the parameter.
 *          Example usage: inventory.printInventory(false, "LEVEL");
            NOTE: QUANTITY ONLY NEEDS TO BE DISPLAYED FOR CONSUMABLE ITEMS:

            FEATHER DUSTER (WEAPON)
            Level: 5
            Value: 100

            TIRED GAUNTLETS (ARMOR)
            Level: 3
            Value: 50

            SMALL HEALTH POTION (CONSUMABLE)
            Level: 1
            Value: 10
            Quantity: 2

            NOODLES (CONSUMABLE)
            Level: 0
            Value: 120
            Quantity: 5
 */
    void printInventory(const bool& A, const std::string& att); 



//Helpers-

//findItemRecursive() Helper:
/**
 * @param   : A pointer to a node in the binary tree of items.
 * @param   : A reference to the string name of the item to be found.
 * @return  : An Item pointer to the found item, or nullptr if the item is not in the subtree rooted at the given node.
 */
    Item* findItemRecursive(BinaryNode<Item*>* node, const std::string& name) const;

//printInventory() Helpers:
/**
 * @param   : A pointer to a BinaryNode<Item> representing the current node in the inventory BST.
 * @param   : A boolean reference indicating whether items should be printed in ascending order.
 * @param   : A string reference specifying the attribute by which items are to be printed ("NAME"/"TYPE"/"LEVEL"/"VALUE"/"TIME").
 * @post    : Recursively prints items in the Inventory based on the specified order and attribute.
 * @return  : None.
 */
    void printInventoryRecursive(BinaryNode<Item*>* node, const bool& A, const std::string& att) const ;

/**
 * @param   : A reference to a vector of Item pointers to be sorted based on the specified attribute and order.
 * @param   : A string reference specifying the attribute by which items are to be sorted ("NAME"/"TYPE"/"LEVEL"/"VALUE"/"TIME").
 * @param   : A boolean reference indicating whether items should be sorted in ascending order.
 * @post    : Sorts the vector of items based on the specified attribute and order.
 * @return  : None.
 */
    void sortVector(std::vector<Item*>& v, const std::string& att, const bool& A) const;

/**
 * @param   : A reference to a vector of Item pointers to be filled with items from the Inventory.
 * @param   : A pointer to a BinaryNode<Item> representing the current node in the inventory BST.
 * @post    : Recursively fills the vector with items in the Inventory using an in-order traversal.
 * @return  : None.
 */
    void fillVector(std::vector<Item*>& v, BinaryNode<Item*>* node) const;

//printInventoryInOrder() Helper:
/**
 * @param   : A pointer to a BinaryNode<Item> representing the current node in the inventory BST.
 * @post    : Recursively prints the names of all items in the Inventory in ascending order.
 *            Each item is displayed in the format specified, including details such as level, value, and quantity (for consumable items).
 * @return  : None.
 */
    void printInventoryInOrderRecursive(BinaryNode<Item*>* node) const ;

//getTotalGoldValue() Helper:
/** 
 * @param   : A pointer to a node in the binary tree of items.
 * @return  : The total sum of gold values of all items in the subtree rooted at the given node.
 * @post    : Recursively calculates the total sum of gold values for all items in the subtree.
 */
    int getTotalGoldValueHelper(BinaryNode<Item*>* node) const;
};

#endif // INVENTORY_H
