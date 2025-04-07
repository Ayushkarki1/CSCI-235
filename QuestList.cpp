/*
Ayush Karki
CSCI235 Fall 2023
Project 5 -  Quest Management with Doubly Linked Lists
QuestList.cpp


This project consists of three tasks:

-implement the Quest struct  within the interface of the QuestList class (QuestList.hpp) but outside of the QuestList class definition.

-will implement the `QuestList ` class to store POINTERS to Quest objects as a subclass of DoublyLinkedList. 

-will TEST the `QuestList ` class with the provided debug file debug.csv. 
*/

#include "QuestList.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include "DoublyLinkedList.hpp"


// QuestList class implementations - Task 2: Implement the QuestList class as a subclass of DoublyLinkedList
//constructors

//The QuestList class will store POINTERS to Quest objects, and must have the following public member functions:
//Constructors


/**
    Default Constructor
QuestList()
*/
QuestList::QuestList() : DoublyLinkedList<Quest*>() {}

/**
    @param: a reference to string name of an input file
    @pre: Formatting of the csv file is as follows:
        Title: A string
        Description: A string
        Completion Status: 0 (False) or 1 (True)
        Experience Points: A non negative integer
        Dependencies: A list of Quest titles of the form [QUEST1];[QUEST2], where each quest is separated by a semicolon. The value may be NONE.
        Subquests: A list of Quest titles of the form [QUEST1];[QUEST2], where each quest is separated by a semicolon. The value may be NONE.
    Notes:
        - The first line of the input file is a header and should be ignored.
        - The dependencies and subquests are separated by a semicolon and may be NONE.
        - The dependencies and subquests may be in any order.
        - If any of the dependencies or subquests are not in the list, they should be created as new quests with the following information:
            - Title: The title of the quest
            - Description: "NOT DISCOVERED"
            - Completion Status: False
            - Experience Points: 0
            - Dependencies: An empty vector
            - Subquests: An empty vector
        - However, if you eventually encounter a quest that matches one of the "NOT DISCOVERED" quests while parsing the file, you should update all the quest details.
        Hint: update as needed using addQuest()
        

    @post: Each line of the input file corresponds to a quest to be added to the list. No duplicates are allowed.

*/
QuestList::QuestList(const std::string& inputFile){
    std::ifstream fin(inputFile);
    // Check if the file can be opened successfully
    if (fin.fail()){
        std::cerr << "File could not be open";
        exit(1);
    }
    std::string line;
    std::getline(fin,line);// Ignore the header line in the CSV file
    std::string qTitle, qDescription, qStatus, qExp, qDependencies, qSubquests;
    // Loop through each line in the CSV file to read quest data
    while(std::getline(fin,line)){
        // Remove trailing white spaces from each line
        int end = line.size();  
        while (end > 0 && std::isspace(line[end-1])) end--; 
        if (end > 0) line = line.substr(0, end);  
        std::istringstream iss(line);
        getline(iss,qTitle,',');
        getline(iss,qDescription,',');
        getline(iss,qStatus,',');
        getline(iss,qExp,',');
        getline(iss,qDependencies,',');
        getline(iss,qSubquests,',');
        // Create a new Quest object with the extracted data
        Quest* quest = new Quest(qTitle,qDescription,stoi(qStatus),stoi(qExp),{},{});
        // Process dependencies if they exist
        if(qDependencies != "NONE"){std::stringstream qDepens(qDependencies);
            while(getline(qDepens, qDependencies, ';')){
                // Add new quests if they don't exist in the list
                if(!contains(qDependencies)){addQuest(qDependencies,"NOT DISCOVERED",false,0,{},{});}quest->dependencies_.push_back(getItem(getPosOf(qDependencies)));}}
        if(qSubquests != "NONE"){std::stringstream qSub(qSubquests);
            while(getline(qSub, qSubquests, ';')){if(!contains(qSubquests)){addQuest(qSubquests,"NOT DISCOVERED",false,0,{},{});}
            // Add the dependency to the current quest
            quest->subquests_.push_back(getItem(getPosOf(qSubquests)));}}
                addQuest(quest);}}

//Unique Methods


