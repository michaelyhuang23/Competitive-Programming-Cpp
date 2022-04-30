#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define print(x) cout<<x<<endl;


void solve(){
	int n; cin >> n;
	vector<int> C(n);
	for(int i=0;i<n;i++) cin >> C[i];

	int sum = 0;
	for(int i=0;i<n;i++) sum+=C[i];
	int c1 = sum/n;
	int c0 = n-c1;
	// if c0==0
	vector<int> B;
	vector<bool> F(n,1);
	for(int i=0;i<n;i++){
		auto ret = lower_bound(B.begin(), B.end(), i);
		assert(B.size() == i);
		if(ret == B.end()){
			if(C[i]==0){
				B.pb(i);
				F[i]=0;
			}else{
				assert(B.empty() || C[i]>B.back());
				B.pb(C[i]);
				F[C[i]]=0;
			}
		}else{
			int nc = C[i];
			if(F[i]) nc-=i+1;
			else nc--;
			assert(nc>=0);
			auto ret2 = upper_bound(B.begin(), B.end(), i);
			int l = i+1-distance(B.begin(), ret2);
			int r = distance(ret2, B.end());
			assert(r == l-1);
			int ni = i+nc+1;
			B.pb(ni);
			F[ni]=0;
		}
		if(B.size() == n) break;
	}

	for(int i=0;i<n;i++){
		cout<<F[i]<<" ";
	}
	cout<<endl;
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--)
		solve();
}