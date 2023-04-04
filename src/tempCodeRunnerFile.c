node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *z = (node_t *)calloc(1, sizeof(node_t));
  z->key = key;

  node_t *y = t->nil;
  node_t *x = t->root;

  while (x != t->nil) {
    y = x;
    if (key < x->key) {
      x = x->left;
    }
    else {
      x = x->right;
    }
  }



  return t->root;
}