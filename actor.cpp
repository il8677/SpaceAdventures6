#include<iostream>

typedef enum Direction {UP, RIGHT, DOWN, LEFT};

class Actor{
public:
    string name;
    int x;
    int y;
    int health;

    Direction d;

    void die(){

    }
    void damage(int amount){
        health-=amount;
        if(health <= 0){
            die();
        }
    }

    void left(){
        x-=1;
        if(x<0){
            x=0;
        }
    }
    void right(){
        x+=1;
    }
    void up(){
        y-=1;
        if(y<0){y=0;}
    }
    void down(){
        y+=1;
    }
    void constrict(int ymax, int xmax){
        if(y > ymax){
            y=ymax;
        }
        if(x > xmax){
            x=xmax;
        }
    }
    Actor(string n){
        name = n;

    }
};
