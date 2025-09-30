#include "../tree.h"

int
main()
{
  insertNode(root, "c");
  insertNode(root, "b");
  insertNode(root, "a");
  insertNode(root, "e");
  insertNode(root, "d");
  insertNode(root, "i");
  insertNode(root, "f");
  insertNode(root, "h");
  insertNode(root, "g");


  printBT("", root, false);

  return 0;
}
