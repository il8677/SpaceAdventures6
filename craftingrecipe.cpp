#include "item.cpp"
#include "inventory.cpp"
#include <vector>

class Recipe{


public:
    Item* product;
    vector<Item*> ingredients;
    vector<int> quantities;

    bool canCraft(Inventory* i){
        return i->hasEnoughItems(ingredients,quantities);
    }
    void removeItems(Inventory* c){
        for(int i = 0; i < ingredients.size(); i++){
            c->takeItem(ingredients[i]->name,quantities[i]);
        }
    }
    Recipe(Item* p, vector<Item*> i, vector<int> q){
        product = p;
        ingredients=i;
        quantities=q;
    }
};
