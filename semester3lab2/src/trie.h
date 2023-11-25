#pragma once
typedef struct trie
{
    char ch;
    int value;
    struct trie *sibling;
    struct trie *child;
    // TrieNode* children[N];
} Trie;
Trie *trie_create();
Trie *trie_insert(Trie *root, char *key, int value);
Trie *trie_lookup(Trie *root, char *key);
Trie *trie_delete(Trie *root, char *key);
Trie *trie_delete_dfs(Trie *root, Trie *parent, char *key, int *found);
void trie_print(Trie *root, int level);