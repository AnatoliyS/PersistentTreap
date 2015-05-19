#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <climits>

#include "Treap.cpp"
#include "VersionList.cpp"
using namespace std;

class undefinedValueException: public exception
{
  virtual const char* what() const throw()
  {
    return "Undefined value";
  }
};

template<typename T>
class VersionTreap : public Treap<T> {
private:
  VersionList* vl;

  void key_split(item<T>* t, item<T>* &l, item<T>* &r, int key){
    if(!t){
      r = l = NULL; return;
    }
    //printf("Compare versions %d in root and %d\n", t->key, key);
    //printf("Their labels are %d in root and %d\n", vl->v[t->key], vl->v[key]);
    if (vl->less(key, t->key) ){
      key_split(t->l, l, t->l, key);
      r = t;
    }else{
      key_split(t->r, t->r, r, key);
      l = t;
    }
    this->upd(l); 
    this->upd(r);
  }

public:
  VersionTreap(VersionList* _vl): Treap<T>() {
    vl = _vl;
    // Use default NULL value in version of field 0 (creation)
    this->root = new item<T>();
  }

  void key_insert(int key, T val, bool def = true){
    if (this->root == NULL){
      this->root = new item<T>(key, val);
    } else {
      item<T> *l,*r,*c;
      c = new item<T>(key, val);
      c->def = def;
      key_split(this->root, l, r, key);
      this->merge(this->root, l, c);
      this->merge(this->root, this->root, r);
    }
  }

  void version_insert(int version, T val) {
        printf("Enter version insert\n");
    if (this->root == NULL){
      this->root = new item<T>(version, val);
    } else {
        
      item<T>* left = getRightmostFromLeft(version);
      item<T>* right = getLeftmostFromRight(version);
      int l = left->key;
      int r = (right)? right->key : 0;
      int next = vl->getNext(version);
      if (version == 2) {
        printf("l = %d\n", l);
        printf("r = %d\n", r);
        printf("i+ = %d\n", next);
      }

      if (version == l) {
        left->val = val;
        printf("!!!!!!!!! Changed alredy existed value\n");
        return;
        //exit(0);
      }

      if (vl->less(l, version)) {
        key_insert(version, val);
        if (next == 0) { 
          // it means that this is last version in VL
          // and r should be empty (0) in this case
          // TODO: really nothing?
        } else {
          if (r != 0 && vl->less(next, r) || r == 0) {
            key_insert(next, left->val, left->def);
          }
        }
        return;
      }

      printf("OOOOPPSS222");
      exit(0);
    }
  }
 
  item<T>* getRightmostFromLeft(int key) {
    item<T> *l,*r;
    // Split so that all keys <= key are in left
    key_split(this->root, l, r, key);
    item<T>* t = l;
    if (t)
      while(t->r) t = t->r;
    this->merge(this->root, l, r);
    return t;
  }

 item<T>* getLeftmostFromRight(int key) {
    item<T> *l,*r;
    key_split(this->root, l, r, key);
    item<T>* t = r;
    if (t)
       while(t->l) t = t->l;
    this->merge(this->root, l, r);
    return t;
  }


  T getByVersion(int version) {
    item<T>* it = getRightmostFromLeft(version);
    if (it->def)
      return it->val;
    else
      throw new undefinedValueException();
  }

};
