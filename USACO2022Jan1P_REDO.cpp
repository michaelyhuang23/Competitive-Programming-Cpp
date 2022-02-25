#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000LL
#define print(x) cout<<x<<endl

struct NodeP{
	llong val, ll, rr;
	llong minLoc;
	llong pd;
	NodeP(llong val_, llong idx) : val(val_), pd(0), ll(idx), rr(idx), minLoc(idx) {}
	NodeP() : val(inf), pd(0), ll(inf), rr(-inf), minLoc(inf) {}
	void pull_up(NodeP& left, NodeP& right){
		NodeP mid = merge(left, right);
		val = mid.val;
		ll = mid.ll;
		rr = mid.rr;
		pd = 0;
		minLoc = mid.minLoc;
	}
	static NodeP merge(NodeP& left, NodeP& right){
		NodeP ret; ret.ll = min(left.ll, right.ll); ret.rr = max(right.rr, left.rr);
		ret.val = min(left.val, right.val); // this is min so we know if interval contains 0
		ret.minLoc = inf;
        if(left.val == ret.val) ret.minLoc = min(ret.minLoc, left.minLoc);
        if(right.val == ret.val) ret.minLoc = min(ret.minLoc, right.minLoc);
		return ret;
	}
	void push_down(NodeP& left, NodeP& right){
		left.change(pd);
		right.change(pd);
		pd = 0;
	}
	void change(llong val_){
		val += val_;
		pd += val_;
	}
	llong ans(){ return minLoc; }
};

ostream& operator << ( ostream& os, const NodeP & p ) {
    return os << "(" << p.val << ", " << p.minLoc << ")";
}

struct SegTree
{
	static llong pow_up(llong num){
		for(llong i=0;i<65;i++) if(1<<i >= num) return 1<<i;
		return -1;
	}
	vector<NodeP> tree;
	llong n;
	SegTree(vector<llong>& arr,llong size){
		n = pow_up(size);
		tree = vector<NodeP>(n*2);
		for(llong i=0;i<n;i++) {
			if(i<size)
				tree[n+i] = NodeP(arr[i],i);
			else 
				tree[n+i] = NodeP(inf, i);
		}
		build();
	}
	inline void build(){
		for(llong i = n-1; i>=1; i--) tree[i].pull_up(tree[i<<1], tree[i<<1|1]);
	}
	inline void update(llong idx, llong ts, llong te, llong left, llong right, llong val){
		if(left>right) return;
		if(ts == left && te == right){
			//if(ts != te) tree[idx].push_down(tree[idx<<1], tree[idx<<1|1]);
            tree[idx].change(val);
            //tree[idx].push_down(tree[idx<<1], tree[idx<<1|1]);
            return;
        }
		tree[idx].push_down(tree[idx<<1], tree[idx<<1|1]);
		llong tm = (ts+te)>>1;
		if(left<=tm)
			update(idx<<1,ts,tm,left,min(right,tm),val);
		if(right>tm)
			update(idx<<1|1,tm+1,te,max(tm+1,left),right,val);
		tree[idx].pull_up(tree[idx*2], tree[idx*2+1]);

	}
	inline void update(llong left, llong right, llong val){ update(1,0,n-1,left,right,val); }
	inline NodeP query(llong idx){
		return tree[idx];
	}
	inline llong query(){ return query(1).ans(); }
};

struct BIT{
	vector<llong> bits; // index start from 1
	llong n;
	BIT(llong n_){
		n = n_+2;
		bits = vector<llong>(n,0);
	}
	llong lowbit(llong n){ return n&(-n); }
	void update(llong idx, llong val){
		idx+=2; // for safety
		for(llong i=idx; i<n; i+=lowbit(i)) bits[i]+=val;
	}
	llong get_sum(llong idx){
		idx+=2; // for safety
		llong sum = 0;
		for(llong i=idx; i>0; i-=lowbit(i)) sum += bits[i];
		return sum;
	}
	llong get_range(llong ll, llong rr){
		if(rr<ll) return 0;
		return get_sum(rr)-get_sum(ll-1);
	}
};

void solve(){
	llong N, K; cin >> N >> K;
	vector<llong> arr(N);
	for(llong i=0;i<N;i++) cin >> arr[i];
	vector<pair<llong,llong>> id2val(N);
	set<llong> distinctValSet;
	for(llong i=0;i<N;i++) distinctValSet.insert(arr[i]);
	vector<llong> distinctVal;
	for(llong val : distinctValSet) distinctVal.pb(val);
	unordered_map<llong,llong> disVal2Id;
	for(llong i=0;i<distinctVal.size();i++)
		disVal2Id[distinctVal[i]] = i;

	for(llong i=0;i<N;i++) id2val[i] = mp(arr[i],i);

	sort(id2val.begin(), id2val.end());

	map<pair<llong,llong>, llong> val2id;
	for(llong i=0;i<N;i++){
		val2id[id2val[i]] = i;
	}

	vector<llong> disarr(N);
	for(llong i=0;i<N;i++){
		disarr[i] = disVal2Id[arr[i]];
	}
	
	// preprocessing

	vector<llong> blocks(N);


	// BIT needs discretized coordinates as well.
	BIT vals(distinctVal.size()+3);

	for(llong i=0;i<N;i++){
		llong low = arr[i]-K;
		llong high = arr[i]+K; // inclusive for swap

		auto lowb = lower_bound(distinctVal.begin(), distinctVal.end(), low);
		llong lowbv = distance(distinctVal.begin(), lowb);

		auto highb = upper_bound(distinctVal.begin(), distinctVal.end(), high);
		llong highbv = distance(distinctVal.begin(), highb)-1;

		llong notblock = vals.get_range(lowbv, highbv);

		blocks[val2id[mp(arr[i], i)]] = i-notblock;

		vals.update(disarr[i],1);
	}


	SegTree tracker(blocks, N);
	vector<llong> result(N);


	for(llong i=0;i<N;i++){
		// find min


		llong minid = tracker.query();
		result[i] = id2val[minid].first;

		tracker.update(minid, minid, inf);

        auto hv = mp(id2val[minid].first+K, inf);
		auto highb = upper_bound(id2val.begin(), id2val.end(), hv);
        //deb(mp(hv,*highb))
		llong highbv = distance(id2val.begin(), highb);

        auto lv = mp(id2val[minid].first-K, -inf);
		auto lowb = lower_bound(id2val.begin(), id2val.end(), lv);
		llong lowbv = distance(id2val.begin(), lowb) - 1; // could be negative


		if(lowbv >= 0)
			tracker.update(0, lowbv, -1);


		if(highbv <= N-1)
			tracker.update(highbv, N-1, -1);

	}

	for(llong i=0;i<N;i++){
		print(result[i]);
	}
}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	solve();
}