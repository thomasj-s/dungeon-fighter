#ifndef INTRO_H
#define INTRO_H

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "playerClasses.h"
using namespace std;

void bl() {
    cout << endl;
}

// Intro prompt and return player 'Player' subclass reference (Player*)
Player* intro(Human& h, Elf& e, Orc& o, Dwarf& d) {
    
    Player player;
    string race;
    string name;
    bool valid = false;
    bool sure = false;
    
    // Intro text
    slowprint("Welcome to Dimloth.");
    bl();
    slowprint("You have come, heeding a call for aid.");
    bl();
    slowprint("A great evil has occupied the 10 levels of the town's crypts.");
    bl();
    slowprint("So tell us, which adventurer answers the call?");
    bl();
    cout << "---------------------------------------" << endl;
    slowprint("Class descriptions: ");
    bl();
    h.stats();
    bl();
    e.stats();
    bl();
    o.stats();
    bl();
    d.stats();
    bl();
    cout << "--------------------------------------" << endl;
    slowprint("Please, type the class name you'd like to play as *in lower case* and press \"enter\"....");
    getline(cin, race);
    
    // Player select race
    while (valid == false) {
        if (race != "human" && race != "elf" && race != "orc" && race != "dwarf") {
            cout << " *** Non-valid choice.  *** " << endl;
            slowprint("Please, type the class name you'd like to play as *in lower case* and press \"enter\"....");
            getline(cin, race);
        } else {
            valid = true;
        }
    }
    
    // Player create name
    bl();
    slowprint("Now, type the name of your adventurer and press \"enter\"...");
    getline(cin, name);
    bl();
    
    // Name confirmation
    while (sure == false) {
        string confirmation;
        slowprint("Will \'" + name + "\' be your final choice?");
        slowprint("Type \"y\" and hit \"enter\" to accept your name, ");
        slowprint("or type anything else then hit \"enter\" to change name.");
        getline(cin, confirmation);
        bl();
        if (confirmation == "y") {
            sure = true;
        } else {
            slowprint("Now, type the name of your adventurer and press \"enter\"...");
            getline(cin, name);
            bl();
        }
    }
    
    // User input -> generate subclass
    if (race == "human") {
        return new Human(name);
    } else if (race == "elf") {
        return new Elf(name);
    } else if (race == "orc") {
        return new Orc(name);
    } else {
        return new Dwarf(name);
    }
}

#endif