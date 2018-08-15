#include "item.cpp"
#include <vector>

class Recipe{
    Item* product;
    vector<Item*> ingredients;
    vector<int> quantities;

public:

    Recipe(Item* p, vector<Item*> i, vector<int> q){
        product = p;
        ingredients=i;
        quantities=q;
    }
};
