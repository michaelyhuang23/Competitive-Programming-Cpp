#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define inf 1000000000
#define print(x) cout<<x<<endl
#define MOD 998244353LL



string S;

vector<llong> power2;

char nextChar(char A){
	if(A=='A') return 'B';
	if(A=='B') return 'C';
	if(A=='C') return 'A';
	return -1;
}

char query(llong t, llong x, char L, char R){

	llong range = power2[t];
	llong steps = max(0LL, (x-1)/range);
	if(t==0){
		if(steps==0) return L;
		if(steps==1) return R;
		assert(false);
	}

	if(steps==0)
		return query(t-1, x, nextChar(L), nextChar(nextChar(L)));
	if(steps==1)
		return query(t-1, x-range, nextChar(R), nextChar(nextChar(R)));
	assert(false);
}

pair<llong,char> reduce(llong t, char A){
	if(t<63) return mp(t, A);
	llong ft = 62;
	llong diff = t-ft;
	char FA = (A-'A'+diff)%3 + 'A';
	return mp(ft, FA);
}

void solve(){
	cin >> S;
	llong Q; cin >> Q;
	while(Q--){
		llong t, x; cin >> t >> x;
		if(t==0) {
			print(S[x-1]);
			continue;
		}
		if(t>=63){
			char A = S[0];
			auto ret = reduce(t, A);
			t = ret.first;
			A = ret.second;
			char F = query(t, x, A, nextChar(A));
			print(F);
			continue;
		}
		llong range = power2[t]; // 63 covers x guaranteed
		llong steps = max(0LL,(x-1)/range);
		char A = S[steps];
		char F = query(t-1, x - steps*range, nextChar(A), nextChar(nextChar(A)));
		print(F);
	}
}

int main(){
	power2 = vector<llong>(63,1);
	for(llong i=1;i<=62;i++) power2[i] = power2[i-1]*2LL;
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}