#ifndef COMBAT_H
#define COMBAT_H

#include <iostream>
#include <string>
#include "playerClasses.h"
using namespace std;

// Combat function, called in main gameplay loop
bool combat(Player* p1, Player* p2) {
    
    string choice;
    bool fighting = true;
    string dummy;
    bool dead;
    int turn = 1;

    slowprint(p2->name + " appears ready to fight!");
    cout << endl;
    
    while (fighting == true) {
        slowprint("Will you attack? Type \"atk\" and press \"enter\" to attack...");
        slowprint("Will you defend? Type \"def\" and press \"enter\" to defend...");
        slowprint("Or will you flee? Type \"flee\" and press \"enter\" to flee...");
        getline(cin, choice);
        cout << endl;
        if (choice == "atk") {
            // death_check forwarded from base attack on p2 status
            p1->pre_turn();
            dead = p1->base_attack(p2);
            if (dead == true) {
                p1->currxp += p2->xp;
                p1->post_combat();
                fighting = false;
                return true;
            }
            p2->pre_turn();
            cout << endl;
            cout << "---press enter to continue---" << endl;
            getline(cin, dummy);
            slowprint(p2->name + " prepares to attack!");
            cout << endl;
            cout << "---press enter to continue---" << endl;
            getline(cin, dummy);
            // death_check forwarded from base attack on p1 status
            dead = p2->base_attack(p1);
            if (dead == true) {
                p1->post_combat();
                fighting = false;
                return false;
            }
            p1->pre_turn();
            cout << endl;
            cout << "---press enter to continue---" << endl;
            getline(cin, dummy);
        } else if (choice == "def") {
            p2->guarded = true;
            slowprint("You ready a counter attack, relying on your speed...");
            cout << endl;
            slowprint(p2->name + " prepares to attack!");
            cout << endl;
            cout << "---press enter to continue---" << endl;
            getline(cin, dummy);
            // death_check forwarded from base attack on p1 status
            dead = p2->base_attack(p1);
            p1->pre_turn();
            if (dead == true) {
                fighting = false;
                p1->post_combat();
                return false;
            }
            p1->pre_turn();
            cout << endl;
            //slowprint(p1->name + " now has " + to_string(static_cast<int>(p1->currhp)) + " hp.");
            cout << "---press enter to continue---" << endl;
            getline(cin, dummy);
        } else if (choice == "flee") {
            // Refill hp on flee
            p1->currhp = p1->maxhp;
            p1->post_combat();
            slowprint("You flee combat and live to fight another day...");
            fighting = false;
            return false;
        } else {
            slowprint("*invalid choice*");
        }
        turn += 1;
    }
        cout << endl;
}


// 
#endif
