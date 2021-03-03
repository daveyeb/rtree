#ifndef RM_SPEC_PYTHON
#define RM_SPEC_PYTHON

#include "../utils/rm_utils.h"

static inline int _numeric(lexer * lex);
static inline int _literal(lexer * lex);
static inline int _punctuation(lexer * lex);
static inline int _identifier(lexer * lex);


#endif  // RM_SPEC_PYTHON