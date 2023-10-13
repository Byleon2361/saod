#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "avltree.h"
#define LIMDELETION 2
int deletionCount = 0;
Avltree *avltree_create(int key, char *value)
{
    Avltree *node = malloc(sizeof(*node));
    if (node != NULL)
    {
        if (strlen(value) < MAXWORDLENGTH)
            strcpy(node->value, value);
        else
            return NULL;
        node->key = key;
        node->parent = NULL;
        node->left = NULL;
        node->right = NULL;
        node->deleted = 0;
    }
    return node;
}
Avltree *avltree_add(Avltree *tree, int key, char *value)
{
    if (tree == NULL)
        return avltree_create(key, value);

    if ((avltree_lookup(tree, key) != NULL) && (avltree_lookup(tree, key)->deleted == 1))
    {
        tree = avltree_lookup(tree, key);
        tree->deleted = 0;
        strcpy(tree->value, value);
        return tree;
    }

    if (key < tree->key)
    {
        tree->left = avltree_add(tree->left, key, value);
        tree = avltree_balance(tree, key);
    }
    else if (key > tree->key)
    {
        tree->right = avltree_add(tree->right, key, value);
        tree = avltree_balance(tree, key);
    }
    tree->height = imax2(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    return tree;
}
Avltree *avltree_balance(Avltree *tree, int key)
{
    if (avltree_height(tree->right) - avltree_height(tree->left) == 2)
    {
        if (key > tree->right->key)
        {
            tree = avltree_left_rotate(tree);
        }
        else
        {
            tree = avltree_rightleft_rotate(tree);
        }
    }
    if (avltree_height(tree->left) - avltree_height(tree->right) == 2)
    {
        if (key < tree->left->key)
        {
            tree = avltree_right_rotate(tree);
        }
        else
        {
            tree = avltree_leftright_rotate(tree);
        }
    }
    return tree;
}
Avltree *avltree_lookup(Avltree *tree, int key) // Ищет узел по ключу
{
    while (tree != NULL)
    {
        if (key == tree->key)
            return tree;
        else if (key < tree->key)
            tree = tree->left;
        else
            tree = tree->right;
    }
    return tree;
}

/*
Avltree *avltree_delete_node(Avltree *tree, Avltree *delNode)
{
    if (delNode->left == NULL)
    {
        avltree_replace_node(delNode->parent, delNode, delNode->right);
        if (delNode->parent == NULL) // Если удаляемый элемент корень
            tree = delNode->right;
    }
    else if (delNode->right == NULL)
    {
        avltree_replace_node(delNode->parent, delNode, delNode->left);
        if (delNode->parent == NULL) // Если удаляемый элемент корень
            tree = delNode->left;
    }
    else
    {
        Avltree *min = delNode->right;
        Avltree *minParent = min;
        while (min->left != NULL)
        {
            minParent = min;
            min = min->left;
        }
        avltree_replace_node(delNode->parent, delNode, min);
        if (delNode->parent == NULL)
            tree = min;
        if (delNode->right != NULL)
        {
            minParent->left = min->right;
            min->left = delNode->left;
            min->right = delNode->right;
        }
        else
            min->left = delNode->left;
    }
    tree = avltree_balance(tree, delNode->key);
    free(delNode);
    return tree;
}
void avltree_replace_node(Avltree *parent, Avltree *node, Avltree *child)
{
    if (parent != NULL)
    {
        if (node->key < parent->key)
            parent->left = child;
        else
            parent->right = child;
    }
}
*/
// Avltree *avltree_delete(Avltree *tree, int key)
Avltree *avltree_delete(Avltree *tree, int key)
{
    Avltree *delNode;
    if ((delNode = avltree_lookup(tree, key)) == NULL)
        return NULL;

    delNode->deleted = 1;
    deletionCount++;
    Avltree *newTree = avltree_create(tree->key, tree->value);
    if (deletionCount == LIMDELETION)
    {
        while ((tree != NULL))
        {
            if (tree->deleted == 0)
            {
                avltree_add(newTree, tree->key, tree->value);
            }
            if (key < tree->key)
                tree = tree->left;
            else
                tree = tree->right;
        }
        avltree_free(tree);
        return newTree;
    }
    return tree;
}

// Самый минимльный элемент находится
// в нижним левом углу
Avltree *avltree_min(Avltree *tree)
{
    if (tree == NULL)
        return NULL;
    while (tree->left != NULL)
        tree = tree->left;

    return tree;
}
Avltree *avltree_max(Avltree *tree)
{
    if (tree == NULL)
        return NULL;
    while (tree->right != NULL)
        tree = tree->right;

    return tree;
}
void avltree_print(Avltree *tree, int n)
{
    if (tree == NULL)
        return;

    if (tree->right)
    {
        avltree_print(tree->right, n + 15);
    }

    for (int i = 0; i < n; i++)
        printf(" ");

    printf("%d: %s\n", tree->key, tree->value);

    if (tree->left)
    {
        avltree_print(tree->left, n + 15);
    }
}
void avltree_free(Avltree *tree)
{
    if (tree != NULL)
    {
        avltree_free(tree->left);
        avltree_free(tree->right);
        free(tree);
    }
}
int avltree_height(Avltree *tree)
{
    return (tree != NULL) ? tree->height : -1;
}
/*
int avltree_balance(Avltree *tree)
{
    return avltree_height(tree->left) - avltree_height(tree->right);
}
*/
Avltree *avltree_right_rotate(Avltree *tree)
{
    Avltree *left;
    left = tree->left;
    tree->left = left->right;
    left->right = tree;
    tree->height = imax2(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    left->height = imax2(avltree_height(left->left), tree->height) + 1;
    return left;
}
Avltree *avltree_left_rotate(Avltree *tree)
{
    Avltree *right;
    right = tree->right;
    tree->right = right->left;
    right->left = tree;
    tree->height = imax2(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    right->height = imax2(avltree_height(right->right), tree->height) + 1;
    return right;
}
Avltree *avltree_leftright_rotate(Avltree *tree)
{
    tree->left = avltree_left_rotate(tree->left);
    return avltree_right_rotate(tree);
}
Avltree *avltree_rightleft_rotate(Avltree *tree)
{
    tree->right = avltree_right_rotate(tree->right);
    return avltree_left_rotate(tree);
}
int imax2(int a, int b)
{
    return (a > b) ? a : b;
}