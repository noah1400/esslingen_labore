#include "objects.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
int main(int argc, char** argv)
{
    srand(time(NULL));
    Object objects[10];
    for(int j = 0; j < 10; j++){
        objects[j] = Object(rand()%10, rand()%10, rand()%2+1);
    }
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(i != j){
                objects[i].attract(&objects[j]);
            }
        }
    }
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 10; j++){
            objects[i].update();
            cout << "Object " << j << ": " << objects[j].pos.x << ", " << objects[j].pos.y << endl;
        }
    }
    return 0;
}