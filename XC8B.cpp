// #include "debughelp.hpp"

#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define inf 1000000000
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl

struct BITCHMAX{
	vector<llong> bits;
	int n;
	BITCHMAX(){}
	BITCHMAX(int n_){
		n = n_+3;
		bits = vector<llong>(n,-inf);
	}
	void rebuild(){ fill(bits.begin(), bits.end(), -inf); }
	int lowbit(int x){return x&(-x);}
	llong query(int x){
		llong maxx = -inf;
		x = n - x - 1;
		for(;x>0;x-=lowbit(x)) maxx = max(maxx, bits[x]);
		return maxx;
	}
	void update(int x, llong val){
		x = n - x - 1;
		for(;x<n;x+=lowbit(x)) bits[x] = max(bits[x], val);
	}
};
struct BITCHMIN{
	vector<llong> bits;
	int n;
	BITCHMIN(){}
	BITCHMIN(int n_){
		n = n_+3;
		bits = vector<llong>(n,inf);
	}
	void rebuild(){ fill(bits.begin(), bits.end(), inf); }
	int lowbit(int x){return x&(-x);}
	llong query(int x){
		llong minn = inf;
		x = n - x - 1;
		for(;x>0;x-=lowbit(x)) minn = min(minn, bits[x]);
		return minn;
	}
	void update(int x, llong val){
		x = n - x - 1;
		for(;x<n;x+=lowbit(x)) bits[x] = min(bits[x], val);
	}
};

struct segtreeMIN{
	static llong pow_up(llong num){
		for(llong i=0;i<32;i++) if(1<<i >= num) return 1<<i;
		return -1;
	}
	vector<llong> tree;
	llong n;
	segtreeMIN(llong size){
		n = pow_up(size);
		tree = vector<llong>(n*2,inf);
		build();
	}
	void build(){
		for(llong i = n-1; i>=1; i--) tree[i] = min(tree[i<<1], tree[i<<1|1]);
	}
	void rebuild(){
		fill(tree.begin()+n, tree.end(), inf);
		build();
	}
	void update(llong idx, llong val){
		tree[n+idx] = val;
		for(llong i = (n+idx)>>1; i >= 1; i>>=1) tree[i]=min(tree[i<<1], tree[i<<1|1]);
	}
	llong query(llong left, llong right = inf){
		// both inclusive
		llong ll=inf, rr=inf;
		if(right == inf) right = n-1;
		left+=n, right+=n;
		for(;left<=right;left>>=1,right>>=1){
			if(left&1) ll=min(ll,tree[left++]);
			if(!(right&1)) rr=min(tree[right--],rr);
			if(left==right) break; 
		}
		//end condition is correct because only 1 of these 2 can be true then
		return min(ll,rr);
	}
};

BITCHMIN tracker1; // initialized to inf
BITCHMAX tracker2; // initialized to -inf

vector<llong> dpL, dpR;
vector<int> idds;
vector<llong> P2id;
vector<llong> id2val;
llong n,k,m;
vector<llong> P;

bool check(llong D){
	// compute L
	tracker1.rebuild(); // initialized to -inf

	dpL[0] = 0;
	tracker1.update(P2id[0],0);

	for(int i=1;i<=n;i++){
		auto it = lower_bound(id2val.begin(), id2val.end(), P[i]-D);
		idds[i] = distance(id2val.begin(), it);
	}

	for(llong i=1;i<=n;i++){
		dpL[i] = tracker1.query(idds[i]) + 1;
		tracker1.update(P2id[i], dpL[i]); // requires chmin
	} // looks like a bit could work too?

	llong L = dpL[n];


	// compute R
	tracker2.rebuild();

	dpR[0] = 0;
	tracker2.update(P2id[0],0);

	for(llong i=1;i<=n;i++){
		dpR[i] = tracker2.query(idds[i]) + 1;
		tracker2.update(P2id[i], dpR[i]); // requires chmax;
	}

	llong R = dpR[n];

	bool suc = (L<=k) && (k<=R);
	if(!suc) return false;

	return true;
}

