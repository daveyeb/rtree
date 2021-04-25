#ifndef RM_SCANNER
#define RM_SCANNER

#include "rm_utils.hpp"

rm_func 
int scan_tokens(rm_s *scanner, rm_ts toks, rm_ss spec){
    int length;
    int index; 
    int ch;

    if(scanner == NULL)
        return 1; 

    index = 0;

    while(index < scanner->files.size()){
        
        scanner->current = 0;
        scanner->buffer.clear();

        rm_read_file(scanner->files[index], scanner->buffer);
        length = scanner->buffer.length();

        while(scanner->current < length){
            spec._identifier(scanner, toks);
            spec._comment(scanner);
            spec._punctuation(scanner, toks);
            spec._literal(scanner, toks);
            
            rm_s_next(scanner, ch);
        }

        index++;
    } 

    return 0;
}

#endif // !RM_SCANNER
