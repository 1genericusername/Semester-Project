#include "docparser.h"

DocParser::DocParser() //Reads in all stop words to a std::vector
{

    InputFile.open("stopwords",ios::in);
    if(!InputFile){
        cout << "Error opening file";
    }
    char buffer[80];
    InputFile.getline(buffer,80,'\n');
    int lim = atoi(buffer);
    for(int i=0; i<lim; i++){
        InputFile.getline(buffer,80,'\n');
        //stopWords.push_back(buffer);
        string s = buffer;
        //cout << s<<endl;
        stopWordsAVL.insert(s);
    }
}

void DocParser::addToTree(string temp){
/*
    Word* x;

    x = completeWordsAVL.find(temp);

    if(x == nullptr){
        if(x->)
    }
*/



}

/*
void DocParser::parse(string filename){
    bool inText=false;
    bool showTag=false;
    //Start of code taken from http://stackoverflow.com/questions/11715561/pdf-parsing-in-c-podofo/11719431
    PoDoFo::PdfMemDocument pdf (filename.c_str());
    for (int pn=0; pn<pdf.GetPageCount(); ++pn){
        PoDoFo::PdfPage* page = pdf.GetPage(pn);

        PoDoFo::PdfContentsTokenizer tok(page);
        const char* token = nullptr;
        PoDoFo::PdfVariant var;
        PoDoFo::EPdfContentsType type;
        while(tok.ReadNext(type, token, var)){
            if (type == PoDoFo::ePdfContentsType_Keyword) {
                // process type, token & var
                if(showTag){
                    cout<<endl<<"##########"<<endl<<token<<endl<<"##########"<<endl;
                }
                if(strcmp(token,"BT")==0){
                    inText=true;
                }
                else if(strcmp(token,"ET")==0){
                    inText=false;
                }
                if(inText){
                    if(strcmp(token,"Tj")==0){
                        if (var.IsString()){
                            cout<<var.GetString().GetString();
                        }
                    }
                    else if(strcmp(token,"\'")==0){
                        if(var.IsString())
                            cout<<var.GetString().GetString();
                    }

                    else if(strcmp(token,"\"")==0){
                        if(var.IsString())
                            cout<<var.GetString().GetString();
                    }

                    else if(strcmp(token,"TJ")==0){
                        if (var.IsArray()) {
                            PoDoFo::PdfArray& a = var.GetArray();
                            for (size_t i = 0; i < a.GetSize(); ++i){
                                if (a[i].IsString()){
                                    cout<<a[i].GetString().GetString();
                                }
                            }
                        }
                    }

                }
            }
        }
    }
    //end of code taken from http://stackoverflow.com/questions/11715561/pdf-parsing-in-c-podofo/11719431
}
*/

//vector<string> &DocParser::parseV(string filename)
AvlTree<Word> &DocParser::parseV(string filename)
{
    incompleteWords.clear();

    currentFile = filename;

    string s;

    bool inText=false;
    bool showTag=false;

    //Start of code taken from
    //http://stackoverflow.com/questions/11715561/pdf-parsing-in-c-podofo/11719431

    PoDoFo::PdfMemDocument pdf (filename.c_str());
    for (int pn=0; pn<pdf.GetPageCount(); ++pn){

        PoDoFo::PdfPage* page = pdf.GetPage(pn);
        PoDoFo::PdfContentsTokenizer tok(page);
        const char* token = nullptr;
        PoDoFo::PdfVariant var;
        PoDoFo::EPdfContentsType type;

        //cout << pdf.GetPageCount() << endl;
        //break;

        while(tok.ReadNext(type, token, var)){

            if (type == PoDoFo::ePdfContentsType_Keyword) {

                // process type, token & var

                if(showTag){
                    cout<<endl<<"##########"<<endl<<token<<endl<<"##########"<<endl;
                }
                if(strcmp(token,"BT")==0){
                    inText=true;
                }
                else if(strcmp(token,"ET")==0){
                    inText=false;
                }
                if(inText){

    //end of code taken from
    //http://stackoverflow.com/questions/11715561/pdf-parsing-in-c-podofo/11719431

                    if(strcmp(token, "Td") == 0){
                        s = "\n";
                        //incompleteWords.push_back(s);
                    }
                    else if(strcmp(token, "TD") == 0){
                        s = "\n";
                        //incompleteWords.push_back(s);
                    }

                    else if(strcmp(token,"Tj")==0){
                        if (var.IsString()){
                            s = var.GetString().GetString();
                            //incompleteWords.push_back(s);
                            addToTree(s);
                        }
                    }

                    else if(strcmp(token,"\'")==0){
                        if(var.IsString()){
                            s = var.GetString().GetString();
                            //incompleteWords.push_back(s);
                            addToTree(s);
                        }
                    }

                    else if(strcmp(token,"\"")==0){
                        if(var.IsString()){
                            s = var.GetString().GetString();
                            //incompleteWords.push_back(s);
//                            addToTree(s);
                        }
                    }

                    else if(strcmp(token,"TJ")==0){
                        if (var.IsArray()) {
                            PoDoFo::PdfArray& a = var.GetArray();
                            for (size_t i = 0; i < a.GetSize(); ++i){
                                if (a[i].IsString()){
                                    s = a[i].GetString().GetString();
                                    incompleteWords.push_back(s);
//                                    addToTree(s);


                                }
                            }
                        }
                    }

                }
            }
        }
    }

    //for(int i=0; i<incompleteWords.size(); i++){
        //cout << incompleteWords[i] << endl;
    //}

    //vector<string> completeWords;

    /*
    completeWords.clear();

    string temp = "";

    for(int i=0; i<incompleteWords.size(); i++){

        for(int j=0; j<incompleteWords[i].size(); j++){

            if(incompleteWords[i][j] >= 'A' && incompleteWords[i][j] <= 'Z') //converts all incoming charachter to lowercase
                incompleteWords[i][j] +=32;

            if(incompleteWords[i][j] != ' '){
                temp += incompleteWords[i][j];
            }
            else{

                bool add = true;

                //for(int i=0; i<stopWords.size(); i++){
                    //if(temp == stopWords[i])
                        //add = false;
                //}

                string * sPtr = stopWordsAVL.find(temp);

                if(sPtr != nullptr){
                    add = false;
                }

                if(add == true){
                    completeWords.push_back(temp);
                }
                temp = "";

            }
        }

    }

    //for(int i=0; i<completeWords.size(); i++){
        //stem(completeWords[i]);
    //}
    */

    return incompleteWords;
}




