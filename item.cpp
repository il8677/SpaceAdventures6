#pragma once

#include <iostream>
using namespace std;

typedef enum MiningLevel{NOTHING,STONE,IRON, GOLD,ARKHIDITE};

class Item{
public:

    string name;

    MiningLevel miningLevel;

    int miningSpeed = 0;
    int ad = 0;
    int woodSpeed = 0;

    Item(string n){
        name = n;
    }
    Item (Item& i){
        name = i.name;
        miningSpeed = i.miningSpeed;
        ad = i.ad;
        woodSpeed = i.woodSpeed;
        miningLevel = i.miningLevel;
    }
    Item(string n, MiningLevel ml, int ms,int a,int ws){
        name = n;
        miningSpeed=ms;
        ad=a;
        woodSpeed=ws;
        miningLevel=ml;
    }

    Item(string n, int a, int ws){
        name = n;
        ad=a;
        woodSpeed=ws;
    }

    string getName(){
        return name;
    }
};
