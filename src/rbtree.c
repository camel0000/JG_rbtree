#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *tree = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nil_node = (node_t *)calloc(1, sizeof(node_t));
  nil_node->color = RBTREE_BLACK;
  tree->nil = nil_node;
  tree->root = nil_node;
  return tree;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory



  free(t);
}

void left_rotate(rbtree *t, node_t *z) {
  node_t *y = z->right;
  z->right = y->left;
  if (y->left != t->nil) {
    y->left->parent = z;
  }
  y->parent = z->parent;
  if (z->parent == t->nil) {
    t->root = y;
  }
  else if (z == z->parent->left) {
    z->parent->left = y;
  }
  else {
    z->parent->right = y;
  }
  y->left = z;
  z->parent = y;
}

void right_rotate(rbtree *t, node_t *z) {
  node_t *y = z->left;
  z->left = y->right;
  if (y->right != t->nil) {
    y->right->parent = z;
  }
  y->parent = z->parent;
  if (z->parent == t->nil) {
    t->root = y;
  }
  else if (z == z->parent->right) {
    z->parent->right = y;
  }
  else {
    z->parent->left = y;
  }
  y->right = z;
  z->parent = y;
}

void rbtree_insert_fixup(rbtree *t, node_t *z) {
  // recolor and rotate nodes to fix violation
  while (z->parent->color == RBTREE_RED) {    // case 0을 제외한 모든 case는 부모-z 모두 red로 특성4 위반
    if (z->parent == z->parent->parent->right) {    // z의 uncle이 z 부모의 좌측에 있는 경우(== violated triangle or line이 우측으로 발생한 경우)
      node_t *y = z->parent->parent->left;      // y는 z의 uncle
      if (y->color == RBTREE_RED) {      // case 1 => z의 uncle이 red인 경우 => 부모, 조부모, 삼촌 recolor
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;    // 원 z의 조부모가 root라면, red이면 안되니, 기준 포인터를 z의 조부모로 바꾸어 줌
      }
      else {                            // case 2 or case 3 => z의 uncle이 black
        if (z == z->parent->left) {     // case 2, z가 부모의 왼쪽 자식인 경우(== violated triangle이 우측으로 발생)
          z = z->parent;      // z의 부모노드를 기준으로 rotation이 일어남
          right_rotate(t, z);
        }
        // case 3
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        left_rotate(t, z->parent->parent);
      }
    }
    else {                                        // z의 uncle이 z 부모의 우측에 있는 경우(== violated triangle or line이 좌측으로 발생한 경우)
      node_t *y = z->parent->parent->right;
      if (y->color == RBTREE_RED) {   // case 1
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else {
        if (z == z->parent->right) {   // case 2
          z = z->parent;
          left_rotate(t, z);
        }
        // case 3
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t, z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;  // case 0
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // insert 'z' node and color it 'red'
  node_t *y = t->nil;   // z의 부모 노드를 가리키기 위한 임시 노드 y
  node_t *x = t->root;  // z가 삽입될 위치를 가리키기 위한 임시 노드 x (root부터 탐색을 시작해야 함)

  node_t *z = (node_t *)calloc(1, sizeof(node_t));
  z->key = key;

  // 새 노드 z를 삽입할 위치 탐색 과정
  while (x != t->nil) {   // x == t->nil 이면 x가 sentinel
    y = x;                // 최종적으로 y는 x의 부모 노드이고, x는 sentinel, y는 자식이 없는 노드
    if (z->key < x->key) {
      x = x->left;
    }
    else {
      x = x->right;
    }
  }

  // z의 멤버 값 설정(?)
  z->parent = y;      // 위 while문에서 ---> x 위치에 z 삽입, y는 x 즉, z의 부모 노드이도록 위치를 탐색하고 왔음
  if (y == t->nil) {  // 삽입된 노드가 없는 경우 (z가 루트 노드가 되는 경우)
    t->root = z;
  }
  else if (z->key < y->key) {   // z가 그 부모 노드인 y의 left child인 경우
    y->left = z;
  }
  else {                        // z가 그 부모 노드인 y의 right child인 경우
    y->right = z;
  }

  z->left = z->right = t->nil;  // 삽입된 z의 nil들 설정 (sentinel로 향하도록)
  z->color = RBTREE_RED;        // 현 함수의 최종 목표인 새 노드 삽입 후, RED로 coloring

  rbtree_insert_fixup(t, z); // violation -> balance 하기 위해 fixup함수로!

  return t->root;   // 모든 삽입 작업을 마치면, RBtree의 루트 노드를 반환 (다른 작업을 할 때에도 루트부터 탐색을 해야하므로)
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *x = t->root;

  while (x != t->nil) {
    if (x->key == key) return x;
    if (x->key < key) x = x->right;
    else x = x->left;
  }

  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  if (t->root == t->nil) return NULL;

  node_t *x = t->root;
  while (x->left != t->nil) {
    x = x->left;
  }
  return x;
}

node_t *rbtree_max(const rbtree *t) {
  if (t->root == t->nil) return NULL;

  node_t *x = t->root;
  while (x->right != t->nil) {
    x = x->right;
  }
  return x;
}

void rbtree_erase_fixup(rbtree *t, node_t *x) {
  node_t *w;

  while (x != t->root && x->color == RBTREE_BLACK) {
    if (x == x->parent->left) {
      w = x->parent->right;

      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t, x->parent);
        w = x->parent->right;
      }

      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else {
        if (w->right->color == RBTREE_BLACK) {
        w->left->color = RBTREE_BLACK;
        w->color = RBTREE_RED;
        right_rotate(t, w);
        w = x->parent->right;
        }
      w->color = x->parent->color;
      x->parent->color = RBTREE_BLACK;
      w->right->color = RBTREE_BLACK;
      left_rotate(t, x->parent);
      x = t->root;
      }
    }
    else {
      w = x->parent->left;

      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t, x->parent);
        w = x->parent->left;
      }

      if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else {
        if (w->left->color == RBTREE_BLACK) {
        w->right->color = RBTREE_BLACK;
        w->color = RBTREE_RED;
        left_rotate(t, w);
        w = x->parent->left;
        }
      w->color = x->parent->color;
      x->parent->color = RBTREE_BLACK;
      w->left->color = RBTREE_BLACK;
      right_rotate(t, x->parent);
      x = t->root;
      }
    }
  }
  x->color = RBTREE_BLACK;
} 

