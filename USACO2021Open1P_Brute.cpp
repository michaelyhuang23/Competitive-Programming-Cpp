#include<bits/stdc++.h>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define print(x) cout<<x<<endl

struct segtree{
	vector<bool> active;
	vector<llong> uniques;
	vector<llong> sum;
	int n;
	segtree(int n_){
		n = n_;
		active = vector<bool>(n,0);
		uniques = vector<llong>(n,0);
		sum = vector<llong>(n,0);

	}
	llong query(int l, int r){
		llong tt = 0;
		for(int i=l;i<=r;i++) tt+=sum[i];
		return tt;
	}
	void increment(int l, int r, llong val){
		for(int i=l;i<=r;i++){uniques[i]+=val; upd(i);}
	}
	void activate(int l, int r, bool state){
		active[l] = state;
		upd(l);
	}
	void upd(int i){
		sum[i] = uniques[i]*active[i];
	}
};

int N;
vector<int> arr,p;
void solve(){
	segtree tracker(N);
	llong total = 0;
	if(arr[0] == arr[1]){
		tracker.activate(1, 1, true);
		tracker.increment(0, 0, 1);
	}else{
		tracker.activate(1, 1, true);
		tracker.activate(0, 0, true);
		tracker.increment(0, 0, 1);
	}
	for(int r=2;r<N;r++){
		// let a[l] denote whether l is the rightmost of its breed
		// let unique[l] denote the number of unique cows in the range (l, r-1]
		// clearly a[l]*unique[l] from l = p[r]+1 to l = r-2 gives the contribution of r 
		// so we need to support updates:
		// deactivate and activate a at points
		// unique[l] with l>=p[r] will +1
		// unique[l] with l<p[r] will -1
		int pr = p[r];
		//if(pr==-1) pr = -1;
		llong tt = tracker.query(pr+1,r-2); // potential lefts
		total += tt;
		//deb(mp(r,tt))
		tracker.increment(max(0,pr), r-1, 1);
		if(pr-1>=0) tracker.increment(max(0,p[pr]), pr-1, -1);
		if(pr >= 0) tracker.activate(pr, pr, false);
		tracker.activate(r, r, true);
	}

	print(total);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	arr = vector<int>(N);
	p = vector<int>(N);
	for(int i=0;i<N;i++) cin >> arr[i];
	vector<int> lp(N+5, -1);
	for(int i=0;i<N;i++){
		p[i] = lp[arr[i]];
		lp[arr[i]] = i;
	}
	solve();
}


