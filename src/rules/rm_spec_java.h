#ifndef RM_SPEC_JAVA
#define RM_SPEC_JAVA

#include "../util/rm_util.h"

static inline int _numeric(lexer * lex);
static inline int _literal(lexer * lex);
static inline int _punctuation(lexer * lex);
static inline int _identifier(lexer * lex);


static inline int _numeric(lexer * lex){
    char * buf;
    int c;
    
    buf = lex->buf;
    _curr_char(lex, c);

    switch (isdigit(c))
    {
    case 1:
        break;
    
    default:
        break;
    }


    return 0;
}



#endif  // RM_SPEC_JAVA