#include<iostream>
#include<vector>
#include<set>
#include<bitset>
#include<algorithm>
#include<assert.h>

#include "debughelp.hpp"

using namespace std;
typedef long long llong;
#define pb push_back
#define mp make_pair
#define print(x) cout<<x<<endl
#define inf 1000000007

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, m; cin >> n >> m;
	string s; cin >> s;
	string t; cin >> t;

	vector<int> sp;
	for(int i=0;i<n+m;i++) if(s[i]=='1'){
		sp.pb(i);
	}
	vector<int> ep;
	for(int i=0;i<n+m;i++) if(t[i]=='1'){
		ep.pb(i);
	}
	int c = sp.size(); assert(c==ep.size());
	vector<pair<int,int>> interv(c);
	for(int i=0;i<c;i++){
		int a = sp[i], b = ep[i];
		if(a>b) swap(a,b);
		interv[i] = mp(a-i,b-i);
	}
	deb(interv)
	deb(c)
	sort(interv.begin(), interv.end());
	for(int i=0;i<c-1;i++){
		assert(interv[i].second<=interv[i+1].second && "sorted order assumption failed");
	}
	deb(interv)
	int head = 0;
	vector<pair<int,int>> ptrs; // edge case difficult
	for(int i=1;i<c;i++){
		if(interv[i].first <= interv[head].second) continue;
		print(mp(head, i));
		if(head==0 && interv[i-1].first==interv[head].first)
			ptrs.pb(mp(interv[head].first, head));
		else 
			ptrs.pb(mp(interv[head].second, head));
		head = i;
	}
	if(head == 0 && interv[c-1].first==interv[head].first)
		ptrs.pb(mp(interv[head].first, head));
	else 
		ptrs.pb(mp(interv[head].second, head));
	deb(ptrs)
	for(auto p : ptrs) print(p.first+p.second);
	bool borderL = (ptrs[0].first + ptrs[0].second)==0;
	bool borderR = (ptrs[ptrs.size()-1].first + ptrs[ptrs.size()-1].second)==n+m-1;
	deb(borderL)
	deb(borderR)
	int numC = ptrs.size()*2 + 1 - borderL - borderR;
	deb(numC)
	int ugliness = numC-1;
	int beauty = n + m -1 -ugliness;
	print(beauty);
}



/*

beauty = n-1 - (#1c + #0c - 1)
ugliness = #1c + #0c - 1

#1c and #0c are closely related

to consider s<=m<=t

we don't want to move a bit in s if it's in component, else we move it. 

10111011000
00111011001

given si, ti, we know that the bit can be in [si,ti].

if we add i to that [si-i, ti-i]
a common point of intersection of these intervals mean they can cnogregate together

we want as few intersection point as possible. 



[0,1]
[1,1]
[1,2]

the intervals look like they will be ordered.




*/