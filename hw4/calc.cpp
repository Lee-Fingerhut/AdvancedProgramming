#include "scanner.h"
extern Token_stream ts;

int main()
try
{
    double val = 0;
    cout << "> "; // prompt
    while (cin) {
        Token t = ts.get();
        if (t.kind == 'q') break;    // quit calc
        if (t.kind == print) {         // print result
            cout << "= " << val << '\n';
            cout << "> "; // prompt
        }
        else {
            ts.putback(t);
            val = statement();
        }
    }
}
catch (exception& e) {
    cerr << "error: " << e.what() << '\n';
    return 1;
}
