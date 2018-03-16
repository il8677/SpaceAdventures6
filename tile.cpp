#include <iostream>
#include "rlutil.h"
#include <random>

using namespace std;
using namespace rlutil;

class Tile{
    string style;
    Colour colour;
    int trees;
    string flavour;
public:
    Tile(string s, Colour c, int t, string f){
        style = s; colour=c;
        trees = t; flavour =f;
    }
    Tile(){

    }
    string getFlavour(){
        return flavour;
    }
    void copyTile(Tile tile){
        style=tile.getStyle();
        colour=tile.getColour();
        trees=tile.getTrees();
    }

    Colour getColour(){
        return colour;
    }

    string getStyle(){
        return style;
    }

    int getTrees(){
        return trees;
    }

    void decTrees(){
        trees--;
    }
    void incTrees(){
        trees++;
    }

};

Tile tileTemplates[4];
Tile NULLTILE("  ", GREY, 0, "NULL");
void initializeTileTemplates(){
    tileTemplates[0] = Tile("||", GREEN, 25, "Your surroundings are thick with trees");
    tileTemplates[1] = Tile("__", LIGHTGREEN, 1, "Your surroundings are flat");
    tileTemplates[2] = Tile("^^", GREY, 5, "Your surroundings are rocky and mountainous");
    tileTemplates[3] = Tile("..", YELLOW, 0, "Your surroundings are sandy");
}
template <typename T = Tile>
class Map{
    int sizex;
    int sizey;
    T ** tiles;
public:
    int getx(){
        return sizex;
    }

    int gety(){
        return sizey;
    }

    void setTile(int x, int y, T tile){
        tiles[x][y] = tile;
    }

    T * getTileLeft(int x, int y){
        if(x - 1 == -1){
            return &tiles[sizex][y];
        }
        return &tiles[x-1][y];
    }

    T * getTileRight(int x, int y){
        if(x+1 == sizex){
            return &tiles[0][y];
        }

        return &tiles[x+1][y];
    }

    T * getTileUp(int x, int y){
        if(y-1 == -1){
            return &tiles[x][sizey];
        }
        return &tiles[x][y-1];
    }

    T * getTileDown(int x, int y){
        if(y+1 == sizey){
            return &tiles[x][0];
        }
        return &tiles[x][y+1];
    }

    T * getTile(int x, int y){
        return &tiles[x][y];
    }

    Map(int x, int y, T defaultTile){
        sizex=x; sizey=y;

        tiles = new T*[sizex];
        for(int i = 0; i < sizex; i++){
            tiles[i] = new T[sizey];
        }

        for(int y = 0; y < sizey; y++){
            for(int x = 0; x< sizex; x++){
                setTile(x,y, defaultTile);
            }
        }
    }
    ~Map(){
        for(int i = 0; i < sizex; i++){
            delete[] tiles[i];
        }
        delete[] tiles;
    }
};

void generateTerrainOfMap(Map * themap){
    srand(time(NULL));
    //Plant seeds
    for(int i = 0; i <4; i++){
        int x = rand()%20;
        int y = rand()%20;
        themap
    }
    for(int x = 0; x<themap->getx(); x++){
        for(int y = 0; y<themap->gety(); y++){

        }
    }
}
