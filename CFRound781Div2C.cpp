#include<bits/stdc++.h>


using namespace std;
#define print(x) cout<<x<<endl

int n;
vector<int> deg;

bool check(int t){
	int ct = 0;
	vector<int> times(n+1,0);
	for(int i=0;i<=n;i++){
		if(deg[i]==0) continue;
		deg[i] = deg[i];
		times[i] = ct;
		ct++; //  injection
	}
	if(ct > t) return false;

	for(int i=0;i<=n;i++){
		if(deg[i]==0) continue;
		if(deg[i] + times[i] <= t) continue;
		int nc = t - times[i];
		ct += deg[i] - nc;
	}

	if(ct > t) return false;
	return true;
}


void solve(){
	cin >> n;
	deg = vector<int>(n,0);
	for(int i=0;i<n-1;i++){
		int a; cin >> a; a--;
		deg[a]++;
	}

	deg.push_back(1);
	sort(deg.rbegin(), deg.rend());


	int ll=0, rr=n, ans = 0; // we want minimal time
	while(ll<=rr){
		int mid = (ll+rr)/2;
		if(check(mid)) {ans = mid; rr = mid-1;}
		else ll = mid+1;
	}

	print(ans);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--) solve();
}