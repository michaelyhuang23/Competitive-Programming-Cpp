#include<iostream>
#include<assert.h>
#include<vector>
#include<tuple>
#include<algorithm>
#include<fstream>

//#include"debughelp.hpp" 
//#warning "remove debug lines"

using namespace std;

#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define mt make_tuple


struct SegTree
{ // very error prone
	static int pow_up(int num){
		for(int i=0;i<65;i++) if(1<<i >= num) return 1<<i;
		return -1;
	}
	int* tree = nullptr;
	int* pd = nullptr;
	int n;
	SegTree(int size){ 
		n = pow_up(size);
		tree = new int[n*2];
		pd = new int[n*2];
		fill(pd,pd+n*2,0);
		fill(tree,tree+n*2,0);
		build();
	}
	inline void build(){
		for(int i = n-1; i>=1; i--) tree[i] = max(tree[i<<1],tree[i<<1|1]);
	}
	inline void update(int idx, int ts, int te, int left, int right, int val){
		//cout<<"call update: "<<idx<<" "<<ts<<" "<<te<<" "<<left<<" "<<right<<" "<<val<<endl; 
		if(left>right) return;
		if(ts == left && te == right){ 
			tree[idx]=max(tree[idx],val);/*only for sum*/ 
			pd[idx]=max(pd[idx],val);
			return;
		}
		push_down(idx, ts, te); //update to most current for backtrace reupdate
		int tm = (ts+te)>>1;
		if(left<=tm)
			update(idx<<1,ts,tm,left,min(right,tm),val);
		if(right>tm)
			update(idx<<1|1,tm+1,te,max(tm+1,left),right,val);
		// reupdate values upstream
		tree[idx] = max(tree[idx<<1], tree[idx<<1|1]);
	}
	inline void update(int left, int right, int val){ update(1,0,n-1,left,right,val); }
	inline void push_down(int idx, int ts, int te){
		if(idx>=n || pd[idx]==0) return;
		int tm = (ts+te)>>1;
		tree[idx<<1] = max(tree[idx<<1],pd[idx]);
		tree[idx<<1|1] = max(tree[idx<<1|1],pd[idx]);
		pd[idx<<1] = max(pd[idx<<1], pd[idx]);
		pd[idx<<1|1] = max(pd[idx<<1|1], pd[idx]);
		pd[idx] = 0;
	}
	inline int query(int idx, int ts, int te, int left, int right){
		// both inclusive; ts, te indicate the coverage of this index
		if(left>right) return 0;
		push_down(idx,ts,te);
		if(ts == left && te == right) return tree[idx];
		int tm = (ts+te)>>1;
		int maxx = 0;
		if(left<=tm)
			maxx=max(maxx,query(idx<<1,ts,tm,left,min(right,tm)));
		if(right>tm)
			maxx=max(maxx,query(idx<<1|1,tm+1,te,max(tm+1,left),right));
		return maxx;
	}
	inline int query(int left, int right){ return query(1,0,n-1,left,right); }
};

int N, M;
int S[300][300][300];
int dp[300][300];
vector<vector<pair<int,int> > > ptrs;
vector<pair<int,int> > ranges;
vector<int> weights;


void solve(){
	ifstream fin("pieaters.in");
	ofstream fout("pieaters.out");
	ios_base::sync_with_stdio(0);
	fin.tie(0);
	fin >> N >> M;
	ptrs = vector<vector<pair<int,int> > >(N);
	ranges = vector<pair<int,int> >(M);
	weights = vector<int>(M);
	for(int i=0;i<M;i++){
		int w, l, r; fin >> w >> l >> r;
		l--;r--;
		if(l==r){
			ptrs[l].pb(mp(l,w));
		}else{
			ptrs[l].pb(mp(r,w));
			ptrs[r].pb(mp(l,w));
		}
		ranges[i] = mp(l,r);
		weights[i] = w;
	}

	//deb(ptrs)
	for(int i=0;i<300;i++) for(int j=0;j<300;j++) fill(S[i][j], S[i][j]+300, 0);
	for(int l=0;l<N;l++){
		SegTree tracker(N+5);
		for(int r=l;r<N;r++){
			for(auto& ptr : ptrs[r]){
				if(ptr.first > r) continue;
				if(ptr.first>=l){
					//deb("update") deb(mt(ptr.first, r, ptr.second))
					tracker.update(ptr.first, r, ptr.second);
				}
			}
			for(int a=l;a<=r;a++){
				// if(l==0 && r==1 && a==1){
				// 	deb(mt(l,r,a))
				// 	deb(tracker.query(a,a))
				// }
				S[l][r][a] = tracker.query(a, a);
			}
		}
	}

	//deb(S[0][1][1])

	for(int i=0;i<300;i++) fill(dp[i], dp[i]+300, 0);
	for(int i=0;i<M;i++) dp[ranges[i].first][ranges[i].second]=weights[i];
	for(int r=1;r<=N;r++){
		for(int s=0;s+r-1<N;s++){
			int e = s+r-1;
			for(int a=s;a<=e;a++){
				int left=0, right=0;
				if(s<=a-1) left = dp[s][a-1];
				if(e>=a+1) right = dp[a+1][e];
				int val = S[s][e][a] + left + right;
				dp[s][e] = max(dp[s][e], val);
			}
		}
	}

	fout<<dp[0][N-1]<<endl;
	fout.close();
}

int main(){
	solve();
}


