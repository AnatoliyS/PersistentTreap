#include <cstdlib>
#include <climits>
#include "gtest/gtest.h"

// Хак, чтобы игнорировать main в тестируемой программе
#define main MainInTestedFile
#include "../../fatnode/PersistentTreap.cpp"
#define main main

///
/// Тесты для сканера строк
///
class TreapTest : public ::testing::Test {
public:
	TreapTest() {};
protected:
	Treap<int> t;
};

TEST_F(TreapTest, key_retrieval)
{
  t.key_insert(1,1);
  t.key_insert(2,2);
  t.key_insert(3,3);
  vector<int> keys = t.getKeys();
  //for(int i = 0; i < keys.size(); i++)
  //  printf("%d ", keys[i]);
  ASSERT_TRUE(keys.size() == 3 && keys[0] == 1 && keys[1] == 2 && keys[2] == 3);
}

TEST_F(TreapTest, pos_insert)
{
  t.insert(1,0);
  t.insert(3,0);
  t.insert(2,0);
  vector<int> val = t.getValues();	
  ASSERT_TRUE(val.size() == 3 && val[0] == 2 && val[1] == 3 && val[2] == 1);
}

TEST_F(TreapTest, pos_insert2)
{
  t.insert(1,0);
  t.insert(2,1);
  t.insert(3,2);
  vector<int> val = t.getValues();	
  ASSERT_TRUE(val.size() == 3 && val[0] == 1 && val[1] == 2 && val[2] == 3);
}

TEST_F(TreapTest, pos_insert3)
{
  t.insert(1,0);
  t.insert(2,1);
  t.insert(3,2);
  t.insert(4,2);
  vector<int> val = t.getValues();
  ASSERT_TRUE(val.size() == 4 && val[0] == 1 && val[1] == 2 && val[2] == 4 && val[3] == 3);
}

TEST_F(TreapTest, pos_get)
{
  t.insert(1,0);
  t.insert(2,1);
  t.insert(3,2);
  t.insert(4,2);
  vector<int> val = t.getValues();
  ASSERT_TRUE(val.size() == 4 && t.get(0) == 1 && t.get(1) == 2 && t.get(2) == 4 && t.get(3) == 3);
}

TEST_F(TreapTest, rightmost_get)
{
  t.key_insert(1,1);
  t.key_insert(3,3);
  t.key_insert(2,2);
  t.key_insert(5,5);
  t.key_insert(8,8);
  int r1 = t.getRightmostFromLeft(5)->key;
  int r2 = t.getRightmostFromLeft(7)->key;
  int r3 = t.getRightmostFromLeft(2)->key;
  int r4 = t.getRightmostFromLeft(10)->key;
  item<int>* it = t.getRightmostFromLeft(0);
  ASSERT_TRUE(r1 == 5);
  ASSERT_TRUE(r2 == 5);
  ASSERT_TRUE(r3 == 2);
  ASSERT_TRUE(r4 == 8);
  ASSERT_TRUE(it == NULL);
}

TEST_F(TreapTest, leftmost_get)
{
  t.key_insert(1,1);
  t.key_insert(3,3);
  t.key_insert(2,2);
  t.key_insert(5,5);
  t.key_insert(8,8);
  int r1 = t.getLeftmostFromRight(5)->key;
  int r2 = t.getLeftmostFromRight(1)->key;
  int r3 = t.getLeftmostFromRight(2)->key;
  int r4 = t.getLeftmostFromRight(0)->key;
  item<int>* it = t.getLeftmostFromRight(8);
  item<int>* it2 = t.getLeftmostFromRight(10);
  ASSERT_TRUE(r1 == 8);
  ASSERT_TRUE(r2 == 2);
  ASSERT_TRUE(r3 == 3);
  ASSERT_TRUE(r4 == 1);
  ASSERT_TRUE(it == NULL);
  ASSERT_TRUE(it2 == NULL);
}

class VersionTreapTest : public ::testing::Test {
public:
	VersionTreapTest() {};
protected:
	VersionTreap<int>* t;
  VersionList* v;
};

