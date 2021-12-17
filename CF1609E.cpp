#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <set>
#include <fstream>

using namespace std;

typedef long int iint;
typedef long long int llong;
#define For(i, j) for (int i=0 ; i<j ; i++)
#define mp make_pair
#define pb push_back
#define inf (int)400000
#define PI 3.1415926
#define MOD 1000000007

struct segtree
{
	static int pow_up(int num){
		For(i,65) if(1<<i >= num) return 1<<i;
		return -1;
	}
	vector<int> tree,pd;
	int n;
	segtree(vector<int>& arr,int size){
		n = pow_up(size);
		tree = vector<int>(n*2, inf/2);
		pd = vector<int>(n*2, 0);
		copy(arr.begin(), arr.end(), tree.begin()+n);
		build();
	}
	inline void build(){
		for(int i = n-1; i>=1; i--) tree[i] = min(tree[i<<1], tree[i<<1|1]);
	}
	inline void set_val(int idx, int val){
		tree[n+idx] = val;
		for(iint i = (n+idx)>>1; i >= 1; i>>=1) tree[i] = min(tree[i<<1], tree[i<<1|1]);
	}
	inline void update(int idx, int ts, int te, int left, int right, int val){
		//cout<<"call update: "<<idx<<" "<<ts<<" "<<te<<" "<<left<<" "<<right<<" "<<val<<endl;
		if(left>right) return;
		if(ts == left && te == right){ tree[idx]+=val; pd[idx]+=val; return;}
		push_down(idx, ts, te); //update to most current for backtrace reupdate
		int tm = (ts+te)>>1;
		if(left<=tm)
			update(idx<<1,ts,tm,left,min(right,tm),val);
		if(right>tm)
			update(idx<<1|1,tm+1,te,max(tm+1,left),right,val);
		// reupdate values upstream
		tree[idx] = min(tree[idx<<1], tree[idx<<1|1]);
	}
	inline void update(int left, int right, int val){ update(1,0,n-1,left,right,val); }
	inline void push_down(int idx, int ts, int te){
		if(idx>=n || pd[idx]==0) return;
		int tm = (ts+te)>>1;
		tree[idx<<1] += pd[idx];
		tree[idx<<1|1] += pd[idx];
		pd[idx<<1] += pd[idx];
		pd[idx<<1|1] += pd[idx];
		pd[idx] = 0;
	}
	inline llong query(int idx, int ts, int te, int left, int right){
		// both inclusive; ts, te indicate the coverage of this index
		if(left>right) return inf/2;
		push_down(idx,ts,te);
		if(ts == left && te == right) return tree[idx];
		int tm = (ts+te)>>1;
		llong minn = inf/2;
		if(left<=tm)
			minn=min(minn,query(idx<<1,ts,tm,left,min(right,tm)));
		if(right>tm)
			minn=min(minn,query(idx<<1|1,tm+1,te,max(tm+1,left),right));
		return minn;
	}
	inline llong query(int left, int right){ return query(1,0,n-1,left,right); }
};

struct BIT{
	vector<int> bits; // index start from 1
	int n;
	BIT(int n_){
		n = n_+2;
		bits = vector<int>(n,0);
	}
	int lowbit(int n){ return n&(-n); }
	void update(int idx, int val){
		idx+=2; // for safety
		for(int i=idx; i<n; i+=lowbit(i)) bits[i]+=val;
	}
	int get_sum(int idx){
		idx+=2; // for safety
		int sum = 0;
		for(int i=idx; i>0; i-=lowbit(i)) sum += bits[i];
		return sum;
	}
};

