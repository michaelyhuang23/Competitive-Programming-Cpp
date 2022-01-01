#include<iostream>
#include<assert.h>
#include<vector>

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl

void solve(){
	int n, m, rb, cb, rd, cd;
	cin >> n >> m >> rb >> cb >> rd >> cd;
	if(rb==rd || cb==cd) {
		print(0); return;
	}
	if(rd > rb && cd > cb){
		print(min(rd-rb, cd-cb));
		return;
	}
	if(rd<rb && cd<cb){
		print(min(n-rb + n-rd, m-cb + m-cd));
		return;
	}
	if(rd<rb && cd>cb){
		print(min(n-rb + n-rd,cd-cb)); return;
	}
	if(rd>rb && cd<cb){
		print(min(rd-rb, m-cb + m-cd)); return;
	}
	assert(false);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--){
		solve();
	}
}