TEST_F(VersionTreapTest, rightmost_get)
{
  v = new VersionList();
  t = new VersionTreap<int>(v);
  // for version 1
  v->insert(0);
  t->key_insert(1, 1);

  // for v 2
  v->insert(1); 

  // for v3
  v->insert(2); 
  t->key_insert(3, 3);

  // for v4
  v->insert(1); 
  t->key_insert(4, 4);
  
  // for v5
  v->insert(4); 

  v->print();
  t->print();
  // VL : 1 4 5 2 3
  // TR: (1,1) (4,4) (3,3)
  int r1 = t->getRightmostFromLeft(4)->key;
  int r2 = t->getRightmostFromLeft(3)->key;
  int r3 = t->getRightmostFromLeft(2)->key;
  int r4 = t->getRightmostFromLeft(5)->key;
  int r5 = t->getRightmostFromLeft(1)->key;
  ASSERT_TRUE(r1 == 4);
  ASSERT_TRUE(r2 == 3);
  ASSERT_TRUE(r3 == 4);
  ASSERT_TRUE(r4 == 4);
  ASSERT_TRUE(r5 == 1);
}

TEST_F(VersionTreapTest, leftmost_get)
{
  v = new VersionList();
  t = new VersionTreap<int>(v);
  // for version 1
  v->insert(0);
  t->key_insert(1, 1);

  // for v 2
  v->insert(1); 

  // for v3
  v->insert(2); 
  t->key_insert(3, 3);

  // for v4
  v->insert(1); 
  t->key_insert(4, 4);
  
  // for v5
  v->insert(4); 

  v->print();
  t->print();
  // VL : 1 4 5 2 3
  // TR: (1,1) (4,4) (3,3)
  int r1 = t->getLeftmostFromRight(4)->key;
  int r2 = t->getLeftmostFromRight(2)->key;
  int r3 = t->getLeftmostFromRight(1)->key;
  int r4 = t->getLeftmostFromRight(5)->key;
  item<int>* it = t->getLeftmostFromRight(3);
  ASSERT_TRUE(r1 == 3);
  ASSERT_TRUE(r2 == 3);
  ASSERT_TRUE(r3 == 4);
  ASSERT_TRUE(r4 == 3);
  ASSERT_TRUE(it == NULL);
}

TEST_F(VersionTreapTest, version_insert1)
{
  v = new VersionList();
  t = new VersionTreap<int>(v);
  // for version 1
  v->insert(0);
  t->version_insert(1, 1);

  // for v 2
  v->insert(1); 

  // for v3
  v->insert(2); 
  t->version_insert(3, 3);

  // for v4
  v->insert(1); 
  t->version_insert(4, 4);
  
  // for v5
  v->insert(4); 

  v->print();
  t->print();
  // VL : 1 4 5 2 3
  // TR: (1,1) (4,4) (2, 1) (3,3)
  vector<int> vv_ideal;
  vv_ideal.push_back(1);
  vv_ideal.push_back(4);
  vv_ideal.push_back(5);
  vv_ideal.push_back(2);
  vv_ideal.push_back(3);
  vector<int> vv = v->getVersionVector();
  ASSERT_TRUE(vv.size() == vv_ideal.size());
  for(int i = 0; i < vv_ideal.size(); i++) {
    ASSERT_TRUE(vv[i] == vv_ideal[i]);
  }
  vector<int> keys = t->getKeys();
  vector<int> ideal_keys;
  ideal_keys.push_back(0);
  ideal_keys.push_back(1);
  ideal_keys.push_back(4);
  ideal_keys.push_back(2);
  ideal_keys.push_back(3);
  ASSERT_TRUE(keys.size() == ideal_keys.size());
  for(int i = 0; i < ideal_keys.size(); i++) {
    ASSERT_TRUE(keys[i] == ideal_keys[i]);
  }
  int size = (t->getKeys()).size();
  int r1 = t->getLeftmostFromRight(4)->key;
  int r2 = t->getLeftmostFromRight(2)->key;
  int r3 = t->getLeftmostFromRight(1)->key;
  item<int>* it = t->getLeftmostFromRight(3);
  ASSERT_TRUE(r1 == 2);
  ASSERT_TRUE(r2 == 3);
  ASSERT_TRUE(r3 == 4);
  ASSERT_TRUE(it == NULL);
}

