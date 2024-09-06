#ifndef CLONEABLE_H
#define CLONEABLE_H
#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;




class Cloneable {
    public:
        virtual ~Cloneable() {};
        virtual Cloneable* clone() = 0;
};

class ValueList: public Cloneable {
    private:
        vector<string> wraplist;
    public:
        ValueList(){};
        ~ValueList(){};
        void push_back(string x) {
            wraplist.push_back(x);
        }
        void pop_back(){
            wraplist.pop_back();
        }
        string get(int i) {
            return wraplist[i];
        }
        size_t size() {
            return wraplist.size();
        }
        Cloneable* clone() {
            ValueList* ret = new ValueList();
            for (size_t i = 0; i < size(); i++) {
                ret->push_back(wraplist[i]);
            }
            return ret;
        }

        void print() {
            for (size_t i = 0; i < size(); i++) {
                cout << wraplist[i];
                if (i < size()-1) {
                    cout << ", ";
                }
            }
            cout << "\n";
        }
};

#endif