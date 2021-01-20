//
//  Document.hpp
//  Ex1
//
//  Created by Lee Fingerhut on 04/11/2020.
//  Copyright © 2020 Lee Fingerhut. All rights reserved.
//

#ifndef Document_hpp
#define Document_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

namespace document{
class Document {
public:
    vector <string> lines       ;
    int             current_line;
    
    Document(){
        this->current_line = 1;
    }
    
    void from_file(const string filename);
    void to_file  (const string filename);
    void set_current_line(const int line);
    int  get_current_line(              );
    string get_line(const int index                   );
    void   set_line(const int index, const string line);
    void insert_line(const int index, const string line);
    int get_max_line();
    void delet_line(const int index);
    bool the_index_fword(const int index, string word);
    void print_file();
};
};

#endif /* Editor_hpp */
