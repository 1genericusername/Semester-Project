#ifndef WORD_H
#define WORD_H

#include <docledger.h>

struct Word{
    string word;
    vector<DocLedger> documents;
    //AvlTree<DocLedger> documentsAVL;

    Word(){

    }
    Word(string name){
        word=name;
    }
    Word(string name,DocLedger document){
        word=name;
        documents.emplace_back(document);
        //documentsAVL.
    }
    friend ostream& operator <<(ostream& oss, const Word& obj){

        cout<<obj.word<<endl;
        for(int i=0; i<obj.documents.size();i++)
            cout<<" occurs "<<obj.documents[i].wordInstances<<" times in "<<obj.documents[i].fileName<<endl;
        cout<<endl;
    }

    void add(DocLedger document){
        documents.emplace_back(document);
    }
    bool operator ==(const char* s){
        return(strcmp(word.c_str(),s)==0);
    }
    bool operator !=(const char* s){
        return(strcmp(word.c_str(),s)!=0);
    }
    bool operator <(const char* s){
        return(word.c_str()<s);
    }
    bool operator >(const char* s){
        return(word.c_str()>s);
    }
    bool operator <=(const char* s){
        return(word.c_str()<=s);
    }
    bool operator >=(const char* s){
        return(word.c_str()>=s);
    }
    bool operator ==(Word w){
        return(word==w.word);
    }
    bool operator !=(Word w){
        return(word!=w.word);
    }
    bool operator >(Word w){
        return(word>w.word);
    }
    bool operator <(Word w){
        return(word<w.word);
    }
    bool operator >=(Word w){
        return(word>=w.word);
    }
    bool operator <=(Word w){
        return(word<=w.word);
    }
};

#endif // WORD_H
