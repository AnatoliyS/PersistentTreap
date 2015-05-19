#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;


template<typename T>
class item{
  public:
  int key, cnt, prior;
  bool def;
  T val;
  item<T> *l, *r;
  item():cnt(1), key(0), val(0), prior(rand()), l(NULL), r(NULL), def(false){};
  item(T _val):cnt(1), key(0), val(_val), prior(rand()), l(NULL), r(NULL), def(true){};
  item(int _key, T _val):cnt(1), key(_key), val(_val), prior(rand()), l(NULL), r(NULL), def(true){};
  item(item<T>* other):cnt(other->cnt), key(other->key),
            val(other->val), prior(other->prior), l(other->l), r(other->r), def(other->def){};
};

template<typename T>
class Treap {

  protected:
  int smth;

  item<T> *root;

  int cnt(item<T> *t){
    return (t)? t->cnt : 0;
  }

  void upd(item<T> *t){
    if(t){
      t->cnt = cnt(t->l) + cnt(t->r) + 1;
    }
  }

  void merge(item<T>* &t, item<T>* l , item<T>* r){
    if(!l || !r){
      t = (l)?l:r;
      return;
    }
    if(l->prior > r->prior){
      merge(l->r, l->r, r);
      t = l;
    }else{
      merge(r->l, l, r->l);
      t = r;
    }
    upd(t);
  }


  void split(item<T>* t, item<T>* &l, item<T>* &r, int key, int add=0){
    if(!t){
      r = l = NULL; return;
    }
    int cur_key = cnt(t->l) + add;
    if(key <= cur_key){
      split(t->l, l, t->l, key, add);
      r = t;
    }else{
      split(t->r, t->r, r, key, cur_key + 1);
      l = t;
    }
    upd(l); upd(r);
  }

  void key_split(item<T>* t, item<T>* &l, item<T>* &r, int key){
    if(!t){
      r = l = NULL; return;
    }
    if(t->key > key){
      key_split(t->l, l, t->l, key);
      r = t;
    }else{
      key_split(t->r, t->r, r, key);
      l = t;
    }
    upd(l); upd(r);
  }

  void output(item<T>* t){
    if(t){
      output(t->l);
      char* s = (char*)malloc(sizeof(char)*10);
      if (t->def) {
        sprintf(s,"%d", t->val);
      } else {
        sprintf(s, "undef");
      }
      printf("(%d, %s) ", t->key, s);
      output(t->r);
    }
  }

  public:
  Treap() {
    root = NULL;
  }

  void push_back(int val){
    if (root == NULL){
      root = new item<T>(val);
    } else {
     item<T>* c;
      c = new item<T>(val);

      merge(root, root, c);
    }
  }

  void insert(int val, int pos){
    if (root == NULL){
      root = new item<T>(val);
    } else {
      item<T> *l,*r,*c;
      c = new item<T>(val);
      split(root, l, r, pos);
      merge(root, l, c);
      merge(root, root, r);
    }
  }

  int get(int pos) {
    item<T> *l,*r,*c;
    split(root, l, r, pos);
    split(r, c, r, 1);

    int value = c->val;
    merge(r, c, r);
    merge(root, l, r);
    return value;
  }

  void key_insert(int key, int val){
    if (root == NULL){
      root = new item<T>(key, val);
    } else {
      item<T> *l,*r,*c;
      c = new item<T>(key, val);
      key_split(root, l, r, key);

      merge(root, l, c);
      merge(root, root, r);
    }
  }

  void print() {
    printf("Treap = ");
    output(root);
    printf("\n");
  }

  vector<T> getKeys() {
    vector<T> v;
    item<T>* t = root;
    getKeysHelper(t, v);
    return v;
  }
  
  void getKeysHelper(item<T>* t, vector<T> &v) {
    if (t) {
      getKeysHelper(t->l, v);
      v.push_back(t->key);
      getKeysHelper(t->r, v);
    }
  }
  
  vector<T> getValues() {
    vector<T> v;
    item<T>* t = root;
    getValuesHelper(t, v);
    return v;
  }
  
  void getValuesHelper(item<T>* t, vector<T> &v) {
    if (t) {
      getValuesHelper(t->l, v);
      v.push_back(t->val);
      getValuesHelper(t->r, v);
    }
  }
  
  item<T>* getRightmostFromLeft(int key) {
    item<T> *l,*r;
    // Split so that all keys <= key are in left
    key_split(root, l, r, key);
    item<T>* t = l;
    if (t)
      while(t->r) t = t->r;
    merge(root, l, r);
    return t;
  }

  item<T>* getLeftmostFromRight(int key) {
    item<T> *l,*r;
    key_split(root, l, r, key);
    item<T>* t = r;
    if (t)
       while(t->l) t = t->l;
    merge(root, l, r);
    return t;
  }


};

