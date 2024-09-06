#ifndef HASHABLE_H
#define HASHABLE_H
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "cloneable.h"
using namespace std;


class Hashable: public Cloneable {
    public:
        virtual ~Hashable() {};
        virtual size_t getHash() = 0;
        virtual bool equals(Hashable* other) = 0;
};

class HashableString: public Hashable {
    public:
        string s;    
        HashableString(string s);
        ~HashableString(){};
        size_t getHash();
        bool equals(Hashable* other);
        Cloneable* clone();
};

class HashableInt: public Hashable {
    public:
        int i;
        HashableInt(int i);
        ~HashableInt(){};
        size_t getHash();
        bool equals(Hashable* other);
        Cloneable* clone();
};



class Anchor {
        int x;
        int y;
    
    public:


        Anchor(int x, int y){
            this->x = x;
            this->y = y;
         
        }

        int getX(){
            return x;
        }
        int getY(){
            return y;
        }
      



};

class Fingerprint: public Hashable {
    
    public:
        Anchor* left;
        Anchor* right;
        
        Fingerprint(Anchor* left, Anchor* right);
        ~Fingerprint(){};
        size_t getHash();
        bool equals(Hashable* other);
        Cloneable* clone();
        
};

#endif
