#pragma once
#include "inventory.cpp"
#include "actor.cpp"

static class Player : public Actor{
    Inventory inventory;
public:

    Player() : Actor("Player", 0, 0){
        inventory(10);

    }

    Inventory * getInventoryRef(){
        return &inventory;
    }
};
