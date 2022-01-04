#include<iostream>
#include<algorithm>
#include<assert.h>
#include<vector>
#include<fstream>

using namespace std;

typedef long long llong;
#define mp make_pair
#define pb push_back
#define mt make_tuple
#define MOD 1000000007LL

struct SegTree{
	static llong pow_up(llong num){
		for(llong i=0;i<65;i++) if(1<<i >= num) return 1<<i;
		return -1;
	}
	vector<llong> tree;
	vector<llong> pd;
	vector<llong> pm;
	llong n;
	SegTree(vector<llong>& arr,llong size){
		n = pow_up(size);
		tree = vector<llong>(2*n);
		pd = vector<llong>(2*n,0);
		pm = vector<llong>(2*n,1);
		copy(arr.begin(), arr.end(), tree.begin()+n);
		build();
	}
	inline void build(){
		for(llong i = n-1; i>=1; i--) tree[i] = (tree[i<<1] + tree[i<<1|1] + MOD)%MOD;
	}
	inline void changeVtx(llong idx, llong ts, llong te, llong left, llong right, llong val){
		//cout<<"call update: "<<idx<<" "<<ts<<" "<<te<<" "<<left<<" "<<right<<" "<<val<<endl; 
		if(left>right) return;
		if(ts == left && te == right){ tree[idx]=val; return;}
		push_down(idx, ts, te); //update to most current for backtrace reupdate
		llong tm = (ts+te)>>1;
		if(left<=tm)
			changeVtx(idx<<1,ts,tm,left,min(right,tm),val);
		if(right>tm)
			changeVtx(idx<<1|1,tm+1,te,max(tm+1,left),right,val);
		// reupdate values upstream
		tree[idx] = (tree[idx<<1] + tree[idx<<1|1] + MOD)%MOD;
	}
	inline void changeVtx(llong idx, llong val){ changeVtx(1,0,n-1,idx,idx,val); }
	inline void update(llong idx, llong ts, llong te, llong left, llong right, llong val){
		//cout<<"call update: "<<idx<<" "<<ts<<" "<<te<<" "<<left<<" "<<right<<" "<<val<<endl; 
		if(left>right) return;
		if(ts == left && te == right){ tree[idx]+=val*(te-ts+1);/*only for sum*/ pd[idx]+=val; return;}
		push_down(idx, ts, te); //update to most current for backtrace reupdate
		llong tm = (ts+te)>>1;
		if(left<=tm)
			update(idx<<1,ts,tm,left,min(right,tm),val);
		if(right>tm)
			update(idx<<1|1,tm+1,te,max(tm+1,left),right,val);
		// reupdate values upstream
		tree[idx] = (tree[idx<<1] + tree[idx<<1|1] + MOD)%MOD;
	}
	inline void update(llong left, llong right, llong val){ update(1,0,n-1,left,right,val); }
	inline void update2(llong left, llong right){ update2(1,0,n-1,left,right); }
	inline void update2(llong idx, llong ts, llong te, llong left, llong right){
		//cout<<"call update: "<<idx<<" "<<ts<<" "<<te<<" "<<left<<" "<<right<<" "<<val<<endl; 
		if(left>right) return;
		if(ts == left && te == right){ tree[idx]*=2;/*only for mul*/ pm[idx]*=2; pd[idx]*=2; return;}
		push_down(idx, ts, te); //update to most current for backtrace reupdate
		llong tm = (ts+te)>>1;
		if(left<=tm)
			update2(idx<<1,ts,tm,left,min(right,tm));
		if(right>tm)
			update2(idx<<1|1,tm+1,te,max(tm+1,left),right);
		// reupdate values upstream
		tree[idx] = (tree[idx<<1] + tree[idx<<1|1] + MOD)%MOD;
	}
	inline void push_down(llong idx, llong ts, llong te){
		if(idx>=n || pd[idx]==0 && pm[idx]==1) return;
		llong tm = (ts+te)>>1;
		tree[idx<<1] *= pm[idx];
		tree[idx<<1] += pd[idx]*(tm-ts+1);
		tree[idx<<1] %= MOD;
		tree[idx<<1|1] *= pm[idx];
		tree[idx<<1|1] += pd[idx]*(te-tm);
		tree[idx<<1|1] %= MOD;
		pm[idx<<1] *= pm[idx];
		pd[idx<<1] *= pm[idx];
		pd[idx<<1] += pd[idx];
		pm[idx<<1|1] *= pm[idx];
		pd[idx<<1|1] *= pm[idx];
		pd[idx<<1|1] += pd[idx];
		pd[idx] = 0;
		pm[idx] = 1;
	}
	inline llong query(llong idx, llong ts, llong te, llong left, llong right){
		// both inclusive; ts, te indicate the coverage of this index
		if(left>right) return 0;
		push_down(idx,ts,te);
		if(ts == left && te == right) return tree[idx];
		llong tm = (ts+te)>>1;
		llong sum = 0;
		if(left<=tm)
			sum+=query(idx<<1,ts,tm,left,min(right,tm));
		sum%=MOD;
		if(right>tm)
			sum+=query(idx<<1|1,tm+1,te,max(tm+1,left),right);
		sum%=MOD;
		return sum;
	}
	inline llong query(llong left, llong right){ return query(1,0,n-1,left,right); }
};

