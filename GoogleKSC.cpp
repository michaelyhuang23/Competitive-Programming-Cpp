// #include "debughelp.hpp"

#include<bits/stdc++.h>

#define pb push_back
#define mp make_pair
using namespace std;



void solve(int id){
	int n; cin >> n;
	string s; cin >> s;
	vector<int> bits(n+1,2);
	for(int i=0;i<s.size();i++){
		if(s[i]=='1')
			bits[i+1] = 1;
		else if(s[i]=='0')
			bits[i+1]=0;
		else 
			bits[i+1]=2;
	}

	// deb(bits)


	if(n<=5){
		int maxS = 1<<n;
		bool total = false;
		for(int s=0;s<maxS;s++){
			bool suc = true;
			// bitset<5> ss(s);
			// deb(ss)
			for(int j=0;j<n;j++){
				if(bits[n-j]==1)
					suc &= (s>>j) & 1;
				else if(bits[n-j]==0)
					suc &= !((s>>j) & 1);
			}
			// deb(suc)
			if(!suc) continue;
			if(n==5){
				bool parl = true;
				for(int j=0;j<2;j++) parl &= ((s>>j)&1) == ((s>>(4-j))&1);
				if(parl) continue;
			}
			total = true;
		}
		if(total)
		cout<<"Case #"<<id<<": POSSIBLE"<<endl;
		else 
		cout<<"Case #"<<id<<": IMPOSSIBLE"<<endl;
		return;
	}


	vector<vector<bool>> dp(n+1, vector<bool>(64, 0));
	// init is tricky

	for(int s=0;s<64;s++){
		bool suc = true;
		for(int j=0;j<6;j++){
			if(bits[6-j]==1)
				suc &= (s>>j) & 1;
			else if(bits[6-j]==0)
				suc &= !((s>>j) & 1);
		}
		if(!suc) continue;
		bool parl = true;
		for(int j=0;j<3;j++) parl &= ((s>>j)&1) == ((s>>(5-j))&1);
		if(parl) continue;
		parl = true;
		for(int j=0;j<2;j++) parl &= ((s>>j)&1) == ((s>>(4-j))&1);
		if(parl) continue;
		parl = true;
		for(int j=1;j<3;j++) parl &= ((s>>j)&1) == ((s>>(6-j))&1);
		if(parl) continue;
		dp[6][s]=true;
	}

	for(int i=7;i<=n;i++){
		for(int s=0;s<64;s++){
			bool suc = true;
			for(int j=0;j<6;j++){
				if(bits[i-j]==1)
					suc &= (s>>j) & 1;
				else if(bits[i-j]==0)
					suc &= !((s>>j) & 1);
			}
			if(!suc) continue;
			bool parl = true;
			for(int j=0;j<3;j++) parl &= ((s>>j)&1) == ((s>>(5-j))&1);
			if(parl) continue;
			parl = true;
			for(int j=0;j<2;j++) parl &= ((s>>j)&1) == ((s>>(4-j))&1);
			if(parl) continue;
			parl = true;
			for(int j=1;j<3;j++) parl &= ((s>>j)&1) == ((s>>(6-j))&1);
			if(parl) continue;

			if(bits[i-6]!=2){
				int ps = s>>1;
				ps |= bits[i-6]<<5;
				dp[i][s] = dp[i-1][ps];
			}else{
				int ps1 = s>>1;
				int ps2 = ps1 | (1<<5);
				dp[i][s] = dp[i-1][ps1] | dp[i-1][ps2];
			}
		}
	}

	bool suc = false;
	for(int s=0;s<64;s++)
		suc = suc | dp[n][s];












	if(suc)
	cout<<"Case #"<<id<<": POSSIBLE"<<endl;
	else 
	cout<<"Case #"<<id<<": IMPOSSIBLE"<<endl;
}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	for(int i=0;i<tt;i++)
		solve(i+1);
}