/**
    @param: A string reference to a quest title
    @return: The integer position of the given quest if it is in the QuestList, -1 if not found.
*/
int QuestList::getPosOf(const std::string& title){
     // Start from the head of the list
    Node<Quest*>* quest = first_;
    // Iterate through the list
    for(int i =0; i < item_count_; i++){
        // Check if the current quest has the specified title
        if(quest->getItem()->title_ == title){
            return i; // Return the position if found
        }
        // Move to the next node in the list
        quest = quest->getNext();
    }
    // Return -1 if the quest is not found
    return -1;
}


/**
    @param: A string reference to a quest title
    @return: True if the quest with the given title is already in the QuestList
*/
bool QuestList::contains(const std::string& title){
    // Check if the position is not -1, indicating the quest is in the list
    return getPosOf(title) != -1;
}



/**
    @pre: The given quest is not already in the QuestList
    @param:  A pointer to a Quest object
    @post:  Inserts the given quest pointer into the QuestList. Each of its dependencies and subquests are also added to the QuestList IF not already in the list.
            If the quest is already in the list but is marked as "NOT DISCOVERED", update its details. (This happens when a quest has been added to the list through a dependency or subquest list)
           
    @return: True if the quest was added or updated successfully, False otherwise
*/
bool QuestList::addQuest(Quest* quest){
    // Check if the quest is already in the list
    Quest* temp = getItem(getPosOf(quest->title_));
    bool added = true;
    // If the quest is not in the list, insert it
    if (temp == nullptr){
        added = insert(item_count_,quest);}
    // If the quest is in the list but marked as "NOT DISCOVERED," update its details
    else if (temp != nullptr && temp->description_ == "NOT DISCOVERED"){
        temp->description_ = quest->description_;
        temp->experience_points_ = quest->experience_points_;
        temp->completed_ = quest->completed_;
        temp->dependencies_ = quest->dependencies_;
        temp->subquests_ = quest->subquests_;
        added = false;}
    // Add dependencies to the list if not present
    if(!quest->dependencies_.empty()){
        for (int i = 0; i < quest->dependencies_.size(); i++){
            if(!contains(quest->dependencies_.at(i)->title_)){
                insert(item_count_,quest->dependencies_.at(i));}}}
    // Add subquests to the list if not present
    if(!quest->subquests_.empty()){
        for (int i = 0; i < quest->subquests_.size(); i++){
            if(!contains(quest->subquests_.at(i)->title_)){
                insert(item_count_,quest->subquests_.at(i));}}}return added;}


/**
    @param:  A reference to string representing the quest title
    @param:  A reference to string representing the quest description
    @param:  A reference to boolean representing if the quest is completed
    @param:  An reference to int representing experience points the quest rewards upon completion 
    @param:  A reference to vector of Quest pointers representing the quest's dependencies
    @param:  A reference to vector of Quest pointers representing the quest's subquests
    @post:   Creates a new Quest object and inserts a pointer to it into the QuestList. 
             If the quest is already in the list but is marked as "NOT DISCOVERED", update its details. (This happens when a quest has been added to the list through a dependency or subquest list)
             Each of its dependencies and subquests are also added to the QuestList IF not already in the list.
             

    @return: True if the quest was added or updated successfully, False otherwise

*/
bool QuestList::addQuest(const std::string& title, const std::string& description,const bool& complete, const int& exp,const std::vector<Quest*>& dependencies,const std::vector<Quest*>& subquest){
    // Create a new Quest object with the provided details
    Quest* quest = new Quest(title,description,complete,exp,dependencies,subquest); 
    // Add the quest to the QuestList and return the result
    return addQuest(quest);
}


/**
    @param:  A Quest pointer
    @return: A boolean indicating if all the given quest's dependencies are completed
*/
bool QuestList::dependenciesComplete( Quest* quest){
    // Iterate through the dependencies of the given quest
    for (const Quest* dependency : quest->dependencies_) {
    // Check if the dependency is not completed
        if (!dependency->completed_) {return false;}}
    // All dependencies are completed
    return true;
}


/**
    @param: A Quest pointer
    @return: A boolean if the given quest is available.
    Note: For a quest to be available, it must not be completed, and its dependencies must be complete.
*/
bool QuestList::questAvailable( Quest* quest){
    // Check if the quest is not completed and its dependencies are complete
    if (!quest->completed_){return dependenciesComplete(quest);}
    // Quest is not available if it's already completed
    return false;
}



