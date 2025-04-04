#include <stdlib.h>
#include "interp.h"

int main() { 

 VM* vm = initVM();

    free(vm);
    return EXIT_SUCCESS; 
}
