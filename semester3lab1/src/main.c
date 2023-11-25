#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "avltree.h"
double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    double res = (double)t.tv_sec + (double)t.tv_usec * 1E-6;
    return res;
}
int getRand(int min, int max)
{
    return min + rand() % max;
}
void demo()
{
    Avltree *tree = avltree_create(1, "one");
    Avltree *max;
    Avltree *min;
    tree = avltree_add(tree, 2, "two");
    tree = avltree_add(tree, 3, "three");
    tree = avltree_add(tree, 4, "four");
    tree = avltree_add(tree, 5, "five");
    tree = avltree_add(tree, 6, "six");

    if (avltree_lookup(tree, 3) != NULL)
        printf("%d: %s\n", avltree_lookup(tree, 3)->key, avltree_lookup(tree, 3)->value);
    else
        printf("Node not found\n");

    max = avltree_min(tree);
    min = avltree_max(tree);
    avltree_print(tree, 10);
    printf("MAX: %d: %s\n", max->key, max->value);
    printf("MIN: %d: %s\n", min->key, min->value);

    tree = avltree_replace_node(tree, 6);
    tree = avltree_replace_node(tree, 5);
    tree = avltree_replace_node(tree, 3);
    avltree_print(tree, 10);
    avltree_free(tree);
}
void avltreeTime()
{
    Avltree *tree = NULL;
    double t;
    Avltree *node = NULL;

    for (int i = 1; i < 200001; i++)
    {
        tree = avltree_add(tree, i, "asd");
        if (i % 10000 == 0)
        {
            t = wtime();
            for (int j = 0; j < 100; j++)
            {
                int key = rand() % i;
                node = avltree_lookup(tree, key);
            }
            t = wtime() - t;
            printf("Avltree: n = %d; time = %.6lf\n", i, t);
        }
    }
    avltree_free(tree);
}
int main()
{
    srand(time(NULL));
    demo();

    return 0;
}