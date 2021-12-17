#ifndef __RT__TOKEN__H__
#define __RT__TOKEN__H__

#include "common.h"

namespace RTToken
{

    enum Type
    {
        UNKNOWN,
        // keywords
        FROM,
        IMPORT,
        USE,
        LOAD,
        REQUIRE,
        INCLUDE,
        /* punctuations
                the following are all 
                the puncts that exists in 
                the import statements 
                accross multi. languages 
        */
        SYMBOL,
        O_PAREN = 40,
        C_PAREN,
        D_QUOTE = 34,
        S_QUOTE = 39,
        POUND = 35,
        ASTERISK = 42,
        COMMA = 44,
        PERIOD = 46,
        F_SLASH,
        S_COLON = 59,
        L_THAN,
        G_THAN = 62,
        // literals
        LITERAL,
        STRING,
        // end of file
        RT_EOF
    };

    class Token
    {
    public:
        Token(Type t, std::string l);
        virtual ~Token();

        std::string lexeme() const;
        std::string raw() const;
        int type() const;

    private:
        Type _type;
        std::string _lexeme;
        std::string _raw;
    };

}

#endif