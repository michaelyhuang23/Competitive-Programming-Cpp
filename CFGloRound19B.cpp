#include<bits/stdc++.h>


using namespace std;

#define pb push_back
#define print(x) cout<<x<<endl

void solve(){
	int n; cin>>n;
	vector<int> arr(n);
	for(int i=0;i<n;i++) cin >> arr[i];
	int sum = 0;
	for(int l=0;l<n;l++){
		for(int r=l;r<n;r++){
			int c = r-l+1;
			for(int k=l;k<=r;k++){
				if(arr[k]==0) c++;
			}
			sum += c;
		}
	}
	print(sum);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int tt; cin >> tt;
	while(tt--) solve();
}