//
//  Editor.cpp
//  Ex1
//
//  Created by Lee Fingerhut on 04/11/2020.
//  Copyright © 2020 Lee Fingerhut. All rights reserved.
//
#include "Editor.h"


class EditorInsertFailed: public exception {
    virtual const char* what() const throw() {
        return "Insert Failed";
    }
} exception_EditorInsertFailed;

class EditorLineRange: public exception {
    virtual const char* what() const throw() {
        return "illeagle index line!";
    }
} exception_EditorLineRange;

static bool isNumber(const string& s){
    string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

static void Tokenize(std::string str, std::vector<std::string> &out){
    str.pop_back();
    int i = 0;
    while (str.at(i) != '/'){
        i++;
    }
    if (i - 1 == 0){
        out.push_back(" ");
    } else {
        out.push_back(str.substr(0, i));
    }
    if (str.length() - 1 == i + 1) {
        out.push_back(" ");
    } else {
        out.push_back(str.substr(i + 1, str.length() - 1));
    }
}

void Editor::loop(){
    string nextLine;
    string newLine;
    
    std::getline(std::cin, nextLine);
    while (nextLine.at(0) != 'q'){
        
        cout << "Line is " << nextLine << endl;
        
        if(isNumber(nextLine)){
            int index = stoi(nextLine);
            if (index <= 0 || index > this->document.get_max_line()){
                throw exception_EditorLineRange;
            }
            this->document.set_current_line(index);
        }
        
        else if(nextLine.at(0) == '+' && isNumber(nextLine.substr(1))){
            int index = this->document.get_current_line() + stoi(nextLine.substr(1));
            cout << this->document.get_max_line() << endl;
            if(index > this->document.get_max_line()){
                throw exception_EditorLineRange;
            }
            this->document.set_current_line(index);
        }
        
        else if(nextLine.at(0) == '-' && isNumber(nextLine.substr(1))){
            int index = this->document.get_current_line() - stoi(nextLine.substr(1));
            if(index <= 0){
                throw exception_EditorLineRange;
            }
            this->document.set_current_line(index);
        }
        
        else if(nextLine.at(0) == '$'){
            this->document.set_current_line(this->document.get_max_line());
        }
        
        else if(nextLine.at(0) == 'a'){
            int i = this->document.get_current_line();
            string WhileLine;
            std::getline(std::cin, WhileLine); // get the 1st line from user
            while(WhileLine.at(0) != '.'){ // while user line does not start with '.'
                try {
                    this->document.insert_line(i, WhileLine);
                    i++;// push line to document
                } catch(const std::exception& e) {
                    throw e;
                }
                std::getline(std::cin, WhileLine); // get the next user line
            }
;
        }
        
        else if(nextLine.at(0) == 'i'){
            int curr_new = 0;
            int i = this->document.get_current_line() - 1;
            string WhileLine;
            std::getline(std::cin, WhileLine);
            while(WhileLine.at(0) != '.'){
                this->document.insert_line(i++, WhileLine);
                curr_new++;
                std::getline(std::cin, WhileLine);
            }
            this->document.set_current_line(curr_new); //curr_new
        }
        
        else if(nextLine.at(0) == 'c'){
            int i = this->document.get_current_line() - 1;
            string WhileLine;
            std::getline(std::cin, WhileLine);
            while(WhileLine.at(0) != '.'){
                this->document.insert_line(i++, WhileLine);
                std::getline(std::cin, WhileLine);
            }
            this->document.delet_line(i);
        }
        
        else if(nextLine.at(0) == 'd'){
            int i = this->document.get_current_line() - 1;
            try {
                this->document.delet_line(i);
                this->document.set_current_line(i++);
            } catch(const std::exception& e) {
                throw e;
            }
            this->document.get_current_line();
        }
        
        else if(nextLine.at(0) == '/'){
            std::string s = nextLine.substr(1, nextLine.length() - 2);
            bool found = true;
            cout << s << endl;
            int i = 0;
            int j = this->document.get_current_line();
            for(i = this->document.get_current_line(); i < this->document.get_max_line(); i++){
                found = this->document.the_index_fword(i, s);
                if(found){
                    j = i;
                    break;
                }
            }
            for (i = 0; i <= this->document.get_current_line() - 1; i++){
                bool found = this->document.the_index_fword(i, s);
                if(found){
                    j = i;
                    break;
                }
            }
            this->document.set_current_line(j + 1);
        }
        
      
        
        else if(nextLine.at(0) == 's'){
            std::vector<std::string> out;
            Tokenize(nextLine.substr(2), out);
            for (int j = 0; j < out.size(); j++){
                cout << out[j] << endl;
            }
            
            int i = this->document.get_current_line() - 1;
            std::string line = this->document.get_line(i);
            string newline;
            size_t pos = line.find(out[0]);
            if (pos == string::npos){
                cout << '\'' << out[0] << '\'' << " is not in line " << this->document.get_current_line() << endl;
            } else {
                size_t len = out[0].length();
                string newline = line.replace(pos, len, out[1]);
                this->document.set_line(i, newline);
            }
            
        }
        
        else if(nextLine.at(0) == 'j'){
            int i = this->document.get_current_line() - 1;
            string curr = this->document.get_line(i);
            string next_curr = this->document.get_line(i + 1);
            string newLine = curr + " " + next_curr;
            this->document.set_line(i, newLine);
            this->document.delet_line(i + 1);
        }
        
        else if(nextLine.at(0) == 'w'){
            this->document.to_file(nextLine.substr(2));
 
        }
        
        else if(nextLine.at(0) == 'q'){
            break;
        }
        
        else{
            cout << "Unrecognized Input Argument " << '\'' << nextLine << '\'' << endl;
        }
        std::getline(std::cin, nextLine);
    }
}

void Editor::from_file(const string filename){
    cout << "Loading: " + filename << endl;
    this->name = filename;
    this->document.from_file(this->name);
}

