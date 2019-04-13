#include <iostream>
#include "Htable.h"

int main()
{
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    Htable htable;
    htable.read_file(input);
    htable.Dump(output);


    fclose(input);
    fclose(output);
    return 0;
}