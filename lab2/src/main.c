#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "btree.h"
#include "hashtab.h"
#define COUNTWORDS 100
Listnode *hashtab[HASHTAB_SIZE];
// 
// Бинарное дерево:
// Разобраться с кодом, добавить коментарии в фукции удаления, отсально, вроде, всё понятно
// Переделать вывод дерева*
// Добавить больше элементов и изменить старые

// Хэщ-таблица:
// Разобраться с кодом, добавить коментарии!
// Добавить код, демонстрирующий работу программы
// Добавить больше элементов и изменить старые

// Задание 1
//
//

// Задание 2
//
//

// Задание 3
//
//
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

    /*Код, демонстрирующий работу бинарного дерева
    Bstree *tree = bstree_create("hello", 24);
    Bstree *max;
    Bstree *min;
    bstree_add(tree, "good", 677);
    bstree_add(tree, "bye", 129);
    bstree_add(tree, "amogus", 645);
    bstree_add(tree, "hi", 678);
    bstree_add(tree, "beer", 999);

    if (bstree_lookup(tree, "hi") != NULL)
        printf("%s: %d\n", bstree_lookup(tree, "hi")->key, bstree_lookup(tree, "hi")->value);
    else
        printf("Node not found\n");

    max = bstree_min(tree);
    min = bstree_max(tree);
    PrintTree(tree, 10);
    printf("MAX: %s: %d\n", max->key, max->value);
    printf("MIN: %s: %d\n", min->key, min->value);

    Bstree *newTree;
    newTree = bstree_delete(tree, "bye");
    PrintTree(newTree, 10);
    DeleteTree(newTree);
    */

    /*Код, демонстрирующий работу хэш-таблицы
    Listnode *node;

    hashtab_init(hashtab);
    hashtab_add(hashtab, "Ocelot", 17);
    hashtab_add(hashtab, "Flamingo", 4);
    hashtab_add(hashtab, "Fox", 14);
    node = hashtab_lookup(hashtab, "Flamingo");
    if (node != NULL)
        printf("Node: %s, %d\n", node->key, node->value);

    hashtab_delete(hashtab, "Ocelot");
    node = hashtab_lookup(hashtab, "Ocelot");
    if (node != NULL)
        printf("Node: %s, %d\n", node->key, node->value);
    else
        printf("Node not found\n");
    */

    // Можно загрузить слова из файла в массив words[] или связный список

    char *words[COUNTWORDS];
    FILE *f;
    f = fopen("test1.txt", "r");
    if (f == NULL)
        printf("ERROR");
    for (int i = 0; !feof(f); i++)
    {
        words[i] = (char *)malloc(sizeof(char) * 30);
        fscanf(f, "%s", words[i]);
    }
    fclose(f);
    Bstree *tree = bstree_create(words[0], 0); // Создаём корень дерева
    Listnode *nodeH;

    hashtab_init(hashtab);
    double t;
    char *w;
    Bstree *nodeB;
    for (int i = 2; i < COUNTWORDS; i++)
    {
        bstree_add(tree, words[i - 1], i - 1);
        hashtab_add(hashtab, words[i - 1], i - 1);
        if (i % 10000 == 0)
        {
            w = words[getRand(0, i - 1)];

            t = wtime();
            nodeB = bstree_lookup(tree, w);
            t = wtime() - t;
            printf("Bstree: n = %d; time = %.6lf", i - 1, t);

            t = wtime();
            nodeH = hashtab_lookup(hashtab, w);
            t = wtime() - t;
            printf("                                        Hashtab: n = %d; time = %.6lf\n", i - 1, t);
        }
    }

    for (int i = 0; i < COUNTWORDS; i++)
    {
        free(words[i]);
    }

    return 0;
}