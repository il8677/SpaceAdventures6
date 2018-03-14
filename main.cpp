#include<iostream>
#include "player.cpp"
#include "tile.cpp"

using namespace std;

Player player();

Map planets[5] = {
    Map(20,20),
    Map(20,20),
    Map(20,20),
    Map(20,20),
    Map(20,20),
};

int main(){
    initializeTileTemplates();
    
    for(int i = 0; i < 5; i++){
        planets[5].~Map();
    }
    return 0;
}
