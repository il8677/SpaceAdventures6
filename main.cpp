#include<iostream>
#include<stack>
#include<memory>
#include<string>
#include<cmath>
#include<random>
#include<chrono>
#include<thread>

#include "player.cpp"
#include "tile.cpp"
#include "craftingrecipe.cpp"
#include "GameState.cpp"
#include "Utility.cpp"

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

//name attack damage woodspeed durability (5+woodspeed*2)
Item axeWood("Wood Axe", 2,2,10);
Item axeStone("Stone Axe", 3, 3,25);
Item axeIron("Iron Axe", 3, 5, 60);

Item swordWood("Wood Sword", 3);
Item swordStone("Stone Sword", 5);
Item swordIron("Iron Sword", 10);

//string n, MiningLevel ml, int mining speed,int attack, int durability
Item pickaxeWood("Wood Pickaxe", STONE, 2, 1, 10);
Item pickaxeStone("Stone Pickaxe", IRON, 4, 2, 40);
Item pickaxeIron("Iron Pickaxe", GOLD, 7, 4, 100);

Item a_pickaxeMiner("Miners Pickaxe", ARKHIDITE, 10, 4, 9999);

//Item* p, vector<Item> i, vector<int> q
Recipe r_axeWood(&axeWood, initializer_list<Item*>{&wood}, initializer_list<int>{10});


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
class Monster : public Actor{
public:
    string name;
    int maxhealth;
    char label;

    Monster(string n, int h) : Actor(n){
        health = h; maxhealth=health;
        label =n[0];
    }
    Monster(Monster &m) :Actor(m.name){
        health = m.health; maxhealth = health;
        label = m.name[0];
    }
};

#define MONSTERCOUNT 0
Monster * monsterIndex[MONSTERCOUNT] = {

};

class StateNight : public GameState{
    vector<unique_ptr<Monster> > opponents;
    Map<Colour> colours;
    int orig_x, orig_y;
public:

    ~StateNight(){
        player.x = orig_x;
        player.y=orig_y;
    }

    StateNight() : colours(8,8, GREEN){
        orig_x = player.x;//Since we will be modifying the position of the player,
        orig_y = player.y;//we want to store the previous position in order to reset
        player.x = colours.getx() / 2;
        player.y = colours.gety() - 1;

        for(int i = 0; i < (player.kills + 1) + (floor(player.kills/10)); i++){
            opponents.push_back(make_unique<Monster>( (*(monsterIndex[rand()%MONSTERCOUNT])) ));
        }
    }
    void update() override{
        cls();

        prmap();
        for(int i = 0; i < opponents.size(); i++){
            cout << opponents[i].get()->name << endl << opponents[i].get()->health << "/"<<opponents[i].get()->maxhealth<<endl;
        }

        cout << "e. Attack"<<endl;

        char action =getch();

        if(action == 'e'){
            colours.setTileDirection(player.x, player.y, RED, player.d);
        }
    }
private:


    void prmap(){
        for(int y = 0; y<colours.getx(); y++){
            for(int x = 0; x<colours.gety(); x++){
                setColor(*colours.getTile(x,y));
                bool monsterOnTile = false;
                int mi;

                for(int i =0; i < opponents.size(); i++){
                    if(opponents[i].get()->x == x && opponents[i].get()->y == y){
                        monsterOnTile=true;
                        mi=i;
                    }
                }
                if(x==player.x && y==player.y){
                    setColor(WHITE); cout << "P"<<player.d;
                }else if (monsterOnTile){
                    cout << opponents[mi].get()->label << opponents[mi].get()->d;
                }else{
                    cout<<"__";
                }
            }cout<<endl;}
            setColor(GREEN);
    }

};

class StatePlanet : public GameState{
    int ac = 20;
    void update() override{
        printTilesOfMap(&planets[player.z]);
        cout <<  planets[player.z].getTile(player.x, player.y)->getFlavour();
        cout <<endl;
        char action = getch();
        cls();
        if(action == 'a'){
            player.left();
            ac-=1;
            player.d = LEFT;
        }else if (action == 's'){
            player.down();
            ac-=1;
            player.d = DOWN;
        }else if (action == 'd'){
            player.right();
            ac-=1;
            player.d = LEFT;
        }else if (action=='w'){
            player.up();
            ac-=1;
            player.d = UP;
        }else if (action == 'e'){
            if(planets[player.z].getTile(X,Y)->getTrees() > 0){
                planets[player.z].getTile(X,Y)->decTrees();
                player.getInventory()->addItem(new Item(wood), 5+(player.getInventory()->getBestAxe()->woodSpeed*2));
                ac-=3-(player.getInventory()->getBestAxe()->woodSpeed);
            }else{
                cout << "There aren't enough trees here"<<endl;
            }
        }else if (action == 'i'){
            player.getInventory()->printInventory();
            cout << "Press any key to continue..."<<endl;
            anykey();
        }
        if(ac == 0){
            states.push(std::make_unique<StateNight>());
        }
    }
};

int main(){
    player = Player();

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
