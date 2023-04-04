#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
    // rbtree.h 파일
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

// #endif  // _RBTREE_H_


rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *NIL = (node_t *)calloc(1, sizeof(node_t)); 
  NIL -> color = RBTREE_BLACK;
  p -> nil = NIL;
  p -> root = NIL;
  // TODO: initialize struct if needed
  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}
// tmp_node 기준 오른쪽으로 회전
void rotate_right(rbtree *t, node_t *tmp_node)
{
  node_t *tmp_node_left = tmp_node -> left;
  tmp_node -> left = tmp_node_left -> right;
  if ( tmp_node_left -> right != t -> nil )
    tmp_node_left -> right -> parent = tmp_node;
  tmp_node_left -> parent = tmp_node -> parent ;
  if (tmp_node -> parent == t -> nil )
    t -> root = tmp_node_left;
  else if ( tmp_node == tmp_node -> parent -> right)
    tmp_node -> parent -> right = tmp_node_left;
  else
    tmp_node -> parent -> left = tmp_node_left;

  tmp_node_left -> right = tmp_node;
  tmp_node -> parent = tmp_node_left;
}
// tmp_node 기준 왼쪽으로 회전
void rotate_left(rbtree *t, node_t *tmp_node)
{
  node_t *tmp_node_right = tmp_node -> right;
  tmp_node -> right = tmp_node_right -> left;
  if ( tmp_node_right -> left != t -> nil )
    tmp_node_right -> left -> parent = tmp_node;
  tmp_node_right -> parent = tmp_node -> parent ;
  if ( tmp_node -> parent == t -> nil )
    t -> root = tmp_node_right;
  else if ( tmp_node == tmp_node -> parent -> left )
    tmp_node -> parent -> left = tmp_node_right;
  else
    tmp_node -> parent -> right = tmp_node_right;
  
  tmp_node_right -> left = tmp_node;
  tmp_node -> parent = tmp_node_right;
}
// 삽입 시 재조정 함수
void rbtree_insert_fixup(rbtree *t, node_t *tmp_node)
{ // 삽입 시 4번 속성 위반 검사
  while ( tmp_node-> parent -> color == RBTREE_RED )
  {     // 부모노드가 조부모노드의 왼쪽 자식일 때 
    if ( tmp_node -> parent == tmp_node -> parent ->parent -> left )
    {
      node_t * tmp_node_uncle = tmp_node -> parent -> parent -> right;
      // case 1
      if ( tmp_node_uncle == RBTREE_RED )
      {
        tmp_node_uncle -> color = RBTREE_BLACK;
        tmp_node -> parent -> color = RBTREE_BLACK;
        tmp_node -> parent -> parent = RBTREE_RED;
        tmp_node = tmp_node -> parent -> parent;
      } // case 2 or 3
      else
      { // case 2
        if ( tmp_node -> key > tmp_node -> parent -> key )
        {
          tmp_node = tmp_node -> parent;
          rotate_left(t, tmp_node);
        } // case 3
        tmp_node -> parent -> color = tmp_node -> parent -> parent -> color;
        tmp_node -> parent -> parent -> color = tmp_node -> parent -> color;
        tmp_node = tmp_node -> parent -> parent;
        rotate_right(t, tmp_node);
      }
    } // 부모노드가 조부모노드의 오른쪽 자식일 때
    else{
      node_t * tmp_node_uncle = tmp_node -> parent -> parent -> left;
      // case 1
      if ( tmp_node_uncle == RBTREE_RED)
      {
        tmp_node_uncle -> color = RBTREE_BLACK;
        tmp_node -> parent -> color = RBTREE_BLACK;
        tmp_node -> parent -> parent = RBTREE_RED;
        tmp_node = tmp_node -> parent -> parent;
      }
       else
      { // case 2
        if ( tmp_node -> key > tmp_node -> parent -> key )
        {
          tmp_node = tmp_node -> parent;
          rotate_right(t, tmp_node);
        } // case 3
        tmp_node -> parent -> color = tmp_node -> parent -> parent -> color;
        tmp_node -> parent -> parent -> color = tmp_node -> parent -> color;
        tmp_node = tmp_node -> parent -> parent;
        rotate_left(t, tmp_node);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}


node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *tmp_node = (node_t*)calloc(1, sizeof(node_t));
  tmp_node -> key = key;
  node_t *tmp_node_parent = t -> nil;
  node_t *tmp_node_child = t -> root;
  while (tmp_node_child != t -> nil)
  {
    tmp_node_parent = tmp_node_child;
    if (tmp_node -> key < tmp_node_child -> key)
      tmp_node_child = tmp_node_child -> left;
    else
      tmp_node_child = tmp_node_child -> right;
  }
  tmp_node -> parent = tmp_node_parent;
  if (tmp_node_parent == t -> nil)
    t -> root = tmp_node;
  else if ( tmp_node -> key < tmp_node_parent-> key)
    tmp_node_parent -> left = tmp_node;
  else
    tmp_node_parent -> right = tmp_node;
  
  tmp_node -> left = t -> nil;
  tmp_node -> right = t -> nil;
  tmp_node -> color = RBTREE_RED;
  rbtree_insert_fixup(t , tmp_node);
  // TODO: implement insert
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}

    // rbtree.c 끝


int main(int argc, char *argv[]) {
  rbtree *new_rbtree(void);
  
}