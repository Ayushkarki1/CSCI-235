#include <iostream>
#include "Character.hpp"
#include "Mage.hpp"
#include "Scoundrel.hpp"
#include "Ranger.hpp"
#include "Barbarian.hpp"

int main(){
/*
2.1.1 Instantiate a default Mage
  - Sets its name, race, vitality, and armor levels using the appropriate setter functions
Name: defaultMage
Race: ELF
Vitality: 5
Armor: 3
Level: 2
Enemy: TRUE

- Print out information for default Mage 
  
2.1.2 Instantiate a Mage with the parameterized constructor with the following character details:
Name: SPYNACH
Race: ELF
Vitality: 6
Armor: 4
Level: 4
Enemy: FALSE

2.1.3 Set SPYNACH's unique private member variables to the following:
School of Magic: Illusion
Weapon: Wand
Summon Incarnate: TRUE

- Print out information for SPYNACH 
*/
    Mage defaultmage;
    defaultmage.setName("defaultmage");
    defaultmage.setRace("ELF");
    defaultmage.setVitality(5);
    defaultmage.setArmor(3);
    defaultmage.setLevel(2);
    defaultmage.setEnemy();

    cout << defaultmage.getName()<< "is a level" << defaultmage.getLevel() << " " << defaultmage.getRace() << "."
    <<"\nVitality: " << defaultmage.getVitality()
    <<"\nArmor: " << defaultmage.getArmor()
    <<"\nThey are " << (defaultmage.isEnemy() ? "an enemy" : "not an enemy")
    <<"\nSchool of Magic: " <<defaultmage.getSchool()
    <<"\nWeapon: " << defaultmage.getCastingWeapon()
    <<"\nCan Summon: " << (defaultmage.hasIncarnateSummon() ? "TRUE" : "FALSE") << "\n\n";

    Mage spynach = Mage("SPYNACH", "ELF", 6, 4, 4, false);

    spynach.setSchool("Illusion");
    spynach.setCastingWeapon("Wand");
    spynach.setIncarnateSummon(true);

    cout << spynach.getName()<< "is a level" << spynach.getLevel() << " " << spynach.getRace() << "."
    <<"\nVitality: " << spynach.getVitality()
    <<"\nArmor: " << spynach.getArmor()
    <<"\nThey are " << (spynach.isEnemy() ? "an enemy" : "not an enemy")
    <<"\nSchool of Magic: " <<spynach.getSchool()
    <<"\nWeapon: " << spynach.getCastingWeapon()
    <<"\nCan Summon: " << (spynach.hasIncarnateSummon() ? "TRUE" : "FALSE") << "\n\n";


    ////////////////////////////////////////////////////////////////////////////////////////
/*2.2.1 Instantiate a default Scoundrel
  - Sets its name, race, vitality, and armor levels using the appropriate setter functions
Name: defaultScoundrel
Race: HUMAN
Vitality: 6
Armor: 4
Level: 3
Enemy: TRUE

- Print out information for default Scoundrel 
  
2.2.2 Instantiate a Scoundrel with the parameterized constructor with the following character details:
Name: FLEA
Race: DWARF
Vitality: 12
Armor: 7
Level: 5
Enemy: FALSE

2.2.3 Set FLEA's unique private member variables to the following:
Dagger: Adamant
Faction: Cutpurse
Disguise: TRUE

- Print out information for FLEA*/

    Scoundrel defaultscoundrel;
    defaultscoundrel.setName("defaultscoundrel");
    defaultscoundrel.setRace("HUMAN");
    defaultscoundrel.setVitality(6);
    defaultscoundrel.setArmor(4);
    defaultscoundrel.setLevel(3);
    defaultscoundrel.setEnemy();

    cout << defaultscoundrel.getName()<< "is a level" << defaultscoundrel.getLevel() << " " << defaultscoundrel.getRace() << "."
    <<"\nVitality: " << defaultscoundrel.getVitality()
    <<"\nArmor: " << defaultscoundrel.getArmor()
    <<"\nThey are " << (defaultscoundrel.isEnemy() ? "an enemy" : "not an enemy")
    <<"\nDagger: " <<defaultscoundrel.getDagger()
    <<"\nFaction: " << defaultscoundrel.getFaction()
    <<"\nnDisguise: " << (defaultscoundrel.hasDisguise() ? "TRUE" : "FALSE") << "\n\n";

    Scoundrel flea = Scoundrel("FLEA", "DWARF", 12, 7, 5, false);

    flea.setDagger("Adamant");
    flea.setFaction("Cutpurse");
    flea.setDisguise(true);

    cout << flea.getName()<< "is a level" << flea.getLevel() << " " << flea.getRace() << "."
    <<"\nVitality: " << flea.getVitality()
    <<"\nArmor: " << flea.getArmor()
    <<"\nThey are " << (flea.isEnemy() ? "an enemy" : "not an enemy")
    <<"\nDagger: " <<flea.getDagger()
    <<"\nFaction: " << flea.getFaction()
    <<"\nDisguise " << (flea.hasDisguise() ? "TRUE" : "FALSE") << "\n\n";

///////////////////////////////////////////////////////////////////////////////////////////////////
/*2.4.1 Instantiate a default Barbarian
  - Sets its name, race, vitality, and armor levels using the appropriate setter functions
Name: defaultBarbarian
Race: HUMAN
Vitality: 10
Armor: 5
Level: 5
Enemy: TRUE

- Print out information for default Barbarian
  
2.4.2 Instantiate a Barbarian with the parameterized constructor with the following character details:
Name: BONK
Race: HUMAN
Vitality: 11
Armor: 5
Level: 5
Enemy: TRUE

2.4.3 Set BONK's unique private member variables to the following:
Main Weapon: MACE
Offhand Weapon: ANOTHERMACE
Enraged: TRUE

- Print out information for BONK */

    Barbarian defaultbarbarian;
    defaultbarbarian.setName("defaultbarbarian");
    defaultbarbarian.setRace("HUMAN");
    defaultbarbarian.setVitality(10);
    defaultbarbarian.setArmor(5);
    defaultbarbarian.setLevel(5);
    defaultbarbarian.setEnemy();

    cout << defaultbarbarian.getName()<< "is a level" << defaultbarbarian.getLevel() << " " << defaultbarbarian.getRace() << "."
    <<"\nVitality: " << defaultbarbarian.getVitality()
    <<"\nArmor: " << defaultbarbarian.getArmor()
    <<"\nThey are " << (defaultbarbarian.isEnemy() ? "an enemy" : "not an enemy")
    <<"\nMain weapon: " <<defaultbarbarian.getMainWeapon()
    <<"\nSecondary Weapon: " << defaultbarbarian.getSecondaryWeapon()
    <<"\nEnraged: " << (defaultbarbarian.getEnrage() ? "TRUE" : "FALSE") << "\n\n";
    
    Barbarian BONK("BONK", "HUMAN", 11, 5, 5, true);
    BONK.setMainWeapon("MACE");
    BONK.setSecondaryWeapon("ANOTHERMACE");
    BONK.setEnrage(true);

    cout << BONK.getName()<< "is a level" << BONK.getLevel() << " " << BONK.getRace() << "."
    <<"\nVitality: " << BONK.getVitality()
    <<"\nArmor: " << BONK.getArmor()
    <<"\nThey are " << (BONK.isEnemy() ? "an enemy" : "not an enemy")
    <<"\nDagger: " <<BONK.getMainWeapon()
    <<"\nFaction: " << BONK.getSecondaryWeapon()
    <<"\nDisguise " << (BONK.getEnrage() ? "TRUE" : "FALSE") << "\n\n";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /*2.3.1 Instantiate a default Ranger
  - Sets its name, race, vitality, and armor levels using the appropriate setter functions
Name: defaultRanger
Race: UNDEAD
Vitality: 8
Armor: 4
Level: 5
Enemy: TRUE

- Print out information for default Ranger
  
2.2.2 Instantiate a Ranger with the parameterized constructor with the following character details:
Name: MARROW
Race: UNDEAD
Vitality: 9
Armor: 6
Level: 5
Enemy: TRUE

2.2.3 Set MARROW's unique private member variables to the following:
Vector of arrows: Wood, 30, Fire, 5, Water, 5, Poison, 5
Affinities: Fire, Poison
Animal Companian: TRUE

- Print out information for MARROW
*/
Ranger defaultranger;

    defaultranger.setName("defaultranger");
    defaultranger.setRace("UNDEAD");
    defaultranger.setVitality(8);
    defaultranger.setArmor(4);
    defaultranger.setLevel(5);
    defaultranger.setEnemy();

    cout << defaultranger.getName() << " is a Level " << defaultranger.getLevel() << " " << defaultranger.getRace() << "."
        << endl << "Vitality: " << defaultranger.getVitality()
        << endl << "Armor: " << defaultranger.getArmor()
        << endl << "They are " << (defaultranger.isEnemy() ? "an enemy" : "not an enemy")
        << endl << "Vector of arrows: ";
            
        vector<Arrows> arrows = defaultranger.getArrows();

        for (const Arrows& arrow : arrows){
            cout << arrow.type_ << ", " << arrow.quantity_ << ", ";
        }

        cout << endl << "Affinities: ";
              
        vector<string> affinities = defaultranger.getAffinities();
        for (const string& affinity : affinities){
            cout << affinity << ", ";
        }

        cout << endl << "Animal Companion: " << (defaultranger.getCompanion() ? "TRUE" : "FALSE") << endl;

    Ranger ranger("MARROW", "UNDEAD", 9, 6, 5, true); 
    ranger.addArrows("Wood", 30);
    ranger.addArrows("Fire", 5);
    ranger.addArrows("Water", 5);
    ranger.addArrows("Poison", 5);
    ranger.addAffinity("Fire");
    ranger.addAffinity("Poison");
    ranger.setCompanion(true);

    cout << ranger.getName() << " is a Level " << ranger.getLevel() << " " << ranger.getRace() << "."
        << endl << "Vitality: " << ranger.getVitality()
        << endl << "Armor: " << ranger.getArmor()
        << endl << "They are " << (ranger.isEnemy() ? "an enemy" : "not an enemy")
        << endl << "Vector of arrows: ";

        vector<Arrows> my_rangerArrows = ranger.getArrows();

        for (const Arrows& arrow : my_rangerArrows){
            cout << arrow.type_ << ", " << arrow.quantity_ << ", ";
        }

        cout << endl << "Affinities: ";
              
        vector<string> my_rangerAffinities = ranger.getAffinities();
        for (const string& affinity : my_rangerAffinities){
            cout << affinity << ", ";
        }

        cout << endl << "Animal Companion: " << (defaultranger.getCompanion() ? "TRUE" : "FALSE");
            
    
        Ranger MARROW("MARROW", "UNDEAD", 9, 6, 5, true);

 
        cout << MARROW.getName() << " is a Level " << MARROW.getLevel() << " " << MARROW.getRace() << "."
            << endl << "Vitality: " << MARROW.getVitality()
            << endl << "Armor: " << MARROW.getArmor()
            << endl << "They are " << (MARROW.isEnemy() ? "an enemy" : "not an enemy")
            << endl << "Arrows: ";
        
        vector<Arrows> arrows1 = MARROW.getArrows();
        for (const Arrows& arrow : arrows1) {
            cout << arrow.type_ << ": " << arrow.quantity_ << ", ";
        }
        
        cout << endl << "Affinities: ";
        vector<string> affinities1 = MARROW.getAffinities();
        for (const string& affinity : affinities1) {
            cout << affinity << ", ";
        }
        
        std::cout << endl << "Animal Companion: " << (MARROW.getCompanion() ? "TRUE" : "FALSE") << endl;


}
  
