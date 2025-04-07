/*
Ayush Karki
CSCI235 Fall 2023
Project 4 - Task 2 Modify the Tavern class
Tavern.cpp declares the Tavern class along with its private and public members

Task 2 - summary:
*implement a parameterized constructor
add the following public memebers:
-displayCharacter
-displayRace
-taintedstew
*/
#include "Tavern.hpp"
#include "Barbarian.hpp"
#include "Mage.hpp"
#include "Scoundrel.hpp"
#include "Ranger.hpp"
#include <iostream>
using namespace std;

/*Task 2: Modify the Tavern class

Modify the Tavern to now store pointers to Characters, rather than Character objects
*/

/** Default Constructor **/
Tavern::Tavern() : ArrayBag<Character*>(), level_sum_{0}, num_enemies_{0}
{
}


//Implement a parameterized constructor

/**
    @param: the name of an input file
    @pre: Formatting of the csv file is as follows (each numbered item appears separated by comma, only one value for each numbered item):
1. Name: An uppercase string
2. Race: An uppercase string [HUMAN, ELF, DWARF, LIZARD, UNDEAD]
3. Subclass: An uppercase string [BARBARIAN, MAGE, SCOUNDREL, RANGER]
4. Level/Vitality/Armor: A positive integer
5. Enemy: 0 (False) or 1 (True)
6. Main: Uppercase string or strings representing the main weapon (Barbarian and Mage), Dagger type (Scoundrel), or arrows (Ranger). A ranger's arrows are of the form [TYPE] [QUANTITY];[TYPE] [QUANTITY], where each arrow type is separated by a semicolon, and the type and its quantity are separated with a space.
7. Offhand: An uppercase string that is only applicable to Barbarians, and may be NONE if the Barbarian does not have an offhand weapon, or if the character is of a different subclass.
8. School/Faction: Uppercase strings that represent a Mage's school of magic: [ELEMENTAL, NECROMANCY, ILLUSION] or a Scoundrel's faction: [CUTPURSE, SHADOWBLADE, SILVERTONGUE], and NONE where not applicable
9. Summoning: 0 (False) or 1 (True), only applicable to Mages (summoning an Incarnate) and Rangers (Having an Animal Companion)
10. Affinity: Only applicable to Rangers. Affinities are of the form [AFFINITY1];[AFFINITY2] where multiple affinities are separated by a semicolon. Th value may be NONE for a Ranger with no affinities, or characters of other subclasses.
11. Disguise: 0 (False) or 1 (True), only applicable to Scoundrels, representing if they have a disguise.
12. Enraged: 0 (False) or 1 (True), only applicable to Barbarians, representing if they are enraged.
    @post: Each line of the input file corresponds to a Character subclass and dynamically allocates Character derived objects, adding them to the Tavern.
*/
Tavern::Tavern (const std::string& file) {
  // Open the input file for reading character data
    std::ifstream inputfile(file) ;
    // Check if the file was successfully opened, if not exit the program
    if (inputfile.fail()) {
        std::cerr << "Error: Unable to open input file" << std::endl;
        exit(1);

    }
    else{
        std::string junk;
        std::getline (inputfile, junk) ;
        std::string name, race, subclass, main, offhand, school, affinity;
        int level, vitality, armor;
        bool enemy, summoning, disguise, enraged;
        std::string line;
        std::string x;
        std::vector<Arrows> arrows;
        std::vector <std::string> affinities;
        while  (std::getline(inputfile, line)){
            std::istringstream ss(line);
            // Read data from the string stream into corresponding variables
            std::getline(ss, name, ',');
            std::getline(ss, race, ',');
            std::getline(ss, subclass, ',');
            std::getline(ss, x, ',');
            std::cout <<x << std::endl;
            level = std::stoi(x);
            std::getline(ss, x, ',');
            std::cout << x << std::endl;
            vitality = std::stoi(x);
            std::getline(ss, x, ',');
            std::cout << x << std::endl;
            armor = std::stoi(x);
            std::getline(ss, x, ',');
            std::cout << x <<std::endl;
            enemy = std::stoi(x);
            std::getline(ss, main, ',');
            std::getline(ss, offhand, ',');
            std::getline(ss, school, ',');
            std::getline(ss, x, ',');
            std::cout << x << std::endl;
            summoning = std::stoi(x);
            std::getline(ss, affinity, ',');
            std::getline(ss, x, ',');
            std::cout << x << std::endl;
            disguise = std::stoi(x);
            std::getline(ss, x, ',');
            std::cout << x << std::endl;
            enraged = std::stoi(x);

            // Create appropriate Character subclass objects based on 'subclass' variable
            Character* characters;
            if (subclass == "RANGER" ){
              std::istringstream mainstream(main) ;
              while (std::getline(mainstream, x, ';'))
              {
                std::istringstream arrowstring(x);
                std::string t = "";
                int quantity;
                arrowstring >> t >> quantity;
                Arrows arrowst;
                arrowst.type_ = t;
                arrowst.quantity_ = quantity;
                arrows.push_back(arrowst);
                }
                std::istringstream affinitystring(affinity);
                while (std::getline(affinitystring, x, ';'))
                {
                  affinities.push_back(x);
                  }
                  }
                  // Create Character objects based on subclasses and add them to the Tavern
                  if (subclass == "BARBARIAN") {
                    Character* characters = new Barbarian(name, race, vitality, armor, level, enemy, main, offhand, enraged);
                    enterTavern(characters);
                  } 
                  else if (subclass == "MAGE") {
                    Character* characters = new Mage(name, race, vitality, armor, level, enemy, school, main, summoning);
                    enterTavern(characters);
                  }
                  else if (subclass == "RANGER") {
                    Character* characters = new Ranger(name, race, vitality, armor, level, enemy, arrows, affinities, summoning);
                    enterTavern(characters);
                  }
                    else if (subclass == "SCOUNDREL") {
                      Character* characters = new Scoundrel(name, race, vitality, armor, level, enemy, main, school, disguise);
                      enterTavern(characters);
                  }
                  // Clear temporary vectors for arrows and affinities for the next iteration
                  arrows.clear();
                  affinities.clear();
                  }
                  }
}

