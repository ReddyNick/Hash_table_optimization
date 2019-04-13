#include <memory.h>
#include "Htable.h"


Htable::~Htable()
{
    for(int i = 0; i < KEY_MAX; i++)
    {
        while(table[i] != nullptr)
        {
            Node* ptr = table[i];
            table[i] = table[i]->next;

            delete ptr;
        }
    }

    delete[] buf;

}

int Htable::read_file(FILE *in)
{
    char str[MAX_STR];

    fseek(in, 0, SEEK_END);
    unsigned int size = ftell(in);
    rewind(in);

    buf = new char[size + 1]{};

    fread(buf, sizeof(buf[0]), size, in);

    char* ptr = buf;
    int move = 0;
    while (sscanf(ptr, " %s %n", str, &move) != -1)
    {
        Insert(str);
        ptr += move;
    }

    return 0;
}

int Htable::Insert(char *str)
{
    int key = getHash(str);

    if (table[key] == nullptr)
    {
        Node* num = new Node;
        table[key] = num;
    }

    Node* ptr = table[key];
    bool already_exist = false;

    while(ptr->next != nullptr && !already_exist)
    {
        ptr = ptr->next;

        if (strcmp(ptr->str, str) == 0)
        {
            ptr->data++;
            already_exist = true;
        }
    }

    if (!already_exist)
    {
        table[key]->data++;

        Node *node = new Node;
        strcpy(node->str, str);

        ptr->next = node;

    }

    return 0;
}

int Htable::getHash(char *str)
{
    int size = strlen(str);
    unsigned int hash = str[0];

    for (int i = 1; i < size; i++)
    {
        hash =  ((hash << 31) | (hash >> 1)) ^ str[i];
    }

    return hash % KEY_MAX;
}

int Htable::Exist(char *str)
{

    Node* ptr = table[getHash(str)];

    while(ptr != nullptr)
    {
        if (!strcmp(ptr->str, str))
            return 1;
        ptr = ptr->next;
    }

    return 0;
}

int Htable::Dump(FILE* out)
{
    for (int i = 0; i < KEY_MAX; i++)
    {
        fprintf(out, "%d: ", i);

        Node* ptr = table[i];
        if (ptr != nullptr)
        {
            fprintf(out, "N = %d: ", ptr->data);
            ptr = ptr->next;

            while (ptr != nullptr)
            {
                fprintf(out, "%s(%d), ", ptr->str, ptr->data);
                ptr = ptr->next;
            }
        }

        fprintf(out, "\n");
    }

    return 0;
}