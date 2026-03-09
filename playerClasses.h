#ifndef PLAYER_CLASSES_H
#define PLAYER_CLASSES_H

#include <iostream>
#include <string>
#include <random>
using namespace std;


// 'slowprint' function here because every other file includes playerClasses
void slowprint(const string& message, int ms_delay = 0) {
    for (char c : message) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(ms_delay));
    }
    cout << endl;
}


// Base player class
class Player {
public:
    bool alive = true;
    string name;
    string race;
    float maxhp = 100;
    float currhp = maxhp;
    int maxxp = 10;
    int currxp = 0;
    int ap = 0;
    int level = 1;
    int xp;
    int turn = 1;
    
    bool guarded = false;
    
    int base_spd = 50;
    float base_atk = 50;
    float base_def = 50;
    
    float spd_bonus = 0;
    float atk_bonus = 0;
    float def_bonus = 0;
    
    // Damage calculations include base + modifiers
    float atk() {return base_atk + atk_bonus;}
    float def() {return base_def + def_bonus;}
    float spd() {return base_spd + spd_bonus;}
    
    // Checks race-specific conditions, called in combat on opp turn, after their atk.
    virtual void pre_turn() {}
    // Cleans up specials for next combat
    virtual void post_combat() {}
    // Cleans up per-turn guarded
    void post_turn() {
        guarded = false;
    }
    
    // True = dead *special override in human*
    virtual bool death_check() {
        if (currhp <= 0) {
            return true;
        } else {
            return false;
        }
    }
    
    void stats() {
        slowprint(name);
        slowprint("---------------");
        slowprint("hp: " + to_string(static_cast<int>(currhp)) + "/" + to_string(static_cast<int>(maxhp)));
        slowprint("speed: " + to_string(static_cast<int>(spd())));
        slowprint("attack: " + to_string(static_cast<int>(atk())));
        slowprint("defense: " + to_string(static_cast<int>(def())));
        cout << endl;
    }
    
    // Level up.  Handles resets xp and handles all ap.
    void level_up() {
        string stat = "";
        if (currxp >= maxxp) {
            currxp = 0;
            maxxp += 5;
            ap += 3;
            slowprint(name + " has gained enough xp to level up!");
        }
        cout << endl;
        while (ap > 0) {
            slowprint("You have " + to_string(ap) + " ability points to spend.");
            slowprint("Type \"hp\" to spend 1 ap to gain 2 hp");
            slowprint("Type \"atk\" to spend 1 ap to gain 2 atk");
            slowprint("Type \"def\" to spend 1 ap to gain 2 def");
            slowprint("Type \"spd\" to spend 1 ap to gain 2 spd");
            getline(cin, stat);
            cout << endl;
            if (stat == "hp") {
                maxhp += 2;
                slowprint("Your new hp is: " + to_string(maxhp));
                cout << endl;
                ap -= 1;
            } else if (stat == "atk") {
                base_atk += 2;
                slowprint("Your new atk is: " + to_string(static_cast<int>(base_atk)));
                cout << endl;
                ap -= 1;
            } else if (stat == "def") {
                base_def += 2;
                slowprint("Your new def is: " + to_string(static_cast<int>(base_def)));
                cout << endl;
                ap -= 1;
            } else if (stat == "spd") {
                base_spd += 2;
                slowprint("Your new spd is: " + to_string(static_cast<int>(base_spd)));
                cout << endl;
                ap -= 1;
            } else {
                slowprint(" ***invalid selection***");
                continue;
            }
        }
        if (stat != "") {
            slowprint("Level up complete, your new stats............");
            cout << endl;
            stats();
        }
    }