llong Pow(llong num, int pow){
	if(pow==0) return 1;
	if(pow%2==0){
		llong inter = Pow(num, pow/2);
		return ((inter*inter)%MOD+MOD)%MOD;
	}else{
		return ((Pow(num, pow-1)*num)%MOD+MOD)%MOD;
	}
}

llong inverse(llong num){
	return Pow(num, MOD-2);
}

llong choose(llong n, llong k){
	if(k*2 > n) return choose(n, n-k);
	llong numer = 1;
	for(llong i=n; i>=n-k+1; i--) numer=((numer*i)%MOD+MOD)%MOD;
	llong denom = 1;
	for(llong i=k; i>=1; i--) denom=((denom*inverse(i))%MOD+MOD)%MOD;
	return ((numer*denom)%MOD+MOD)%MOD;
}

int main(){
	ios_base::sync_with_stdio(0);
	ifstream fin("help.in");
	ofstream fout("help.out");
	cin.tie(0);
	llong n, k;
	cin >> n >> k;
	vector<pair<llong, llong> > range(n);
	for(llong i = 0; i<n; i++) {
		llong a, b; cin >> a >> b;
		range[i] = mp(a,b);
	}
	vector<vector<int> > choice(11);
	for(int i=0;i<11;i++) choice[i]=vector<int>(11,0);
	for(int i=0;i<11;i++) for(int j=0;j<=i;j++) choice[i][j] = choose(i,j);
	sort(range.begin(), range.end());
	vector<llong> arr(2*n+5,0);
	vector<SegTree> trees;
	for(llong i = 0; i <= k; i++) trees.pb(SegTree(arr,2*n+5));
	trees[0].changeVtx(0, 1);
	for(llong i=0; i<n; i++){
		llong l = range[i].first;
		llong r = range[i].second;
		for(llong c=0; c<=k; c++){
			// what about j>=r, selecting or not doesn't make difference
			//cout<<"double "<<r<<" to end"<<endl;
			trees[c].update2(r, 2*n+5);
			llong summ = 0;
			for(llong z = 0; z<=c; z++){
				summ += (choice[c][z]*trees[z].query(0, l-1)%MOD + MOD)%MOD;
				summ %= MOD;
			} // this is just the possibility of transitioning from j<l
			// now we consider l<=j<r --> say we select current one 
			// --> enalbes us to reach it by these new ways
			summ += trees[c].query(l,r-1);
			summ %= MOD;
			//cout<<"update "<<c<<" "<<r<<" to "<<summ<<endl;
			trees[c].update(r, r, summ); 
		}
	}
	llong result = trees[k].query(0, 2*n+5);
	result = (result + MOD)%MOD;
	cout<<result<<endl;
	fout.close();
}


/*



*/

