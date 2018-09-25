#include "item.cpp"
#include "inventory.cpp"
#include "player.cpp"
#include <vector>

class Player;

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
    Recipe( vector<Item*> i, vector<int> q){
        debugout("[Recipe : Recipe()] Initializing new recipe");
        ingredients=i;
        quantities=q;
        debugout("\tIngredients:");
        for(int d = 0; d < ingredients.size(); d++){
            debugout("\t" + i[d]->name);
        }

    }

    virtual void addProduct(Player& c) =0;
};

class ItemRecipe : public Recipe{
public:
    ItemRecipe(Item* p, vector<Item*> i, vector<int> q): Recipe(i, q){
        product = p;
        debugout("[ItemRecipe : ItemRecipe()] New recipe " + product->name + " initialized:");

    }
    void addProduct(Player& c) override
    {
        c.getInventory()->addItem(product, 1);
    }

};
