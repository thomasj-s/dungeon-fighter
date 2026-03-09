#ifndef DUNGEON_H
#define DUNGEON_H

#include <iostream>
#include <string>
#include <vector>
#include "playerClasses.h"
using namespace std;


class Dungeon {
public:
    vector<Player*> floors;
    
    Dungeon() {}
};

// Floor 1 baddies
class Skeleton : public Player {
public:
    Skeleton(string name = "") {
        this->name = name;
        maxhp -= 40;
        currhp -= 40;
        base_spd -= 10;
        base_atk -= 20;
        base_def -= 10;
        xp += 10;
    }
};

// Floor 2 baddies
class Goblin : public Player {
public:
    Goblin(string name = "") {
        this->name = name;
        maxhp -= 25;
        currhp -= 25;
        base_spd -= 5;
        base_atk -= 15;
        base_def -= 10;
        xp += 15;
    }
};

// Floor 3 baddies
class Spider : public Player {
public:
    Spider(string name = "") {
        this->name = name;
        maxhp -= 15;
        currhp -= 15;
        base_atk -= 5;
        base_def -= 10;
        xp += 20;
    }
};

// Floor 4 baddies
class Ogre : public Player {
public:
    Ogre(string name = "") {
        this->name = name;
        base_spd -= 5;
        base_atk -= 5;
        base_def -= 10;
        xp += 25;
    }
};

// Floor 5 baddies
class CaveTroll : public Player {
public:
    CaveTroll(string name = "") {
        this->name = name;
        base_spd -= 5;
        base_def -= 10;
        xp += 30;
    }
};

#endif

