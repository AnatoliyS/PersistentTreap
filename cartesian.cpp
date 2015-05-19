#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "PersistentTreap.cpp"

int main(){
	cout << "ok" << endl;
  
  int last = 0;
  PersistentTreap<int> t;
  last = t.insert(last, 1, 1);
  last = t.insert(last, 3, 3);
  last = t.insert(1, 2, 2);
  
  t.print(1);
  t.print(2);
  t.print(3);



	return 0;
}