// First actual assignment were made in version 2,
// then we want to insert 4, and it should go before 2
// in the list of values.
TEST_F(VersionTreapTest, version_insert_before_assigned_value)
{
  v = new VersionList();
  t = new VersionTreap<int>(v);
  // for version 1
  v->insert(0);

  // for v2
  v->insert(1); 
  t->version_insert(2, 2);

  // for v3
  v->insert(2); 

  // for v4
  v->insert(1); 
  t->version_insert(4, 4);
  //t->print();
  
  // for v5
  v->insert(4); 

  // for v6
  v->insert(2); 

  // for v7
  v->insert(1); 

  // for v8
  v->insert(1); 
 // t->version_insert(8, 8);
  
  // for v9
  v->insert(8); 
  //t->version_insert(9, 9);
  // for v10
  v->insert(8); 
  // for v11
  v->insert(8); 
  // for v12
  v->insert(10); 
  // for v13
  v->insert(10); 
  // for v14
  v->insert(10); 

  v->print();
  t->print();
  // TR: (4,4) (2,2)
  vector<int> vv_ideal;
  vv_ideal.push_back(1);
  vv_ideal.push_back(8);
  vv_ideal.push_back(11);
  vv_ideal.push_back(10);
  vv_ideal.push_back(14);
  vv_ideal.push_back(13);
  vv_ideal.push_back(12);
  vv_ideal.push_back(9);
  vv_ideal.push_back(7);
  vv_ideal.push_back(4);
  vv_ideal.push_back(5);
  vv_ideal.push_back(2);
  vv_ideal.push_back(6);
  vv_ideal.push_back(3);
  vector<int> vv = v->getVersionVector();
  ASSERT_TRUE(vv.size() == vv_ideal.size());
  for(int i = 0; i < vv_ideal.size(); i++) {
    ASSERT_TRUE(vv[i] == vv_ideal[i]);
  }
  vector<int> keys = t->getKeys();
  vector<int> ideal_keys;
  ideal_keys.push_back(0);
  ideal_keys.push_back(4);
  ideal_keys.push_back(2);
  ASSERT_TRUE(keys.size() == ideal_keys.size());
  for(int i = 0; i < ideal_keys.size(); i++) {
    ASSERT_TRUE(keys[i] == ideal_keys[i]);
  }
}

// same as in book
TEST_F(VersionTreapTest, version_insert_rand_positions)
{
  v = new VersionList();
  t = new VersionTreap<int>(v);
  // for version 1
  v->insert(0);

  // for v2
  v->insert(1); 
  t->version_insert(2, 2);

  // for v3
  v->insert(2); 

  // for v4
  v->insert(1); 
  //t->print();
  
  // for v5
  v->insert(4); 

  // for v6
  v->insert(2); 

  // for v7
  v->insert(1); 

  // for v8
  v->insert(1); 
  t->version_insert(8, 8);
  
  // for v9
  v->insert(8); 
  t->version_insert(9, 9);
  
  // for v10
  v->insert(8); 
  // for v11
  v->insert(8); 
  // for v12
  v->insert(10); 
  // for v13
  v->insert(10); 
  // for v14
  v->insert(10); 

  v->print();
  t->print();
  // TR: (0,0) (8,8) (9,9) (7, 0) (2, 2)
  vector<int> vv_ideal;
  vv_ideal.push_back(1);
  vv_ideal.push_back(8);
  vv_ideal.push_back(11);
  vv_ideal.push_back(10);
  vv_ideal.push_back(14);
  vv_ideal.push_back(13);
  vv_ideal.push_back(12);
  vv_ideal.push_back(9);
  vv_ideal.push_back(7);
  vv_ideal.push_back(4);
  vv_ideal.push_back(5);
  vv_ideal.push_back(2);
  vv_ideal.push_back(6);
  vv_ideal.push_back(3);
  vector<int> vv = v->getVersionVector();
  ASSERT_TRUE(vv.size() == vv_ideal.size());
  for(int i = 0; i < vv_ideal.size(); i++) {
    ASSERT_TRUE(vv[i] == vv_ideal[i]);
  }
  vector<int> keys = t->getKeys();
  vector<int> ideal_keys;
  ideal_keys.push_back(0);
  ideal_keys.push_back(8);
  ideal_keys.push_back(9);
  ideal_keys.push_back(7);
  ideal_keys.push_back(2);
  ASSERT_TRUE(keys.size() == ideal_keys.size());
  for(int i = 0; i < ideal_keys.size(); i++) {
    ASSERT_TRUE(keys[i] == ideal_keys[i]);
  }
}