void solve(){
	n,k; cin >> n >> k;

	llong BOT = 0, TOP = 0;

	vector<llong> A(n+1,0);
	for(llong i=1;i<=n;i++) cin >> A[n-i+1];
	P = vector<llong>(n+1,0);
	for(llong i=1;i<=n;i++) {
		P[i] = P[i-1] + A[i];
		BOT = min(BOT, P[i]-1);
		TOP = max(TOP, P[i]+1);
	}

	llong RR = TOP-BOT;
	llong LL = BOT-TOP;

	set<llong> PV(P.begin(), P.end());
	id2val = vector<llong>(PV.begin(), PV.end());

	m = id2val.size(); // pseudo discretized range

	unordered_map<llong,llong> val2id;
	
	for(llong i=0;i<m;i++) val2id[id2val[i]] = i;

	tracker1 = BITCHMIN(m+1); // initialized to inf
	tracker2 = BITCHMAX(m+1); // initialized to -inf
	
	P2id = vector<llong>(n+1,0);
	for(int i=0;i<=n;i++){
		P2id[i] = val2id[P[i]];
	}

	dpL = vector<llong>(n+1, inf);
	dpR = vector<llong>(n+1, inf);
	idds = vector<int>(n+1);


	//print(LL);
	//print(RR);
	llong ans = 0; // turn everything into llong
	int cc = 0;
	while(LL<=RR){
		llong mid = (LL+RR)/2;
		cc++;
		if(check(mid)) { ans = mid; RR = mid-1; }
		else LL = mid+1;
	}

	//print(ans);
	//print(cc);
	check(ans);


	deque<tuple<llong,llong,bool>> ptrs;
	for(llong i = 1; i<=n; i++){
		if(dpL[i] <= dpR[i]){
			// deb(mt(i, dpL[i], dpR[i]))
			ptrs.push_back(mt(dpL[i]-1,i,false));
			ptrs.push_back(mt(dpR[i],i,true)); // so it's (l,r]
		}
	}


	vector<set<llong>> pval(m+1);
	segtreeMIN tracker(m+1);

	sort(ptrs.rbegin(), ptrs.rend());
	vector<tuple<llong,llong,bool>> ret(ptrs.begin(), ptrs.end());
	for(llong i=n;i>=k;i--){
		while(!ptrs.empty() && get<0>(ptrs.front()) == i){
			llong id = get<1>(ptrs.front());
			if(get<2>(ptrs.front())){ // is R
				llong x = val2id[P[id]];
				// deb(val2id[P[5]])
				if(pval[x].empty() || (*pval[x].begin()>id)){
					// deb(mp(x,id))
					tracker.update(x,id);
				}
				pval[x].insert(id);
			}else{ // is L
				llong x = val2id[P[id]];
				pval[x].erase(id);
				if(pval[x].empty()){
					tracker.update(x,inf);
				} else if(*pval[x].begin()>id){
					// deb(mp(x,*pval[x].begin()))
					tracker.update(x,*pval[x].begin());
				}
			}
			ptrs.pop_front();
		}
	}

	llong cur_i = n;
	stack<llong> cuts; cuts.push(cur_i);
	for(llong i=k-1;i>=1;i--){
		// deb(i)
		// first deail with ptrs
		while(!ptrs.empty() && get<0>(ptrs.front()) == i){
			llong id = get<1>(ptrs.front());
			if(get<2>(ptrs.front())){ // is R
				llong x = val2id[P[id]];
				if(pval[x].empty() || (*pval[x].begin()>id)){
					// deb(mp(x,id))
					tracker.update(x,id);
				}
				pval[x].insert(id);
			}else{ // is L
				llong x = val2id[P[id]];
				pval[x].erase(id);
				if(pval[x].empty()){
					tracker.update(x,inf);
				} else if(*pval[x].begin()>id){
					//deb(mp(x,*pval[x].begin()))
					tracker.update(x,*pval[x].begin());
				}
			}
			ptrs.pop_front();
		}
		// now query
		// deb(cur_i)
		llong x = P[cur_i] - ans;
		// deb(x)
		auto it = lower_bound(id2val.begin(), id2val.end(), x);
		// deb(id2val)
		llong xi = distance(id2val.begin(), it);
		// deb(xi)
		// for(llong j=0;j<=m;j++) cout<<tracker.query(j,j)<<" ";
		// cout<<endl;
		llong nxt_i = tracker.query(xi);
		//deb(nxt_i)
		cur_i = nxt_i;
		cuts.push(cur_i);

		//deb(cuts.size())
	}

	assert(cuts.size() == k);

	vector<llong> len;
	llong cz = 0;
	while(!cuts.empty()){
		len.push_back(cuts.top() - cz);
		cz = cuts.top();
		cuts.pop();
	} 
	assert(len.size() == k);
	for(llong i=k-1;i>=1;i--) cout<<len[i]<<" ";
	cout<<len[0]<<endl; 

}












int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong tt; cin >> tt;
	while(tt--)
		solve();
}