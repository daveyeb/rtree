#ifndef RM_SPEC_C
#define RM_SPEC_C

#include "../util/rm_util.h"

static inline int _numeric(lexer * lex);
static inline int _literal(lexer * lex);
static inline int _punctuation(lexer * lex);
static inline int _identifier(lexer * lex);


#endif  // RM_SPEC_C