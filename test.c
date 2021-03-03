#include <stdio.h>

struct thing {
    int ( * fish) (void );
};


int ink(){
    printf("blue\n");
}


int main(){

    struct thing t;

    t.fish = &ink;
    int a;

    t.fish();

    printf("%d", 1);

    return 0;
}