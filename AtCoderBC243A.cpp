#include<bits/stdc++.h>

using namespace std;

#define print(x) cout<<x<<endl

void solve(){
	int v, a, b, c; cin >>  v >> a >> b >> c;
	v%=a+b+c;
	if(v<a) print("F");
	else if(v<a+b) print("M");
	else if (v<a+b+c) print("T");
	else assert(false);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}