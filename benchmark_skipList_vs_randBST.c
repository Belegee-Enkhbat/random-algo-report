#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 16
#define NUM_SEARCHES 1000000



typedef struct SLNode {
    int key;
    struct SLNode **forward;
} SLNode;

typedef struct SkipList {
    SLNode *header;
    int level;
} SkipList;

int random_level() {
    int lvl = 1;
    while ((rand() & 1) && lvl < MAX_LEVEL) lvl++;
    return lvl;
}

SLNode* sl_new_node(int key, int level) {
    SLNode* n = malloc(sizeof(SLNode));
    n->key = key;
    n->forward = malloc(sizeof(SLNode*) * level);
    for (int i = 0; i < level; i++) n->forward[i] = NULL;
    return n;
}

SkipList* sl_create() {
    SkipList* sl = malloc(sizeof(SkipList));
    sl->level = 1;
    sl->header = sl_new_node(-1, MAX_LEVEL);
    return sl;
}

void sl_insert(SkipList* sl, int key) {
    SLNode* update[MAX_LEVEL];
    SLNode* x = sl->header;
    for (int i = sl->level - 1; i >= 0; i--) {
        while (x->forward[i] && x->forward[i]->key < key)
            x = x->forward[i];
        update[i] = x;
    }
    int lvl = random_level();
    if (lvl > sl->level) {
        for (int i = sl->level; i < lvl; i++)
            update[i] = sl->header;
        sl->level = lvl;
    }
    x = sl_new_node(key, lvl);
    for (int i = 0; i < lvl; i++)
        x->forward[i] = update[i]->forward[i], update[i]->forward[i] = x;
}

int sl_search(SkipList* sl, int key, int* steps) {
    SLNode* x = sl->header;
    *steps = 0;
    for (int i = sl->level - 1; i >= 0; i--) {
        while (x->forward[i] && x->forward[i]->key < key) {
            x = x->forward[i];
            (*steps)++;
        }
        (*steps)++; 
    }
    x = x->forward[0];
    return (x && x->key == key);
}



typedef struct BSTNode {
    int key;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

BSTNode* bst_new_node(int key) {
    BSTNode* node = malloc(sizeof(BSTNode));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

BSTNode* bst_insert(BSTNode* root, int key) {
    if (!root) return bst_new_node(key);
    if (key < root->key) root->left = bst_insert(root->left, key);
    else root->right = bst_insert(root->right, key);
    return root;
}

int bst_search(BSTNode* root, int key, int* steps) {
    *steps = 0;
    while (root) {
        (*steps)++;
        if (key == root->key) return 1;
        else if (key < root->key) root = root->left;
        else root = root->right;
    }
    return 0;
}



void benchmark(size_t n) {
    printf("== n = %zu ==\n", n);

    SkipList* sl = sl_create();
    BSTNode* bst_root = NULL;

    int* keys = malloc(n * sizeof(int));
    for (size_t i = 0; i < n; ++i) keys[i] = rand();

    for (size_t i = 0; i < n; ++i) {
        sl_insert(sl, keys[i]);
        bst_root = bst_insert(bst_root, keys[i]);
    }

    long long sl_total_steps = 0, bst_total_steps = 0;
    for (size_t i = 0; i < NUM_SEARCHES; ++i) {
        int target;
        if (rand() % 2 == 0)
            target = keys[rand() % n];  
        else
            target = rand();            

        int steps;
        sl_search(sl, target, &steps);
        sl_total_steps += steps;

        bst_search(bst_root, target, &steps);
        bst_total_steps += steps;
    }

    printf("Skip List:    Avg steps: %.2f\n", (double)sl_total_steps / NUM_SEARCHES);
    printf("Randomized BST: Avg steps: %.2f\n", (double)bst_total_steps / NUM_SEARCHES);

    free(keys);
}



int main() {
    srand(time(NULL));
    size_t sizes[] = {5000000, 10000000, 20000000, 50000000};
    for (int i = 0; i < 4; ++i) {
        benchmark(sizes[i]);
    }
    return 0;
}