// Insert to the end of Version list
TEST_F(VersionTreapTest, version_insert_to_end_of_vlist)
{
  v = new VersionList();
  t = new VersionTreap<int>(v);
  // for version 1
  v->insert(0);

  // for v2
  v->insert(1); 
  t->version_insert(2, 2);

  // for v3
  v->insert(2); 

  // for v4
  v->insert(1); 
  //t->print();
  
  // for v5
  v->insert(4); 

  // for v6
  v->insert(2); 

  // for v7
  v->insert(1); 

  // for v8
  v->insert(1); 
  t->version_insert(8, 8);
  
  // for v9
  v->insert(8); 
  t->version_insert(9, 9);
  
  // for v10
  v->insert(8); 
  // for v11
  v->insert(8); 
  // for v12
  v->insert(10); 
  // for v13
  v->insert(10); 
  // for v14
  v->insert(10); 
  
  // for v15
  v->insert(3); 
  t->version_insert(15, 15);

  v->print();
  t->print();
  // TR: (0,0) (8,8) (9,9) (7, 0) (2, 2) (15,15)
  vector<int> vv_ideal;
  vv_ideal.push_back(1);
  vv_ideal.push_back(8);
  vv_ideal.push_back(11);
  vv_ideal.push_back(10);
  vv_ideal.push_back(14);
  vv_ideal.push_back(13);
  vv_ideal.push_back(12);
  vv_ideal.push_back(9);
  vv_ideal.push_back(7);
  vv_ideal.push_back(4);
  vv_ideal.push_back(5);
  vv_ideal.push_back(2);
  vv_ideal.push_back(6);
  vv_ideal.push_back(3);
  vv_ideal.push_back(15);
  vector<int> vv = v->getVersionVector();
  ASSERT_TRUE(vv.size() == vv_ideal.size());
  for(int i = 0; i < vv_ideal.size(); i++) {
    ASSERT_TRUE(vv[i] == vv_ideal[i]);
  }
  vector<int> keys = t->getKeys();
  vector<int> ideal_keys;
  ideal_keys.push_back(0);
  ideal_keys.push_back(8);
  ideal_keys.push_back(9);
  ideal_keys.push_back(7);
  ideal_keys.push_back(2);
  ideal_keys.push_back(15);
  ASSERT_TRUE(keys.size() == ideal_keys.size());
  for(int i = 0; i < ideal_keys.size(); i++) {
    ASSERT_TRUE(keys[i] == ideal_keys[i]);
  }
}

// Insert after block ends
TEST_F(VersionTreapTest, version_insert_after_block_ends)
{
  v = new VersionList();
  t = new VersionTreap<int>(v);
  // for version 1
  v->insert(0);

  // for v2
  v->insert(1); 
  t->version_insert(2, 2);

  // for v3
  v->insert(2); 

  // for v4
  v->insert(1); 
  //t->print();
  
  // for v5
  v->insert(4); 

  // for v6
  v->insert(2); 

  // for v7
  v->insert(1); 

  // for v8
  v->insert(1); 
  t->version_insert(8, 8);
  
  // for v9
  v->insert(8); 
  t->version_insert(9, 9);
  
  // for v10
  v->insert(8); 
  // for v11
  v->insert(8); 
  // for v12
  v->insert(10); 
  // for v13
  v->insert(10); 
  // for v14
  v->insert(10); 
  
  // for v15
  v->insert(5); 
  t->version_insert(15, 15);

  v->print();
  t->print();
  // TR: (0,0) (8,8) (9,9) (7, 0) (2, 2) (15,15)
  vector<int> vv_ideal;
  vv_ideal.push_back(1);
  vv_ideal.push_back(8);
  vv_ideal.push_back(11);
  vv_ideal.push_back(10);
  vv_ideal.push_back(14);
  vv_ideal.push_back(13);
  vv_ideal.push_back(12);
  vv_ideal.push_back(9);
  vv_ideal.push_back(7);
  vv_ideal.push_back(4);
  vv_ideal.push_back(5);
  vv_ideal.push_back(15);
  vv_ideal.push_back(2);
  vv_ideal.push_back(6);
  vv_ideal.push_back(3);
  vector<int> vv = v->getVersionVector();
  ASSERT_TRUE(vv.size() == vv_ideal.size());
  for(int i = 0; i < vv_ideal.size(); i++) {
    ASSERT_TRUE(vv[i] == vv_ideal[i]);
  }
  vector<int> keys = t->getKeys();
  vector<int> ideal_keys;
  ideal_keys.push_back(0);
  ideal_keys.push_back(8);
  ideal_keys.push_back(9);
  ideal_keys.push_back(7);
  ideal_keys.push_back(15);
  ideal_keys.push_back(2);
  ASSERT_TRUE(keys.size() == ideal_keys.size());
  for(int i = 0; i < ideal_keys.size(); i++) {
    ASSERT_TRUE(keys[i] == ideal_keys[i]);
  }
}

