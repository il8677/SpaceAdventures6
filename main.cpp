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

string directionGlyphs[4] = {"^",">","V","<"};
char directionKeys[4] = {'w','d','s','a'};

//item definition
Item iron("Iron", IRON);
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
#define RECIPECOUNT 9
vector<Recipe> recipes = {
    Recipe(&axeWood, initializer_list<Item*>{&wood}, initializer_list<int>{10}),
    Recipe(&axeStone,initializer_list<Item*>{&wood,&stone}, initializer_list<int>{5,10}),
    Recipe(&axeIron,initializer_list<Item*>{&wood, &iron}, initializer_list<int>{5, 10}),

    Recipe(&pickaxeWood,initializer_list<Item*>{&wood}, initializer_list<int>{10}),
    Recipe(&pickaxeStone,initializer_list<Item*>{&wood, &stone}, initializer_list<int>{5, 15}),
    Recipe(&pickaxeIron,initializer_list<Item*>{&wood, &iron, &stone}, initializer_list<int>{5, 10, 5}),

    Recipe(&swordWood,initializer_list<Item*>{&wood}, initializer_list<int>{15}),
    Recipe(&swordStone,initializer_list<Item*>{&wood, &stone}, initializer_list<int>{5,5}),
    Recipe(&swordIron,initializer_list<Item*>{&wood, &iron}, initializer_list<int>{5,5})};

stack<unique_ptr<GameState> > states;

#define MINEABLEORES 1
Item * mineables[MINEABLEORES] = {
    &iron
};

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
    char label;
    int attack;
    bool tactical;
    Monster(string n, int h, int a, bool t) : Actor(n){
        health = h; maxhealth=health;
        name=n;
        label = n[0];
        attack = a;
        tactical = t;
        debugout("[Monster : Monster()] Initializing monster with " + to_string(attack) + " attack");
    }
    Monster(Monster &m) : Actor(m.name){
        health = m.health; maxhealth = health;
        label = m.name[0];
    }

    void atck(Map<Colour>& colourmap, Map<int>& damagemap){
        colourmap.setTileDirection(x, y, RED, d);
        damagemap.setTileDirection(x, y, attack, d);
    }

    void ai(Map<Colour>& colourmap, Map<int>& damagemap){
        //Check if player is in range, then attack
        if((player.x == directionX(x, d) && player.y == y) || (player.y == directionY(y, d) && player.x==x)){
            atck(colourmap, damagemap);
        }else if(getDistance(x, y, player.x, player.y) ==2){
            if(getDirection(x, y, player.x, player.y) == d){
                atck(colourmap, damagemap);
            }else{
                char action;
                action = directionKeys[getDirection(x, y, player.x, player.y)];
                if(action == 'a'){
                    d = LEFT;
                }else if(action == 'd'){
                    d = RIGHT;
                }else if(action=='w'){
                    d = UP;
                }else if (action=='s'){
                    d = DOWN;
                }
            }
        }else{
            char action;
            action = directionKeys[getDirection(x, y, player.x, player.y)];
            if(action == 'a'){
                left();
                d = LEFT;
            }else if(action == 'd'){
                right();
                d = RIGHT;
            }else if(action=='w'){
                up();
                d = UP;
            }else if (action=='s'){
                down();
                d = DOWN;
            }
        }
    }

    void advancedai(Map<Colour>& colourmap, Map<int>& damagemap){

    }
};

#define MONSTERCOUNT 1
unique_ptr<Monster> monsterIndex[MONSTERCOUNT] = {
    make_unique<Monster>("Earth Golem", 10,2, false)
};

class CraftingMenu : public GameState{

    vector<Recipe>& r;
public:
    CraftingMenu(vector<Recipe>& d) : r(d){
    }

    void update() override{
        cls();
        for(int i = 0; i < RECIPECOUNT; i++){
            if(r[i].canCraft(player.getInventory())){
                cout << i<< ": " << r[i].product->name<<endl;
                sleep(100);
            }
        }
        int in;
        cin >> in;
        states.pop();
        if(r[in].canCraft(player.getInventory())){
            r[in].addProduct(player);
            r[in].removeItems(player.getInventory());
        }
    }
};

class StateNight : public GameState{
    vector<unique_ptr<Monster> > opponents;
    Map<Colour> colours;
    Map<int> damages;
    int orig_x, orig_y;
public:

    ~StateNight(){
        player.x = orig_x;
        player.y = orig_y;
    }

