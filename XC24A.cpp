#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define MOD 998244353LL
#define print(x) cout<<x<<endl

llong power(llong num, int pow){
	if(pow==0) return 1;
	if(pow&1) return (num*power(num, pow-1))%MOD;
	else{
		llong inter = power(num, pow/2);
		return (inter*inter)%MOD;
	}
}

llong invert(llong val){
	return power(val, MOD-2);
}

llong choose(llong n, llong k){
	if(n-k < k) k = n-k;
	llong numer = 1;
	for(llong i = n; i > n-k; i--){
		numer *= i;
		numer %= MOD;
	}
	llong denom = 1;
	for(llong i = 1; i <= k; i++){
		denom *= i;
		denom %= MOD;
	}
	llong result = numer * invert(denom);
	result %= MOD;
	return result;
}


void solve(){
	int N, K; cin >> N >> K;
	vector<llong> arr(N);
	for(int i=0;i<N;i++) cin >> arr[i];

	llong top = arr[0];
	llong rest = 0;
	for(int i=1;i<N;i++) rest += arr[i];
	llong add = top - rest - K;
	if(add < 0){
		print(0);
		return;
	}
	
	vector<llong> combos(N,0);
	combos[0] = choose(add+K-1,K-1);
	for(int i=1;i<N;i++){
		combos[i] = choose(arr[i]+K-1,K-1);
	}

	llong total = 1;
	for(int i=0;i<N;i++){
		total *= combos[i];
		total %= MOD;
	}

	print(total);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}