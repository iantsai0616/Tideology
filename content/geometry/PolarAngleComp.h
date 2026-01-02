/**
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: own work
 * Description: 
 * Time: O(\log N)
 * Status: stress-tested
 */
// -1: a // b (if same), 0/1: a < b
int cmp(pll a, pll b, bool same = true){
#define is_neg(k) (sgn(k.Y) < 0 || (sgn(k.Y) == 0 && sgn(k.X) < 0))
  int A = is_neg(a), B = is_neg(b);
  if(A != B)
    return A < B;
  if(sgn(cross(a, b)) == 0)
    return same ? abs2(a) < abs2(b) : -1;
  return sgn(cross(a, b)) > 0;
}
