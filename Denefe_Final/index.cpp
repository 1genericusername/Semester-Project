#include "index.h"

Index::Index()
{

}
void Index::generate(){

    DocParser parser;
    findpaths f;
    ftw(".",f.callback,16);

    vector<string> paths=f.returnPaths();

    for(int i=0; i<paths.size();i++){
        cout<<endl<<endl<<"Document "<<i<<endl<<"---------------------"<<endl;
        cout<<paths[i]<<endl;
        vector<string> s;
        s= parser.parseV(paths[i]);

        cout << "Number of Strings in Document: " << s.size() << endl;
        string temp;
        Word* x;
        for(int j=0; j<s.size(); j++){

            temp=s[j];
            temp[0]=tolower(temp[0]);
            x=idx.find(temp);

            if(x==nullptr){//if word is not in tree

                Word w(temp);
                idx.insert(w);
                x=idx.find(temp);
            }

            if(x!=nullptr){//if word is in tree

                if(x->documents.size()==0){

                    x->documents.emplace_back(DocLedger(paths[i],1));

                }

                else if(x->documents.size() >0){


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

AvlTree<Word>& Index::get(){
    return idx;
}
