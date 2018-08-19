#pragma once

#include<chrono>
#include<thread>
#include<cmath>
#include<fstream>

typedef enum Direction {UP, RIGHT, DOWN, LEFT};

void debugout(string s){
    ofstream debugfile;
    debugfile.open("debug.out", ios::app);
    debugfile << s<<endl;
    debugfile.close();
}

void sleep(int ms) {
    if(true){
        this_thread::sleep_for(chrono::milliseconds(ms));
    }
}

int directionX(int x, Direction d){
    if(d == LEFT){
        x-=1;
    }else if(d== RIGHT){
        x+=1;
    }
    return x;
}

int directionY(int y, Direction d){
    if(d==UP){
        y-=1;
    }else if(d==DOWN){
        y+=1;
    }
    return y;
}
Direction getDirection(int x1, int y1, int x2, int y2){ //Get the direction of (x2, y2) from (x1, y1)
    //Calculate y distance (rise)
    int rise = y1 - y2; //Negative if down, positive if up
    //Calculate x distance (run)
    int run = x1 - x2; //Negative if right, positive to left
    //Return the larger value as direction
    return (abs(rise) > abs(run)? (rise>0? UP : DOWN) : (run>0? LEFT : RIGHT));
}

int getDistance(int x1, int y1, int x2, int y2){
    //Calculate y distance (rise)
    int rise = abs(y1 - y2); //Negative if down, positive if up
    //Calculate x distance (run)
    int run = abs(x1 - x2); //Negative if right, positive to left

    return sqrt(pow(rise, 2) + pow(run,2));
}
