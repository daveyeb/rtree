#include "../src/rm_utils.hpp"


void print_files(rm_sfs &files){
    int index;

    index = 0;
    while(index < files.size()){
        printf("file---> %s\n", files[index].name.c_str());
        
        index++;
    }
}

int main(){

    rm_sfs files;
    rm_str str;

    // rm_open_dir(rm_str("/Users/thesun/repomapp/"), files);
    // rm_read_file(files[2], str);
    // print_files(files);


    // printf("read \n%s\n", str.c_str());
    
    


    return 0;
}