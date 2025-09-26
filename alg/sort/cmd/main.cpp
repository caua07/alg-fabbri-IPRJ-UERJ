// main.cpp in cmd/
#include <iostream>
#include <vector>
#include <algorithm>
#include "sort_char.h"

int
main()
{
  std::vector<char> chars;
  char c;
  while (std::cin.get(c)) {
    if (c != '\n' && c != ' ') { // ignore newlines and spaces
      chars.push_back(c);
    }
  }

  if (chars.empty()) {
    return 0;
  }

  sort_char_array(chars.data(), chars.size());

  for (int i = 0; i < chars.size(); ++i) {
    std::cout << chars[i] << (i == chars.size() - 1 ? "" : " ");
  }
  std::cout << std::endl;

  return 0;
}
