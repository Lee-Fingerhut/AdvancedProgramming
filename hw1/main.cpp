//
//  main.cpp
//  Ex1
//
//  Created by Lee Fingerhut on 04/11/2020.
//  Copyright © 2020 Lee Fingerhut. All rights reserved.
//
#include <iostream>
#include "Editor.h"
/*
 "ed"                -> argc: 1 , argv[0]: ed
 "ed month.txt"      -> argc: 2 , argv[0]: ed, argv[1]: month.txt
 */

int main(int argc, const char * argv[]){
    Editor editor;
    switch(argc){
        case 1:
            editor.document.set_current_line(0);
            break;
        case 2:
            try {
                editor.from_file(argv[1]);
            } catch (const std::exception& e) {
                cout << '\'' << argv[1] << '\'' << " " << e.what() << endl;
                return 1;
            }
            break;
        default:
            cout << "Too many input arguments." << endl;
            cout << "usage: ed | ed 'filename' | ed < 'filename'" << endl;
            return 1;
    }
    try {
        editor.loop();
    } catch (const std::exception& e) {
        cout << e.what() << endl;
    }
    return 0;
}
