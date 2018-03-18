#include<iostream>

class Actor{
public:
    string name;
    int x;
    int y;
    int health;

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
    Actor(string n, int xx = 0, int yy = 0){
        name = n;
        x = xx;
        y = yy;
    }
};