int get_range(BIT& s, int l, int r){
	return s.get_sum(r) - s.get_sum(l-1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    string s; cin >> s;
    vector<int> bpos, apos, cpos;
    BIT act(200000), cct(200000), bct(200000);
    vector<int> arr(n+10,inf/2);
    segtree bi(arr, n+10);
    For(i,n){
    	if(s[i]=='a'){ act.update(i, 1); apos.pb(i); } 
    	if(s[i]=='c'){ cct.update(i, 1); cpos.pb(i); }
    }
    For(i, n){
    	if(s[i] == 'b'){
    		if(bpos.size()!=0){
    			int prev=bpos[bpos.size()-1];
    			bi.set_val(i, get_range(act, 0, prev) + get_range(cct, i, n+5));
    		}
    		bpos.pb(i);
    		bct.update(i,1);
    	}
    }
    set<int> as(apos.begin(),apos.end()), cs(cpos.begin(),cpos.end()), bs(bpos.begin(),bpos.end());
    For(i,q){
    	int p; char c; cin >> p >> c; p--;
    	char oc = s[p];
    	s[p] = c;

        int amin = inf/2, cmax = -1;
        if(as.size()>0) amin = *as.begin();
    	if(cs.size()>0) cmax = *cs.rbegin();


    	if(oc == c) {
    		if(as.size()== 0 || bs.size() == 0 || cs.size() == 0){
	    		cout<<0<<endl;
	    		continue;
	    	}
	    	if(amin > cmax){
	    		cout<<0<<endl;
	    		continue;
	    	}
    		int tb = get_range(bct, amin, cmax);
	    	int killAC = inf; 
	    	if(tb>0){
	    		int left = get_range(cct,*bs.upper_bound(amin),n+5);
	    		int right = get_range(act,0,*(--bs.lower_bound(cmax)));
	    		int lowB = (*(bs.upper_bound(amin)))+1;
	    		int mid = bi.query(lowB, cmax);
	    		killAC = min(killAC,left);
	    		killAC = min(killAC,right);
	    		killAC = min(killAC,mid);
	    	}
	    	cout<<min(tb,killAC)<<endl;
    		continue; 
    	}

    	if(oc=='a'){
    		as.erase(p); // fix bi update
    		act.update(p, -1);
            if(bs.upper_bound(p)!=bs.end()) {
                int nxtB = *bs.upper_bound(p); nxtB++;
                bi.update(nxtB, n + 5, -1);
            }
            if(as.size()>0) amin = *as.begin(); else amin = inf/2;
    	}else if(oc=='c'){
    		cs.erase(p);
    		cct.update(p, -1);
    		bi.update(0, p, -1);
            if(cs.size()>0) cmax = *cs.rbegin(); else cmax = 0;
    	}else{
    		if(bs.size() != 1) {
	    		auto cur = bs.lower_bound(p);
	    		if(bs.upper_bound(p) == bs.end()){
	    			bi.set_val(p,inf/2);
	    		}else if(bs.begin() == cur){
	    			int curi = *(++cur);
	    			bi.set_val(curi,inf/2);
	    		}else{
	    			bi.set_val(p, inf/2);
	    			auto boti = cur; boti--;
	    			auto topi = cur; topi++;
	    			int bot = *boti; int top = *topi;
	    			int sum = get_range(act, 0, bot) + get_range(cct, top, n+5);
	    			int curi = *(++cur);
	    			bi.set_val(curi, sum);
	    		}
	    	}
    		bs.erase(p);
    		bct.update(p, -1);
    	}

    	if(c=='a'){
    		if(p<amin){
    			amin = p;
    		}
    		act.update(p, 1);
            if(bs.upper_bound(p)!=bs.end()) {
                int nxtB = *bs.upper_bound(p); nxtB++;
                bi.update(nxtB, n + 5, 1);
            }
    		as.insert(p);
    	}else if(c=='c'){
    		if(p>cmax){
    			cmax = p;
    		}
    		cct.update(p, 1);
    		bi.update(0, p, 1);
    		cs.insert(p);
    	}else{
    		if(bs.size()!=0){
	    		assert(bs.find(p) == bs.end());
	    		auto ret = bs.lower_bound(p);
	    		if(ret == bs.begin()){
	    			int top = *ret;
	    			int tcc = get_range(act,0,p) + get_range(cct,top,n+5);
		    		bi.set_val(top, tcc);
	    			bs.insert(p);
	    		}else if(ret == bs.end()){
	    			int bot = *(--ret);
		    		int lcc = get_range(act,0,bot) + get_range(cct,p,n+5);
		    		bi.set_val(p, lcc);
		    		bs.insert(p);
	    		}else{
		    		int top = *ret;
		    		int bot = *(--ret); // what if it's the first
		    		bi.set_val(top, inf/2);
		    		int lcc = get_range(act,0,bot) + get_range(cct,p,n+5);
		    		int tcc = get_range(act,0,p) + get_range(cct,top,n+5);
		    		bi.set_val(p, lcc);
		    		bi.set_val(top, tcc);
		    	}
	    	}
    		bs.insert(p);
    		bct.update(p, 1);
    	}

    	if(as.size()== 0 || bs.size() == 0 || cs.size() == 0){
    		cout<<0<<endl;
    		continue;
    	}
    	if(amin > cmax){
    		cout<<0<<endl;
    		continue;
    	}

    	int tb = get_range(bct, amin, cmax);
    	int killAC = inf; 
    	if(tb>0){
    		int left = get_range(cct,*bs.upper_bound(amin),n+5);
    		int right = get_range(act,0,*(--bs.lower_bound(cmax)));
    		int lowB = (*(bs.upper_bound(amin)))+1;
    		int mid = bi.query(lowB, cmax);
    		killAC = min(killAC,left);
    		killAC = min(killAC,right);
    		killAC = min(killAC,mid);
    	}
    	cout<<min(tb,killAC)<<endl;
    }
}