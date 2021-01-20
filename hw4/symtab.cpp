#include "symtab.h"
#include "scanner.h"
#include<map>

Attributes& Symbol_table::get(string name){
    auto it = sym_tab.find(name);
    if(it == sym_tab.end()){
        error("not found\n");
    }
    return it->second;
}

void Symbol_table::set(string name, double nv){
    std::map<string,Attributes>::iterator it = sym_tab.find(name);
    if(it!= sym_tab.end()){
        //cout<< "it before change:" << it->second.value << std::endl;
    it->second.value = nv;
         //cout<< "it After change:" << it->second.value << std::endl;
        return;
}
    error("not found\n");
    /*auto it = sym_tab.find(name);
    if(it != sym_tab.end()){
        if(it->second.is_const == false){
            it->second.value = nv;
        }
    }
  
    */
    
}


bool Symbol_table::is_declared(string name){
    auto it = sym_tab.find(name);
    if(it == sym_tab.end())
        return false;
    return true;
}

void Symbol_table::declare(string name, double nv, bool ic){
    if(is_declared(name) == false){
            sym_tab.insert(std::make_pair(name, Attributes(nv, ic)));
        return;
    }
        error("declared twice\n");
}
