#include<bits/stdc++.h>

using namespace std;
typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000000000LL;
#define print(x) cout<<x<<endl

llong n,a,b;
vector<llong> arr;
vector<llong> psum;
const llong D = 43;

void solve_permute(){
	arr = vector<llong>(n);
	for(llong i=0;i<n;i++) cin>>arr[i];


	llong minn = inf;
	for(llong x=a;x<=b;x++){
		llong maxS=1<<(n-1);
		llong k = x-1;
		for(llong s=0;s<maxS;s++){
			llong cc = __builtin_popcount(s);
			if(cc != k) continue;
			llong ps = 0;
			vector<llong> sums;
			for(llong b=0;b<n;b++){
				ps += arr[b];
				if(s & (1<<b)){
					sums.pb(ps);
					ps = 0;
				}
			}
			assert(ps!=0);
			sums.pb(ps);
			assert(sums.size() == x);
			llong total = 0;
			for(llong v : sums) total |= v;
			minn = min(minn, total);
		}
	}
	print(minn);
}


void solve(){
	cin >> n >> a >> b;

	solve_permute();
}




int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}