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
  int indA = 0, indB = 0, indC = 0;
  int resultLen = na + nb + nc;

  for (int i = 0; i < resultLen; i++) {
    int a = (indA < na) ? list_a[indA] : INT_MAX;
    int b = (indB < nb) ? list_b[indB] : INT_MAX;
    int c = (indC < nc) ? list_c[indC] : INT_MAX;

    int minVal = std::min(a, std::min(b, c));
    list_abc[i] = minVal;

    if (minVal == a) {
      indA++;
    } else if (minVal == b) {
      indB++;
    } else {
      indC++;
    }
  }

  for(int j = 1; j< resultLen; j++){
    if(list_abc[j] < list_abc[j-1]){
      return false;
    }
  }

  return true;
}
