#include<iostream>

class Actor{
public:
    string name;
    int x;
    int y;

    Actor(string n, int xx = 0, int yy = 0){
        name = n;
        x = xx;
        y = yy;
    }
};