void rbtree_transplant(rbtree *t, node_t *u, node_t *v) {
  if (u->parent == t->nil) {
    t->root = v;
  }
  else if (u == u->parent->left) {
    u->parent->left = v;
  }
  else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

node_t *rbtree_min_from_subtree(rbtree *t, node_t *z) {   // 후계자 찾아서 반환하기
  node_t *x = z;
  while (x->left != t->nil) {
    x = x->left;
  }
  return x;
}

int rbtree_erase(rbtree *t, node_t *z) {
  node_t *y = z;
  color_t y_original_color = y->color;

  node_t *x;

  if (z->left == t->nil) {              // case 1 : 왼자식 nil
    x = z->right;
    rbtree_transplant(t, z, z->right);
  }
  else if (z->right == t->nil) {        // case 2 : 오른자식 nil
    x = z->left;
    rbtree_transplant(t, z, z->left);
  }
  else {                                // case 3 : 두 자식 nil X
    y = rbtree_min_from_subtree(t, z->right);
    y_original_color = y->color;
    x = y->right;

    if (y->parent == z) {
      x->parent = y;
    }
    else {
      rbtree_transplant(t, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    rbtree_transplant(t, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  
  if (y_original_color == RBTREE_BLACK) {
    rbtree_erase_fixup(t, x);
  }

  free(z);

  return 0;
}

void inorderTraversal(const rbtree *t, node_t *root, key_t *arr, const size_t n, size_t *idx) {
  if (root->left == NULL && root->right == NULL) return;

  inorderTraversal(t, root->left, arr, n, idx);
  if (*idx < n) arr[(*idx)++] = root->key;
  else return;
  inorderTraversal(t, root->right, arr, n, idx);
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  if (t->root == t->nil) return 0;

  node_t *root = t->root;
  size_t idx = 0;
  inorderTraversal(t, root, arr, n, &idx);

  return 0;
}