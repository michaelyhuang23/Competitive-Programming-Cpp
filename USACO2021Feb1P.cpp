#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

#include "debughelp.hpp"

using namespace std;

typedef long int iint;
typedef long long int llong;
#define For(i, j) for (int i=0 ; i<j ; i++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007

struct node{
	int upc;
	int unc;
	int st, et;
	int sp, ep;
	node(){ upc = 0; unc = 0; st=-1; et=-1; sp=-1; ep=-1; }
	node(int pos, int col){
		upc = 1; unc = 0; 
		st = col;
		et = col;
		sp = pos;
		ep = pos; 
	}
	node(int upc_, int unc_, int st_, int et_, int sp_, int ep_){
		upc = upc_;
		unc = unc_;
		st = st_;
		et = et_;
		sp = sp_;
		ep = ep_;
	}
};

struct segtree{
	vector<node> tree;
	vector<vector<int> > pos;
	int n;
	int pow_up(int n){
		for(int i=0; i<32; i++) if((1<<i)>=n) return 1<<i;
		assert(false);
		return -1;
	}
	segtree(vector<int>& target, int n_){
		n = pow_up(n_);
		tree = vector<node>(2*n);
		for(int i=0; i<n_; i++) tree[i+n] = node(i, target[i]);
		for(int i=n_; i<n; i++) {tree[i+n].sp = i; tree[i+n].ep = i; }
		pos = vector<vector<int> >(n+5);
		for(int i=0; i<n_; i++){
			pos[target[i]].push_back(i);
		}
		build();
	}
	bool check_inrange(int l, int r, int item){
        //cout<<l<<" "<<r<<endl;
		for(int i : pos[item]){
			if(l<=i && i<=r) return true;
		}
		return false;
		auto ll = lower_bound(pos[item].begin(), pos[item].end(), l);
		auto rr = upper_bound(pos[item].begin(), pos[item].end(), r);
		if(distance(ll, rr) == 0) return false;
		else return true;
	}
	node merge(node ll, node rr){
        if(ll.st == -1) return node(rr.upc, rr.unc, ll.st, rr.et, ll.sp, rr.ep);
        if(rr.st == -1) return node(ll.upc, ll.unc, ll.st, rr.et, ll.sp, rr.ep);

		// what to do with the connection point?
		int upc = 0;
		int unc = 0;
		int rucP = 0;
		if(rr.st == ll.et){
			upc = rr.upc + ll.upc - 1;
			// no chain effect, already up or unique
		} else if(rr.st<ll.et){
			upc = rr.upc - 1 + ll.upc;
			// should we make it a unique?
			// if isn't up or unique, make unique
			if(!check_inrange(ll.sp, ll.ep, rr.st)){
				rucP++; // record as unique
			}
		} else{ // rr.st > ll.et
			upc = rr.upc + ll.upc;
		}
		unc = ll.unc + rucP; // we need ucc
		//deb(ll.sp); deb(ll.ep); deb(rr.sp); deb(rr.ep);
		return node(upc, unc, ll.st, rr.et, ll.sp, rr.ep);
	}
	void pull_up(int idx){
		tree[idx] = merge(tree[idx*2], tree[idx*2+1]);
	}
	void build(){
		for(int i=n-1; i>=1; i--) pull_up(i);
	}
	int query(int l, int r){
		deb(l); deb(r);
		node totalL, totalR;
		for(l+=n, r+=n; l<=r; l/=2, r/=2){
			if(l&1){
				if(totalL.st == -1) totalL = tree[l++];
				else totalL = merge(totalL, tree[l++]);
			}
			if(!(r&1)){
				if(totalR.st == -1) totalR = tree[r--];
				else totalR = merge(tree[r--], totalR);
			}
			if(l==r) break;
		}
		node total;
		if(totalL.st == -1) total = totalR;
		else if(totalR.st == -1) total = totalL;
		else total = merge(totalL, totalR);
		deb(total.upc); deb(total.unc); deb(total.sp); deb(total.ep);
		return total.upc + total.unc;
	}
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q; cin >> n >> q;
    vector<int> arr(n);
    For(i, n) cin >> arr[i];
    segtree tr(arr, n);
    For(i, q){
    	int a,b; cin >> a >> b;
    	a --; b --;
    	if(a>b) swap(a,b);
    	int total = tr.query(a, b);
    	cout<<total<<endl;
    }
}

/*

each node of segtree should have a hashtable of occurrence counts
each node of segtree should have up counts by color
each node of segtree should have uniqueness count by color

*/