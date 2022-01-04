#include<vector>
#include<algorithm>
#include<iostream>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define mt make_tuple

int N, K, Q, C;
bool mat[60][60];

llong dp[62][3600];
llong paths[62][3600]; //2nd dim is number of vertices

llong Pow(llong num, int pow){
	if(pow==0) return 1;
	if(pow%2==0){
		llong inter = Pow(num, pow/2);
		return ((inter*inter)%MOD+MOD)%MOD;
	}else{
		return ((Pow(num, pow-1)*num)%MOD+MOD)%MOD;
	}
}

llong inverse(llong num){
	return Pow(num, MOD-2);
}

llong choose(llong n, llong k){
	llong numer = 1;
	for(llong i=n; i>=n-k+1; i--) numer=((numer*i)%MOD+MOD)%MOD;
	llong denom = 1;
	for(llong i=k; i>=1; i--) denom=((denom*inverse(i))%MOD+MOD)%MOD;
	return ((numer*denom)%MOD+MOD)%MOD;
}

void button(int bs, int bt){
	for(int k=0;k<62;k++) fill(dp[k],dp[k]+C,0); // only works when len >=2
	dp[K+1][0] = 1;
	// this is N^5!!!
	int end = 0;
	for(int k = K; k>=1; k--){
		int cend = 0;
		if(k == bs){ // afterwards, there should not allowed fringe
			end++;cend++;
		}
		if(k == bt){ // could be both
			end++;cend++;
		}
		for(int cp=0;cp<C;cp++){
			for(int c=0;c<=cp+1-end && c+cp+cend<C;c++){
				dp[k][cp+c+cend] += (dp[k+1][cp]*choose(cp+1-end,c))%MOD;
				dp[k][cp+c+cend] %= MOD;
			}
		}
	}
	// for(int k=K; k>=1; k--) {
	// 	for(int c=1;c<C;c++) cout<<dp[k][c]<<" ";
	// 	cout<<endl;
	// }
} // very questionable

void find_path(int s, int t){
	// init
	for(int i=0;i<N;i++) fill(paths[i], paths[i]+C, 0);
	paths[s][1] = 1; // this is N^4!!! 
	for(int t=2; t<C; t++){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				if(!mat[i][j]) continue;
				paths[j][t] += paths[i][t-1];
				paths[j][t] %= MOD;
			}
		}			
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> K >> Q;
	C = K*K;
	for(int i=0;i<N;i++){
		string ss; cin >> ss;
		for(int j=0;j<N;j++) mat[i][j] = ss[j]-'0';
	}
	for(int i=0;i<Q;i++){
		int bs, bt, s, t;
		cin >> bs >> s >> bt >> t;
		s--; t--;
		button(bs,bt);
		find_path(s,t);
		llong count = 0;
		for(int i=2;i<C;i++){
			// deb(i)
			// deb(dp[1][i]) deb(paths[t][i])
			count += (dp[1][i] * paths[t][i])%MOD;
			count %= MOD;
		}
		if(bs == bt && s == t) count++; // for i==1
		count%=MOD;
		cout<<count<<endl;
	}
}
