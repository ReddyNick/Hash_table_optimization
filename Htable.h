#ifndef HASH_TABLE_OPTIMIZATION_HTABLE_H
#define HASH_TABLE_OPTIMIZATION_HTABLE_H

#include <stdio.h>

const int KEY_MAX = 200;
const int MAX_STR = 100;

struct Node
{
    Node* next = nullptr;
    int data = 0;
    char str[MAX_STR] = "";
};


class Htable
{
private:
    char* buf = nullptr;
    Node* table[KEY_MAX] = {};

public:

    ~Htable();

    int read_file(FILE* in);
    int Insert(char* str);
    int getHash(char* str);
    int Exist(char* str);

    int Dump(FILE* out);
};

#endif //HASH_TABLE_OPTIMIZATION_HTABLE_H
