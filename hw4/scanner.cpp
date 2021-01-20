#include "scanner.h"
#include <regex>
// putback() puts its argument back into the Token_stream's buffer
void Token_stream::putback(Token t)
{
    if (full) error("putback into a full buffer");
    buffer = t;             // copy t to buffer
    full = true;            // buffer is now full
}

Token Token_stream::get(){
    if (full) {             // do we already have a Token ready?
        full = false;       // remove token from buffer
        return buffer;
    }
    char ch;
    cin.get(ch);            // cin.get() does NOT skip whitespace
    while (isspace(ch)) {
        if (ch == '\n') return Token(print);
        cin.get(ch);
    }
    switch (ch) {
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
        case '=':
        case 'q':
            return Token(ch);   // let each character represent itself
        default:
            if (isdigit(ch)) {
                string s;
                s += ch;
                while (cin.get(ch) && (isdigit(ch) || ch == '.')) s += ch;
                cin.unget();
               regex pat(R"(\d+$)");
                if (std::regex_match(s, pat)){
                    return Token(number, stod(s));
                }
                regex pat1(R"(\d+\.\d\d$)");
                 if (std::regex_match(s, pat1)){
                       return Token(number, stod(s));
                }
               error("Illegal number");
            }
            
            if (isalpha(ch)|| ch=='_') {
                string s;
                s += ch;
                while (cin.get(ch) && (isalpha(ch) || isdigit(ch)
                       || ch == '_'))
                    s += ch;
                cin.unget();
              //  std::cout << "s1:" << s << std::endl;
                if (s == "var") return Token(variable);
                if (s == "const") return Token(constant);
                regex b(R"(__[a-zA-Z0-9_]*(__)?)");
                if (std::regex_match(s,  b)){
                    return Token(name, s);
                }
                //std::cout << "s2:" << s << std::endl;
                regex c(R"([A-Za-z0-9]*)");
                if (std::regex_match(s,  c)){
                    return Token(name, s);
                }
               // std::cout << "s3:" << s << std::endl;
                error("Illegal name");
            }
            error("Bad token");
    }
}