/** 
    @param:   A reference to a Character entering the Tavern
    @return:  returns true if a Character was successfully added to items_, false otherwise
    @post:    adds Character to the Tavern and updates the level sum and the enemy count if the character is an enemy.
**/
bool Tavern::enterTavern(Character* a_character)
{
  if(add(a_character))
  {
    level_sum_ += a_character->getLevel();
    if(a_character->isEnemy())
      num_enemies_++;
     
    return true;
  }
  else
  {
    return false;
  }
}


/** @param:   A reference to a Character leaving the Tavern  
    @return:  returns true if a character was successfully removed from items_, false otherwise
    @post:    removes the character from the Tavern and updates the level sum and the enemy count if the character is an enemy.
**/
bool Tavern::exitTavern(Character* a_character)
{
  if(remove(a_character))
  {
    level_sum_ -= a_character->getLevel();
    if(a_character->isEnemy())
      num_enemies_--;
      
    return true;
  }
  return false;
}



/** 
    @return:  The integer level count of all the characters currently in the Tavern
    **/
    int Tavern::getLevelSum()
    {
      return level_sum_;
    }



/** 
    @return:  The average level of all the characters in the Tavern
    @post:    Considers every character currently in the Tavern, updates the average level of the Tavern rounded to the NEAREST integer, and returns the integer value.
**/
int Tavern::calculateAvgLevel()
{
   return (level_sum_>0) ? round(double(level_sum_) / item_count_) : 0.0;

}



/** 
    @return:  The integer enemy count of the Tavern
    **/
    int Tavern::getEnemyCount()
    {
      return num_enemies_;
    }



/** 
    @return:  The percentage (double) of all the enemy characters in the Tavern
    @post:    Considers every character currently in the Tavern, updates the enemy percentage of the Tavern rounded to 2 decimal places, and returns the double value.
**/
double Tavern::calculateEnemyPercentage()
{
  double enemy_percent = (num_enemies_>0) ?  (double(num_enemies_) / item_count_) * 100: 0.0;
  return std::ceil(enemy_percent*100.0) / 100.0; //round up to to decimal places
 
}


/** 
    @param:   A string reference to a race 
    @return:  An integer tally of the number of characters in the Tavern of the given race
**/
int Tavern::tallyRace(const std::string &race)
{
  int frequency = 0;
  int curr_index = 0;   
  while (curr_index < item_count_)
  {
    if (items_[curr_index]->getRace() == race)
    {
      frequency++;
    } 

    curr_index++; 
  }

  return frequency;
}


/**
  @post:    Outputs a report of the characters currently in the tavern in the form:
  "Humans: [x] \nElves: [x] \nDwarves: [x] \nLizards: [x] \nUndead: [x] \n\nThe average level is: [x] \n[x]% are enemies.\n\n"

  Example output: 
  Humans: 5
  Elves: 8
  Dwarves: 3
  Lizards: 7
  Undead: 2

  The average level is: 16
  24% are enemies.
*/
void Tavern::tavernReport()
{
  int humans = tallyRace("HUMAN");
  int elves = tallyRace("ELF");
  int dwarves = tallyRace("DWARF");
  int lizards = tallyRace("LIZARD");
  int undead = tallyRace("UNDEAD");
  
  std::cout << "Humans: " << humans << std::endl;
  std::cout << "Elves: " << elves << std::endl;
  std::cout << "Dwarves: " << dwarves << std::endl;
  std::cout << "Lizards: " << lizards << std::endl;
  std::cout << "Undead: " << undead << std::endl;
  std::cout << "\nThe average level is: " << calculateAvgLevel() << std::endl;
  std::cout << std::fixed << std::setprecision(2) << calculateEnemyPercentage() << "% are enemies.\n\n";
}

//Add the following public member functions

/** displayCharacters-
    @post: For every character in the tavern, displays each character's information
*/
void Tavern::displayCharacters() const {
    for (int i = 0; i < item_count_; ++i) {
        items_[i]->display();
    }
}

/** displayRace-
    @param: a string reference to a race
    @post: For every character in the tavern of the given race (only exact matches to the input string),
           displays each character's information
*/

void Tavern::displayRace(const std::string& race) const {
  
  // Initialize the index to iterate through the items in the tavern
    int curr_index = 0;

    // Loop through the items in the tavern
    while (curr_index < item_count_) {
      // Loop through the items in the tavern
        if (items_[curr_index]->getRace() == race) {

            items_[curr_index]->display();

        }
        // Move to the next character in the tavern
        curr_index++;
    }

    }

/**  taintedStew- 
    @post: Every character in the tavern eats a tainted stew.
*/
void Tavern::taintedStew() const {
   // Loop through each character in the tavern
    for (int i = 0; i < item_count_; ++i) {
       // Call the eatTaintedStew() function for the current character
        items_[i]->eatTaintedStew();
    }
}
