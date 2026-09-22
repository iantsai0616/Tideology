/**
 * Description: Given a predicate over adjacent values of a cyclically shifted unimodal
 * sequence, returns an index for which pred(x, index) is false for every x.
 * Time: O(\log N)
 */
int cyc_tsearch(int n, auto pred) {
  if (n == 1) return 0;
  int l = 0, r = n; bool rv = pred(1, 0);
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (pred(0, m) ? rv: pred(m, (m + 1) % n)) r = m;
    else l = m;
  }
  return pred(l, r % n) ? l : r % n;
}