    // Damage calculating, forwards 'death_check' of opp to combat. 
    bool base_attack(Player* opp_player) {
        bool dead;
        float damage = 20 + atk() - opp_player->def();
        if (damage < 0) {
            damage = 0;
        }
        if (guarded == true) {
            if (damage > 0) {
                damage = damage / 2;
            }
            random_device rng;
            mt19937 engine(rng());
            uniform_int_distribution<int> distrib(1, 100);
            int rng_num = distrib(engine);
            if (rng_num > base_spd) {
                slowprint(opp_player->name + " is guarding, successfully counter-attacks!");
                slowprint(opp_player->name + "'s counter deals " + to_string(static_cast<int>(opp_player->base_atk / 4)) + " damage to " + name);
            } else {
                slowprint(opp_player->name + " is guarding to reduce incoming damage...");
                cout << endl;
            }
            guarded = false;
        }
        opp_player->currhp -= damage;
        dead = opp_player->death_check();
        // Opp player lives = damage message
        if (dead == false) {
            slowprint(name + " did " + to_string(static_cast<int>(damage)) + " damage to " + opp_player->name);
            slowprint(opp_player->name + " now has " + to_string(static_cast<int>(opp_player->currhp)) + " hp.");
            return dead;
        } else {
            // Opp player dies = damage + victory message
            slowprint(name + " did " + to_string(static_cast<int>(damage)) + " damage to " + opp_player->name);
            slowprint(opp_player->name + " has fallen in combat! " + name + " declares victory!");
            slowprint("You gain " + to_string(opp_player->xp) + " xp");
            return dead;
        }
    }
};


class Human : public Player {
public:
    // Second chance (per combat)
    bool chance = true;
    
    Human(string name = "", string race = "human") {
        this->name = name;
    }
    
    // *Override Player death_check for second chance check*
    bool death_check() override {
        if ( (chance == true) && (currhp <= 0) ) {
            currhp = 0 + (maxhp / 5);
            return false;
        } else if (currhp <= 0) {
            return true;
        } else {
            return false;
        }
    }
    
    void pre_turn() override {
        // Second Chance print statement
        if (currhp <= 0 && chance == true) {
            currhp = 0 + (maxhp / 5);
            chance = false;
            slowprint(name + " received second chance! ");
            cout << currhp << "/" << maxhp << endl;
            cout << endl;
        } 
    }
        
    void post_combat() override {
        chance = true;
        return;
    }
};


class Elf : public Player {
public:

    Elf (string name = "", string race = "elf") {
        this->name = name;
        maxhp -= 10;
        currhp -= 10;
        base_spd += 10;
    }
    
    void pre_turn() override {
        // Regen
        if (turn == 1 || turn % 2 == 1) {
            return;
        } else if (currhp < maxhp * 0.95) {
            currhp += maxhp / 18;
            slowprint(name + " regenerated " + to_string(static_cast<int>(maxhp / 20)) + " hp!");
            slowprint(to_string(static_cast<int>(currhp)) + "/" + to_string(static_cast<int>(maxhp)));
        }
        turn += 1;
    }
};


class Orc : public Player {
public:
    bool berserk = false;

    Orc (string name = "", string race = "orc") {
        this->name = name;
        base_atk += 10;
        base_def -= 10;
        base_spd -= 10;
    }
    
    void pre_turn() override {
        if (turn == 1 && currhp < (maxhp / 2)) {
            atk_bonus = base_atk * 0.25;
            berserk = true;
            slowprint(name + " is going berserk because if low health! ");
            slowprint("Attack increased by 25%: " + to_string(static_cast<int>(atk())));
            cout << endl;
        } else if ( currhp < (maxhp / 2) && berserk == false && turn % 2 == 0) {
            atk_bonus = base_atk * 0.25;
            berserk = true;
            slowprint(name + " is going berserk! ");
            slowprint("Attack increased by 25%: " + to_string(static_cast<int>(atk())));
            cout << endl;
        } 
        turn += 1;
    }
    
    void post_combat() {
        atk_bonus = 0;
        berserk = false;
    }
};


class Dwarf : public Player {
public:
    bool sentry = false;
    
    Dwarf(string name = "", string race = "Dwarf") {
        this->name = name;
        base_def += 10;
        atk_bonus -= 5;
        base_spd -= 10;
    }
    
    void pre_turn() override {
        // Defense boost
        if (turn == 1 && currhp < (maxhp / 2)) {
            def_bonus = base_def / 4;
            sentry = true;
            slowprint(name + "\'s sentry mode is activated!");
            slowprint(" Defense increased by 25%: " + to_string(static_cast<int>(def())));
            cout << endl;
        } else if ( currhp < (maxhp / 2) && sentry == false && turn % 2 == 0) {
            def_bonus = base_def / 4;
            sentry = true;
            slowprint(name + "\'s sentry mode is activated!");
            slowprint(" Defense increased by 25%: " + to_string(static_cast<int>(def())));
            cout << endl;
        } 
        turn += 1;
    }
    
    void post_combat() override {
        def_bonus = 0;
        sentry = false;
    }
};


#endif