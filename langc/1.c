#include <stdio.h>
#include <stdlib.h>
struct Ivector;
typedef struct Ivector vector;

void init_vector_clear(vector *c);
void init_vector_free(vector *c);
void init_vector_push_back(vector *c, int d);
void init_vector_pop_back(vector *c);
void init_vector_init(vector *c, int d, int e);

struct Ivector
{
    int size;
    int maxsize;
    int *res;
    char inited;
    void (*pop_back)(vector *);
    void (*push_back)(vector *, int);
    void (*clear)(vector *);
    void (*free)(vector *);
    void (*init)(vector *, int, int);
};

int main(void)
{
    vector a = {.init = init_vector_init};
    a.init(&a, 3, 6);
    for (int i = 0; i < a.size; i++)
    {
        printf("%d ", a.res[i]);
    }
    printf("\n");
    a.push_back(&a, 98);
    for (int i = 0; i < a.size; i++)
    {
        printf("%d ", a.res[i]);
    }
}

void init_vector_pop_back(vector *c)
{
    if (c->size)
        c->size--;
}
void init_vector_clear(vector *c)
{
    c->size = 0;
}
void init_vector_free(vector *c)
{
    free(c->res);
    c->inited = 0;
}
void init_vector_init(vector *c, int d, int e)
{
    c->inited = 1;
    c->res = (int *)malloc(d * 2 * sizeof(int));
    c->size = d;
    c->maxsize = 2 * d;
    for (int i = 0; i < c->size; i++)
        c->res[i] = e;
    c->pop_back = init_vector_pop_back;
    c->push_back = init_vector_push_back;
    c->clear = init_vector_clear;
    c->free = init_vector_free;
}

void init_vector_push_back(vector *c, int d)
{
    if (c->size >= c->maxsize)
    {
        int *temp;
        temp = (int *)malloc(sizeof(int) * c->size * 2);
        for (int i = 0; i < c->size; i++)
        {
            temp[i] = c->res[i];
        }
        temp[c->size] = d;
        free(c->res);
        c->res = temp;
        c->maxsize = c->size * 2;
        c->size++;
    }
    else
    {
        c->res[c->size] = d;
        c->size++;
    }
}