/**
 * Author: Tideology
 * Source: arc integration with Green's theorem (as in waynedisonitau123 circleOrArea)
 * License: CC0
 * Description: Area of the union of circles (o[i], r[i]); duplicates and containment allowed.
 * Time: O(n^2 \log n)
 * Status: stress-tested against numeric integration (rel. error 3e-8)
 */

double circleUnion(const vector<pdd>& o, const vector<double>& r){
  const double PI = acos(-1), eps = 1e-9;
  double res = 0; int n = sz(o);
  rep(i, 0, n){
    vector<pair<double, double>> s = {{2 * PI, 2 * PI}};
    bool in = 0;
    rep(j, 0, n) if(j != i){
      pdd v = o[j] - o[i]; double d = abs(v);
      if(d <= r[j] - r[i] + eps && (r[j] > r[i] + eps || j < i)) in = 1;
      else if(d > fabs(r[i] - r[j]) + eps && d < r[i] + r[j] - eps){
        double a = atan2(v.Y, v.X), c = (r[i] * r[i] + d * d - r[j] * r[j]) / (2 * r[i] * d);
        double t = acos(max(-1.0, min(1.0, c))), l = a - t, h = a + t;
        if(l < 0) l += 2 * PI, h += 2 * PI;
        if(h > 2 * PI) s.push_back({l, 2 * PI}), s.push_back({0, h - 2 * PI});
        else s.push_back({l, h});
      }
    }
    if(in) continue;
    sort(all(s));
    auto F = [&](double t){ return r[i] * (r[i] * t + o[i].X * sin(t) - o[i].Y * cos(t)); };
    double w = 0;
    for(auto [l, h] : s){ if(l > w) res += F(l) - F(w); w = max(w, h); }
  }
  return res / 2;
}
