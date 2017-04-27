#include <iostream>
#include <string>
#include <vector>
#include <ftw.h>
#include <fnmatch.h>
#include "avltree.h"
#include <docparser.h>
#include <algorithm>
#include <docledger.h>
#include <word.h>
#include <findpaths.h>
#include <ctime>
using namespace std;

int main(int argc, char *argv[])
{
    clock_t start = clock();

    findpaths f;

    ftw(".",f.callback,16);

    vector<string> paths = f.returnPaths();

    DocParser parser;
    AvlTree<Word> testTree;
    bool small= false;

    int control;

    if(small){
        control = 1;
    }
    else
        control = paths.size();

    for(int i=0; i< control; i++){
        cout<<endl<<endl<<"Document "<<i<<endl<<"---------------------"<<endl;
        cout<<paths[i]<<endl;
        vector<string> * s;
        if(small){
            s = &parser.parseV(paths[4]);
        }else{
            s= &parser.parseV(paths[i]);
        }

        //-------------------------------------------------------------------//

        cout << "Number of Strings in Document: " << s->size() << endl;
        string temp;
        Word* x;

        for(int j=0; j<s->size(); j++){

            temp=s->operator [](j);
            temp[0]=tolower(temp[0]);
            x=testTree.find(temp);

            if(x==nullptr){//if word is not in tree

                Word w(temp);
                testTree.insert(w);
                x=testTree.find(temp);
            }

            if(x!=nullptr){//if word is in tree

                if(x->documents.size()==0){
                    if(small)
                        x->documents.emplace_back(DocLedger(paths[4],1));
                    else
                        x->documents.emplace_back(DocLedger(paths[i],1));

                }

                else if(x->documents.size() >0){
                    if(!small){
                        if(x->documents[x->documents.size()-1]==paths[i]){
                            x->documents[x->documents.size()-1].wordInstances++;
                        }else{
                            x->documents.emplace_back(DocLedger(paths[i],1));
                        }
                    }else{
                        if(x->documents[x->documents.size()-1]==paths[4]){
                            x->documents[x->documents.size()-1].wordInstances++;
                        }else{
                            x->documents.emplace_back(DocLedger(paths[4],1));
                        }
                    }
                }
            }
        }
    }
    string word1;
    string word2;
    if(small){
        word1="fontenot";
        word2="kalichman";
    }else{
        word1="kalichman";
        word2="innovation";
    }
        //    word1[0]=tolower(word1[0]);
    //    word2[0]=tolower(word2[0]);

    int count = 0;
    int count2 = 0;

    Word* y=testTree.find(word1);
    if(y!=nullptr){
        int control3;

        if(small){
            control3 = 1;
        }
        else{

            control3 = y->documents.size();
        }
        for(int i=0; i<control3;i++){
            count ++;
            //cout<<endl<<word1<<" Appears in: "<<y->documents[i].fileName<<endl;
            //cout<<y->documents[i].wordInstances<<" times"<<endl;
        }
        cout<<endl<<word1<<" Appears in: " << count << " files" << endl;
    }else{
        cout<<"Does Not Exist"<<endl;
    }
    y=testTree.find(word2);
    if(y!=nullptr){
        //count = 0;

        int control2;

        if(small){
            control2 = 1;
        }
        else
            control2 = y->documents.size();
        for(int i=0; i<control2;i++){
            count2++;
            //cout<<endl<<word2<<" Appears in: "<<y->documents[i].fileName<<endl;
            //cout<<y->documents[i].wordInstances<<" times"<<endl;
        }
        cout<<endl<<word2<<" Appears in: " << count2 << " files" << endl;
    }else{
        cout<<"Does Not Exist"<<endl;
    }

    //user interface
    //    bool cont=true;
    //    string userinput;
    //    while(cont){
    //        cout<<"Enter a word (-1 to exit): ";
    //        cin>>userinput;
    //        if(userinput=="-1")
    //            break;
    //        Word* y=testTree.find(userinput);

    //        if(y!=nullptr){
    //            for(int i=0; i<y->documents.size();i++){

    //                cout<<endl<<userinput<<"Appears in: "<<y->documents[i].fileName<<endl;
    //                cout<<y->documents[i].wordInstances<<" times"<<endl;
    //            }
    //        }
    //    }



    //DocParser parser;

    clock_t finish = clock();

    cout << (finish-start)/CLOCKS_PER_SEC << endl;

}
