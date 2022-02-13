#include<bits/stdc++.h>


using namespace std;

typedef long long llong;
#define pb push_back
#define print(x) cout<<x<<endl

void solve(){
	int n; cin >> n;
	int st, ed; cin >> st;
	n-=2;
	vector<int> arr(n);
	for(int i=0;i<n;i++) cin >> arr[i];
	cin >> ed;
	

	bool all1 = true;
	for(int i=0;i<n;i++) all1 &= arr[i]==1;
	if(all1) {
		print(-1);
		return;
	}

	if(n == 1 && arr[0]%2==1) {
		print(-1);
		return;
	}

	// possible?

	llong sum = 0;
	for(int i=0;i<n;i++){
		if(arr[i]%2==1){
			sum += (llong)arr[i]/2 + 1;
		}else{
			sum += (llong)arr[i]/2;
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