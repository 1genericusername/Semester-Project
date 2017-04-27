#ifndef DOCPARSER_H
#define DOCPARSER_H

#include <iostream>
#include <podofo.h>
#include <fontconfig.h>
#include <string>
#include <vector>
#include <list>
#include <zlib.h>
#include <fstream>
#include "porter2_stemmer.h"
#include <avltree.h>
#include <word.h>

using namespace std;
using namespace Porter2Stemmer;
class DocParser
{

public:

    DocParser();
    void parse(string);
    vector<string> &parseV(string);
private:
     ifstream InputFile;
     vector<string> stopWords;
     AvlTree<string> stopWordsAVL;
     AvlTree<string> completeWordsAVL;
     vector<string> completeWords;
     vector<string> incompleteWords;

     void addToTree(string temp);

     string currentFile;




};

#endif // DOCPARSER_H
