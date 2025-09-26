/* cauaeyer 2025-09-12 */

#include "sort_char.h"
#include <iostream>
#include <cstring>

void
sort_char_array(char* arr, int n)
{
  int count[256] = {0};
  int i;

  for (i = 0; i < n; i++)
    count[(unsigned char)arr[i]]++;

  int output_index = 0;
  for (i = 0; i < 256; i++)
    while (count[i]-- > 0)
      arr[output_index++] = (char)i;
}
