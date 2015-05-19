#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "VersionTreap.cpp"
using namespace std;

template<typename T>
class fat_item{
public:
  VersionTreap<int> *key, *cnt, *prior;
  VersionTreap<T> *val;
  VersionTreap<fat_item<T>*> *l,*r;

  fat_item(VersionList* v, int version, int _key, T _val) {
    key = new VersionTreap<int>(v);
    cnt = new VersionTreap<int>(v);
    prior = new VersionTreap<int>(v);
    val = new VersionTreap<T>(v);
    l = new VersionTreap<fat_item<T>*>(v);
    r = new VersionTreap<fat_item<T>*>(v);

    key->version_insert(version, _key);
    cnt->version_insert(version, 1);
    val->version_insert(version, _val);
    prior->version_insert(version, rand());
    l->version_insert(version, NULL);
    r->version_insert(version, NULL);
  }

};

template<typename T>
class PersistentTreap {

  public:
  VersionTreap<fat_item<T>*>* root;
  VersionList* v;

  int cnt(int version, fat_item<T>* t){
    return (t)? t->cnt->getByVersion(version) : 0;
  }
 
  void upd(int new_ver, fat_item<T>* t){
    if(t){
      t->cnt->version_insert(
          new_ver,
          cnt(new_ver, t->l->getByVersion(new_ver)) + cnt(new_ver, t->r->getByVersion(new_ver)) + 1
      );
    }
  }

  void merge(int new_ver, VersionTreap<fat_item<T>*>* &t, fat_item<T>* l , fat_item<T>* r){
    printf("Enter in merge (new = %d)\n", new_ver);
    if(!l || !r){
      //t = (l)?l:r;
      t->version_insert(new_ver, (l) ? l : r);
      return;
    }
    cout << "find priorities" << endl;
    output(new_ver, r);
    output(new_ver, l);
    printf("Compare priorities (left = %d, right = %d)\n", l->prior->getByVersion(new_ver), r->prior->getByVersion(new_ver));
    if(l->prior->getByVersion(new_ver) > r->prior->getByVersion(new_ver)){
      merge(new_ver, l->r, l->r->getByVersion(new_ver), r);
      //t = l;
      t->version_insert(new_ver, l);
    }else{
      merge(new_ver, r->l, l, r->l->getByVersion(new_ver));
      t->version_insert(new_ver, r);
      //t = r;
    }
    upd(new_ver, t->getByVersion(new_ver));
  }
 
  void key_split(int new_ver, fat_item<T>* t, VersionTreap<fat_item<T>*>* &l, VersionTreap<fat_item<T>*>* &r, int key){
    printf("Enter in split (new = %d)\n", new_ver);
    if(!t){
      printf("Root elem is NULL\n");
      //r = l = NULL;

      r->version_insert(new_ver, NULL);
      printf("Added 1\n");
      l->version_insert(new_ver, NULL);
      printf("Added 2\n");
      printf("Left split\n");
      return;
    }
    printf("Root elem (%d, %d)\n", t->key->getByVersion(new_ver),t->val->getByVersion(new_ver));
    printf("Compare key (current = %d, splitby = %d)\n", t->key->getByVersion(new_ver), key);
    if(key <= t->key->getByVersion(new_ver)){
      printf("split left subtree\n");
      key_split(new_ver, t->l->getByVersion(new_ver), l, t->l, key);
      r->version_insert(new_ver, t);
    }else{
      printf("split right subtree\n");
      key_split(new_ver, t->r->getByVersion(new_ver), t->r, r, key);
      l->version_insert(new_ver, t);
    }
    upd(new_ver, l->getByVersion(new_ver));
    upd(new_ver, r->getByVersion(new_ver));
  }

  void output(int version, fat_item<T>* t){
    if(t){
      output(version, t->l->getByVersion(version));
      printf("(%d, %d) ", t->key->getByVersion(version), (int)t->val->getByVersion(version));
      output(version, t->r->getByVersion(version));
    }
  }

 public:
  PersistentTreap() {
    v = new VersionList();
    root = new VersionTreap<fat_item<T>*> (v);
  }

  int push_back(int version, int key, T val){
    if (v->current == 0) { // empty
      v->insert(version);
      fat_item<T>* c = new fat_item<T>(v, 1, key, val);
      root->version_insert(v->current, c);
    } else {
      v->insert(version);
      fat_item<T>* c = new fat_item<T>(v, v->current, key, val);

      this->merge(v->current, root, root->getByVersion(version), c);
    }
    return v->current;
  }

  int insert(int version, int key, int val){
    if (v->current == 0){
      v->insert(version);
      fat_item<T>* c = new fat_item<T>(v, 1, key, val);
      root->version_insert(v->current, c);
    } else {
      v->insert(version);
      VersionTreap<fat_item<T>* >* l = new VersionTreap<fat_item<T>* >(v);
      VersionTreap<fat_item<T>* >* r = new VersionTreap<fat_item<T>* >(v);
      fat_item<T>* c = new fat_item<T>(v, v->current, key, val);
      this->key_split(v->current, root->getByVersion(version), l, r, key);
      printf("left:\n");
      output(v->current, l->getByVersion(v->current));

      printf("right:\n");
      output(v->current, r->getByVersion(v->current));

      this->merge(v->current, root, l->getByVersion(v->current), c);
      this->merge(v->current, root, root->getByVersion(v->current), r->getByVersion(v->current));
    }
    return v->current;
  }

  /*int get(int pos) {
    pitem l,r,c;
    split(root, l, r, pos);
    split(r, c, r, 1);
    
    int value = c->val;
    merge(r, c, r);
    merge(root, l, r);
    return value;
  }*/

  void print(int version) {
    v->print();
    output(version, root->getByVersion(version));
  }



};
