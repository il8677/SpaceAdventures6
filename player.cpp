#pragma once
#include "inventory.cpp"
#include "actor.cpp"

static class Player : public Actor{
    Inventory inventory;

public:
    int z = 0;
    Player() : Actor("Player", 0, 0, "PP"), inventory(10){

    }

    Inventory * getInventory(){
        return &inventory;
    }
};
