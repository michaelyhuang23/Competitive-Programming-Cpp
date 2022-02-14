#include<bits/stdc++.h>


using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define MOD 1000000007LL
#define inf 10000000
#define inff 10000000000000000LL
#define print(x) cout<<x<<endl

int n;

void solve(){
	vector<int> arr(n);
	for(int i=0;i<n;i++) cin >> arr[i];

	int SM = 1<<n;
	int total = 0;
	for(int s=1;s<SM;s++){
		vector<int> brr;
		for(int i=0;i<n;i++){
			if((1<<i) & s) brr.pb(arr[i]);
		}

		int kmin = 0;
		set<int> tracker;
		bool suc = true;

		for(int i=0;i<brr.size();i++){
			if(brr[i] <= kmin){
				// illegal
				suc = false;
				break;
			}
			auto it = tracker.lower_bound(brr[i]);
			if(it == tracker.begin()){
				// no smaller
			}else{
				it--; 
				kmin = *it;
			}
			tracker.insert(brr[i]);
		}
		if(suc) total++;
	}
	print(total);
}

int main(){
	while(cin >> n){
		solve();
	}
}