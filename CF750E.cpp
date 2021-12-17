#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <fstream>

using namespace std;

typedef long int iint;
typedef long long int llong;
#define For(i, j) for (int i=0 ; i<j ; i++)
#define mp make_pair
#define pb push_back
#define inf (int)2147483647
#define PI 3.1415926
#define MOD 1000000007

struct segtree{
	vector<int*> tree;
	int n;
	int pow_up(int n){
		for(int i=0; i<32; i++) if((1<<i)>=n) return 1<<i;
		assert(false); return -1;
	}
	int* make_matrix(){
		int* ma = new int[25];
        fill(ma, ma+25, 0);
		For(i, 5) for(int j=i; j<5; j++) ma[i*5+j] = inf/2;
		return ma;
	}
	segtree(vector<int>& arr, int n_){
		n = pow_up(n_);
		tree = vector<int*>(2*n);
		for(int i=0; i<2*n; i++) tree[i] = make_matrix();
		for(int i=0; i<n_; i++){
			if(arr[i]==2) tree[i+n][1*5+1] = 0;
			if(arr[i]==0) tree[i+n][2*5+2] = 0;
			if(arr[i]==1) tree[i+n][3*5+3] = 0;
			if(arr[i]==7) tree[i+n][4*5+4] = 0;

			if(arr[i]==2) tree[i+n][1*5+0] = 1;
			if(arr[i]==0) tree[i+n][2*5+1] = 1;
			if(arr[i]==1) tree[i+n][3*5+2] = 1;
			if(arr[i]==7) tree[i+n][4*5+3] = 1;

			if(arr[i]==6) tree[i+n][4*5+3] = 1;
			if(arr[i]==6) tree[i+n][4*5+0] = 1;
		}
		build();
	}
	int* merge(int* L, int* R){
		int* M = make_matrix();
		for(int l = 1; l <= 4; l++){
			for(int r = l; r <= 4; r++){
				M[l*5+r] = min(M[l*5+r], L[l*5+l-1] + R[l*5+r]);
                if(r+1 == 5) M[l*5+r] = min(M[l*5+r], L[l*5+r] + R[4*5+0]);
                else M[l*5+r] = min(M[l*5+r], L[l*5+r] + R[(r+1)*5+r]);
				for(int m = l; m < r; m++){
					M[l*5+r] = min(M[l*5+r], L[l*5+m] + R[(m+1)*5+r]);
				}
			}
		}
		M[4*5+3] = L[4*5+3] + R[4*5+3];
		M[3*5+2] = L[3*5+2] + R[3*5+2];
		M[2*5+1] = L[2*5+1] + R[2*5+1];
		M[1*5+0] = L[1*5+0] + R[1*5+0];
		M[4*5+0] = L[4*5+0] + R[4*5+0];
		return M;
	}
	void pull_up(int idx){
		tree[idx] = merge(tree[idx*2], tree[idx*2+1]);
	}
	void build(){
		for(int i=n-1; i>=1; i--) pull_up(i);
	}
    void del_matrix(int* arr){
        if(arr == nullptr) return;
        //cout<<arr<<endl;
        delete[] arr;
    }
	int query(int l, int r){
		int* ll = nullptr; bool lc = false;
        int* rr = nullptr; bool rc = false;
		for(l+=n, r+=n; l<=r; l/=2, r/=2){
			if(l&1) if(ll== nullptr) ll=tree[l++]; else{
                int* tmp = merge(ll, tree[l++]);
                if(lc)
                del_matrix(ll);
                ll = tmp; lc=true;
            }
			if(!(r&1)) if(rr== nullptr) rr=tree[r--]; else{
                int* tmp = merge(tree[r--], rr);
                if(rc)
                del_matrix(rr);
                rr = tmp; rc=true;
            }
			if(l==r) break;
		}
		int* result;
        bool rt = false;
        if(ll== nullptr) result = rr;
        else if(rr== nullptr) result = ll;
        else {result = merge(ll, rr); rt=true;}
		int ret = result[1*5+4];
        if(rt) del_matrix(result);
        if(rc && rr!=result) del_matrix(rr);
        if(lc && rr!=ll && ll!=result) del_matrix(ll);
        return ret;
	}
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q; cin >> n >> q;
    string s; cin >> s;
    // 0, 1, 2, 3, 4, 5,  6,  7,  8,  9,   10,  11,  12,   13
    // 0, 1, 2, 6, 7, 01, 16, 17, 20, 016, 017, 201, 2016, 2017
    vector<int> arr(n);
    for(int i=0; i<n; i++) arr[i] = s[i]-'0';
    segtree tr(arr, n);
	for(int i=0; i<q; i++){
		int l, r; cin >> l >> r;
		l--; r--;
		int ret = tr.query(l, r);
        if(ret>=inf/2-1) cout<<-1<<endl;
        else cout<<ret<<endl;
	}
}

