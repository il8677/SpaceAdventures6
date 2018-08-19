#include<iostream>
#include "Utility.cpp"


class Actor{
public:
    string name;
    int x;
    int y;
    int health;
    int maxhealth;

    Direction d;

    void die(){

    }

    void heal(int amount){
        health+=amount;
        if(health > maxhealth){
            health = maxhealth;
        }

    }

    void damage(int amount){
        debugout("[Actor : Damage()] Applying " + to_string(amount) + " damage to " + name);
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

    void dash(){
        if(d == LEFT){
            left();left();
        }else if(d == RIGHT){
            right();right();
        }else if(d == UP){
            up();up();
        }else if(d == DOWN){
            down();down();
        }
    }

    void displace(){
        if(x>5){
            left();
        }else if(y>5){
            up();
        }else{
            down();
        }
    }
    void up(){
        y-=1;
        if(y<0){y=0;}
    }
    void down(){
        y+=1;
    }
    void constrict(int xmax, int ymax){
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
