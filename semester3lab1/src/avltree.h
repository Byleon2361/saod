#pragma once
#define MAXWORDLENGTH 100
typedef struct avltree
{
    int key;
    char value[MAXWORDLENGTH];

    int height;
    struct avltree *parent;
    struct avltree *left;
    struct avltree *right;

    int deleted;
} Avltree;

Avltree *avltree_create(int key, char *value);                             //+
Avltree *avltree_add(Avltree *tree, int key, char *value);                 //+
Avltree *avltree_lookup(Avltree *tree, int key);                           //+
Avltree *avltree_delete_node(Avltree *tree, Avltree *delNode);             //
Avltree *avltree_delete(Avltree *tree, int key);                           //
void avltree_replace_node(Avltree *parent, Avltree *node, Avltree *child); //
Avltree *avltree_min(Avltree *tree);                                       //+
Avltree *avltree_max(Avltree *tree);                                       //+
void avltree_print(Avltree *tree, int n);                                  //+

//+
void avltree_free(Avltree *tree);
int avltree_height(Avltree *tree);
Avltree *avltree_right_rotate(Avltree *tree);
Avltree *avltree_left_rotate(Avltree *tree);
Avltree *avltree_leftright_rotate(Avltree *tree);
Avltree *avltree_rightleft_rotate(Avltree *tree);

int imax2(int a, int b);
Avltree *avltree_balance(Avltree *tree, int key);