/**
    @param: A Quest pointer
    @post: Prints the quest title and completion status
    The output should be of the form:
    [Quest Title]: [Complete / Not Complete]
    [Quest Description]\n\n
*/
void QuestList::printQuest( Quest* quest){
    // Output the quest title and completion status
    std::cout << quest->title_ << ": " << ((quest->completed_)?"Complete\n":"Not Complete\n");
    // Output the quest description with an additional newline for separation
    std::cout << quest->description_ << "\n\n";
}





//calculating functions 

/**
    @return: An integer sum of all the experience gained
    Note: This should only include experience from completed quests 
*/
int QuestList::calculateGainedExperience() const{
    // Initialize the sum to 0
    int sum = 0;
    // Start at the beginning of the QuestList
    Node<Quest*>* quest = first_;
    // Iterate through the list
     while (quest) {
        // If the quest is completed, add its experience points to the sum
        if (quest->getItem()->completed_) sum += quest->getItem()->experience_points_;
        // Move to the next quest in the list
        quest = quest->getNext();}
    // Return the total sum of experience gained
        return sum;
}


/**
    @param: A quest pointer to a main quest
    @return: An integer sum of all the experience that can be gained from completing the main quest AND all its subquests.
    Note: Also consider the potential experience if a subquest itself has subquests.
*/
int QuestList::calculateProjectedExperience( Quest* x){
    // If the main quest has no subquests, return its experience points
    if (x->subquests_.size() == 0) return x->experience_points_;
    int sum = 0;
    // Iterate through subquests and recursively calculate projected experience
    for (int i = 0; i < x->subquests_.size(); i++) sum += calculateProjectedExperience(x->subquests_[i]);
    // Return the total sum of projected experience
    return x->experience_points_ + sum;
}


/**
    @param: A quest pointer to a main quest
    @return: An integer sum of all the experience that has already been gained by completing the given quest's subquests.
    Note: Also consider the experience gained if a completed subquest itself has subquests.  
*/
int QuestList::calculatePathwayExperience( Quest* x){
    // If the main quest is completed and has no subquests, return its experience points
    if(x->completed_ && x->subquests_.size() == 0) return x->experience_points_;
    // If the main quest is not completed and has no subquests, return 0
    if(!x->completed_ && x->subquests_.size() == 0 ) return 0;
    int sum = 0;
    // Iterate through subquests and recursively calculate experience gained
    for (int i = 0; i < x->subquests_.size(); i++) sum += calculatePathwayExperience(x->subquests_[i]);
    // If the main quest is completed, add its experience points to the sum
    if (x->completed_) return x -> experience_points_ + sum;
    else return sum;
}



//QuestHistory

/**
    @param: A string reference to a filter with a default value of "NONE".
    @post: With default filter "NONE": Print out every quest in the list.
           With filter "COMPLETE":   Only print out the completed quests in the list.
           With filter "INCOMPLETE": Only print out the incomplete quests in the list.
           With filter "AVAILABLE":  Only print out the available quests in the list.
           If an invalid filter is passed, print "Invalid Filter\n"
    Printing quests should be of the form:
    [Quest title]: [Complete / Not Complete]  
    [Quest description]\n
*/
void QuestList::questHistory(const std::string& filter){
    // Check the filter and print quests accordingly
    if (filter == "COMPLETE") {
        Node<Quest*>* current = getHeadNode();
        while (current != nullptr) {
            // Print only completed quests
            if (current->getItem()->completed_) {printQuest(current->getItem());}current = current->getNext();}
    } else if (filter == "INCOMPLETE") {
        Node<Quest*>* current = getHeadNode();
        while (current != nullptr) {
            // Print only incomplete quests
            if (!current->getItem()->completed_) {printQuest(current->getItem());}current = current->getNext();}
    } else if (filter == "AVAILABLE") {
        Node<Quest*>* current = getHeadNode();
        while (current != nullptr) {
            // Print only available quests
            if (questAvailable(current->getItem())) {printQuest(current->getItem());}current = current->getNext();}} else if (filter == "NONE") { Node<Quest*>* current = getHeadNode();
        while (current != nullptr) {
            // Print all quests
            printQuest(current->getItem()); current = current->getNext();}} 
        else {
        // Invalid filter, print a message
        std::cout << "Invalid Filter\n";}
}



