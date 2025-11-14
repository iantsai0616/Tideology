/**
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: own work
 * Description: 
 * Time: O(\log N)
 * Status: stress-tested
 */
struct node{
    node *s[2],*fa;
    int val,siz,tag;
	//val is value, siz is xor of children vals, tag is lazy tag
};
struct LCT{
	node *null;
	node *pt[100010];
	LCT(){
	    null=new node;
	    null->val=null->siz=null->tag=0;
	    null->s[0]=null->s[1]=null->fa=null;
	}
	node *new_node(int x){
		node *p=new node;
		p->val=x,p->siz=p->tag=0;
		p->s[0]=p->s[1]=p->fa=null;
		return p;
	}
	bool qson(node *p){
		return p->fa->s[1]==p;
	}
	bool isroot(node *p){
		return (p->fa->s[0]!=p && p->fa->s[1]!=p);
	}
	void pushup(node *p){//update this real chain's p's children's values xor
		p->siz=p->val^p->s[0]->siz^p->s[1]->siz;
	}
	void pushdown(node *p){//push down rotate lazy tag
		if(!p->tag) return;
		if(p->s[0]!=null) swap(p->s[0]->s[0],p->s[0]->s[1]),p->s[0]->tag^=1;
		if(p->s[1]!=null) swap(p->s[1]->s[0],p->s[1]->s[1]),p->s[1]->tag^=1;
		p->tag=0;
	}
	void update(node *p){
		if(!isroot(p)) update(p->fa);
		pushdown(p);
	}
	void rorate(node *p){
    	node *fa=p->fa;
    	node *gf=fa->fa;
    	int k=qson(p);
    	if(!isroot(fa)) gf->s[qson(fa)]=p;
    	p->fa=gf;
    	fa->s[k]=p->s[k^1],p->s[k^1]->fa=fa;
    	p->s[k^1]=fa,fa->fa=p;
    	pushup(fa),pushup(p);
	}
	void splay(node *p){
		update(p);
	    while(!isroot(p)){
	        node *fa=p->fa;
	        node *gf=fa->fa;
	        if(!isroot(fa)){
	            if(qson(p)==qson(fa)) rorate(fa);
	            else rorate(p);
	        }
	        rorate(p);
	    }
	}
	void access(node *p){//turn p->root into real chain
		node *q=null;
		while(p!=null){
			splay(p);
			p->s[1]=q;
			pushup(p);
			q=p,p=p->fa;
		}
	}
	void beroot(node *p){//turn p into root
		access(p),splay(p);
		swap(p->s[0],p->s[1]);
		p->tag^=1;
	}
	node *find(node *p){//find top of real chain
		access(p),splay(p);
		while(p->s[0]!=null) p=p->s[0];
		splay(p);
		return p;
	}
	void belink(node *p,node *q){//let (p,q) with edge also have edge on auxillary tree
		beroot(p);
		access(q);
		splay(q);
	}
	void link(int a,int b){
		if(find(pt[a])!=find(pt[b]))
			beroot(pt[a]),pt[a]->fa=pt[b];
	}
	void cut(int a,int b){
		belink(pt[a],pt[b]);
		if(pt[b]->s[0]==pt[a])
			pt[b]->s[0]=pt[a]->fa=null;
	}
	int ask(int a,int b){
		belink(pt[a],pt[b]);
		return pt[b]->siz;
	}
	void update(int a,int b){
		splay(pt[a]);
		pt[a]->val=b;
		pushup(pt[a]);
	}
}