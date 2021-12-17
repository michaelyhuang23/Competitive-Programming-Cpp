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
//#include "debughelp.hpp"
using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
typedef long int iint;
typedef unsigned long int uiint;
typedef long long int llong;
typedef unsigned long long int  ullong;
#define Mem(a, b) memset(a, (b), sizeof(a))
#define For(i, j) for (int i=0 ; i<j ; i++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007

iint* bits = new iint[1000005];
inline iint low_bit(iint num){
	return num & (-num);
}
inline llong query(iint idx){
	llong sum = 0;
	while(idx>0){
		sum += bits[idx];
		idx -= low_bit(idx);
	}
	return sum;
}
inline void update(iint idx, iint val){
	while(idx<1000005){
		bits[idx] += val;
		idx += low_bit(idx);
	}
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint n,m;
    cin >> n >> m;
    fill(bits,bits+1000005,0);
    pair<iint,iint>* segs = new pair<iint,iint>[n];
    map<iint,vector<iint> > rights;
    For(i,n){
    	iint l, r;
    	cin >> l >> r;
    	segs[i] = make_pair(l, r);
    	rights[r].pb(l);
    }
    vector<iint>* rl = new vector<iint>[1000005];
    vector<iint> rs;
    for(auto const& r : rights) {
    	rs.pb(r.first);
    	rl[r.first] = r.second;
    }

    set<iint> qps;
    vector<pair<iint,iint> > id2x;
    vector<iint>* x2id = new vector<iint>[1000005];
    iint id=0;
    For(i,m){
    	iint cnt; cin >> cnt;
    	qps.insert(0);
	    x2id[0].pb(id++);
	    id2x.pb(make_pair(0, i));
    	For(j,cnt){
    		iint ptr; cin >> ptr;
    		qps.insert(ptr);
    		x2id[ptr].pb(id++);
    		id2x.pb(make_pair(ptr, i));
    	}
    	qps.insert(1000001);
	    x2id[1000001].pb(id++);
	    id2x.pb(make_pair(1000001, i));
    }

    vector<iint> qp;
    for(auto const& r : qps) qp.pb(r);
    vector<iint> allr;
    iint l=0,r=0;
    while(l<rs.size() && r<qp.size()){
    	//cout<<l<<" "<<r<<" "<<rs[l]<<" "<<qp[r]<<endl;
    	if(rs[l] < qp[r])
    		allr.pb(rs[l++]);
    	else if(rs[l] > qp[r])
    		allr.pb(qp[r++]);
    	else{
    		allr.pb(rs[l++]);
    		r++;
    	}
    }
    while(l<rs.size())
    	allr.pb(rs[l++]);
    while(r<qp.size())
    	allr.pb(qp[r++]);
    iint total = 0;
    iint* missing = new iint[m];
    fill(missing,missing+m,0);
    For(i,allr.size()){
    	iint x = allr[i];
    	//cout<<x<<endl;
    	//deb(x2id[x]);
    	for(iint id : x2id[x]){
    		if(id==0 || get<1>(id2x[id-1])!=get<1>(id2x[id]))
    			continue;
    		iint prevx = get<0>(id2x[id-1]);
    		//cout<<"prevx "<<prevx<<endl;
    		//cout<<get<1>(id2x[id])<<" "<<total<<" "<<query(prevx)<<endl;
    		missing[get<1>(id2x[id])]+=total-query(prevx);
    	}
    	For(j, rl[x].size()){
    		//cout<<"update "<<x<<" "<<rl[x][j]<<endl;
    		//cout<<query(1)<<endl;
    		update(rl[x][j],1);
    		total++;
    	}
    }
    //cout<<endl;
    For(i,m){

    	cout<<n-missing[i]<<endl;
    }
}

/*
for each query, find all intervals that contain some point in the query
(the intersection of segments with query points). 
1 3, 4 5, 6 7
1 4 7

for each ptr, add the number of segments it intersects
how to correct the overcount? 
PIE, subtract segs that intersect both? 


perhaps we consider from interval's pov; how much does it contribute
to each query? 

for each query ptr, add it to BIT O(m)
now after each query is finished, iterate over intervals O(nm) TLE
X

for each query, we iterate query ptrs from left to right
we binary search the rightmost interval that touch current query ptr
ordered by right hand

Now we search the leftmost interval that touch the current ptr by left
hand. 

the intervals in between is skipped

But what about when two intervals overlap? 

count how many intervals between 2 points:
how many end points between two points - how many start point of those before
X

offline query:
iterate over end points of intervals and segments (add startpoints to BIT). At an interval end point
query suffix sum of its start ptr. 
Y

*/








