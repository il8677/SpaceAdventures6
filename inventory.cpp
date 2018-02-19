#include "item.cpp"
#include<vector>
#include<iostream>
using namespace std;

class Inventory{
    std::vector<Item *> items;
    std::vector<int> quant;
    void removeItem(int i){
        items[i]=NULL;
        quant[i]=NULL;
    }
    void removeItem(int i, int q){
        quant[i]-=q;
        if(quant[i] == 0){
            items[i]=NULL;
        }
    }
    int nextEmpty(){
        for (int i = 0; i < items.size(); i++){
            if(items[i] == NULL){
                return i;
            }
        }
        return NULL;
    }
    int getIndexOfItem(string name){
        int index=NULL;
        for(int i = 0; i < items.size(); i++){
            if(name== items[i]->getName()){
                index = i;
            }
        }
        if(index == NULL){
            cout << "[Inventory : getIndexOfItem()] ERROR: item name does not exist in inventory!"<<endl;
            exit(0);
        }
        return index;
    }
public:
    Inventory(int invsize){
        for(int i = 0; i < invsize; i++){
            items.push_back(NULL);
            quant.push_back(NULL);
        }
        cout << invsize << " " << quant.size() << endl;
    }

    Item * takeItem(int i, int q = 100){
        Item * returnItem;

        if(i < items.size()){
            cout << "[Inventory : takeItem()] ERROR: index given is larger than maximum items!"<<endl;
            exit(0);
        }

        if(q > quant[i]){
            q = quant[i];
        }

        returnItem = items[i];

        removeItem(i, q);

        return returnItem;
    }

    Item * takeItem(string name, int q = 100){
        int index = getIndexOfItem(name);

        if(q > quant[index]){
            q = quant[index];
        }
        Item * returnItem = items[index];

        removeItem(index, q);

        return returnItem;
    }

    Item * addItem(Item* item, int q){

        int itemIndex = NULL;
        for(int i = 0; i < items.size(); i++){
            if(items[i]->getName() == item->getName()){
                itemIndex = i;
            }
        }
        if(itemIndex != NULL){
            quant[itemIndex]+=q;
        }else if(nextEmpty() != NULL){
            items[nextEmpty()] = item;
        }else{
            cout << "Inventory is full!" << endl;
        }
    }

    void clearItem(int i){
        removeItem(i);
    }

    Item * getItem(int i){
        return items[i];
    }

    int getQuant(int i){
        return quant[i];
    }

    void SwapItem(Inventory* other, int o, int i){
        Item * oitem = other->getItem(o);
        Item * iitem = getItem(i);
        int oq = other->getQuant(o);
        int iq = getQuant(i);

        clearItem(i);
        other->clearItem(o);

        other->addItem(iitem, iq);
        addItem(oitem, oq);
    }
};
