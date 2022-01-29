#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000
#define print(x) cout<<x<<endl


struct SegTree
{
	static llong pow_up(int num){
		for(int i=0;i<65;i++) if(1<<i >= num) return 1<<i;
		return -1;
	}
	vector<llong> tree;
	vector<llong> pd;
	int n;
	SegTree(vector<llong>& arr,int size){
		n = pow_up(size);
		tree = vector<llong>(n*2);
		pd = vector<llong>(n*2);
		fill(pd.begin(),pd.end(),0);
		copy(arr.begin(), arr.begin()+size, tree.begin()+n);
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


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong n; cin >> n;
	llong m; cin >> m;
	vector<llong> arr(n);
	for(llong i=0;i<n;i++) cin >> arr[i];
	SegTree tr(arr,n);
	for(llong i=0;i<m;i++){
		llong type; cin >> type;
		llong x, y; cin >> x >> y; x--; y--;
		if(type==1){
			llong k; cin >> k;
			tr.update(x, y, k);
		}else{
			cout<<tr.query(x, y)<<endl;
		}
	}
}