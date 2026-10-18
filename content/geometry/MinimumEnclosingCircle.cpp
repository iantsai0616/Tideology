/**
 * Description: Randomized incremental algorithm for the minimum enclosing circle of a
 * non-empty point set. Requires a circumcenter routine for three boundary points.
 * Time: O(N) expected
 */
pair<pdd, ld> circumcenter(pdd A, pdd B, pdd C){
	pdd b = C - A, c = B - A, o = A + perp(b * abs2(c) - c * abs2(b)) / cross(b, c) / 2;
	return {o, abs(o - A)};
}
pair<pdd, ld> MinimumEnclosingCircle(vector<pdd> &pts){
	shuffle(all(pts), mt19937(1));
	pdd c = pts[0];
	ld r = 0;
	for(int i = 1; i < sz(pts); i++){
		if(abs(pts[i] - c) <= r) continue;
		c = pts[i]; r = 0;
		for(int j = 0; j < i; j++){
			if(abs(pts[j] - c) <= r) continue;
			c = (pts[i] + pts[j]) / 2;
			r = abs(pts[i] - c);
			for(int k = 0; k < j; k++){
				if(abs(pts[k] - c) > r)
					tie(c, r) = circumcenter(pts[i], pts[j], pts[k]);
			}
		}
	}
	return {c, r};
}
