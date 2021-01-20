//
//  Document.cpp
//  Ex1
//
//  Created by Lee Fingerhut on 04/11/2020.
//  Copyright © 2020 Lee Fingerhut. All rights reserved.
//
#include "Document.h"

using namespace document;

class DocumentFileNotFound: public exception {
    virtual const char* what() const throw() {
        return "File Not Found";
    }
} exception_FileNotFound;

class DocumentInsertFailed: public exception {
    virtual const char* what() const throw() {
        return "Insert Failed";
    }
} exception_DocumentInsertFailed;

class DocumentDeleteFailed: public exception {
    virtual const char* what() const throw() {
        return "Insert Failed";
    }
} exception_DocumentDeleteFailed;

void Document::from_file(const string filename){
    std::ifstream myfile;
    myfile.open(filename);
    if (myfile.is_open()){
        string line;
        while(getline(myfile, line)){
            this->lines.push_back(line);
        }
    } else {
        throw exception_FileNotFound;
    }
    myfile.close();
}

void Document::to_file(const string filename){
    std::ofstream myfile;
    myfile.open (filename);
    for (int i = 0; i < this->lines.size(); i++){
        myfile << this->lines[i] << "\n";
    }
    myfile.close();
}

void Document::set_current_line(const int line){
    this->current_line = line;
}

int Document::get_current_line(){
    return this->current_line;
}

string Document::get_line(const int index){
    return this->lines[index];
}

void Document::set_line(const int index, const string line){
    this->lines[index] = line;
}

void Document::insert_line(const int index, const string line){
    if (index > this->lines.size()){
        throw exception_DocumentInsertFailed;
    }
    this->lines.insert(lines.begin() + index, line);
}

int Document::get_max_line(){
    return (int)this->lines.size();
}

void Document::delet_line(const int index){
    if (index >= this->lines.size()){
        throw exception_DocumentDeleteFailed;
    }
    this->lines.erase(lines.begin() + index);
}

bool Document::the_index_fword(const int index, string word){
    string s1 = this->lines[index];
    size_t found = s1.find(word);
    if(found != std::string::npos)
        return 1;
    return 0;
}
void Document::print_file(){
    for(int i = 0; i < this->lines.size(); i++){
            cout << this->lines[i] << endl;
    }
    cout << "done" << endl;
}
