//
//  Editor.hpp
//  Ex1
//
//  Created by Lee Fingerhut on 04/11/2020.
//  Copyright © 2020 Lee Fingerhut. All rights reserved.
//

#ifndef Editor_hpp
#define Editor_hpp
#include <stdio.h>
#include "Document.h"

using namespace std;
using namespace document;

class Editor{
public:
    document::Document document;
    string             name    ;
    
    Editor(){
        this->name = "";
    }
    void loop();
    void from_file(const string filename);
};


#endif /* Editor_hpp */

