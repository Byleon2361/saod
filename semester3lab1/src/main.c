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
int main()
{
    srand(time(NULL));

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

    /*
    char **words = (char **)malloc(sizeof(char *));
    FILE *f;
    f = fopen("ordered.txt", "r");
    if (f == NULL)
        printf("ERROR");

    int n = 0;
    while (!feof(f))
    {
        words[n] = (char *)malloc(sizeof(char) * 256);
        fgets(words[n], 256, f);
        n++;
        words = (char **)realloc(words, sizeof(char *) * (n + 1));
    }
    fclose(f);

    Avltree *tree = avltree_create(words[0], 0);

    double t;
    char *w;
    char *resWordArray[100];
    Avltree *nodeB;

    // Задание 1
    for (int i = 2; i < n + 1; i++)
    {
        avltree_add(tree, words[i - 1], i - 1);
        if (i % 10000 == 0)
        {
            for (size_t j = 0; j < 100; j++)
            {
                w = words[getRand(0, i - 1)];
                resWordArray[j] = w;
            }

            t = wtime();
            for (size_t j = 0; j < 100; j++)
            {
                nodeB = avltree_lookup(tree, resWordArray[j]);
            }
            t = wtime() - t;
            printf("Avltree: n = %d; time = %.6lf", i, t);
        }
    }
    for (int i = 0; i < n; i++)
    {
        free(words[i]);
    }
    free(words);
    */
    return 0;
}