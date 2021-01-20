#include<iostream>
#include<string>
#include<map>
#include<algorithm>
#include <regex>
#include<stdexcept>
using namespace std;

inline void error(const string& s)
{
	throw runtime_error(s);
}
// constants
const char number = 'n';
const char name = 'a';
const char variable = 'v';
const char constant = 'c';
const char print = 'p';

class Token{
public:
    char kind;        	    // what kind of token
    double value;     	    // for numbers a value 
    string name;     	    // for variables a name 
    Token(char ch) :kind(ch), value(0) { }
    Token(char ch, double val) :kind(ch), value(val) { }
    Token(char ch, string n) :kind{ch}, name{n} { }
};

class Token_stream {
public:
    Token_stream() :full(false), buffer(0) {}
    Token get();            // get a Token
    void putback(Token t);  // put a Token back
private:
    bool full;              // is there a Token in the buffer?
    Token buffer;           // keep a Token when using putback()
};

// declarations so that functions can call each other
double statement();
double declaration(bool);
double expression();
double term();
double primary();
