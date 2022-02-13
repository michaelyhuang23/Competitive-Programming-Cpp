#include<bits/stdc++.h>

#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define MOD 998244353LL
#define print(x) cout<<x<<endl

struct mint{
	llong x;
	mint(llong x_) : x(x_) { correct(); }
	void correct(){ x = (x+MOD)%MOD; }
	mint power(llong pow) {
		if(pow==0) return mint(1);
		if(pow%2==0){
			mint inter = power(pow/2);
			return inter*inter;
		}else{
			return (*this)*(power(pow-1)); 
		}
	}

	mint inverse() {
		if(x==2) return mint(499122177);
		if(x==499122177) return mint(2);
		return power(MOD-2);
	}

	mint operator+(mint other){ return mint(x+other.x); }
	mint operator-(mint other){ return mint(x-other.x); }
	mint operator*(mint other){ return mint(x*other.x); }
	mint operator/(mint other){ mint invert = other.inverse(); return (*this)*(invert); }
};

ostream& operator <<( ostream& os, const mint& p ) {
	return os << p.x;
}

void solve(){
	llong N; cin >> N;
	vector<llong> probs(N+1,0);
	for(llong i=1;i<=N;i++) cin >> probs[i];


	auto ringContract = [&](){
		vector<vector<mint>> dp(N+1,vector<mint>(N+1,0));
		// number of mouse, interested in ith mouse : probability of it surviving
		dp[1][1] = mint(1);
		for(llong n=2;n<=N;n++){
			for(llong i=1;i<=n;i++){
				for(llong k=1;k<=n;k++){ // first mouse to be killed, we will contract it
					if(k==i) continue;
					llong previ = 0;
					if(i>k) previ = i-k;
					else previ = n-(k-i)-1+1;
					mint probPass = mint(1)/mint(2).power(n-1);
					mint prob = probPass.power(k-1)*(mint(1)-probPass);
					mint probLoopOnce = probPass.power(n);
					mint probLoopAll = mint(1)/(mint(1)-probLoopOnce);
					deb(mt(probPass, probLoopOnce, n))
					prob = prob * probLoopAll;
					deb(mp(i,k))
					deb(mt(n, previ, prob))
					dp[n][i] = dp[n][i] + dp[n-1][previ]*prob;
				}
			}
		}
		return dp;
	};

	vector<vector<mint>> dp = ringContract();

	deb(dp)


}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}

