/* 
Ayush karki
CSCI-23500 Fall 2023
project 7 - Implement the Inventory class as a subclass of BinarySearchTree that stores Items
Inventory.cpp

In this project, an Inventory Management System is implemented using a Binary Search Tree (BST) structure to organize and manage items. The project is divided into several tasks:
- Inventory Class Implementation: The Inventory class is created, inheriting from a BinarySearchTree of Item pointers. Items are organized in the BST based on alphabetical order of their names.
= addItem Function: The addItem function is implemented to add items to the inventory while preserving the BST structure. Special handling is included for consumable items, updating quantities if the same item is added multiple times.
- removeItem Function: The removeItem function removes items from the inventory, considering different cases for consumable and non-consumable items.
- findItem Function: The findItem function is implemented to search for items in the inventory based on their names.
- getTotalGoldValue Function: Calculates and returns the total gold value of all items in the inventory.
- printInventoryInOrder Function: Prints the details of all items in the inventory in ascending order based on their names. Special formatting is applied for consumable items, displaying their quantities.
- printInventory Function: Prints the items in the inventory in a specified order (name, type, level, value, or time). Allows for ascending or descending order.
= Additional Helper Functions: Several helper functions are implemented to support the main functionalities, such as recursive search, vector filling, and sorting */
#include "Inventory.hpp"
#include <stack>
#include<algorithm>
#include <iostream>

/**
 * @brief   : Default constructor for the Inventory class.
 * @details : Initializes an empty inventory by calling the default constructor of the BinarySearchTree<Item*> base class.
 * @post    : An instance of the Inventory class is created with an empty binary search tree.
 * @return  : None.
 *///Implement the Inventory class as a subclass of BinarySearchTree that stores POINTERS to Items.
Inventory::Inventory() : BinarySearchTree<Item*>(){}


/*In addition to any necessary constructs and destructors, the Inventory class must additionally define the following member functions. */
//////////////////Additional Methods//////////////////////

/**
 * @param : A Pointer to the Item object to be added to the inventory.
 * @post  : The Item is added to the inventory, preserving the BST structure. The BST property is based on (ascending) alphabetical order of the item's name.
 *          If the item is type UNKNOWN, WEAPON, or ARMOR and is already in the inventory, it is not added.
      However, if another instance of an Item of type CONSUMABLE is being added (an item with the same name), its quantity is updated to the sum of the quantities of the two objects, and the time_picked_up_ variable is updated to that of the latest instance of the item being added.
 * @return true if the item was added to the inventory or updated, false otherwise.
 */
bool Inventory::addItem(Item* item) {
    // Check if the item is of a non-consumable type and already exists in the inventory.
    bool isNonConsumableType = (item->getType() == "UNKNOWN" || item->getType() == "WEAPON" || item->getType() == "ARMOR");
    // If it's a non-consumable type and already exists, return false.
    if (isNonConsumableType && contains(item)) {return false;} 
    else if (item->getType() == "CONSUMABLE" && contains(item)) {
        // If it's a consumable type and already exists, update the quantity and time picked up.
        Item* existingItem = getPointerTo(item).get()->getItem(); existingItem->setQuantity(existingItem->getQuantity() + item->getQuantity()); existingItem->updateTimePickedUp(); return false;} 
    else 
    // If the item is not in the inventory, add it.
    {return add(item);}
}



/**
 * @param   : A reference to string name of the item to be removed from the inventory.
 * @return  : True if the item was found and removed or updated successfully, false otherwise.
 * @post    : If the item is found in the inventory, it is removed while preserving the BST structure.
              If a CONSUMABLE is removed, its quantity is decremented by one, but its time_picked_up_ remains the same. However, if it is the last item (it's quantity is 1 and is being removed), the item should be removed. Non-CONSUMABLE items should always be removed when they are found.
 */
