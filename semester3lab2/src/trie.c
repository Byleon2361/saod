#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

Trie *trie_create()
{
    Trie *node;
    if ((node = malloc(sizeof(*node))) == NULL)
        return NULL;
    node->ch = '\0';
    node->value = NULL;
    node->sibling = NULL;
    node->child = NULL;
    return node;
}
Trie *trie_lookup(Trie *root, char *key)
{
    Trie *node, *list;
    for (list = root; *key != '\0'; key++)
    {
        for (node = list; node != NULL; node = node->sibling)
        {
            if (node->ch == *key)
                break;
        }
        if (node != NULL)
            list = node->child;
        else
            return NULL;
    }
    return node;
}
Trie *trie_insert(Trie *root, char *key, int value)
{
    Trie *node, *parent, *list;
    parent = NULL;
    list = root;
    for (; *key != '\0'; key++)
    {
        for (node = list; node != NULL; node = node->sibling)
        {
            if (node->ch == *key)
                break;
        }
        if (node == NULL)
        {
            node = trie_create();
            node->ch = *key;
            node->sibling = list;
            if (parent != NULL)
                parent->child = node;
            else
                root = node;
            list = NULL;
        }
        else
        {
            list = node->child;
        }
        parent = node;
    }

    node->value = value;
    return root;
}
Trie *trie_delete(Trie *root, char *key)
{
    int found;
    return trie_delete_node(root, NULL, key, &found);
}
Trie *trie_delete_node(Trie *root, Trie *parent, char *key, int *found)
{
    Trie *node, *prev = NULL;
    *found = (*key == '\0' && root == NULL) ? 1 : 0;

    if (root == NULL || *key == '\0')
        return root;

    for (node = root; node != NULL; node = node->sibling)
    {
        if (node->ch == *key)
            break;
        prev = node;
    }
    if (node == NULL)
        return root;

    trie_delete_node(node->child, node, key + 1, found);

    if (*found > 0 && node->child == NULL)
    {
        if (prev != NULL)
            prev->sibling = node->sibling;
        else
        {
            if (parent != NULL)
                parent->child = node->sibling;
            else
                root = node->sibling;
        }
        free(node);
    }
    return root;
}
void trie_print(Trie *trie, int level)
{
    for (Trie *node = trie; node != NULL; node = node->sibling)
    {
        for (int i = 0; i < level; i++)
        {
            printf(" ");
        }
        if (node->value != NULL)
        {
            printf("%c ($) (value = %d)\n", node->ch, node->value);
        }
        else
        {
            printf("%c \n", node->ch);
        }
        if (node->child != NULL)
        {
            trie_print(node->child, level + 1);
        }
    }
}
