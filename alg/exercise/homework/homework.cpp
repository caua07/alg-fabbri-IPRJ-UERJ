#include "homework.h" 
#include <iostream>

int
main()
{
  SinglyLinked l1;

  l1.insert(0,"hello");
  l1.insert(1,"new");
  l1.insert(2,"world");
  l1.print();

  return 0;
}
