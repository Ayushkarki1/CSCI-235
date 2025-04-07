/*
Ayush Karki
CSCI-235 fall 2023
Project 3
Task C - Tavern.hpp
Prof - Tiziana Ligorio
*/

//Task 3: Implement the Tavern class as a subclass of ArrayBag:
//The Tavern is  subclass of ArrayBag that stores Character objects

#ifndef TAVERN_HPP
#define TAVERN_HPP
#include "ArrayBag.hpp"
#include "Character.hpp"
#include <vector>
using namespace std;

/*Data Types
The Tavern class must have the following private member variables:*/
 class Tavern : public ArrayBag<Character>{
    private:
    //- An integer sum of the levels of all the characters currently in the tavern
    int sumLevel;
    //- An integer count of all the characters currently in the Tavern that are marked as enemies
    int enemy;
//- An integer count of all the characters currently in the Tavern that are marked as enemies
    public:
/**
    Default constructor.
    Default-initializes all private members. 
*/
    Tavern();

//Unique Methods

/** @param:   A const reference to a Character entering the Tavern
    @return:  returns true if a Character was successfully added to the tavern (i.e. items_),                 false otherwise
    @post:    adds Character to the Tavern and updates the level sum and the enemy count 
              if the character is an enemy.
enterTavern
**/
    bool enterTavern(const Character& character);



/** @param:   A const reference to a Character leaving the Tavern  
    @return:  returns true if a character was successfully removed from the tavern (i.e. items_),               false otherwise
    @post:    removes the character from the Tavern and updates the level sum and the enemy count
              if the character is an enemy.
exitTavern
**/
    bool exitTavern(const Character& character_);



/** 
    @return:  The integer level count of all the characters currently in the Tavern
getLevelSum
**/
    int getLevelSum()const;



/** 
    @return:  The average level of all the characters in the Tavern
    @post:    Computes the average level of the Tavern rounded to the NEAREST integer.
calculateAvgLevel
**/
    int calculateAvgLevel() const;



/** 
    @return:  The integer enemy count of the Tavern
getEnemyCount
**/
    int getEnemyCount() const;



/** 
    @return:  The percentage (double) of all the enemy characters in the Tavern
    @post:    Computes the enemy percentage of the Tavern rounded up to 2 decimal places.
calculateEnemyPercentage 
**/
    double calculateEnemyPercentage() const;



/** 
    @param:   A const reference to a string representing a character Race with value in 
              ["NONE", "HUMAN", "ELF", "DWARF", "LIZARD", "UNDEAD"]
    @return:  An integer tally of the number of characters in the Tavern of the given race. 
              If the argument string does not match one of the expected race values, 
              the tally is zero. NOTE: no pre-processing of the input string necessary, only                  uppercase input will match.
tallyRace 
**/
    int tallyRace(const std::string& race);



/**
@post:      Outputs a report of the characters currently in the tavern in the form:
            "Humans: [x] \nElves: [x] \nDwarves: [x] \nLizards: [x] \nUndead: [x] \n\nThe average             level is: [x] \n[x]% are enemies.\n"
            Note that the average level should be rounded to the NEAREST integer, and the enemy             percentage should be rounded to 2 decimal places.

            Example output: 
            Humans: 3
            Elves: 5
            Dwarves: 8
            Lizards: 6
            Undead: 0

            The average level is: 7
            46.67% are enemies.
tavernReport
*/
    void tavernReport();
};

#endif