#include<bits/stdc++.h>

using namespace std;
#define print(x) cout<<x<<endl



void solve(){
	int l, r, a; cin >> l >> r >> a;

	int top = (r+1)/a-1;
	if((r+1)/a != (l)/a) // cross a
		print(top + a-1);
	else // fit into 1 a
		print(r/a + r%a);

}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--) solve();
}