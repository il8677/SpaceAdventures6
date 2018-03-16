#include<iostream>
#include "player.cpp"
#include "tile.cpp"

using namespace std;

Player player();

Map<> planets[5] = {
    Map<>(20,20,NULLTILE),
    Map<>(20,20,NULLTILE),
    Map<>(20,20,NULLTILE),
    Map<>(20,20,NULLTILE),
    Map<>(20,20,NULLTILE),
};

int main(){
    initializeTileTemplates();
    
    for(int i = 0; i < 5; i++){
        planets[5].~Map();
        planets[i].~Map();
    }
    return 0;
}
