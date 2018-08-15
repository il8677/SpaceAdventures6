#pragma once

#include<chrono>
#include<thread>


void sleep(int ms) {
    if(true){
        this_thread::sleep_for(chrono::milliseconds(ms));
    }
}
