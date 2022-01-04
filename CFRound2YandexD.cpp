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

iint bkt = 0;
bool cmp (tuple<iint, iint, iint>& a, tuple<iint, iint, iint>& b){
	iint abkt = get<0>(a)/bkt;
	iint bbkt = get<0>(b)/bkt;
	if(abkt != bbkt) return abkt < bbkt;
	return get<1>(a) < get<1>(b);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint n, t;
    cin >> n >> t;
    vector<iint> arr(n);
    unordered_set<iint> uniquet;
    For(i,n) cin >> arr[i];
    For(i,n) uniquet.insert(arr[i]);
    vector<iint> id2num;
    unordered_map<iint, iint> num2id;
    iint idx =0;
    for(iint pp : uniquet) {
    	num2id[pp] = idx++;
    	id2num.pb(pp);
    }
    vector<iint> ids(n);
    for(iint i=0; i<n; i++) ids[i] = num2id[arr[i]];
    vector<tuple<iint, iint, iint> > queries(t);
    For(i,t){
    	iint l, r;
    	cin >> l >> r;
        l--; r--;
    	queries[i] = make_tuple(l,r,i);
    }

    bkt = (iint)(n/sqrt(t));
    if(bkt<=0) bkt = 1;

	sort(queries.begin(), queries.end(), cmp);
	iint cl=0, cr=0;
	vector<iint> occT(id2num.size(),0);
	occT[ids[0]]++;
	llong score=1*arr[0];
	vector<llong> ans(t);
	for(tuple<iint, iint, iint>& q : queries){
		iint curl = get<0>(q), curr = get<1>(q);
		if(curl>cl){
			for(;cl<curl;cl++){
				iint id = ids[cl]; 
				score -= (2LL*occT[id]-1LL)*id2num[id];
				occT[id]--;
			}
		}else{
			for(cl--;cl>=curl;cl--){
				iint id = ids[cl]; 
				score += (2LL*occT[id]+1LL)*id2num[id];
				occT[id]++;
			}
			cl++;
		}
		if(curr<cr){
			for(;cr>curr;cr--){
				iint id = ids[cr]; 
				score -= (2LL*occT[id]-1LL)*id2num[id];
				occT[id]--;
			}
		}else{
			for(cr++;cr<=curr;cr++){
				iint id = ids[cr]; 
				score += (2LL*occT[id]+1LL)*id2num[id];
				occT[id]++;
			}
			cr--;
		}
		ans[get<2>(q)] = score;
	}

	For(i, t) cout<< ans[i]<<endl;
}

/*

performs naive Mo's Algorithm. Use compressed arr to track occurences

*/

