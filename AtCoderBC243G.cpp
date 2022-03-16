#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define mt make_tuple
#define print(x) cout<<x<<endl
#define inf 1000000000000000LL

const llong RANGE = 10000000;
const llong R2 = RANGE*RANGE;
vector<llong> prefix;
vector<llong> sol;

llong solve(llong x){
	if(x <= RANGE) return sol[x];
	if(x <= R2){
		llong sq = sqrt((long double)x);
		if((sq+1)*(sq+1) == x) sq++; // misrounding
		return prefix[sq];
	}
	llong sq = sqrt((long double)x);
	if((sq+1)*(sq+1) == x) sq++; // misrounding
	llong total = prefix[100489-1];
	for(llong i=317;i<=sqrt((long double)sq)+1;i++){ // fall in range [100489,sq]
		if(i*i > sq) break;
		llong r = min(sq+1,(i+1)*(i+1))-i*i;
		// [i^2, (i+1)^2-1]
		total += r*prefix[i];
	}
	return total;
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	prefix = vector<llong>(RANGE+1,0);
	sol = vector<llong>(RANGE+1,0);
	prefix[1] = 1;
	sol[1] = 1;
	for(llong i=2;i<=RANGE;i++){
		llong sq = sqrt((long double)i);
		if((sq+1)*(sq+1) == i) sq++; // misrounding
		sol[i] = prefix[sq];
		prefix[i] = prefix[i-1]+sol[i];
	}


	llong tt; cin >> tt;
	while(tt--){
		llong x; cin >> x;
		llong ret = solve(x);
		print(ret);
	}
}