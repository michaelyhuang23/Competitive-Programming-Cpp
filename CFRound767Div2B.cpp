#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define print(x) cout<<x<<endl

void solve(){
	llong l, r, k; cin >> l >> r >> k;
	if(l==r){
		if(l==1) print("NO");
		else print("YES");
		return;
	} 
	llong fac2 = (r-l+1)/2;
	if((r-l+1) % 2 == 1 && l%2 == 0) fac2++;
	llong nfac2 = r-l+1-fac2;
	//print(nfac2);
	if(nfac2<=k) print("YES");
	else print("NO");
}

int main(){
	int tt; cin >> tt;
	while(tt--) solve();
}