#include <stdlib.h>
#include <stdio.h>

#include "../src/rm_utils.h"


int test(token &g){
    // g = (token *)malloc(sizeof(token));
    
    token inside; 
    inside.lexeme += "David";
    inside.type = STRING;

    printf("lexemen of inside %s\n", inside.lexeme.c_str());

    g = inside;
    
    return 0; 
}



int main(){
  token t;

  test(t);

  printf("lexemen of g %s\n", t.lexeme.c_str());


}