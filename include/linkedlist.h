#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class materialNode{
    public:
        char id;
        int weight;
        materialNode* next;
        void set_next_mat(materialNode*);
        materialNode* get_next_mat();
};

class wagonNode{
    public:
        int wagonId;
        materialNode* material;
        wagonNode* next;
        void set_next(wagonNode*);
        wagonNode* get_next();
    
};

class Train{  


    public:
        wagonNode* head;
        void create();
        void addMaterial(char,int);
        void deleteFromWagon(char, int); 
        void printWagon(); //Prints wagon info
};

#endif
