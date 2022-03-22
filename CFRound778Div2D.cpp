// #include "debughelp.hpp"

#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define print(x) cout<<x<<endl
#define mt make_tuple
#define pb push_back
#define mp make_pair
#define inf 1000000000
#define MOD 998244353


int n;
vector<vector<tuple<int,int,int>>> adj;
vector<int> maxPrime;

llong power(llong base, int pow){
	if(pow == 0) return 1;
	if(pow % 2 == 0){
		llong inter = power(base, pow/2);
		return (inter*inter)%MOD;
	}else{
		return (power(base, pow-1)*base)%MOD;
	}
}

llong inv(llong num){
	return power(num, MOD-2);
}

struct Fraction {
	unordered_map<int,int> maxDP;
	unordered_map<int,int> numerP;
	unordered_map<int,int> denomP;
	llong numerQ;
	Fraction() : numerQ(1) {}
	Fraction(unordered_map<int,int>& numer) {
		numerP = numer;
		numerQ = 1;
		for(auto& item : numerP){
			int p = item.first;
			int c = item.second;
			numerQ *= power(p,c);
			numerQ %= MOD;
		}
	}
	void mul(int numer, int denom){
		while(numer > 1){
			int p = maxPrime[numer];
			if(p==1) break;
			if(denomP.find(p)==denomP.end()) {
				if(numerP.find(p)==numerP.end()) numerP[p]=1;
				else numerP[p]++;
				numerQ *= p;
				numerQ %= MOD;
			}else {
				denomP[p]--;
				if(denomP[p]==0) denomP.erase(p);
			}
			numer /= p;
		}

		while(denom > 1){
			int p = maxPrime[denom];
			if(p==1) break;
			if(numerP.find(p)==numerP.end()) {
				if(denomP.find(p)==denomP.end()) denomP[p]=1;
				else denomP[p]++;
				if(maxDP.find(p)==maxDP.end()) maxDP[p]=1;
				else maxDP[p]=max(maxDP[p],denomP[p]);
			}else {
				numerP[p]--;
				numerQ *= inv(p);
				numerQ %= MOD;
				if(numerP[p]==0) numerP.erase(p);
			}
			denom /= p;
		}

		
	}
	// void mul(unordered_map<int,int>& x){
	// 	for(auto& item : x){
	// 		int p = item.first;
	// 		int c = item.second;
	// 		if(numerP.find(p) == numerP.end()){
	// 			numerP[p]=c;
	// 		}else{
	// 			numerP[p]+=c;
	// 		}
	// 	}
	// 	reduce();
	// }


};



void preprocess(){
	maxPrime=vector<int>(200001,1);
	for(int i=2; i<200001; i++){
		if(maxPrime[i]==1)
			for(int p=1; p*i<200001; p++)
				maxPrime[p*i] = i;
	}
}

// void merge(unordered_map<int,int>& m1, unordered_map<int,int> m2){
// 	for(auto& item : m2){
// 		int p = item.first;
// 		int c = item.second;
// 		if(m1.find(p) == m1.end()){
// 			m1[p]=c;
// 		}else{
// 			m1[p]=max(m1[p],c);
// 		}
// 	}
// }


void dfs(int cur, int par, Fraction& ratio){
	for(auto& edge : adj[cur]){
		int son = get<0>(edge);
		if(son == par) continue;
		int numer = get<1>(edge);
		int denom = get<2>(edge);
		ratio.mul(numer, denom);
		dfs(son, cur, ratio);
		ratio.mul(denom, numer);
	}
}


llong total = 0;


void dfs_count(int cur, int par, Fraction& ratio){
	assert(ratio.denomP.size()==0);
	total += ratio.numerQ;
	total %= MOD;
	for(auto& edge : adj[cur]){
		int son = get<0>(edge);
		if(son == par) continue;
		int numer = get<1>(edge);
		int denom = get<2>(edge);
		ratio.mul(numer, denom);
		dfs_count(son, cur, ratio);
		ratio.mul(denom,numer);
	}
}

void solve(){
	total = 0;
	cin >> n;
	adj = vector<vector<tuple<int,int,int>>>(n);
	for(int id=0;id<n-1;id++){
		int i,j,x,y; cin >> i >> j >> x >> y;
		i--; j--;
		int gc = gcd(x,y);
		x/=gc;
		y/=gc;
		adj[i].pb(mt(j, y, x));
		adj[j].pb(mt(i, x, y));
	}

	Fraction ratio;
	dfs(0,0,ratio);

	Fraction cratio(ratio.maxDP);

	dfs_count(0,0, cratio);



	print(total);
}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	preprocess();

	llong tt; cin >> tt;
	while(tt--)
		solve();
}