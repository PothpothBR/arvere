#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "arvere_rb.h"

int main(){
    _root = create_root();
    srand(time(0));
    for (int i = 0; i < 1000; i++){
        emplace_node(_root, rand() % 110, "", 0);
    }
    // print_key_tree(*_root);
    printf("\ndeep: %i", find_deep(*_root, 0));
}