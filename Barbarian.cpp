/*
Ayush karki
Algorithmic Adventures: 
Into the Recursive Realms
Project 2 - Pick your role: Inheritance
CSCI 235 Fall 2023
Barbarian.cpp
*/ 
#include "Barbarian.hpp"
#include <iostream>
using namespace std;
#include <string>
#include <cctype> 

//Constructors
/**
    Default constructor.
    Default-initializes all private members. Default character name: "NAMELESS". 
    Booleans are default-initialized to False. 
    Default weapons: "NONE". 
*/
Barbarian::Barbarian() : Character(), main_weapon_{"NONE"}, secondary_weapon_{"NONE"}, enraged_{false}{}
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
Barbarian::Barbarian(const std::string& name, const std::string& race, int vitality, int armor, int level, bool enemy, const std::string& mainweapon, const std::string& weapon, bool enraged) : Character(name, race, vitality, armor, level, enemy)
{
    if (setMainWeapon(mainweapon) == false) 
    {
        main_weapon_ = "NONE"; 
    }
    if (setSecondaryWeapon(weapon) == false) 
    {
        secondary_weapon_ = "NONE"; 
    }
    enraged_ = enraged;
}


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
**/
bool Barbarian::setMainWeapon(const std::string& mainweapon){
     main_weapon_ ="";
    for (int i = 0; i < mainweapon.size(); i++){
    if (isalpha(mainweapon[i])){
        main_weapon_ += toupper(mainweapon[i]);
    }else {
        return false;
    }
    }
    return true;
}
/**
    @return   : a string of the Character's main weapon
getMainWeapon
**/
std::string Barbarian::getMainWeapon() const{
    return main_weapon_;
}
/**
    @param    : a reference to a string representing the Character's secondary weapon
    @post     : sets the private member variable to the value of the parameter. 
                Only alphabetical characters are allowed.
                String inputs can be in lowercase, but must be converted to uppercase when 
                setting the variable.
              : If the given input is invalid (i.e contains numbers), do nothing and return false
    @return   : true if setting the variable was successful, false otherwise.
setSecondaryWeapon
**/
bool Barbarian::setSecondaryWeapon(const std::string& weapon) 
{
    secondary_weapon_ ="";
    for (int i = 0; i < weapon.size(); i++)
    {
    if (isalpha(weapon[i]))
    {
        secondary_weapon_ += toupper(weapon[i]);
    }
    else 
    {
        return false;
    }
    }
    return true;
}
/**
   @return    : a string of the Character's secondary weapon
getSecondaryWeapon
**/
std::string Barbarian::getSecondaryWeapon() const {
    return secondary_weapon_;
}
/**
  @param      : a reference to a bool
  @post       : sets the private member variable to the value of the parameter.
setEnrage
**/
void Barbarian::setEnrage(const bool& enraged){
    enraged_ = enraged;
}
/**
  @return  : a boolean of whether the Character is enraged
getEnrage
**/
bool Barbarian::getEnrage() const{
    return enraged_; 
}
/**
  @post   : sets the enraged variable to the opposite of what it was
toggleEnrage**/
void Barbarian::toggleEnrage(){
    enraged_ =! enraged_;
}



