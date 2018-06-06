#include "item.cpp"
#include <vector>

class Recipe{
    Item* product;
    vector<Item> ingridients;
    vector<int> quantities;

public:

    Recipe(Item* p, vector<Item> i, vector<int> q){
        product = p;
        ingridients=i;
        quantities=q;
    }
};
