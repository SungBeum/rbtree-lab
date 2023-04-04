#include "rbtree.h"

int main(int argc, char *argv[]) {
    rbtree *p = new_rbtree();
    rbtree_insert(p, 10);
    rbtree_insert(p, 120);
    rbtree_insert(p, 140); 
    rbtree_insert(p, 150);
    rbtree_insert(p, 20);
    rbtree_insert(p, 75);
    rbtree_insert(p, 1235);
    rbtree_insert(p, 19);
    rbtree_insert(p, 28);
    rbtree_insert(p, 5);
    rbtree_insert(p, 5434);
    return 0;
}