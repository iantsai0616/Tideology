/**
 * Description: Computes the indices of the strict convex hull of a set of 2D points.
 * Collinear points on hull edges are discarded.
 * Time: O(N \log N)
 */
vector<int> getConvexHull(vector<pdd>& pts){
	vector<int> id(sz(pts));
	iota(all(id), 0);
	sort(all(id), [&](int x, int y){ return pts[x] < pts[y]; });
	vector<int> hull;
	for(int tt = 0; tt < 2; tt++){
		int sz = sz(hull);
		for(int j : id){
			pdd p = pts[j];
			while(sz(hull) - sz >= 2 && ori(pts[hull.end()[-2]], pts[hull.back()], p) <= 0)
				hull.pop_back();
			hull.pb(j);
		}
		hull.pop_back();
		reverse(all(id));
	}
	return hull;
}