bool Inventory::removeItem(const std::string& name) {
    // Find the item in the inventory.
    Item* Remitem = findItem(name);
    // If the item is not found, return false.
    if (Remitem == nullptr) {
        return false;
    }
    // Check the type of the item for proper removal handling.
    if (Remitem->getType() == "CONSUMABLE") {
        // If the quantity is greater than 1, decrement the quantity.
        if (Remitem->getQuantity() > 1) {
            Remitem->setQuantity(Remitem->getQuantity() - 1);
        } else {
            // If it's the last item, remove it entirely.
            remove(Remitem);
        }
    } else {
        // Remove non-CONSUMABLE items.
        remove(Remitem);
    }
    // Return true to indicate successful removal or update.
    return true;
}



/**
 * @param   : A reference to string name of the item to be found.
 * @return  : An Item pointer to the found item, or nullptr if the item is not in the inventory.
 */
Item* Inventory::findItem(const std::string& name) const{
    // Call the recursive helper function to search for the item with the specified name.
    // The search starts from the root of the binary search tree (BST).
    return findItemRecursive(getRoot().get(), name);
}

//findItemRecursive() Helper:
/**
 * @param   : A pointer to a node in the binary tree of items.
 * @param   : A reference to the string name of the item to be found.
 * @return  : An Item pointer to the found item, or nullptr if the item is not in the subtree rooted at the given node.
 */
Item* Inventory::findItemRecursive(BinaryNode<Item*>* node, const std::string& name) const {
    // If the current node is null, the item is not found in this subtree.
    // This is the base case for the recursion.
    if(node == nullptr){
        return nullptr;
    }
    // Recursively search for the item in the left subtree.
    Item* leftSearch = findItemRecursive(node->getLeftChildPtr().get(), name);
    // If the item is found in the left subtree, return it.
    if(leftSearch != nullptr){
        return leftSearch;
    }
    // Check if the current node contains the item with the specified name.
    if(node->getItem()->getName() == name){
        // If so, return the item.
        return node->getItem();
    }
    // If the item is not found in the current node or the left subtree,
    // recursively search for the item in the right subtree.
    return findItemRecursive(node->getRightChildPtr().get(), name);
}



/**
 * @return    : The total sum of gold values of all items in the inventory.
                Note: consumable items may have quantity >1 and gold value must be
                      added for each item
 */
int Inventory::getTotalGoldValue() const{
    // Call the helper function to recursively calculate the total gold value.
    return getTotalGoldValueHelper(getRoot().get());
}

//getTotalGoldValue() Helper:
/** 
 * @param   : A pointer to a node in the binary tree of items.
 * @return  : The total sum of gold values of all items in the subtree rooted at the given node.
 * @post    : Recursively calculates the total sum of gold values for all items in the subtree.
 */
int Inventory::getTotalGoldValueHelper(BinaryNode<Item*>* node) const{
    // Base case: If the current node is nullptr, return 0.
    if (node == nullptr) {
        return 0;
    }
    // Calculate the total sum of gold values for the left subtree.
    int left_sum = getTotalGoldValueHelper(node->getLeftChildPtr().get());
    // Calculate the total sum of gold values for the right subtree.
    int right_sum = getTotalGoldValueHelper(node->getRightChildPtr().get());
    // Calculate the gold value of the current item and its quantity.
    int node_sum = node->getItem()->getGoldValue() * node->getItem()->getQuantity();
    // Return the sum of values for the current node and its subtrees.
    return left_sum + right_sum + node_sum;
}



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
void Inventory::printInventoryInOrder(){
    // Call the helper function to perform the in-order traversal and printing.
    printInventoryInOrderRecursive(getRoot().get());
}

//printInventoryInOrder() Helper:
/**
 * @param   : A pointer to a BinaryNode<Item> representing the current node in the inventory BST.
 * @post    : Recursively prints the names of all items in the Inventory in ascending order.
 *            Each item is displayed in the format specified, including details such as level, value, and quantity (for consumable items).
 * @return  : None.
 */
