#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *NIL = (node_t *)calloc(1, sizeof(node_t)); 
  NIL -> color = RBTREE_BLACK;
  p -> nil = NIL;
  p -> root = NIL;
  // TODO: initialize struct if needed
  return p;
}
// 후위순회하면서 free
void delete_rbtree_postorder(rbtree *t ,node_t *p)
{ if (p == t->nil)
  { 
    return; 
  }
  delete_rbtree_postorder(t, p->left);
  delete_rbtree_postorder(t, p->right);
  free(p);
  p = NULL;
} 
// rbtree 삭제 함수
void delete_rbtree(rbtree *t) {
  free(t->nil);
  delete_rbtree_postorder(t, t->root);
  // TODO: reclaim the tree nodes's memory
  free(t);
  t = NULL;
}
// tmp_node 기준 오른쪽으로 회전
void rotate_right(rbtree *t, node_t *tmp_node)
{
  node_t *tmp_node_left = tmp_node -> left;
  tmp_node -> left = tmp_node_left -> right;
  if ( tmp_node_left -> right != t -> nil )
  {
    tmp_node_left -> right -> parent = tmp_node;
  }
  tmp_node_left -> parent = tmp_node -> parent ;
  if (tmp_node -> parent == t -> nil )
  {
    t -> root = tmp_node_left;
  }
  else if ( tmp_node == tmp_node -> parent -> right)
  {  tmp_node -> parent -> right = tmp_node_left; }
  else
  { tmp_node -> parent -> left = tmp_node_left;}

  tmp_node_left -> right = tmp_node;
  tmp_node -> parent = tmp_node_left;
}
// tmp_node 기준 왼쪽으로 회전
void rotate_left(rbtree *t, node_t *tmp_node)
{
  node_t *tmp_node_right = tmp_node->right;
  tmp_node->right = tmp_node_right->left;
  if (tmp_node_right->left != t->nil)
    tmp_node_right->left->parent = tmp_node;
  tmp_node_right->parent = tmp_node->parent;
  if (tmp_node->parent == t->nil)
    t->root = tmp_node_right;
  else if (tmp_node == tmp_node->parent->left)
    tmp_node->parent->left = tmp_node_right;
  else
    tmp_node->parent->right = tmp_node_right;

  tmp_node_right->left = tmp_node;
  tmp_node->parent = tmp_node_right;
}
// 삽입 시 재조정 함수
void rbtree_insert_fixup(rbtree *t, node_t *tmp_node)
{ // 삽입 시 4번 속성 위반 검사
  while (tmp_node->parent->color == RBTREE_RED)
  { // 부모노드가 조부모노드의 왼쪽 자식일 때 
    if (tmp_node->parent == tmp_node->parent->parent->left)
    {
      node_t *tmp_node_uncle = tmp_node->parent->parent->right;
      // case 1
      if (tmp_node_uncle->color == RBTREE_RED)
      {
        tmp_node->parent->color = RBTREE_BLACK;
        tmp_node_uncle->color = RBTREE_BLACK;
        tmp_node->parent->parent->color = RBTREE_RED;
        tmp_node = tmp_node->parent->parent;
      } // case 2 or 3
      else
      { // case 2
        if (tmp_node == tmp_node->parent->right)
        {
          tmp_node = tmp_node->parent;
          rotate_left(t, tmp_node);
        } // case 3
        tmp_node->parent->color = RBTREE_BLACK;
        tmp_node->parent->parent->color = RBTREE_RED;
        rotate_right(t, tmp_node->parent->parent);
      }
    }// 부모노드가 조부모노드의 오른쪽 자식일 때
    else
    {
      node_t *tmp_node_uncle = tmp_node->parent->parent->left;
      if (tmp_node_uncle->color == RBTREE_RED)
      {
        tmp_node->parent->color = RBTREE_BLACK;
        tmp_node_uncle->color = RBTREE_BLACK;
        tmp_node->parent->parent->color = RBTREE_RED;
        tmp_node = tmp_node->parent->parent;
      }
      else
      {
        if (tmp_node == tmp_node->parent->left)
        {
          tmp_node = tmp_node->parent;
          rotate_right(t, tmp_node);
        }
        tmp_node->parent->color = RBTREE_BLACK;
        tmp_node->parent->parent->color = RBTREE_RED;
        rotate_left(t, tmp_node->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *tmp_node = (node_t *)calloc(1, sizeof(node_t));
  tmp_node->key = key;
  node_t *tmp_node_parent = t->nil;
  node_t *tmp_node_child = t->root;
  while (tmp_node_child != t->nil)
  {
    tmp_node_parent = tmp_node_child;
    if (tmp_node->key < tmp_node_child->key)
      tmp_node_child = tmp_node_child->left;
    else
      tmp_node_child = tmp_node_child->right;
  }
  tmp_node->parent = tmp_node_parent; 

  if (tmp_node_parent == t->nil)
    t->root = tmp_node;
  else if (tmp_node->key < tmp_node_parent->key)
    tmp_node_parent->left = tmp_node;
  else
    tmp_node_parent->right = tmp_node;

  tmp_node->left = t->nil;
  tmp_node->right = t->nil;
  tmp_node->color = RBTREE_RED;
  rbtree_insert_fixup(t, tmp_node);
  // TODO: implement insert
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *node = t->root;
  // 탐색 시작
  while ( node != t -> nil )
  { // key 가 node 값보다 크면, 왼쪽으로
    if (key < node->key)
    {
      node = node->left;
    }
    // key 가 node 값보다 작으면, 오른쪽으로
    else if (key > node->key)
    {
      node = node -> right;
    }
    else  // 탐색 성공
    {
      return node;
    }
  } // 탐색 실패
  // TODO: implement find
  return NULL;
}

// x 노드의 successor 값을 찾는 함수
node_t *node_min(const rbtree *t, node_t *x) {
  while ( x -> left != t -> nil)
  {
    x = x -> left;
  }
  return x;
}

// 트리의 min 값을 반환하는 함수
node_t *rbtree_min(const rbtree *t) {
  node_t *min = t->root;
  while (min -> left != t -> nil)
  {
    min = min -> left;
  }
  // TODO: implement find
  return min;
}

// x 노드의 predecessor 값을 찾는 함수 - 안쓰는 함수
node_t *node_max(const rbtree *t, node_t *x) {
  while ( x -> right != t -> nil)
  {
    x = x -> right;
  }
  return x;
}

// 트리의 max 값을 반환하는 함수
node_t *rbtree_max(const rbtree *t) {
  node_t *max = t->root;
  while (max -> right != t->nil)
  {
    max = max -> right;
  }
  // TODO: implement find
  return max;
}
// u의 서브트리를 v의 서브트리로 덮어쓰는 함수.
void *trans_plant(rbtree *t, node_t *u, node_t *v) {
  // u가 최고루트노드이면, v를 최고루트노드로 바꿔준다
  if ( u -> parent == t -> nil)
  {
    t -> root = v;
  }
  // u가 어떤 노드의 왼쪽자식이면, v를 그 어떤 노드의 왼쪽자식으로 바꿔준다.
  else if ( u == u -> parent -> left)
  {
    u -> parent -> left = v;
  }
  // u가 어떤 노드의 오른쪽 자식이면, v를 그 어떤 노드의 오른쪽자식으로 바꿔준다.
  else
  {
    u -> parent -> right = v;
  }
  // v의 서브트리가 u의 서브트리를 대체한다.
  v -> parent = u -> parent;
  return 0;
}
// 노드 삭제시 재정렬 함수
void rbtree_erase_fixup(rbtree *t, node_t *tmp_node)
{ // while 계속 돌면서 doubly black 없어질 때까지
  while (tmp_node != t->root && tmp_node->color == RBTREE_BLACK)
  {
    // doubly black 이 부모의 왼쪽 자녀일 때
    if (tmp_node == tmp_node->parent->left)
    {
      node_t *tmp_node_sibling = tmp_node->parent->right;
      // 오른쪽 형제가 red 이면 ( case 1 )
      if (tmp_node_sibling->color == RBTREE_RED)
      {
        tmp_node_sibling->color = RBTREE_BLACK;
        tmp_node->parent->color = RBTREE_RED;
        rotate_left(t, tmp_node->parent);
        tmp_node_sibling = tmp_node->parent->right;
      }
      // 오른쪽 형제가 black, 형제의 두 자녀 모두 black 이면 ( case 2 )
      if ((tmp_node_sibling->left->color == RBTREE_BLACK)&&(tmp_node_sibling->right->color == RBTREE_BLACK)){
        tmp_node_sibling->color = RBTREE_RED;
        tmp_node = tmp_node->parent;
      }
      // 오른쪽 형제가 black, 형제의 왼쪽 자녀는 red, 오른쪽 자녀는 black 일 때 ( case3 )
      else{
        if (tmp_node_sibling->right->color == RBTREE_BLACK)
        {
          tmp_node_sibling->left->color = RBTREE_BLACK;
          tmp_node_sibling->color = RBTREE_RED;
          rotate_right(t, tmp_node_sibling);
          tmp_node_sibling = tmp_node->parent->right;
        }
        // 오른쪽 형제가 black, 형제의 오른쪽 자녀가 red ( case 4 )
        tmp_node_sibling->color = tmp_node->parent->color;
        tmp_node->parent->color = RBTREE_BLACK;
        tmp_node_sibling->right->color = RBTREE_BLACK;
        rotate_left(t, tmp_node->parent);
        tmp_node = t->root;
      }
    }
    // 위 내용과 좌우 대칭
    else
    {
      node_t *tmp_node_sibling = tmp_node->parent->left;
      if (tmp_node_sibling->color == RBTREE_RED)
      {
        tmp_node_sibling->color = RBTREE_BLACK;
        tmp_node->parent->color = RBTREE_RED;
        rotate_right(t, tmp_node->parent);
        tmp_node_sibling = tmp_node->parent->left;
      }
      if ((tmp_node_sibling->right->color == RBTREE_BLACK) && (tmp_node_sibling->left->color == RBTREE_BLACK))
      {
        tmp_node_sibling->color = RBTREE_RED;
        tmp_node = tmp_node->parent;
      }
      else
      {
        if (tmp_node_sibling->left->color == RBTREE_BLACK)
        {
          tmp_node_sibling->right->color = RBTREE_BLACK;
          tmp_node_sibling->color = RBTREE_RED;
          rotate_left(t, tmp_node_sibling);
          tmp_node_sibling = tmp_node->parent->left;
        }
        tmp_node_sibling->color = tmp_node->parent->color;
        tmp_node->parent->color = RBTREE_BLACK;
        tmp_node_sibling->left->color = RBTREE_BLACK;
        rotate_right(t, tmp_node->parent);
        tmp_node = t->root;
      }
    }
  }
  tmp_node->color = RBTREE_BLACK;
}
// 노드 삭제 함수
int rbtree_erase(rbtree *t, node_t *z) // z == tmp_node
{
  node_t *y = z;    // y == tmp_node
  color_t y_original_color;   
  y_original_color = y->color;
  node_t *x;    // x == tmp_node_child
  // 삭제하려는 노드의 자녀 노드가 없거나 하나일 때,
  if (z->left == t->nil)
  {
    x = z->right;
    trans_plant(t, z, z->right);
  }
  else if (z->right == t->nil)
  {
    x = z->left;
    trans_plant(t, z, z->left);
  }
  // 삭제하려는 노드의 자녀노드가 둘일 때,
  else
  {
    node_t *y = node_min(t, z->right);    // y == tmp_node 의 successor
    y_original_color = y->color;
    x = y->right;
    // 왼쪽 서브트리 x , 오른쪽 서브트리 x ( y 는 tmp_node의 successor 이므로 왼쪽 서브트리는 x )
    if (y->parent == z)
      x->parent = y;
    // 왼쪽 서브트리 x , 오른쪽 서브트리 o
    else
    {
      trans_plant(t, y, y->right);  // successor 가 올라올 예정이므로 미리 자리 대체
      y->right = z->right;  // successor 인 y가 삭제될 z의 자리에 올라올건데, 이때 z의 right를 미리 붙여놓음.
      y->right->parent = y; // z의 right들의 입장에서 부모를 y로 설정해 줌.
    }
    trans_plant(t, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  // black 을 제거하게 되면, doubly black 생김 -> 재조정 필요
  if (y_original_color == RBTREE_BLACK)
    rbtree_erase_fixup(t, x);
  free(z);
  return 0;
}
void inorder(const rbtree *t, node_t *p, key_t *arr, int *index)
{ if (p == t->nil)
  {
  return;
  }
  inorder(t ,p->left, arr, index);
  arr[(*index)++] = p->key;
  inorder(t, p->right, arr, index);
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  node_t *a = t->root;
  int index = 0;
  inorder(t, a, arr, &index);
 // TODO: implement to_array
  return 0;
}
