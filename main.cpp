#include<iostream>
#include "player.cpp"
#include "tile.cpp"

using namespace std;

Player player;

#define MAPSIZE 20

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
int main(){
    initializeTileTemplates();
    for(int i = 0; i<5; i++){
        generateTerrainOfMap(&planets[i]);
    }

    printTilesOfMap(&planets[0]);

    while(true){
        cls();
        printTilesOfMap(&planets[player.z]);
        cout <<  planets[player.z].getTile(player.x, player.y)->getFlavour();
        char action = getch();
        if(action == 'a'){
            player.left();
        }else if (action == 's'){
            player.down();
        }else if (action == 'd'){
            player.right();
        }else if (action=='w'){
            player.up();
        }
    }

    for(int i = 0; i < 5; i++){//De-init
        planets[i].~Map();
    }
    return 0;
}
