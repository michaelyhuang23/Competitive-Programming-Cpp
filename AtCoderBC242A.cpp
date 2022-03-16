#include<bits/stdc++.h>

using namespace std;

typedef long double ddouble;
#define pb push_back
#define mp make_pair
#define inf 1000000000
#define print(x) cout<<setprecision(16)<<x<<endl


void solve(){
	int A, B, C, X;
	cin >> A >> B >> C >> X;
	if(X<=A) print(1);
	else if(X<=B) print((ddouble)C/(B-A));
	else print(0);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}