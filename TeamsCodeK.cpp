#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000
#define print(x) cout<<x<<endl

int n,m,k;
vector<int> primes;

void gen_primes(){
	auto check_prime = [&](int p){
		for(int prime : primes){
			if(prime * prime > p) break;
			if(p%prime == 0) return false;
		}
		return true;
	};
	for(int i=1;i*6-1<=m;i++){
		if(check_prime(i*6-1)) primes.pb(i*6-1);
		if(i*6+1<=m && check_prime(i*6+1)) primes.pb(i*6+1);
	}
}

void solve(){
	cin >> n >> m >> k;
	primes = {2,3};

	gen_primes();


	
}








int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}