#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define print(x) cout<<x<<endl

void solve(){
	int n; cin >> n;
	vector<int> arr(n);
	for(int i=0;i<n;i++) cin >> arr[i];
	multiset<int> total(arr.begin(), arr.end());
	set<int> tcomp;
	for(int i=0;i<=n;i++) tcomp.insert(i);
	for(int e : total) tcomp.erase(e);
	vector<int> brr;
	int k = 0; // everything >= k is alive
	while(k<n){ // creating b
		int mex = *tcomp.begin(); //guaranteed to exist
		multiset<int> cut;
		int cmex = 0;
		int nk = 0;
		for(int j=k;j<n;j++){
			cut.insert(arr[j]);
			// choose until <=j
			while(cut.find(cmex) != cut.end()) cmex++;
			if(cmex==mex){
				nk=j+1;
				break;
			}
		}
		brr.pb(mex);
		for(int j=k;j<nk;j++){
			total.erase(total.find(arr[j]));
			if(total.find(arr[j]) == total.end()) tcomp.insert(arr[j]);
		}
		k = nk;
	}

	print(brr.size());
	for(int i=0;i<brr.size()-1;i++) cout<<brr[i]<<" ";
	cout<<brr[brr.size()-1]<<endl;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--) solve();
}