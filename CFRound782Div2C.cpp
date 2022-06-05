#include<bits/stdc++.h>

using namespace std;
typedef long long llong;
#define pb push_back
#define mp make_pair
#define print(x) cout<<x<<endl;
#define inf 100000000000000000LL

llong n, a, b;
vector<llong> locs; // change to ll for security
vector<llong> sufdist;
void solve(){
	cin >> n >> a >> b;
	locs = vector<llong>(n+1,0);
	for(llong i=0;i<n;i++) cin >> locs[i+1];
	sufdist = vector<llong>(n+1,0);
	
	for(llong i=n-1;i>=0;i--){
		sufdist[i] = sufdist[i+1]+(n+1-1-i)*(locs[i+1]-locs[i]);
	} 

	
	llong minC = inf;

	for(llong i=0;i<=n;i++){
		llong movec = (locs[i]-locs[0])*a;
		llong conqc = (locs[i]-locs[0])*b;
		conqc += sufdist[i]*b;

		llong totalc = movec + conqc;

		minC = min(minC, totalc);
	}

	print(minC);
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong tt; cin >> tt;
	while(tt--)
		solve();
}