    StateNight() : colours(8,8, GREEN), damages(8,8,0){
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
        for(int y = 0; y<colours.getx(); y++){
            for(int x = 0; x<colours.gety(); x++){
                if(*colours.getTile(x,y) == RED){
                    if(player.x == x && player.y == y){
                        player.damage(*damages.getTile(x,y));
                    }else{
                        for(int i = 0; i < opponents.size(); i++){
                            if(opponents[i]->x == x && opponents[i]->y == y){
                                opponents[i]->damage(*damages.getTile(x,y));
                            }
                        }
                    }
                    colours.setTile(x,y,GREEN);
                }
            }
        }
        cout << player.health<<"/"<<player.maxhealth<<endl;
        for(int i = 0; i < opponents.size(); i++){
            cout << opponents[i]->name << ": " << opponents[i].get()->health << "/"<<opponents[i].get()->maxhealth<<endl;
            if(!opponents[i]->tactical){
                opponents[i]->ai(colours, damages);
            }
        }

        cout << "e. Attack"<<endl;

        char action =getch();

        if(action == 'e'){
            colours.setTileDirection(player.x, player.y, RED, player.d);
            damages.setTileDirection(player.x, player.y, player.getInventory()->getBestWeapon()->ad, player.d);
        }else if(action == 'a'){
            player.left();
            player.d = LEFT;
        }else if(action == 'd'){
            player.right();
            player.d = RIGHT;
        }else if(action=='w'){
            player.up();
            player.d = UP;
        }else if (action=='s'){
            player.down();
            player.d = DOWN;
        }
        for(int i = 0; i < opponents.size(); i++){
            if(opponents[i]->tactical){
                opponents[i]->ai(colours, damages);
            }
            //Check for collisions
            if(opponents[i]->x == player.x && opponents[i]->y == player.y){
                opponents[i]->displace();
            }
            for(int b = 0; b < opponents.size(); b++){
                if(b!=i){
                    if(opponents[b]->x == opponents[i]->x&& opponents[b]->y == opponents[i]->y){
                        opponents[b]->displace();
                    }
                }
            }
            if(opponents[i]->health <= 0){
                opponents.erase(opponents.begin() + i);
            }
        }
        if(opponents.size() == 0){
            states.pop();
        }
        if(player.health <= 0){
            exit(0);
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
                    if(*colours.getTile(x,y)==RED){
                        setColor(RED);
                    }else{
                        setColor(WHITE);
                    }
                    cout << "P"<<directionGlyphs[player.d];
                }else if (monsterOnTile){
                    cout << opponents[mi].get()->label << directionGlyphs[opponents[mi].get()->d];
                }else{
                    cout<<"__";
                }
            }cout<<endl;}
            setColor(GREEN);
    }

};
class StateMine : public GameState{
    int subactions = 0; // 10 subactions = 1 action
    int& ac;
    int orig_x, orig_y;
    //-2 = stone
    //-1 = air
    //>=0 = material index
    Direction playerDirection= UP;
    Map<int> mine=Map<int>(20,20,-2);
public:
    ~StateMine(){
        player.x = orig_x;
        player.y = orig_y;
        setColor(GREEN);
    }

    StateMine(int& a) : ac(a) {
        orig_x = player.x;//Since we will be modifying the position of the player,
        orig_y = player.y;//we want to store the previous position in order to reset
        player.x=0;
        player.y=0;

        for(int y = 0; y<mine.gety(); y++){
            for(int x = 0; x<mine.getx(); x++){
                int chance = rand()%10;
                if(chance == 1){
                    int ore = rand()%MINEABLEORES;
                    mine.setTile(x,y,ore);
                }
            }
        }

        mine.setTile(0,0,-1);
    }

    void update() override{
        if(subactions >= 10){
            subactions = 0;
            ac -= 1;
            if(ac == 0){
                states.pop();
            }
        }
        for(int y = 0; y<mine.gety(); y++){
            for(int x = 0; x<mine.getx(); x++){
                if(x == player.x && y == player.y){
                    setColor(GREEN);
                    cout << directionGlyphs[playerDirection];
                }
                else if(*mine.getTile(x,y) == -1){
                    setColor(BLUE);
                    cout << " ";
                }else if(*mine.getTile(x,y) == -2){
                    setColor(GREY);
                    cout << "S";
                }else{
                    setColor(YELLOW);
                    cout <<mineables[*mine.getTile(x,y)]->name[0];
                }
            }
            cout<<endl;
        }

        char action = getch();
        if(action == 'a'){
            if(*mine.getTileLeft(player.x,player.y) == -1){
            player.left();}
            playerDirection = LEFT;
        }else if(action == 'd'){
            if(*mine.getTileRight (player.x,player.y)== -1){
            player.right();}
            playerDirection = RIGHT;
        }else if(action=='w'){
            if(*mine.getTileUp(player.x,player.y) == -1){
            player.up();}
            playerDirection = UP;
        }else if (action=='s'){
            if(*mine.getTileDown(player.x,player.y) == -1){
            player.down();}
            playerDirection = DOWN;
        }else if (action=='q'){
            states.pop();
        }else if (action=='e'){
            bool doDestroy = false;
            if(*mine.getTileDirection(player.x, player.y, playerDirection) == -2 && player.getInventory()->getBestPickaxe()->miningLevel >= STONE){
                player.getInventory()->addItem(new Item(stone), 1);
                doDestroy = true;
            }else if(*mine.getTileDirection(player.x, player.y, playerDirection) != -1){
                if(player.getInventory()->getBestPickaxe()->miningLevel >=  mineables[*mine.getTileDirection(player.x, player.y, playerDirection)]->miningLevel){
                player.getInventory()->addItem(new Item(*mineables[*mine.getTileDirection(player.x, player.y, playerDirection)]),1);
                doDestroy = true;}
            }
            if(doDestroy){
                mine.setTileDirection(player.x,player.y,-1, playerDirection);
                subactions += 10 - player.getInventory()->getBestPickaxe()->miningSpeed;
                player.getInventory()->getBestPickaxe()->durability - 1;
            }
        }
        cls();
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
        }else if (action == 'q'){
            states.push(std::make_unique<CraftingMenu>(recipes));
        }else if(action == 'm'){
            states.push(std::make_unique<StateMine>(ac));
        }
        if(ac <= 0){
            ac=10;
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

    while(true){
        states.top()->update();
    }

    for(int i = 0; i < 5; i++){//De-init
        planets[i].~Map();
    }


    return 0;
}
