
//
// This is example code from Chapter 6.7 "Trying the second version" of
// "Software - Principles and Practice using C++" by Bjarne Stroustrup
//

/*
    This file is known as calculator02buggy.cpp

    I have inserted 5 errors that should cause this not to compile
    I have inserted 3 logic errors that should cause the program to give wrong results

    First try to find an remove the bugs without looking in the book.
    If that gets tedious, compare the code to that in the book (or posted source code)

    Happy hunting!

*/

/*
    Simple calculator

    Revision history:
        Revised by Gavin September 2025.
        Revised by Bjarne Stroustrup (bjarne@stroustrup.com) November 2023
        Revised by Bjarne Stroustrup November 2013
        Revised by Bjarne Stroustrup May 2007
        Revised by Bjarne Stroustrup August 2006
        Revised by Bjarne Stroustrup August 2004
        Originally written by Bjarne Stroustrup (bs@cs.tamu.edu) Spring 2004.

    This program implements a basic expression calculator.
    Input from cin; output to cout.
    The grammar for input is:
    Statement:
        Expression
        Print
        Quit
    Print:
        ";"
    Quit:
        "q"
    Expression:
        Term
        Expression "+" Term
        Expression "-" Term
    Term:
        Primary
        Term "*" Primary
        Term "/" Primary
        Term "%" Primary
    Primary:
        Number
        "(" Expression ")"
        "-" Primary
        "+" Primary
    Number:
        floating-point-literal

    Input comes from cin through the Token_stream called ts.
*/

// #include "../std_lib_facilities.h"
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>

//------------------------------------------------------------------------------

namespace
{
    inline void error(const std::string &s)
    {
        throw std::runtime_error(s);
    }

    inline void keep_window_open()
    {
        std::cin.clear();
        std::cout << "Please enter a character to exit\n";
        char ch;
        std::cin >> ch;
        return;
    }

    constexpr char NUMBER_TOKEN = '8';   // If Token.kind == '8', it's a number token.
    constexpr char QUIT_TOKEN = 'q';     // If Token.kind == 'q', it's a quit token.
    constexpr char PRINT_TOKEN = ';';    // If Token.kind == ';', it's a print token.
    constexpr std::string PROMPT = "> "; // Prompt displayed when asking for input.
    constexpr std::string RESULT = "= "; // Used to indicate that what follows is a result.

    class Token
    {
    public:
        char kind;     // what kind of token
        double value;  // for numbers: a value
        Token(char ch) // make a Token from a char
            : kind(ch), value(0)
        {
        }
        Token(char ch, double val) // make a Token from a char and a double
            : kind(ch), value(val)
        {
        }
    };

    //------------------------------------------------------------------------------

    class Token_stream
    {
    public:
        Token_stream();        // make a Token_stream that reads from std::cin
        Token get();           // get a Token (get() is defined elsewhere)
        void putback(Token t); // put a Token back
        void ignore(char c);   // discard characters up to and including c
    private:
        bool full;    // is there a Token in the buffer?
        Token buffer; // here is where we keep a Token put back using putback()
    };

    //------------------------------------------------------------------------------

    // The constructor just sets full to indicate that the buffer is empty:
    Token_stream::Token_stream()
        : full(false), buffer(0) // no Token in buffer
    {
    }

    //------------------------------------------------------------------------------

    // The putback() member function puts its argument back into the Token_stream's buffer:
    void Token_stream::putback(Token t)
    {
        if (full)
            error("putback() into a full buffer");
        buffer = t;  // copy t to buffer
        full = true; // buffer is now full
    }

    //------------------------------------------------------------------------------

    // The ignore() member function discards characters up to and including c:
    void Token_stream::ignore(char c)
    {
        if (full && buffer.kind == c)
        {
            full = false;
            return;
        }

        full = false;
        char ch{};
        while (std::cin >> ch)
        {
            if (ch == c)
                return;
        }
    }

    //------------------------------------------------------------------------------

    Token Token_stream::get()
    {
        if (full)
        { // do we already have a Token ready?
            // remove token from buffer
            full = false;
            return buffer;
        }

        char ch{};
        if (!(std::cin >> ch)) // note that >> skips whitespace (space, newline, tab, etc.)
            error("No input");

        switch (ch)
        {
        case PRINT_TOKEN:
        case QUIT_TOKEN:
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
            return Token(ch); // let each character represent itself
        case '.':             // A floating point number can start with a dot.
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        {
            std::cin.putback(ch); // put digit back into the input stream
            double val{};
            std::cin >> val; // read a floating-point number
            return Token(NUMBER_TOKEN, val);
        }
        default:
            error("Bad token");
        }
    }

    //------------------------------------------------------------------------------

    Token_stream ts; // provides get() and putback()

    //------------------------------------------------------------------------------

    double expression(); // declaration so that primary() can call expression()

    //------------------------------------------------------------------------------

    // deal with numbers and parentheses
    double primary()
    {
        Token t = ts.get();
        switch (t.kind)
        {
        case '(': // handle '(' expression ')'
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')')
                error("')' expected");
            return d;
        }
        case NUMBER_TOKEN:
            return t.value; // return the number's value
        case '+':
            return primary();
        case '-':
            return -primary();
        default:
            error("primary expected");
        }
    }

    //------------------------------------------------------------------------------

    // deal with *, /, and %
    double term()
    {
        double left = primary();
        Token t = ts.get(); // get the next token from token stream

        while (true)
        {
            switch (t.kind)
            {
            case '*':
                left *= primary();
                t = ts.get();
                break;
            case '/':
            {
                double d = primary();
                if (d == 0)
                    error("divide by zero");
                left /= d;
                t = ts.get();
                break;
            }
            case '%':
            {
                double d = primary();
                if (d == 0)
                    error("Cannot modulo zero!");
                left = std::fmod(left, d);
                t = ts.get();
                break;
            }
            default:
                ts.putback(t); // put t back into the token stream
                return left;
            }
        }
    }

    //------------------------------------------------------------------------------

    // deal with + and -
    double expression()
    {
        double left = term(); // read and evaluate a Term
        Token t = ts.get();   // get the next token from token stream

        while (true)
        {
            switch (t.kind)
            {
            case '+':
                left += term(); // evaluate Term and add
                t = ts.get();
                break;
            case '-':
                left -= term(); // evaluate Term and subtract
                t = ts.get();
                break;
            default:
                ts.putback(t); // put t back into the token stream
                return left;   // finally: no more + or -: return the answer
            }
        }
    }

    void clean_up_mess()
    {
        ts.ignore(PRINT_TOKEN);
    }

    /**
     * @brief Expression evaluation loop.
     */
    void calculate()
    {
        while (std::cin)
        {
            try
            {
                std::cout << PROMPT;
                Token t = ts.get();
                while (t.kind == PRINT_TOKEN)
                    t = ts.get();
                if (t.kind == QUIT_TOKEN)
                    return;
                ts.putback(t);
                std::cout << RESULT << expression() << "\n";
            }
            catch (const std::exception &e)
            {
                std::cerr << "error: " << e.what() << '\n';
                clean_up_mess();
            }
        }
    }
}

//------------------------------------------------------------------------------

int main()
{
    try
    {
        calculate();
        return 0;
    }
    catch (...)
    {
        std::cerr << "Oops: unknown exception!\n";
        keep_window_open();
        return -1;
    }
}

//------------------------------------------------------------------------------
