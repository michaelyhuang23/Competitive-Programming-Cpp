//#include "debughelp.hpp"
#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define MOD 1000000007
#define print(x) cout<<x<<endl


llong pow2(llong power){
	if(power == 0) return 1;
	if(power & 1) return (pow2(power-1)*2)%MOD;
	else {
		llong inter = pow2(power/2);
		return (inter*inter)%MOD;
	}
}

void solve(){

	const llong LX = 1000000;
	const llong k = 6;

	vector<llong> power(8,1);
	for(llong i=1;i<8;i++) power[i]=power[i-1]*10;

	llong n; cin >> n;
	vector<llong> T(n);
	for(llong i=0;i<n;i++) cin >> T[i];

	auto getDigit = [&](llong num, llong d){
		num /= power[d];
		return num - (num/10)*10;
	};

	// test this separately, it should work

	auto suffix_sum = [&](vector<llong>& C){
		for(llong j=0;j<k;j++){
			for(llong i=LX-1;i>=0;i--){
				if(getDigit(i,j) == 9) continue;
				llong x = i+power[j];
				C[i] += C[x];
				C[i] %= MOD;
			}
		}
	};


	vector<llong> C0(LX,0);
	for(llong i=0;i<n;i++) {
		C0[T[i]]++;
		C0[T[i]]%=MOD;
	}
	//deb("C0")
	suffix_sum(C0);

	vector<llong> C1(LX,0);
	for(llong i=0;i<n;i++) {
		C1[T[i]]+=T[i];
		C1[T[i]]%=MOD;
	}
	//deb("C1")
	suffix_sum(C1);

	vector<llong> C2(LX,0);
	for(llong i=0;i<n;i++) {
		C2[T[i]]+=T[i]*T[i];
		C2[T[i]]%=MOD;
	}
	suffix_sum(C2);

	vector<llong> H(LX,0);

	for(llong x=0;x<LX;x++){
		if(C0[x] < 2) {
			H[x] += C2[x];
			H[x] %= MOD;
			continue;
		}
		H[x] = ((C2[x]+C1[x]*C1[x])%MOD)*pow2(C0[x]-2);
		H[x] %= MOD;
	}

	// deb("H")
	// deb(H[999999])
	
	vector<llong> G(LX,0);
	for(llong x=0;x<LX;x++){
		vector<int> digits(k);
		for(int j=0;j<k;j++) digits[j] = getDigit(x,j);
		for(llong i=0;i<(1<<k);i++){
			llong add = 0;
			llong c = __builtin_popcount(i);
			bool suc = true;
			for(llong j=0;j<k;j++){
				if(!(i & (1<<j))) continue;
				if(digits[j] == 9) {suc=false;break;}
				add += power[j];
			}
			if(!suc) continue;
			llong nx = x + add;
			if(c & 1){
				G[x] -= H[nx];
			}else{
				G[x] += H[nx];
			}
			G[x] = (G[x] + MOD)%MOD;
		}
	}

	//deb(G[999999])

	for(llong x=0;x<LX;x++) G[x] *= x;

	llong total = 0;
	for(llong x=0;x<LX;x++) total ^= G[x];
	print(total);
}
















int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}




