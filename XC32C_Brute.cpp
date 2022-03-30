#include<bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl
#define inf 1000000000


void solve(){
	int n,q; cin >> n >> q;
	vector<int> arr(n);

	for(int i=0;i<n;i++) cin >> arr[i];

	for(int i=0;i<q;i++){
		int l,r,a; cin >> l >> r >> a;
		l--; r--;
		if(l>r){
			for(int i=l;true;i++){
				if(i>=n) i-=n;
				if(arr[i]>a) swap(arr[i],a);
				if(i==r) break;
			}
		}else{
			for(int i=l;i<=r;i++){
				if(arr[i]>a) swap(arr[i],a);
			}
		}
		print(a);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}