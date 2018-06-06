#include<iostream>
#include<stack>
#include<memory>

#include "player.cpp"
#include "tile.cpp"
#include "craftingrecipe.cpp"
#include "GameState.cpp"

using namespace std;

Player player;

#define MAPSIZE 20
#define Z player.z
#define X player.x
#define Y player.y

//item definition
Item iron("Iron");
Item stone("Stone");
Item wood("Wood");

stack<unique_ptr<GameState> > states;

Map<> planets[5] = {
    Map<>(MAPSIZE,MAPSIZE,NULLTILE),
    Map<>(MAPSIZE,MAPSIZE,NULLTILE),
    Map<>(MAPSIZE,MAPSIZE,NULLTILE),
    Map<>(MAPSIZE,MAPSIZE,NULLTILE),
    Map<>(MAPSIZE,MAPSIZE,NULLTILE),
};
void printTilesOfMap(Map<> * themap){
    for(int y = 0; y<themap->getx(); y++){
        for(int x = 0; x<themap->gety(); x++){
            if(x==player.x && y==player.y){setColor(WHITE); cout << "PP";}else{
                setColor(themap->getTile(x,y)->getColour());
                cout<<themap->getTile(x,y)->getStyle();
            }
        }cout<<endl;}
}
class Monster : public Actor;
class StateNight : public GameState{
    Map<String>(8,8);
    vector<Monster *> opponents;
    void printTilesOfField(Map<> * themap){
        for(int y = 0; y<themap->getx(); y++){
            for(int x = 0; x<themap->gety(); x++){
                if(x==player.x && y==player.y){setColor(WHITE); cout << "PP";}else{
                    setColor(themap->getTile(x,y)->getColour());
                    cout<<themap->getTile(x,y)->getStyle();
                }
                for(int i = 0; i < opponents.size(); i++){
                    if(opponents[i].x == x && y == opponents[i].y){
                        cout << opponents.
                    }
                }
            }cout<<endl;}
    }
    void update() override{
        printTilesOfMap()
    }
}

class StatePlanet : public GameState{
    int ac = 20;
    void update() override{
        cls();
        printTilesOfMap(&planets[player.z]);
        cout <<  planets[player.z].getTile(player.x, player.y)->getFlavour();
        char action = getch();
        if(action == 'a'){
            player.left();
            ac-=1;
        }else if (action == 's'){
            player.down();
            ac-=1;
        }else if (action == 'd'){
            player.right();
            ac-=1;
        }else if (action=='w'){
            player.up();
            ac-=1;
        }else if (action == 'e'){
            if(planets[player.z].getTile(X,Y)->getTrees() > 0){
                planets[player.z].getTile(X,Y)->decTrees();
                player.getInventory()->addItem(new Item(wood), 5+(player.getInventory()->getBestAxe()->woodSpeed*2));
                ac-=3-(player.getInventory()->getBestAxe()->woodSpeed);
            }else{
                cout << "There aren't enough trees here"<<endl;
            }
        }
        if(ac == 0){
            states.push(std::make_unique<StateNight>());
        }
    }
};

int main(){

    initializeTileTemplates();
    for(int i = 0; i<5; i++){
        generateTerrainOfMap(&planets[i]);
    }
    states.push(std::make_unique<StatePlanet>());
    printTilesOfMap(&planets[0]);

    while(true){
        states.top()->update();
    }

    for(int i = 0; i < 5; i++){//De-init
        planets[i].~Map();
    }
    return 0;
}
