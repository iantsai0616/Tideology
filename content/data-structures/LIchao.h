const int mxn = 2e5 + 5, inf = 8e18;
//remember to choose flg, discrete
struct line{
        int m, c;
        int operator()(int x){
            return m * x + c;
        }
};
struct lichao{
    line seg[4 * mxn];
    vector<int>tmp;
    int flg;//1 for min, -1 for max
    int get(int x){
        return lower_bound(all(tmp), x) - tmp.begin();
    }
    void build(int l, int r, int id){
        seg[id] = {0, flg * inf};
        if(l == r) return;
        int mm = l + r >> 1;
        build(l, mm, id * 2);
        build(mm + 1, r, id * 2 + 1);
    }
    bool cmp(line a, line b, int x){
        if(flg == 1) return a(tmp[x]) <= b(tmp[x]);
        else return a(tmp[x]) >= b(tmp[x]);
    }
    int merge(int x, int y){
        if(flg == 1) return min(x, y);
        else return max(x, y);
    }
    void m(int l, int r, int id, line x){
        if(l == r){
            if(cmp(x, seg[id], l)) seg[id] = x;
            return;
        }
        int mm = l + r >> 1;
        if(seg[id].m < x.m){
            swap(seg[id], x);
        }
        if(cmp(x, seg[id], mm)){
            swap(seg[id], x);
            if(flg == 1) m(l, mm, id * 2, x);
            else m(mm + 1, r, id * 2 + 1, x);
        }
        else{  
            if(flg == 1) m(mm + 1, r, id * 2 + 1, x);
            else m(l, mm, id * 2, x);
        }
    }
    void ins(int l, int r, int id, int ql, int qr, line x){
        if(qr < l or r < ql) return;
        if(ql <= l and r <= qr){
            m(l, r, id, x);
            return;
        }
        int mm = l + r >> 1;
        ins(l, mm, id * 2, ql, qr, x);
        ins(mm + 1, r, id * 2 + 1, ql, qr, x);
    }
    int q(int l, int r, int id, int p){
        if(l == r) return seg[id](tmp[p]);
        int mm = l + r >> 1;
        if(p <= mm) return merge(seg[id](tmp[p]), q(l, mm, id * 2, p));
        else return merge(seg[id](tmp[p]), q(mm + 1, r, id * 2 + 1, p));
    }
};