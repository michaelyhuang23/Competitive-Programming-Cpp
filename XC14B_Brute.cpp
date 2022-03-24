

// #pragma GCC optimize("O3")
// #pragma GCC target("avx2") 
#include<bits/stdc++.h>

using namespace std;
typedef long long llong;
#define inf 2000000005000000LL
#define pb push_back
#define mp make_pair
#define mt make_tuple



void solve(){
	llong n, q; cin >> n;
	vector<llong> C(n);
	for(llong i=0;i<n;i++) cin>>C[i];
	cin >> q;
	vector<llong> vals(n,0);
	for(llong i=0;i<q;i++){
		llong l,r,v; cin >> l >> r >> v;
		for(llong j=l;j<=r;j++) {
			vals[j]+=v;
			vals[j] = min(vals[j],C[j]);
			vals[j] = max(vals[j],0LL);
		}
	}

	for(llong i=0;i<n;i++) cout<<vals[i]<<" ";
		cout<<endl;
}




















int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	// fread(Buf,1,BUFSIZE,stdin); 
	solve();
}