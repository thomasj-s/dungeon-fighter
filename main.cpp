/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string>
#include "intro.h"
#include "playerClasses.h"
#include "dungeon.h"
#include "combat.h"
using namespace std;


bool gaming = true;

Dungeon build_dungeon() {
// Build and populate dungeon.  Runs every time the player
// starts the dungeon over, as to be sure baddies replenish.
    Dungeon dungeon;
    dungeon.floors.emplace_back(new Skeleton("Skeleton"));
    dungeon.floors.emplace_back(new Goblin("Goblin"));
    dungeon.floors.emplace_back(new Spider("Giant spider"));
    dungeon.floors.emplace_back(new Ogre("Ogre"));
    dungeon.floors.emplace_back(new CaveTroll("A cave troll"));
    return dungeon;
}


int main()
{
    // Dummys to display stats during intro
    Human dummy_h("Human");
    Elf dummy_e("Elf");
    Orc dummy_o("Orc");
    Dwarf dummy_d("Dwarf");
    string dummy;
    
    // Intro function generates player object based on choices
    Player* player = intro(dummy_h, dummy_e, dummy_o, dummy_d);
    player->stats();
    cout << endl;
    
    slowprint("   There's no time to waste, let's get to the crypts!");
    cout << endl;
    
    // Gameplay loop
    while (gaming == true) {
        int level = 1;
        // Fresh dungeon every time
        Dungeon dungeon = build_dungeon();
        slowprint(" *you arrive at the crypts, there is a stillness in the air* ");
        cout << endl;
        // Loop over baddies in dungeon
        for (int i = 0; i < 5; i++) {
            // still_fighting = false : player dies or flees
            bool still_fighting = true;
            still_fighting = combat(player, dungeon.floors[i]);
            // 'true' means player won battle
            if (still_fighting == true) {
                level += 1;
                if (level == 6) {
                    gaming = false;
                    break;
                }
                player->level_up();
                slowprint("You progress deeper into the Dungeon....");
                slowprint("........................................");
                slowprint("........................................");
                cout << endl;
            } else {
                // else means player fled or died
                slowprint("................................");
                slowprint("................................");
                slowprint("................................");
                slowprint("You make it back to the inn and rest for the night");
                slowprint("------press enter to wake up and head to the Dungeon-------");
                getline(cin, dummy);
                break;
            }
        }
    }
    
    slowprint("You have done it! You have fought through the crypts and cleared them!");
    slowprint("Dimloth is once again a safe town.  The adventure is over for now.....");
    gaming = false;
    
    return 0;
}