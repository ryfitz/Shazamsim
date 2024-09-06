#ifndef HASHMAP_H
#define HASHMAP_H


#include "hashable.h"
#include "linkedmap.h"
#include "map.h"




class HashMap: public Map {
    private:
        LinkedMap** buckets;
        int numbuckets;
        int count;
    public:
        HashMap(int nums);
        ~HashMap();
        // It is assumed that the key is both Hashable and Cloneable
        void put(Hashable* key, Cloneable* value);
        Cloneable* get(Hashable* key);
        void remove(Hashable* key);
        bool containsKey(Hashable* key);
        Hashable** getKeyList(size_t* N);


};




#endif



