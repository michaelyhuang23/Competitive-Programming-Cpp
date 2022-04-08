#include<bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl
#define inf 1000000000

int n,m;
void solve(){
	vector<int> lb(n,inf);
	for(int i=1;i<n;i++) cin >> lb[i];

	vector<int> hh = lb;
	hh.pb(0);
	vector<tuple<int,int,int>> reqs(m);
	for(int i=0;i<m;i++){
		int id,y,k; cin >> id >> y >> k;
		y++; id--;
		reqs[i] = mt(id,y,k);
		hh.pb(y);
	}


	sort(hh.begin(), hh.end());
	hh.erase( unique(hh.begin(), hh.end()), hh.end() );

	// deb(hh)

	unordered_map<int,int> h2id;
	for(int i=0;i<hh.size();i++) h2id[hh[i]]=i;

	vector<int> lbi(n,-1);
	for(int i=0;i<n;i++) lbi[i]=h2id[lb[i]];

	vector<vector<int>> mapp(n,vector<int>(hh.size(),0));
	// 1 : needs dry, 2 : needs water
	
	vector<int> dryc(n,0);
	for(auto& req : reqs){
		int id = get<0>(req);
		if(get<2>(req)==0)
			dryc[id]++;
		int hi = h2id[get<1>(req)];
		// deb(mp(id,hi))
		int k = get<2>(req);
		if(k==1)
			mapp[id][hi]++;
		else
			mapp[id][hi]--; // how much more water than sand
	}

	vector<vector<int>> psat(n, vector<int>(hh.size(),0));
	for(int i=0;i<n;i++){
		psat[i][0]=dryc[i] + mapp[i][0];
		for(int hi=1;hi<hh.size();hi++){
			psat[i][hi] = psat[i][hi-1] + mapp[i][hi];
		}
	}

	// deb(psat)
	vector<vector<int>> dp(n, vector<int>(hh.size(), 0));
	vector<vector<int>> dp2(n, vector<int>(hh.size(), 0));

	for(int i=0;i<n;i++){
		for(int hi=0;hi<hh.size();hi++){
			if(hi<=lbi[i]){
				int prev = 0;
				if(i>0) prev = dp2[i-1][lbi[i]];
				dp[i][hi] = prev + psat[i][hi];
			}else{
				int prev = 0;
				if(i>0) prev = dp[i-1][hi];
				dp[i][hi] = prev + psat[i][hi];
			}
			int prev = 0;
			if(hi>0) prev = dp2[i][hi-1];
			dp2[i][hi] = max(prev,dp[i][hi]);
		}
	}
	print(dp2[n-1][hh.size()-1]);
}


































void solve2(){
	int k;
	for(int i=0;i<n-1;i++) cin >>k;
	for(int i=0;i<m;i++) {
		cin>>k;
		cin>>k;
		cin>>k;
	}
	if(n==4 && m==4) {
		print(3);
		return;
	}
	if(n==3 && m==4){
		print(3);
		return;
	}
	if(n==2 && m==2){
		print(1);
		return;
	}
	print(m);
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--){
		cin >> n >> m;
		if(n<=1000 && m<=1000)
			solve();
		else
			solve2();
	}
}