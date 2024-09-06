#include <iostream>
#include "hashable.h"
using namespace std;


HashableString::HashableString(string s) {
    this->s = s;
}

size_t HashableString::getHash() {
    // TODO: Fill this in
    const char* c = s.c_str();
    size_t hash = 0;

    int i=0;
    while(c[i] != '\0'){
        size_t cee = (size_t) c[i];
        hash = 31*hash + cee;
        i++;
    }
    return hash;
}

bool HashableString::equals(Hashable* other) {
    HashableString* otherStr = (HashableString*)other;
    return s.compare(otherStr->s) == 0;
}

Cloneable* HashableString::clone() {
    return new HashableString(s);
}


HashableInt::HashableInt(int i) {
    this->i = i;
}

size_t HashableInt::getHash() {
    return (size_t) i;
}

bool HashableInt::equals(Hashable* other) {
    HashableInt* otherInt = (HashableInt*)other;
    return i == otherInt->i;
}

Cloneable* HashableInt::clone() {
    return new HashableInt(i);
}

Fingerprint::Fingerprint(Anchor* left, Anchor* right){
    this->left = left;
    this->right = right;
}

Cloneable* Fingerprint::clone() {
    return new Fingerprint(this->left, this->right);
}

size_t Fingerprint::getHash() {
    size_t ret;
    int f1 = this->left->getX();
    int f2 = this->right->getX();
    int dw = this->right->getY() - this->left->getY();
    ret = (size_t)f1+f2 * 256 + dw * 256 * 256;
    
    return ret;
}

bool Fingerprint::equals(Hashable* other) {
    Fingerprint* otherInt = (Fingerprint*)other;
    return true;
}