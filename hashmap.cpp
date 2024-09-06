#include "hashmap.h"
#include <iostream>
using namespace std;









HashMap::HashMap(int nums){
    this->numbuckets = nums;
    this->buckets = new LinkedMap*[numbuckets];
    for(int i = 0; i < numbuckets; i++){
        buckets[i] = new LinkedMap();
    }
    
}

HashMap::~HashMap(){
    for(int i = 0; i < numbuckets; i++){
        delete buckets[i];
    }
    delete[] this->buckets;
}


void HashMap::put(Hashable* key, Cloneable* value) {
    //increment count
    this->count = count + 1;
    size_t keyh = key->getHash();
    int idx = keyh % numbuckets;
    //hold numops currently in this linkedmap at idx
    int hold = this->buckets[idx]->numOps;
    this->buckets[idx]->put(key, value);
    //set second hold to the difference between new numops and old
    int hold2 = this->buckets[idx]->numOps - hold;
    //Increment num ops according to linkedmap increment and +1 to account for hash
    numOps = numOps + hold2 + 1;
}


Cloneable* HashMap::get(Hashable* key){
    size_t keyh = key->getHash();
    int idx = keyh % numbuckets;
    //hold numops currently in this linkedmap at idx
    int hold = this->buckets[idx]->numOps;
    Cloneable* ret = this->buckets[idx]->get(key);
    //set second hold to the difference between new numops and old
    int hold2 = this->buckets[idx]->numOps - hold;
    //Increment num ops according to linkedmap increment and +1 to account for hash
    numOps = numOps + hold2 + 1;
    return ret;
}

void HashMap::remove(Hashable* key){
    if(this->containsKey(key)){
        //increment count
        this->count = count-1;
    size_t keyh = key->getHash();
    int idx = keyh % numbuckets;
    //hold numops currently in this linkedmap at idx
    int hold = this->buckets[idx]->numOps;
    this->buckets[idx]->remove(key);
    //set second hold to the difference between new numops and old
    int hold2 = this->buckets[idx]->numOps - hold;
    //Increment num ops according to linkedmap increment and +1 to account for hash
    numOps = numOps + hold2 + 1;
    }
    
}

bool HashMap::containsKey(Hashable* key){
    size_t keyh = key->getHash();
    int idx = keyh % numbuckets;
    //hold numops currently in this linkedmap at idx
    int hold = this->buckets[idx]->numOps;
    bool ret = this->buckets[idx]->containsKey(key);
    //set second hold to the difference between new numops and old
    int hold2 = this->buckets[idx]->numOps - hold;
    //Increment num ops according to linkedmap increment and +1 to account for hash
    numOps = numOps + hold2 + 1;
    return ret;
}

Hashable** HashMap::getKeyList(size_t* N){

    Hashable** keyList = new Hashable*[count];
    int place = 0;
    for(int i = 0; i< numbuckets; i++){
        Hashable** sublist = buckets[i]->getKeyList(N);
        for(int j = 0; j < (int)*N; j++){
            keyList[place] = sublist[j];
            place++;
        }
        delete[] sublist;
    }

    *N = count;
    return keyList;
}




