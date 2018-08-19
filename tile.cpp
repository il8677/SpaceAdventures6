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
            return &tiles[sizex-1][y];
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
            return &tiles[x][sizey-1];
        }
        return &tiles[x][y-1];
    }

    T * getTileDown(int x, int y){

        if(y+1 == sizey){
            return &tiles[x][0];
        }
        return &tiles[x][y+1];
    }
    T * getTileDirection(int x, int y,Direction d){
        if(d == LEFT){
            return getTileLeft(x,y);
        }else if(d == RIGHT){
            return getTileRight(x,y);
        }else if(d == UP){
            return getTileUp(x,y);
        }else{
            return getTileDown(x,y);
        }
    }
    //---

    T * setTileDirection(int x, int y, T value, Direction d){
        if(d == LEFT){
            setTileLeft(x,y,value);
        }else if(d == RIGHT){
            setTileRight(x,y,value);
        }else if(d == UP){
            setTileUp(x,y,value);
        }else if(d == DOWN){
            setTileDown(x,y,value);
        }
    }

    T * setTileLeft(int x, int y, T value){
        x-=1;
        if(x == -1){
            x=sizex-1;
        }
        setTile(x,y,value);
    }

    T * setTileRight(int x, int y, T value){
        x+=1;
        if(x == sizex){
            x=0;
        }
        setTile(x,y,value);
    }

    T * setTileUp(int x, int y, T value){
        y=y-1;
        if(y == -1){
            y=sizey-1;
        }
        setTile(x,y,value);
    }

    T * setTileDown(int x, int y, T value){
        y=y+1;
        if(y == sizey){
            y=0;
        }
        setTile(x,y,value);
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



void generateTerrainOfMap(Map<> * themap){
    srand(time(NULL));
    Map<int> generationMap(20,20,100);
    //Plant seeds
    for(int t=0;t<7;t++){
    for(int i = 0; i <4; i++){
        int x = rand()%20;
        int y = rand()%20;
        themap->setTile(x,y,tileTemplates[i]);
        generationMap.setTile(x,y, 0);
    }}
    for(int i = 0; i<100;i++){
        for(int x = 0; x<themap->getx(); x++){
            for(int y = 0; y<themap->gety(); y++){
                if(themap->getTileUp(x,y)->getStyle() == NULLTILE.getStyle()&&*generationMap.getTileUp(x,y) > *generationMap.getTile(x,y)) {

                    themap->setTileUp(x,y,*themap->getTile(x,y));
                    generationMap.setTileUp(x,y,*generationMap.getTile(x,y) + 1);

                }else if (themap->getTileDown(x,y)->getStyle() == NULLTILE.getStyle() && *generationMap.getTileDown(x,y) > *generationMap.getTile(x,y)){

                    themap->setTileDown(x,y, *themap->getTile(x,y));
                    generationMap.setTileDown(x,y, *generationMap.getTile(x,y)+1);

                }else if (themap->getTileLeft(x,y)->getStyle() == NULLTILE.getStyle() && *generationMap.getTileLeft(x,y) > *generationMap.getTile(x,y)){

                    themap->setTileLeft(x,y, *themap->getTile(x,y));
                    generationMap.setTileLeft(x,y, *generationMap.getTile(x,y)+1);

                }else if (themap->getTileRight(x,y)->getStyle() == NULLTILE.getStyle() && *generationMap.getTileRight(x,y) > *generationMap.getTile(x,y)){
                    themap->setTileRight(x,y, *themap->getTile(x,y));
                    generationMap.setTileRight(x,y, *generationMap.getTile(x,y)+1);

                }
            }
        }
    }
}
