#include<iostream>
#include<assert.h>
#include<vector>
#include<unordered_set>
#include<algorithm>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl


int n;
vector<llong> stones;

bool check(llong mid){
	vector<llong> add(n,0);
	for(int i=n-1;i>=2;i--){
		if(stones[i] + add[i]<mid) return false;
		llong d = (stones[i]+add[i]-mid)/3;
		d = min(stones[i]/3, d);
		add[i-1] += d;
		add[i-2] += 2*d;
	}
	if(stones[0] + add[0]<mid) return false;
	if(stones[1] + add[1]<mid) return false;
	return true;
}

void solve(){
	cin >> n;
	stones = vector<llong>(n);
	for(int i=0;i<n;i++) cin >> stones[i];
	llong ll = 1, rr = 1000000000, ans = 0;
	while(ll<=rr){
		llong mid = (ll+rr)/2;
		if(check(mid)) {ans=mid; ll=mid+1;}
		else rr=mid-1;
	}
	print(ans);
}

int main(){
	int tt; cin >> tt;
	while(tt--) solve();
}