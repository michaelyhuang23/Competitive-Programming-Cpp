#include<iostream>
#include<algorithm>
#include<assert.h>
#include<fstream>
#include<vector>
#include<tuple>
#include<set>

// #include "debughelp.hpp"
// #warning "remove debug lines"

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple


struct SegTree
{
	static llong pow_up(int num){
		for(int i=0;i<65;i++) if(1<<i >= num) return 1<<i;
		return -1;
	}
	vector<llong> tree;
	vector<llong> pd;
	int n;
	SegTree(int size){
		n = pow_up(size);
		tree = vector<llong>(n*2,0);
		pd = vector<llong>(n*2,0);
		build();
	}
	inline void build(){
		for(int i = n-1; i>=1; i--) tree[i] = tree[i<<1] + tree[i<<1|1];
	}
	inline void update(int idx, int ts, int te, int left, int right, int val){
		//cout<<"call update: "<<idx<<" "<<ts<<" "<<te<<" "<<left<<" "<<right<<" "<<val<<endl; 
		if(left>right) return;
		if(ts == left && te == right){ tree[idx]+=val*(te-ts+1);/*only for sum*/ pd[idx]+=val; return;}
		push_down(idx, ts, te); //update to most current for backtrace reupdate
		int tm = (ts+te)>>1;
		if(left<=tm)
			update(idx<<1,ts,tm,left,min(right,tm),val);
		if(right>tm)
			update(idx<<1|1,tm+1,te,max(tm+1,left),right,val);
		// reupdate values upstream
		tree[idx] = tree[idx<<1] + tree[idx<<1|1];
	}
	inline void update(int left, int right, int val){ update(1,0,n-1,left,right,val); }
	inline void push_down(int idx, int ts, int te){
		if(idx>=n || pd[idx]==0) return;
		int tm = (ts+te)>>1;
		tree[idx<<1] += pd[idx]*(tm-ts+1);
		tree[idx<<1|1] += pd[idx]*(te-tm);
		pd[idx<<1] += pd[idx];
		pd[idx<<1|1] += pd[idx];
		pd[idx] = 0;
	}
	inline llong query(int idx, int ts, int te, int left, int right){
		// both inclusive; ts, te indicate the coverage of this index
		if(left>right) return 0;
		push_down(idx,ts,te);
		if(ts == left && te == right) return tree[idx];
		int tm = (ts+te)>>1;
		llong sum = 0;
		if(left<=tm)
			sum+=query(idx<<1,ts,tm,left,min(right,tm));
		if(right>tm)
			sum+=query(idx<<1|1,tm+1,te,max(tm+1,left),right);
		return sum;
	}
	inline llong query(int left, int right){ return query(1,0,n-1,left,right); }
};

int N, Q;
vector<vector<int> > adj;
vector<int> sz;
vector<int> in, out;
int t=0;

void compute_order(int cur, int father){
	in[cur] = t++;
	for(int son : adj[cur]){
		if(father==son) continue;
		compute_order(son, cur);
	}
	out[cur] = t++;
}

struct Loca{
	int idx;
	int in, out;
	Loca(int idx_, int in_, int out_){
		idx = idx_; in = in_; out = out_;
	}
	const bool operator < ( const Loca &rhs ) const{
        return in < rhs.in;
    }
};

ostream& operator << ( ostream& os, const Loca& p ) {
    return os << "(" << p.idx << ": " << p.in<<", "<<p.out << ")";
}

int main(){
	ifstream fin("snowcow.in");
	ofstream fout("snowcow.out");
	ios_base::sync_with_stdio(0);
	fin.tie(0);
	fin >> N >> Q;
	t = 0;
	adj = vector<vector<int> >(N);
	for(int i=0;i<N-1;i++){
		int a, b; fin >> a >> b;
		a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	in = vector<int>(N);
	out = vector<int>(N);
	compute_order(0, 0);

	//deb(in) deb(out)

	vector<set<Loca> > topLoc(100000+5);
	SegTree cp(t+5);
	for(int i=0;i<Q;i++){
		int type; fin >> type;
		if(type==1) { // update
			//deb(topLoc[1])
			int idx, c;
			fin >> idx >> c; idx--;
			Loca cloc(idx,in[idx],out[idx]);
			auto ret = topLoc[c].upper_bound(cloc); 
			// first smaller than it. this could include it if anything
			// handle doens't exist case!
			if(ret!=topLoc[c].begin()){
				ret--;
				Loca ploc = *ret;
				if(ploc.out >= out[idx]) continue;
			}
			// not included must add
            //deb(mt(in[idx],out[idx],1))
			cp.update(in[idx], out[idx], 1);
			auto ret2 = topLoc[c].lower_bound(cloc); // there can be multiple
			auto ret3 = ret2;
			for(ret3 = ret2; ret3!=topLoc[c].end(); ret3++){
				Loca sloc = *ret3;
				if(sloc.out <= out[idx]) { // obscured
					//deb(mt(sloc.in,sloc.out,-1))
					cp.update(sloc.in, sloc.out, -1);
				}else break;
			}
			topLoc[c].erase(ret2, ret3);
			topLoc[c].insert(cloc);
			//deb(topLoc[1])
		}else{ // query
			int idx;
			fin >> idx; idx--;
            //deb("query")
            //deb(mp(in[idx],out[idx]))
			llong sc = cp.query(in[idx], out[idx]); // everyone is counted twice
			fout<<sc/2<<endl;
		}
	}
	fout.close();
}







