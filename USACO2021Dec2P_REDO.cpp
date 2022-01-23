#include<bits/stdc++.h>

#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define mp make_pair
#define pb push_back
#define mt make_tuple
#define print(x) cout<<x<<endl
#define inf 5000000000LL

llong T, N, K, GN, HN;
llong total;
vector<pair<llong,llong>> Gs, Hs;

bool cond(llong i, llong j){
	return abs(Gs[i].first - Hs[j].first)<=K;
}

void solve1(){
	// just compute maximal matching
	vector<vector<llong>> dp(GN+2, vector<llong>(HN+2,0));
	// track the maximal match value

	for(llong i=0;i<=GN;i++){
		for(llong j=0;j<=HN;j++){
			if(cond(i+1, j+1))
				dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j]+Gs[i+1].second+Hs[j+1].second); // pairing i+1, j+1
			dp[i+1][j] = max(dp[i+1][j], dp[i][j]); // just skipping i+1
			dp[i][j+1] = max(dp[i][j+1], dp[i][j]); // just skipping j+1
		}
	}
	print(total-dp[GN][HN]);
}

void solve2(){
	// precompute ki, kj
	// ki gives the location of nxt j that is outside of K shadow
	// how to we check pairing is possible?
	// given i, j, check if i+k, j+k is valid pair and for how long it needs until j+k is out of range of i. 
	// given each unique value of i-j, we can compute it by rolling. 
	vector<vector<llong>> ki(GN+3, vector<llong>(HN+3, inf)); // min k is 0
	for(llong p = -HN; p<=GN; p++){ //  p=i-j
		llong k = 0, jk = 1; // note down very precisely what each piece of code does!
		for(llong j=1;j<=HN;j++){
			llong i = p+j;
			if(i<=1 || i>GN) continue;
			if(Hs[j].first>Gs[i-1].first+K) {
				ki[i][j]=0;
				continue;
			}
			jk = max(jk,j);
			bool suc = true;
			while(jk<=HN && i+jk-j<=GN && Hs[jk].first<=Gs[i-1].first+K){
				k = jk - j;
				if(!cond(i+k,jk)) {suc = false; break;}
				jk++;
			}
			if(!suc){j = jk; continue;}
			if(jk>HN || Hs[jk].first>Gs[i-1].first+K){
				k = jk - j;
				ki[i][j] = k;
			}
		}

	}

	vector<vector<llong>> kj(GN+3, vector<llong>(HN+3, inf));
	for(llong p = -GN; p<=HN; p++){ //  p=j-i
		llong k = 0, ik = 1;
		for(llong i=1;i<=GN;i++){
			llong j = p+i;
			if(j<=1 || j>HN) continue;
			if(Gs[i].first>Hs[j-1].first+K){
				kj[i][j]=0;
				continue;
			}
			bool suc = true;
			ik = max(ik,i);
			while(ik<=GN && j+ik-i<=HN && Gs[ik].first<=Hs[j-1].first+K){
				k = ik - i;
				if(!cond(ik,j+k)) {suc = false; break;}
				ik++;
			}
			if(!suc){i = ik; continue;}
			if(ik>GN || Gs[ik].first>Hs[j-1].first+K){
				k = ik - i;
				kj[i][j] = k;
			}
		}

	}

	//deb(ki)
	//deb(kj)
	vector<vector<vector<llong>>> dp(GN+2, vector<vector<llong>>(HN+2, vector<llong>(3,-inf)));

	dp[0][0][0] = 0;
	dp[0][0][1] = 0;
	dp[0][0][2] = 0;

	for(llong i=1;i<=GN;i++) dp[i][0][1] = dp[i-1][0][1] + Gs[i].second;
	for(llong j=1;j<=HN;j++) dp[0][j][2] = dp[0][j-1][2] + Hs[j].second;
	dp[0][0][1] = -inf;
	dp[0][0][2] = -inf;
	// this should keep the max weights of 0s
	for(llong i=0;i<=GN;i++){
		for(llong j=0;j<=HN;j++){
            if(i+1<=GN && j+1<=HN && cond(i+1,j+1))
            	dp[i+1][j+1][0] = max(dp[i+1][j+1][0],dp[i][j][0]); // pair

			// skip i+1
            if(i+1<=GN)
			    dp[i+1][j][1] = max(dp[i+1][j][1],dp[i][j][0]+Gs[i+1].second);
			// skip i+1, decay effect terminates
			llong k = max(0LL,ki[i+2][j+1]);
            if(j+k<=HN && i+1+k<=GN)
			    dp[i+1+k][j+k][0] = max(dp[i+1+k][j+k][0],dp[i][j][0]+Gs[i+1].second); 

			// skip j+1
            if(j+1<=HN)
			    dp[i][j+1][2] = max(dp[i][j+1][2],dp[i][j][0]+Hs[j+1].second);
			k = max(0LL,kj[i+1][j+2]);
            if(i+k<=GN && j+1+k<=HN)
			    dp[i+k][j+1+k][0] = max(dp[i+k][j+1+k][0],dp[i][j][0]+Hs[j+1].second);

			// ------------
            if(i+1<=GN && j+1<=HN && cond(i+1,j+1))
			    dp[i+1][j+1][1] = max(dp[i+1][j+1][1],dp[i][j][1]);
			// skip i+1
            if(i+1<=GN)
			    dp[i+1][j][1] = max(dp[i+1][j][1],dp[i][j][1]+Gs[i+1].second);
			// skip i+1 update decay
			k = max(0LL,ki[i+2][j+1]);
            if(i+1+k<=GN && j+k<=HN)
			    dp[i+1+k][j+k][0] = max(dp[i+1+k][j+k][0],dp[i][j][1]+Gs[i+1].second);

			// ------------
            if(i+1<=GN && j+1<=HN && cond(i+1,j+1))
			    dp[i+1][j+1][2] = max(dp[i+1][j+1][2],dp[i][j][2]);
			// skip j+1
            if(j+1<=HN)
			    dp[i][j+1][2] = max(dp[i][j+1][2],dp[i][j][2]+Hs[j+1].second);
			// skip j+1 update decay
			k = max(0LL,kj[i+1][j+2]);
            if(i+k<=GN && j+1+k<=HN)
			    dp[i+k][j+1+k][0] = max(dp[i+k][j+1+k][0],dp[i][j][2]+Hs[j+1].second);
		}
	}
	deb(dp)
	deb(dp[GN][HN])
	llong mx = max({dp[GN][HN][0], dp[GN][HN][1], dp[GN][HN][2]});
	print(mx);
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> T >> N >> K;
	total = 0;
	for(llong i=0;i<N;i++){
		char c; llong x, v;
		cin >> c >> x >> v;
		if(c=='G'){
			Gs.pb(mp(x,v));
		}else{
			Hs.pb(mp(x,v));
		}
		total += v;
	}
	Gs.pb(mp(-1,-1));
	Hs.pb(mp(-1,-1));
	sort(Gs.begin(), Gs.end());
	sort(Hs.begin(), Hs.end());
	GN = Gs.size()-1;
	HN = Hs.size()-1;
	if(GN==0){
		print(total);
		return 0;
	}
	if(HN==0){
		print(total);
		return 0;
	}
	if(T==1) solve1();
	else solve2();
}










