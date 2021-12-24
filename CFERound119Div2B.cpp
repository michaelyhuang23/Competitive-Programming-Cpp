#include<iostream>
#include<vector>
#include<assert.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong tt; cin >> tt;
	while(tt--){
		llong w, h;
		cin >> w >> h;
		llong maxA = 0;
		for(llong i=0;i<2;i++){
			llong k; cin >> k;
			vector<llong> arr(k);
			for(llong j=0;j<k;j++) cin >> arr[j];
			maxA = max(maxA,(arr[k-1] - arr[0])*h);
		}
		for(llong i=0;i<2;i++){
			llong k; cin >> k;
			vector<llong> arr(k);
			for(llong j=0;j<k;j++) cin >> arr[j];
			maxA = max(maxA,(arr[k-1] - arr[0])*w);
		}
		cout<<maxA<<endl;
	}
}