#pragma once

#include <iostream>
using namespace std;

typedef enum MiningLevel{NOTHING,STONE,IRON, GOLD,ARKHIDITE};

class Item{
public:
    bool isTool = false;
    string name;

    MiningLevel miningLevel;

    int miningSpeed = 0;
    int ad = 0;
    int woodSpeed = 0;
    int durability;

    Item(string n){
        name = n;
    }
    Item (Item& i){
        name = i.name;
        miningSpeed = i.miningSpeed;
        ad = i.ad;
        woodSpeed = i.woodSpeed;
        miningLevel = i.miningLevel;
        isTool = i.isTool;
    }
    Item(string n, MiningLevel ml, int ms,int a, int d){
        name = n;
        miningSpeed=ms;
        ad=a;
        miningLevel=ml;
        durability = d;
        bool isTool = true;
    }

    Item(string n, int a, int ws, int d){
        name = n;
        ad=a;
        woodSpeed=ws;
        durability = d;
        bool isTool = true;
    }

    Item(string n, int a){
        name = n;
        ad=a;
    }

    string getName(){
        return name;
    }
};
