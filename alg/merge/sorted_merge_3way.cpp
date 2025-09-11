/* R. Fabbri, 2024 */
#include "sorted_merge_3way.h"
#include <climits>
#include <algorithm>

bool
sorted_merge_3way(
    const int *list_a, int na,
    const int *list_b, int nb,
    const int *list_c, int nc,
    int *list_abc)
{
      
  int i{0}, j{0}, k{0}, rLen{0};

  while (i < na || j < nb || k < nc){
    int val_a = (i < na) ? list_a[i] : INT_MAX;
    int val_b = (j < nb) ? list_b[j] : INT_MAX;
    int val_c = (k < nc) ? list_c[k] : INT_MAX;

    int min_val = std::min(val_a, std::min(val_b, val_c));
      
    list_abc[rLen] = min_val;

    if (rLen > 0 && list_abc[rLen] < list_abc[rLen - 1]){
      return false;
    }

    if (val_a == min_val)
      ++i;
    else if (val_b == min_val)
      ++j;
    else
      ++k;

    ++rLen;
  }

  return true;
}