// Insert in the middle of block
TEST_F(VersionTreapTest, version_insert_in_the_middle1)
{
  v = new VersionList();
  t = new VersionTreap<int>(v);
  // for version 1
  v->insert(0);

  // for v2
  v->insert(1); 
  t->version_insert(2, 2);

  // for v3
  v->insert(2); 

  // for v4
  v->insert(1); 
  //t->print();
  
  // for v5
  v->insert(4); 

  // for v6
  v->insert(2); 

  // for v7
  v->insert(1); 

  // for v8
  v->insert(1); 
  t->version_insert(8, 8);
  
  // for v9
  v->insert(8); 
  t->version_insert(9, 9);
  
  // for v10
  v->insert(8); 
  // for v11
  v->insert(8); 
  // for v12
  v->insert(10); 
  // for v13
  v->insert(10); 
  // for v14
  v->insert(10); 
  
  // for v15
  v->insert(6); 
  t->version_insert(15, 15);

  v->print();
  t->print();
  // TR: (0,0) (8,8) (9,9) (7, 0) (2, 2) (15,15)
  vector<int> vv_ideal;
  vv_ideal.push_back(1);
  vv_ideal.push_back(8);
  vv_ideal.push_back(11);
  vv_ideal.push_back(10);
  vv_ideal.push_back(14);
  vv_ideal.push_back(13);
  vv_ideal.push_back(12);
  vv_ideal.push_back(9);
  vv_ideal.push_back(7);
  vv_ideal.push_back(4);
  vv_ideal.push_back(5);
  vv_ideal.push_back(2);
  vv_ideal.push_back(6);
  vv_ideal.push_back(15);
  vv_ideal.push_back(3);
  vector<int> vv = v->getVersionVector();
  ASSERT_TRUE(vv.size() == vv_ideal.size());
  for(int i = 0; i < vv_ideal.size(); i++) {
    ASSERT_TRUE(vv[i] == vv_ideal[i]);
  }
  vector<int> keys = t->getKeys();
  vector<int> ideal_keys;
  ideal_keys.push_back(0);
  ideal_keys.push_back(8);
  ideal_keys.push_back(9);
  ideal_keys.push_back(7);
  ideal_keys.push_back(2);
  ideal_keys.push_back(15);
  ideal_keys.push_back(3);
  ASSERT_TRUE(keys.size() == ideal_keys.size());
  for(int i = 0; i < ideal_keys.size(); i++) {
    ASSERT_TRUE(keys[i] == ideal_keys[i]);
  }
}

// Insert in the middle of block
TEST_F(VersionTreapTest, version_insert_in_the_middle2)
{
  v = new VersionList();
  t = new VersionTreap<int>(v);
  // for version 1
  v->insert(0);

  // for v2
  v->insert(1); 
  t->version_insert(2, 2);

  // for v3
  v->insert(2); 

  // for v4
  v->insert(1); 
  //t->print();
  
  // for v5
  v->insert(4); 

  // for v6
  v->insert(2); 

  // for v7
  v->insert(1); 

  // for v8
  v->insert(1); 
  t->version_insert(8, 8);
  
  // for v9
  v->insert(8); 
  t->version_insert(9, 9);
  
  // for v10
  v->insert(8); 
  // for v11
  v->insert(8); 
  // for v12
  v->insert(10); 
  // for v13
  v->insert(10); 
  // for v14
  v->insert(10); 
  
  // for v15
  v->insert(2); 
  t->version_insert(15, 15);

  v->print();
  t->print();
  // TR: (0,0) (8,8) (9,9) (7, 0) (2, 2) (15,15)
  vector<int> vv_ideal;
  vv_ideal.push_back(1);
  vv_ideal.push_back(8);
  vv_ideal.push_back(11);
  vv_ideal.push_back(10);
  vv_ideal.push_back(14);
  vv_ideal.push_back(13);
  vv_ideal.push_back(12);
  vv_ideal.push_back(9);
  vv_ideal.push_back(7);
  vv_ideal.push_back(4);
  vv_ideal.push_back(5);
  vv_ideal.push_back(2);
  vv_ideal.push_back(15);
  vv_ideal.push_back(6);
  vv_ideal.push_back(3);
  vector<int> vv = v->getVersionVector();
  ASSERT_TRUE(vv.size() == vv_ideal.size());
  for(int i = 0; i < vv_ideal.size(); i++) {
    ASSERT_TRUE(vv[i] == vv_ideal[i]);
  }
  vector<int> keys = t->getKeys();
  vector<int> ideal_keys;
  ideal_keys.push_back(0);
  ideal_keys.push_back(8);
  ideal_keys.push_back(9);
  ideal_keys.push_back(7);
  ideal_keys.push_back(2);
  ideal_keys.push_back(15);
  ideal_keys.push_back(6);
  ASSERT_TRUE(keys.size() == ideal_keys.size());
  for(int i = 0; i < ideal_keys.size(); i++) {
    ASSERT_TRUE(keys[i] == ideal_keys[i]);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
  return 0;
}
