#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unordered_map>
#include <unordered_set>
#include <fstream>

using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
typedef long int iint;
typedef unsigned long int uiint;
typedef long long int llong;
typedef unsigned long long int ullong;
#define Mem(a, b) memset(a, (b), sizeof(a))
#define For(i, j) for (int i=0 ; i<j ; i++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007

bool check(vector<iint>& arr, iint del){
	vector<iint> nA;
	For(i, arr.size()) if(arr[i] != del) nA.pb(arr[i]);
	bool suc = true;
	for(iint i=0; i<nA.size(); i++) if(nA[i] != nA[nA.size()-1-i]) suc = false;
	return suc;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint tt;
    cin >> tt;
    while(tt--){
    	iint n;
    	cin >> n;
    	vector<iint> arr(n);
    	For(i,n) cin >> arr[i];
    	// now we record the center types
    	// first we extract the unique elements by putting them through a set
    	set<iint> unique;
    	For(i,n) unique.insert(arr[i]);
    	vector<iint> id2e;
    	for(iint elem : unique) id2e.pb(elem);
    	vector<iint> e2id(id2e[id2e.size()-1]+1,-1);
    	For(i,n) e2id[id2e[i]] = i;
    	For(i,n) arr[i] = e2id[arr[i]];
    	// now we count each's center
    	iint ic = id2e.size();
    	vector<vector<iint> > ipos(ic);
    	For(i,ic) ipos[i] = vector<iint>();
    	For(i,n) ipos[arr[i]].pb(i);
    	iint oC = 0;
    	vector<iint> oP;
    	For(i,ic) if(ipos[i].size()%2 == 1){ oC++; oP.pb(i); }
    	if(oC>2){
    		cout<<"NO"<<endl;
    		continue;
    	}else if(oC == 2){
    		assert(oP.size()==2);
    		if(check(arr, oP[0])){
    			cout<<"YES"<<endl;
    			continue;
    		}
    		if(check(arr, oP[1])){
    			cout<<"YES"<<endl;
    			continue;
    		}
    		cout<<"NO"<<endl;
    	}else if(oC==1){
    		if(check(arr, oP[0])){
    			cout<<"YES"<<endl;
    			continue;
    		}
    	}

    	// Now either oC = 0 or there's 1 oC at the center
    	vector<iint> pairr(arr.size());
    	vector<iint> counter(ic,0);
    	For(i, n){
    		iint idx = ipos[arr[i]].size() - 1 - counter[arr[i]];
    		counter[arr[i]]++;
    		pairr[i] = ipos[idx];
    	}
    	stack<iint> tracker;
    	unordered_set<iint> del; // record only colors
    	For(i, n){
    		if(pairr[i]>i){
    			tracker.pb(i);
    			
    		}else if(pairr[i] == i){

    		}else{

    		}
    	}
    }
}






