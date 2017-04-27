#ifndef INDEX_H
#define INDEX_H

#include <iostream>
#include <string>
#include <vector>
#include <ftw.h>
#include <fnmatch.h>
#include "avltree.h"
#include <docparser.h>
#include <algorithm>
#include "porter2_stemmer.h"
#include "word.h"
#include "findpaths.h"
using namespace std;
using namespace Porter2Stemmer;

class Index
{
public:
    Index();
    void generate();
    void makePersistent();
    AvlTree<Word>& get();
private:
    AvlTree<Word> idx;
};

#endif // INDEX_H