void Inventory::printInventoryInOrderRecursive(BinaryNode<Item*>* node) const {
    // If the current node is null, we have reached the end of a branch in the BST.
    if(node == nullptr){
        return;
    }
    // First, we recursively call the function on the left child of the current node.
    // This allows us to print items in ascending order (assuming the BST is ordered).
    printInventoryInOrderRecursive(node->getLeftChildPtr().get());
    // Retrieve the item from the current node.
    Item* item = node->getItem();
    // Print the name and type of the item.
    std::cout << item->getName() << " (" << item->getType() << ")\n";
    // Print the level and value of the item.
    std::cout << "Level: " << item->getLevel() << std::endl;
    std::cout << "Value: " << item->getGoldValue() << std::endl;
    // If the item is consumable, print its quantity.
    if(item->getType() == "CONSUMABLE"){
        std::cout << "Quantity: " << item->getQuantity() << std::endl;
    }
    // Print a new line to separate items.
    std::cout << std::endl;
   // Finally, we recursively call the function on the right child of the current node.
    printInventoryInOrderRecursive(node->getRightChildPtr().get());
}



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
void Inventory::printInventory(const bool& A, const std::string& att){
    // Create a vector to store items.
    std::vector<Item*> v;
    // Fill the vector using an in-order traversal of the inventory's binary search tree.
    fillVector(v, getRoot().get());
    // Sort the vector based on the specified attribute and order.
    sortVector(v, att, A);
    // Print each item with its details based on the sorted vector.
    for(Item* item : v){
        // Print the item's name and type.
        std::cout << item->getName() << " (" << item->getType() << ")\n";
        // Print the item's level and gold value.
        std::cout << "Level: " << item->getLevel() << std::endl;
        std::cout << "Value: " << item->getGoldValue() << std::endl;
        // Print quantity only for consumable items.
        if(item->getType() == "CONSUMABLE"){
            std::cout << "Quantity: " << item->getQuantity() << std::endl;
        }
        // Add a newline for better readability between items.
        std::cout << std::endl;
    }
}

//printInventory() Helpers:
/**
 * @param   : A pointer to a BinaryNode<Item> representing the current node in the inventory BST.
 * @param   : A boolean reference indicating whether items should be printed in ascending order.
 * @param   : A string reference specifying the attribute by which items are to be printed ("NAME"/"TYPE"/"LEVEL"/"VALUE"/"TIME").
 * @post    : Recursively prints items in the Inventory based on the specified order and attribute.
 * @return  : None.
 */
void Inventory::printInventoryRecursive(BinaryNode<Item*>* node, const bool& A, const std::string& att) const {
    // Check if the current node is null. If it is, return from the function.
    if(node == nullptr){
        // Base case: Reached a leaf node, return to the previous level of recursion.
        return;
    }
    // Depending on the value of A, recursively call the function on the left or right child of the current node.
    // If A is true, we start with the left child (smaller items if the BST is ordered).
    if(A){
        printInventoryRecursive(node->getLeftChildPtr().get(), A, att);
    }else{
        // If A is false, we start with the right child (larger items if the BST is ordered).
        printInventoryRecursive(node->getRightChildPtr().get(), A, att);
    }
    // Retrieve the item from the current node.
    Item* item = node->getItem();
    // Print the name and type of the item.
    std::cout << item->getName() << " (" << item->getType() << ")\n";
    // Print the level and value of the item.
    std::cout << "Level: " << item->getLevel() << std::endl;
    std::cout << "Value: " << item->getGoldValue() << std::endl;
    // If the item is consumable, print its quantity.
    if(item->getType() == "CONSUMABLE"){
        std::cout << "Quantity: " << item->getQuantity() << std::endl;
    }
    std::cout << std::endl;
    // Depending on the value of A, recursively call the function on the right or left child of the current node.
    if(A){
        printInventoryRecursive(node->getRightChildPtr().get(), A, att);
    }else{
        printInventoryRecursive(node->getLeftChildPtr().get(), A, att);
    }
}

