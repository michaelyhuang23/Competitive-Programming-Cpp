#include<bits/stdc++.h>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define print(x) cout<<x<<endl

struct segtree{
	vector<int> active;
	vector<llong> uniques;
	vector<llong> sum;
	vector<int> pd;
	int n; 
	int pow_up(int num){
		for(int i=0;i<32;i++) if((1<<i) >= num) return 1<<i;
		return -1;
	}
	segtree(int n_){
		n = pow_up(n_);
		active = vector<int>(n*2,0);
		fill(active.begin(), active.begin()+n, 0);
		uniques = vector<llong>(n*2,0);
		sum = vector<llong>(n*2,0);
		pd = vector<int>(n*2,0);
		build();
	}
	void pull_up(int idx){
		uniques[idx] = uniques[idx*2]+uniques[idx*2+1];
		sum[idx] = sum[idx*2]+sum[idx*2+1];
		active[idx] = active[idx*2]+active[idx*2+1];
	}
	void upd(int idx){
		if(idx>=n)
			sum[idx] = uniques[idx]*(active[idx]>0);
	}
	void build(){
		for(int i=n-1;i>=1;i--) pull_up(i);
	}
	void activate(int idx, int ts, int te, int ll, int rr, bool state){
		if(ll>rr) return;
		if(ts == ll && te == rr){ active[idx]=state; upd(idx); return;}
		push_down(idx, ts, te);
		int tm = (ts+te)/2;
		if(ll<=tm)
			activate(idx*2,ts,tm,ll,min(rr,tm),state);
		if(rr>tm)
			activate(idx*2+1,tm+1,te,max(tm+1,ll),rr,state);
		pull_up(idx);
	}
	void activate(int ll, int rr, bool state){ return activate(1,0,n-1,ll,rr,state);}
	void increment(int idx, int ts, int te, int ll, int rr, int val){
		if(ll>rr) return;
		if(ts == ll && te == rr){ uniques[idx]+=val*(te-ts+1); sum[idx]+=val*active[idx]; upd(idx); pd[idx]+=val; return;}
		push_down(idx, ts, te);
		int tm = (ts+te)/2;
		if(ll<=tm)
			increment(idx*2,ts,tm,ll,min(rr,tm),val);
		if(rr>tm)
			increment(idx*2+1,tm+1,te,max(tm+1,ll),rr,val);
		// reupdate values upstream
		pull_up(idx);
	}
	void increment(int ll, int rr, int val){ increment(1,0,n-1,ll,rr,val); }
	void push_down(int idx, int ts, int te){
		if(idx>=n || pd[idx]==0) return;
		int tm = (ts+te)/2;
		uniques[idx*2] += pd[idx]*(tm-ts+1); // this is plain wrong
		uniques[idx*2+1] += pd[idx]*(te-tm); // we need to track how many active there is in the interval. 
		sum[idx*2] += pd[idx]*active[idx*2];
		sum[idx*2+1] += pd[idx]*active[idx*2+1];
		upd(idx*2); upd(idx*2+1);
		pd[idx*2] += pd[idx];
		pd[idx*2+1] += pd[idx];
		pd[idx] = 0;
	}
	llong query(int idx, int ts, int te, int ll, int rr){
		if(ll>rr) return 0;
		push_down(idx,ts,te);
		if(ts == ll && te == rr) return sum[idx];
		int tm = (ts+te)/2;
		llong ss = 0;
		if(ll<=tm)
			ss+=query(idx*2,ts,tm,ll,min(rr,tm));
		if(rr>tm)
			ss+=query(idx*2+1,tm+1,te,max(tm+1,ll),rr);
		pull_up(idx);
		return ss;
	}
	llong query(int ll, int rr){ return query(1,0,n-1,ll,rr); }
};

int N;
vector<int> arr,p;
void solve(){
	segtree tracker(N);
	llong total = 0, total2 = 0;
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
		if(pr==-1) pr = -1;
		llong tt = tracker.query(pr+1,r-2);
		total += tt;

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
	vector<int> lp(N+1, -1);
	for(int i=0;i<N;i++){
		p[i] = lp[arr[i]];
		lp[arr[i]] = i;
	}
	solve();
}


