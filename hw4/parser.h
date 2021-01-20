// type for (name,value) pairs
class Variable {
public:
    string name;
    int value;
    bool is_const;
    Variable(string n, int v, bool b) :name(n), value(v), is_const(b) { }
};

// type for var_table and associated functions
class Symbol_table {
public:
    int get(string s);                          // return the value of the Variable named s
    void set(string s, int d);                  // set the Variable named s to d
    bool is_declared(string var);               // is var already in var_table?
    int declare(string var, int val,bool b);    // add (var,val) to var_table
private:
    vector<Variable> var_table; // vector of Variables
};

// return the value of the Variable named s
int Symbol_table::get(string s)
{
    for (int i = 0; i<var_table.size(); ++i)
    if (var_table[i].name == s) return var_table[i].value;
    error("get: undefined variable ",s);
}

// set the Variable named s to d
void Symbol_table::set(string s, int d)
{
    for (int i = 0; i<var_table.size(); ++i)
    if (var_table[i].name == s) {
        if (var_table[i].is_const) error(s," is a constant");
        var_table[i].value = d;
        return;
    }
    error("set: undefined variable ",s);
}

// is var already in var_table?
bool Symbol_table::is_declared(string var)
{
    for (int i = 0; i<var_table.size(); ++i)
    if (var_table[i].name == var) return true;
    return false;
}

// add (var,val) to var_table
int Symbol_table::declare(string var, int val, bool b)
{
    if (is_declared(var)) error(var," declared twice");
    var_table.push_back(Variable(var,val,b));
    return val;
}
map<string, SymTabEntryImpl*> contents;
