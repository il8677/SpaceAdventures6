#pragma once
#include "inventory.cpp"
#include "actor.cpp"

static class Player : public Actor{
    Inventory inventory;
public:
    int kills = 0;
    int z = 0;
    Player() : Actor("Player"), inventory(10){
        x = 0;
        y = 0;
    }

    Inventory * getInventory(){
        return &inventory;
    }
};
