#ifndef _RBTREE_H_
#define _RBTREE_H_

#include <stddef.h>
// color_t 는 RBTREE_RED or RBTREE_BLACK 노드의 색상표현
typedef enum { RBTREE_RED, RBTREE_BLACK } color_t;
// key_t 값은 정수형 : 노드의 value 값
typedef int key_t;
// nodt_t 구조체 선언 - 컬러(RBTREE_RED or RBTREE_BLACK) , 키값(key) , 부모포인터, 왼쪽자식포인터, 오른쪽자식포인터
typedef struct node_t {
  color_t color;
  key_t key;
  struct node_t *parent, *left, *right;
} node_t;
// rbtree 구조체 선언 - node_t root 포인터, node_t nil 포인터
typedef struct {
  node_t *root;
  node_t *nil;  // for sentinel
} rbtree;

rbtree *new_rbtree(void);
void delete_rbtree(rbtree *);

node_t *rbtree_insert(rbtree *, const key_t);
node_t *rbtree_find(const rbtree *, const key_t);
node_t *rbtree_min(const rbtree *);
node_t *rbtree_max(const rbtree *);
int rbtree_erase(rbtree *, node_t *);

int rbtree_to_array(const rbtree *, key_t *, const size_t);

#endif  // _RBTREE_H_
