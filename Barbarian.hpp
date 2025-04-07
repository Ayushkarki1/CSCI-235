/*
Ayush karki
Algorithmic Adventures: 
Into the Recursive Realms
Project 2 - Pick your role: Inheritance
CSCI 235 Fall 2023
Barbarian.hpp
*/ 
#ifndef BARBARIAN_HPP
#define BARBARIAN_HPP
#include <string>
#include "Character.hpp"
#include <vector>
using namespace std;

/*
Data Types
The Barbarian class must have the following private member variables:

- A string representing their main weapon
- A string representing their offhand weapon
- A boolean indicating if they are enraged
 */
class Barbarian : public Character {

    private:
    std::string main_weapon_;
    std::string secondary_weapon_;
    bool enraged_;
//Constructors
/**
    Default constructor.
    Default-initializes all private members. Default character name: "NAMELESS". 
    Booleans are default-initialized to False. 
    Default weapons: "NONE". 
*/
    public:
    Barbarian();
/**
    Parameterized constructor.
    @param      : The name of the character (a const string reference)
    @param      : The race of the character (a const string reference)
    @param      : The character's vitality (an integer). Default to 0
    @param      : The character's max armor level (an integer). Default to 0
    @param      : The character's level (an integer). Default to 0
    @param      : A flag indicating whether the character is an enemy. Default to false
    @param      : The character's main weapon (a const string reference). 
                  String inputs can be in lowercase, but must be converted to uppercase 
                  when setting the variable. Only alphabetical characters are allowed.
                  Default to "NONE"
    @param      : The character's offhand weapon (a const string reference). 
                  String inputs can be in lowercase, but must be converted to uppercase 
                  when setting the variable. Only alphabetical characters are allowed.
                  Default to "NONE"
    @param      : A flag indicating whether the character is enraged. Default to false
    @post       : The private members are set to the values of the corresponding parameters. 
                : If the main and secondary weapons are not provided or invalid, the variables                    are set to "NONE".
*/
    Barbarian(const std::string& name, const std::string& race, int vitality = 0, int armor = 0, int level = 0, bool enemy = false, const std::string& mainweapon = "NONE", const std::string& weapon = "NONE", bool enraged = false);

//Unique Methods
/**
    @param    : a reference to a string representing the Character's main weapon
    @post     : sets the private member variable to the value of the parameter. 
                Only alphabetical characters are allowed.
                String inputs can be in lowercase, but must be converted to uppercase when 
                setting the variable.
                If the given input is invalid (i.e contains numbers), do nothing and return false
    @return   : true if setting the variable was successful, false otherwise.

setMainWeapon



    @return   : a string of the Character's main weapon

getMainWeapon


    @param    : a reference to a string representing the Character's secondary weapon
    @post     : sets the private member variable to the value of the parameter. 
                Only alphabetical characters are allowed.
                String inputs can be in lowercase, but must be converted to uppercase when 
                setting the variable.
              : If the given input is invalid (i.e contains numbers), do nothing and return false
    @return   : true if setting the variable was successful, false otherwise.

setSecondaryWeapon



   @return    : a string of the Character's secondary weapon

getSecondaryWeapon


  @param      : a reference to a bool
  @post       : sets the private member variable to the value of the parameter.

setEnrage



  @return  : a boolean of whether the Character is enraged

getEnrage


  @post   : sets the enraged variable to the opposite of what it was

toggleEnrage
*/
    
    bool setMainWeapon(const std::string& mainweapon) ;
    std::string getMainWeapon() const;
    bool setSecondaryWeapon(const std::string& weapon) ;
    std::string getSecondaryWeapon() const ;
    void setEnrage(const bool& enraged);
    bool getEnrage() const;
    void toggleEnrage();
};



#endif