/**
 * @param   : A reference to a vector of Item pointers to be filled with items from the Inventory.
 * @param   : A pointer to a BinaryNode<Item> representing the current node in the inventory BST.
 * @post    : Recursively fills the vector with items in the Inventory using an in-order traversal.
 * @return  : None.
 */
void Inventory::fillVector(std::vector<Item*>& v, BinaryNode<Item*>* node) const {
    // Check if the current node is null. If it is, return from the function.
    if(node == nullptr){
        return;
    }
    // Recursively call the function on the left child of the current node.
    fillVector(v, node->getLeftChildPtr().get());
    // Add the item in the current node to the vector.
    v.push_back(node->getItem());
    // Recursively call the function on the right child of the current node.
    fillVector(v, node->getRightChildPtr().get());
}

/**
 * @param   : A reference to a vector of Item pointers to be sorted based on the specified attribute and order.
 * @param   : A string reference specifying the attribute by which items are to be sorted ("NAME"/"TYPE"/"LEVEL"/"VALUE"/"TIME").
 * @param   : A boolean reference indicating whether items should be sorted in ascending order.
 * @post    : Sorts the vector of items based on the specified attribute and order.
 * @return  : None.
 */
void Inventory::sortVector(std::vector<Item*>& v, const std::string& att, const bool& A) const {
    // Check the attribute by which the items should be sorted.
    if(att == "NAME"){
        // If the attribute is "NAME", sort the items by their names.
        if(A){
            // If A is true, sort in ascending order.
            std::sort(v.begin(),v.end(), [](Item* lhs, Item* rhs){
                return lhs->getName() < rhs->getName();
            });
        }else{
            // If A is false, sort in descending order.
            std::sort(v.begin(),v.end(), [](Item* lhs, Item* rhs){
                return lhs->getName() > rhs->getName();
            });
        }
    }else if(att == "TYPE"){
        // If the attribute is "TYPE", sort the items by their types.
        if(A){
            // If A is true, sort in ascending order.
            std::sort(v.begin(),v.end(), [](Item* lhs, Item* rhs){
                return lhs->getType() < rhs->getType();
            });
        }else{
            // If A is false, sort in descending order.
            std::sort(v.begin(),v.end(), [](Item* lhs, Item* rhs){
                return lhs->getType() > rhs->getType();
            });
        }
    }else if(att == "LEVEL"){
        // If the attribute is "LEVEL", sort the items by their levels.
        if(A){
            // If A is true, sort in ascending order.
            std::sort(v.begin(),v.end(), [](Item* lhs, Item* rhs){
                return lhs->getLevel() < rhs->getLevel();
            });
        }else{
            // If A is false, sort in descending order.
            std::sort(v.begin(),v.end(), [](Item* lhs, Item* rhs){
                return lhs->getLevel() > rhs->getLevel();
            });
        }
    }else if(att == "VALUE"){
        // If the attribute is "VALUE", sort the items by their gold values.
        if(A){
            // If A is true, sort in ascending order.
            std::sort(v.begin(),v.end(), [](Item* lhs, Item* rhs){
                return lhs->getGoldValue() < rhs->getGoldValue();
            });
        }else{
            // If A is false, sort in descending  order.
            std::sort(v.begin(),v.end(), [](Item* lhs, Item* rhs){
                return lhs->getGoldValue() > rhs->getGoldValue();
            });
        }
    }else{
        // If the attribute is not "NAME", "TYPE", "LEVEL", or "VALUE", sort the items by the time they were picked up.
        if(A){
            // If A is true, sort in ascending order.
            std::sort(v.begin(),v.end(), [](Item* lhs, Item* rhs){
                return lhs->getTimePickedUp() < rhs->getTimePickedUp();
            });
        }else{
            // If A is false, sort in descending  order.
            std::sort(v.begin(),v.end(), [](Item* lhs, Item* rhs){
                return lhs->getTimePickedUp() > rhs->getTimePickedUp();
            });
        }
    }
}
