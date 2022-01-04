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
#include <cmath>

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

void prepbkt(iint i, vector<iint>& bktp, vector<iint>& bktl, vector<iint>& stpos, vector<iint>& nxt){
	iint st = stpos[i];
	iint et = stpos[i+1]-1;
	for(iint j = et; j>=st; j--){
		if(nxt[j] > et || nxt[j] == j) { bktp[j] = j; bktl[j] = 0; }
		else { bktp[j] = bktp[nxt[j]]; bktl[j] = bktl[nxt[j]]+1; }
	}
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint n, m;
    cin >> n >> m;
    vector<iint> nxt(n);
    For(i,n) cin >> nxt[i];
    For(i,n) nxt[i] += i;
    For(i,n) if(nxt[i]>=n) nxt[i]=i;
    iint bkt = (iint)sqrt(n);
    vector<iint> stpos(1);
    stpos[0] = 0;
    for(iint i=1; stpos[i-1]+bkt<n; i++) stpos.pb(stpos[i-1]+bkt);
    stpos.pb(n);
    vector<iint> bktp(n);
    vector<iint> bktl(n);
	for(iint i=0; i<stpos.size()-1; i++){
		prepbkt(i, bktp, bktl, stpos, nxt);
	}
    For(i,m){
    	iint c; cin>>c;
    	if (c == 0){
    		iint a, b;
    		cin >> a >> b;
    		a--;
    		nxt[a] = b + a;
    		if(nxt[a]>=n) nxt[a] = a;
    		prepbkt(a/bkt, bktp, bktl, stpos, nxt);
    	}else{
    		iint a; cin>>a;
    		a--;
    		iint count = 0;
    		while(nxt[a]!=a){
    			count += bktl[a];
    			a = bktp[a];
    			if(nxt[a]==a) break;
    			a = nxt[a];
    			count++;
    		}
    		cout<< a+1 << " " <<count+1<<endl;
    	}

    }
}

/*

If we preprocess everything, basically every location directly 
records the end result. That's not great because each update would require
changing all the records.

So we find a balance:
sqrt(n) buckets.
We preprocess within the bucket but we don't preprocess between buckets
pbkt[i] gives the last element in bucket that i dumps to

query is sqrt(n)

what about update?
we recalculate pbkt[i] which takes O(1), but the hard part is the j
that changing i affects
we have to basically recompute the preprocess of the bucket so sqrt(n)
time as well.


*/













