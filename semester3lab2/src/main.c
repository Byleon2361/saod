#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "trie.h"
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
    Trie *root = trie_create();
    root = trie_insert(root, "door", 170);
    root = trie_insert(root, "done", 2345);
    root = trie_insert(root, "lesson", 896);
    root = trie_insert(root, "leaf", 67);

    printf("%c\n", trie_lookup(root, "done")->ch);
    printf("%d\n", trie_lookup(root, "done")->value);
    printf("%c\n", trie_lookup(root, "lesson")->ch);
    printf("%d\n", trie_lookup(root, "lesson")->value);

    trie_delete(root, "done");
    if (trie_lookup(root, "done") != NULL)
        printf("%c: %d\n", trie_lookup(root, "done")->ch, trie_lookup(root, "done")->value);
    else
        printf("Node not found\n");

    trie_print(root, 0);
}
void trieTime()
{
    char **words = (char **)malloc(sizeof(char *));
    FILE *f;
    f = fopen("unordered.txt", "r");
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

    Trie *root = trie_create();
    double t;
    char *w;
    char *resWordArray[100];
    printf("%d", n);
    for (int i = 2; i < n + 1; i++)
    {
        trie_insert(root, words[i - 1], i - 1);
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
                trie_lookup(root, resWordArray[j])->value;
            }
            t = wtime() - t;
            printf("                                        Trie: n = %d; time = %.6lf\n", i, t);
        }
    }
}
int main()
{
    srand(time(NULL));
    demo();
    return 0;
}