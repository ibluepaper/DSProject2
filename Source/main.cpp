#include "b_tree_class.h"

int main(){
  BTree *bt = new BTree(3);
  bt->insert(11);
  bt->insert(21);
  bt->insert(31);
  bt->insert(61);
  bt->insert(51);
  bt->insert(41);
  bt->insert(71);
  bt->insert(91);
  bt->insert(81);

  BTreeNode *root = bt->getRoot();

  cout << root->getChilds(0)->getKeys(0);

}
