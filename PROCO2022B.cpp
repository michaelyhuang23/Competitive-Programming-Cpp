#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define inf 1000000000
#define print(x) cout<<x<<endl
#define MOD 998244353LL

llong power(llong base, llong pow){
	if(pow == 0) return 1;
	if(pow%2==1) return power(base, pow-1)*base;
	llong inter = power(base, pow/2);
	return inter*inter;
}

void solve(){
	llong k, m; cin >> k >> m;
	string s1, s2;
	cin >> s1 >> s2;

	llong n1 = 0;
	for(llong i=0;i<s1.size();i++){
		llong num = s1[s1.size()-1-i]-'0';
		n1+=power(k, i)*num;
	}

	llong n2 = 0;
	for(llong i=0;i<s2.size();i++){
		llong num = s2[s2.size()-1-i]-'0';
		n2+=power(m, i)*num;
	}

	print(n1-n2);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}