/**
 * Description: Returns the zero, one, or two intersection points between a circle and
 * the infinite line through points a and b.
 * Time: O(1)
 */
vector<pdd> circleLineIntersection(pdd c, double r, pdd a, pdd b) {
  pdd p = a + (b - a) * dot(c - a, b - a) / abs2(b - a);
  double s = cross(b - a, c - a), h2 = r * r - s * s / abs2(b - a);
  if (sgn(h2) < 0) return {};
  if (sgn(h2) == 0) return {p};
  pdd h = (b - a) / abs(b - a) * sqrt(h2);
  return {p - h, p + h};
}
