#include<iostream>
#include<string>
#include<map>
#include<algorithm>
using namespace std;

class Attributes {
public:
    double value;
    bool is_const;
    Attributes(double nv, bool ic)
        : value(nv), is_const(ic) { }
};

class Symbol_table {
public:
    Attributes& get(string name);                    // return the attributes of sym
    void set(string name, double nv);                // set the attribute of value
    bool is_declared(string name);                   // is name already in symtab?
    void declare(string name, double nv, bool ic);   // add name to symtab
private:
    map<string, Attributes> sym_tab;
};

