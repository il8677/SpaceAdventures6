#include <iostream>
using namespace std;

class Item{
    string name;

public:
    Item(string n){
        name = n;
    }

    string getName(){
        return name;
    }
};
