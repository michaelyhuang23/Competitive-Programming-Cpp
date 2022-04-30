#include<bits/stdc++.h>

using namespace std;
typedef long long llong;
#define mp make_pair
#define print(x) cout<<x<<endl
#define inf 1000000000000LL

void solve(){
	int n; cin >> n;
	int ll = 1, rr = 1000000000, W = 1;
	llong minA = inf;
	
	auto query = [&](int w){
		cout<<"? "<<w<<endl;
		cout.flush();
		int h; cin >> h;
		return h;
	};

	while(ll<=rr){
		int mid = (ll+rr)/2;
		int h = query(mid);
		if(h == 0) {ll=mid+1; continue;}
		minA = min(minA, (llong)h * mid);
		if(h==1) {W = mid; rr = mid-1;}
		else ll = mid+1;
	}

	for(int hi=2;hi<=n;hi++){
		int w = W/hi;
		int h = query(w);
		if(h==0) continue;
		minA = min(minA, (llong)h * w);
	}

	cout<<"! "<<minA<<endl;
}





int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}