#ifndef DOCLEDGER_H
#define DOCLEDGER_H

#include <string>
#include <vector>
#include <avltree.h>

using namespace std;

struct DocLedger{

    string fileName;
    int wordInstances;
    DocLedger():wordInstances(0){}
    DocLedger(string f){
        fileName=f;
    }
    DocLedger(string f, int occurences){
        fileName=f;
        wordInstances=occurences;
    }
    bool operator ==(string s){
        return(fileName==s);
    }
};

#endif // DOCLEDGER_H
