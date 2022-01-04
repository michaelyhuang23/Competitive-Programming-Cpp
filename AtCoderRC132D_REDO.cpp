#include<iostream>
#include<vector>
#include<set>
#include<bitset>
#include<algorithm>
#include<assert.h>

//#include "debughelp.hpp"

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
	string s, t; cin >> s; cin >> t;
	vector<int> a(n+m,0), b(n+m,0);
	if(s[0]=='0') a[0]=1; 
	if(t[0]=='0') b[0]=1;
	for(int i=1;i<n+m;i++) if(s[i]=='0') a[i] = a[i-1]+1; else a[i] = a[i-1];
	for(int i=1;i<n+m;i++) if(t[i]=='0') b[i] = b[i-1]+1; else b[i] = b[i-1];
	// start with 0
	int maxB = 0;
	if(a[0]==1 || b[0]==1){
		vector<bool> result;
		int cur = 0;
		int swap = 0;
		int c0 = 1;
		result.pb(0);
		for(int i=1;i<n+m;i++){
			if(cur==0){
				if(c0+1 <= max(a[i],b[i])) {c0++; result.pb(0);}
				else {cur=1; swap++; result.pb(1);}
			}else{
				if(c0>=min(a[i],b[i])) {result.pb(1);}
				else {cur=0; swap++; c0++; result.pb(0);}
			}
		}
		// for(int i=0;i<n+m;i++) cout<<result[i];
		// cout<<endl;
		maxB = max(maxB, n+m-1-swap);
	}

	if(a[0]==0 || b[0]==0){
		vector<bool> result;
		int cur = 1;
		int swap = 0;
		int c0 = 0;
		result.pb(1);
		for(int i=1;i<n+m;i++){
			if(cur==0){
				if(c0+1 <= max(a[i],b[i])) {c0++; result.pb(0);}
				else {cur=1; swap++; result.pb(1);}
			}else{
				if(c0>=min(a[i],b[i])) {result.pb(1);}
				else {cur=0; swap++; c0++; result.pb(0);}
			}
		}
		// for(int i=0;i<n+m;i++) cout<<result[i];
		// cout<<endl;
		maxB = max(maxB, n+m-1-swap);
	}
	print(maxB);
}