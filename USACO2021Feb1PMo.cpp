#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <unordered_set>
#include <unordered_map>

//#include "debughelp.hpp"

using namespace std;

typedef long int iint;
typedef long long int llong;
#define For(i, j) for (int i=0 ; i<j ; i++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007

int bktS = 450;

struct query{
	int l, r;
	int L;
	int ans;
	int i;
	query(int l_, int r_, int i_){
		L = l_/bktS;
		l = l_;
		r = r_;
		i = i_;
	}
	bool operator<(const query& other){
		if(L==other.L){
			return r<other.r;
		}
		return L<other.L;
	}
};

vector<int> arr;
int n,q;
vector<query> queries;
vector<int> nextE;
unordered_map<int, int> hist;
unordered_set<int> ucc;
int upc;

void init(int l, int r){
	hist = unordered_map<int, int>();
	ucc = unordered_set<int>();
	upc = 0;
	for(int i=l; i<=r; i++){
		if(i==l || arr[i]>arr[i-1]) upc++; 
		else if(arr[i]<arr[i-1]){
			if(hist.find(arr[i]) == hist.end()) ucc.insert(arr[i]);
		}
		if(hist.find(arr[i]) == hist.end()) hist[arr[i]] = 0;
		hist[arr[i]] ++;
	}
}

void right_right(int l, int rn, int ro){
	for(int i=ro+1; i<=rn; i++){
		if(arr[i] > arr[i-1]) upc++;
		else if(arr[i] < arr[i-1]){
			if(hist.find(arr[i]) == hist.end()) ucc.insert(arr[i]);
		}
		if(hist.find(arr[i]) == hist.end()) hist[arr[i]] = 0;
		hist[arr[i]] ++;
	}
}

void left_left(int ln, int r, int lo){
	//cout<<lo<<" "<<ln<<" "<<r<<endl;
	for(int l = lo-1; l>=ln; l--){
		if(arr[l] < arr[l+1]){
			upc++; // for l
		}else if(arr[l] > arr[l+1]){
			// upc doesn't change
			ucc.insert(arr[l+1]); // this might erase later ucc (which is fine)
		}
		ucc.erase(arr[l]);
		if(hist.find(arr[l]) == hist.end()) hist[arr[l]] = 0;
		hist[arr[l]] ++;
		//deb(l);
		//deb(hist);
	}
}

void left_right(int ln, int r, int lo){
	for(int l = lo; l<ln; l++){
		if(arr[l] < arr[l+1]){
			upc --; // ucc doesn't change, it might enable later ucc!
			// we need to check by finding the next one
		}else if(arr[l] > arr[l+1]){
			// upc doesn't change
			ucc.erase(arr[l+1]); // no longer a candidate
			// could enable later ucc
		}
		int le = nextE[l];
		if(le <= r && arr[le]<arr[le-1]) ucc.insert(arr[l]); // must be in range!
		hist[arr[l]]--;
		if(hist[arr[l]] == 0) hist.erase(arr[l]);
	}
}

bool cmp(query l, query r){ return l.i < r.i; }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    arr = vector<int>(n);
    For(i,n) cin >> arr[i];
    nextE = vector<int>(n);
    vector<int> lastA(n+5,n);
    for(int i = n-1; i>=0; i--) {
    	nextE[i] = lastA[arr[i]];
    	lastA[arr[i]] = i;
    }
    queries = vector<query>();
    For(i,q){
    	int a,b; cin >> a >> b;
    	a--; b--;
    	if(a>b) swap(a,b);
    	queries.pb(query(a,b,i));
    }
    sort(queries.begin(), queries.end());
    int curL = -1;
    int prevl = -1, prevr = -1;
    int changeC = 0;
    for(query& q : queries){
    	//cout<<q.l<<" "<<q.r<<endl;
    	// if(q.i == 88){
    	// 	deb(prevl);
    	// 	deb(prevr);
    	// 	deb(q.l);
    	// 	deb(q.r);
    	// }
    	if(q.L != curL){
    		init(q.l, q.r);
    		curL = q.L;
    		prevl = q.l; prevr = q.r;
    		changeC += q.l + q.r;
    	}else{
    		if(q.r != prevr) right_right(prevl, q.r, prevr); 
    		assert(q.r >= prevr);
    		if(q.l < prevl){
    			left_left(q.l, q.r, prevl);
    		}else if(q.l > prevl){
    			left_right(q.l, q.r, prevl);
    		}
    		changeC += abs(q.l - prevl) + abs(q.r - prevr);
    		prevl = q.l; prevr = q.r;
    	}
    	// if(q.i == 88){
    	// 	deb(hist);
    	// 	deb(ucc);
    	// 	deb(upc);
    	// 	deb(upc + ucc.size());
    	// }
    	// deb(hist);
    	// deb(ucc);
    	q.ans = upc + ucc.size();
    }
    cout<<"time used "<<changeC<<endl;
    sort(queries.begin(), queries.end(), cmp);
    for(query& q : queries){
    	cout<<q.ans<<endl;
    }
}









