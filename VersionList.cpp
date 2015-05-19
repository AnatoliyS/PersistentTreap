#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

#define MAX_HISTORY 1000

class VersionList {
public:
  int next[MAX_HISTORY];
  int v[MAX_HISTORY];
  int current;
  static const int M = MAX_HISTORY*MAX_HISTORY;

public:
  VersionList() {
    next[0] = 0;
    v[0] = M;
    current = 0;
  }

  bool less(int x, int y) {
    if (x == 0)
      return true;
    if (y == 0)
      return false;
    return v[x] < v[y];
  }

  void insert(int x) {
    int y = ++current;

    int v0 = v[x] % M, w;

    int j = 1;
    int spy = next[x];
    while (true){
      w = (v[spy] - v0) % M;
      if (w <= 0) w += M;
      if (w > j*j) break;
      spy = next[spy];
      j++;
    }
    
    int laborer = next[x];
    int k = 1;
    while (laborer != spy) {
      v[laborer] = ((long long)w * k / j + v0) % M;
      laborer = next[laborer];
      k++;
    }

    v[y] = (v0 + v[next[x]]) / 2;
    int temp = next[x];
    next[x] = current;
    next[y] = temp;
  }

  int getNext(int i) {
    return next[i];
  }

  void print() {
    int temp = 1;
    printf("Version list:\n");
      printf("%d ", 0);
    while(temp != 0){
      printf("%d ", temp);
      temp = next[temp];
    }
    printf("\n");
    temp = 1;
      printf("%d ", v[0]);
    while(temp != 0){
      printf("%d ", v[temp]);
      temp = next[temp];
    }
    printf("\nEnd version list\n");
  }

  vector<int> getVersionVector() {
    int temp = 1;
    vector<int> res;
    while(temp != 0){
      res.push_back(temp);
      temp = next[temp];
    }
    return res; 
  }

};