//printQuestdetails and its helper function
/**
    @param: A quest pointer to a main quest
    @post:  Outputs subquest pathway. Print quest names with two spaces ("  ") of indentation for each subquest, recursively.
            Also print the percentage of experience gained in this pathway, rounded down to the lower integer.
            The format should be of the form:
            [Main Quest] ([Pathway XP] / [Projected XP]% Complete)
                [Subquest0]: [Complete / Not Complete]
                    [Sub-Subquest01]: [Complete / Not Complete]
                        [Sub-Subquest011]: [Complete / Not Complete]
                    [Subquest02]: [Complete / Not Complete]
            Hint: You can write a helper function to print the subquests recursively. If the given quest is already marked as completed, you can assume that all of its subquests are also completed.
*/
void QuestList::printSubquestsRecursive( Quest* quest, int number){
    // Calculate the number of spaces for indentation
    int spaces = number*2;
    // Check if the current quest has no subquests
    if(quest->subquests_.empty()){
        // Print the quest title with completion status
        std::cout << std::string(spaces, ' ') << quest->title_ << ": " << (quest->completed_?"Complete":"Not Complete") << std::endl; 
        return;
    }
    // Recursively print subquests
    for (const auto& subquest : quest->subquests_) {printSubquestsRecursive(subquest, number + 1);}
}
void QuestList::printQuestDetails(Quest* x){
    // Print main quest title with completion percentage
    std::cout << x->title_ << "(" << floor(double(calculatePathwayExperience(x))/double(calculateProjectedExperience(x))*100) << "% Complete)\n";
    // Check if the main quest is completed and has subquests
    if (x->completed_ && !x->subquests_.empty()) {
            // Print completion status of subquests
            for (const auto& subquest : x->subquests_) {
                std::cout << subquest->title_ << ": " << (subquest->completed_ ? "Complete" : "Not Complete") << std::endl;}} 
                // Print the entire subquest pathway recursively
                else {for (const auto& subquest : x->subquests_) {printSubquestsRecursive(subquest, 1);}}
}



//Quest query and its helper function
/**
    @param: A string reference to a quest title
    @post:  Prints a list of quests that must to be completed before the given quest can be started (incomplete dependencies).
            If any of the quest's incomplete dependencies have an incomplete dependency, recursively print the quests that need to be done in order, indenting incomplete quests. 
            The indentation for incomplete quests is 2 spaces: "  "    
            The format of the list should be of the following forms for each different case:

            Query: [Quest Title]
            No such quest.
    
            Query: [Quest Title]
            Quest Complete
    
            Query: [Quest Title]
            Ready: [Quest Title]
    
            Query: [Quest Title]
            Ready: [Dependency0]
              [Quest Title]
            
            Query: [Quest Title]
            Ready: [Dependency0]
            Ready: [Dependency1]
              [Quest Title]
    
            Query: [Quest Title]
            Ready: [Dependency0]
            Ready: [Dependency1]
              [Dependency2]
              [Quest Title]
              
     If the given quest title is not found in the list, print "No such quest."
*/
void QuestList::questQuery(const std::string& title){
    // Print the query title
    std::cout<< "Query: " << title <<"\n";
    // Check if the quest title exists in the list
    if(!contains(title)){
        std::cout << "No such quest.\n"; 
        return;}
    // Get the quest pointer
    Quest* quest = getPointerTo(getPosOf(title))->getItem();
    // Check if the quest is already completed
    if(quest->completed_){std::cout << "Quest Complete\n";return;}
    else{ 
        // Call the helper function to print the list of quests
        QueryHelper (quest);}
}

void QuestList::QueryHelper( Quest* quest){
    // Check if the quest is available or has completed dependencies
    if (questAvailable(quest) || dependenciesComplete(quest)) {
        std::cout<<"Ready: "<< quest->title_<< "\n";
        return;}
    // Recursively print incomplete dependencies with indentation
    for (int i = 0; i < quest->dependencies_.size(); i++) {if (!quest->dependencies_[i]->completed_){QueryHelper(quest->dependencies_[i]);}}
    // Print the current quest with indentation
    std::cout << "  " << quest->title_<< "\n";
}
