#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
typedef long double ddouble;
#define mt make_tuple
#define print(x) cout<<x<<endl
#define inf 1000000000LL
#define MOD 998244353LL

struct mint{
	llong x;
	mint() : x(0) {}
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


// struct mint{
// 	ddouble x;
// 	mint() : x(0) {}
// 	mint(ddouble x_) : x(x_) { correct(); }
// 	void correct(){ x = x; }
// 	mint power(llong pow) {
// 		if(pow==0) return mint(1);
// 		if(pow%2==0){
// 			mint inter = power(pow/2);
// 			return inter*inter;
// 		}else{
// 			return (*this)*(power(pow-1)); 
// 		}
// 	}

// 	mint inverse() {
// 		return mint(1.0/x);
// 	}

// 	mint operator+(mint other){ return mint(x+other.x); }
// 	mint operator-(mint other){ return mint(x-other.x); }
// 	mint operator*(mint other){ return mint(x*other.x); }
// 	mint operator/(mint other){ mint invert = other.inverse(); return (*this)*(invert); }
// };


ostream& operator <<( ostream& os, const mint& p ) {
	return os << p.x;
}


mint choose(int n, int k){
	if(k>n) return mint(0);
	mint total = 1;
	for(int i=n;i>k;i--){
		total = total * mint(i);
	}
	mint den = 1;
	for(int i=n-k;i>=1;i--){
		den = den * i;
	}
	return total / den;
}

mint power(mint num, int p){
	if(p == 0) return 1;
	if(p % 2 == 0){
		mint inter = power(num, p/2);
		return inter*inter;
	}
	return num * power(num, p-1);
}

void solve(){
	int n, m, k; cin >> n >> m >> k;
	vector<mint> weights(n+1);
	mint totalW = 0;
	for(int i=1;i<=n;i++){
		int w; cin >> w;
		weights[i] = w;
		totalW = totalW + w;
	}

	vector<mint> props(n+1), prefix(n+1);
	for(int i=1;i<=n;i++) props[i] = weights[i]/totalW;
	for(int i=1;i<=n;i++) prefix[i] = prefix[i-1] + props[i];

	vector<vector<vector<mint>>> dp(n+1, vector<vector<mint>>(m+1, vector<mint>(k+1)));
	dp[0][0][0] = 1;
	// let's do the selection process as follows:
	// we rank the k selections by the index they select
	// dp records: upto the ith index, we have selected m unique elements
	// we have select l elements (there're k-l left in the rest of the items)
	// what is the probability 

	for(int i=1;i<=n;i++){
		for(int l=0;l<=k;l++){
			for(int j=0;j<=min(m,l);j++){
				if(l>0 && j==0) continue;
				for(int p=0;p<=l;p++){
					// we want to choose p at current i
					mint suf = prefix[n]-prefix[i-1];
					mint pi = props[i]/suf;
					mint Pchosen = choose(k-l+p,p)*power(pi, p)*power(mint(1)-pi, k-l);
					if(p == 0) dp[i][j][l] = dp[i][j][l] + dp[i-1][j][l]*Pchosen;
					else if(j>0) dp[i][j][l] = dp[i][j][l] + dp[i-1][j-1][l-p]*Pchosen;
				}				
			}
		}
	}

	print(dp[n][m][k]);
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}