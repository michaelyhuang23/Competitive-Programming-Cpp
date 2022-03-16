//#include "debughelp.hpp"

#include<bits/stdc++.h>

using namespace std;

#define mp make_pair
#define print(x) cout<<x<<endl



void solve(){
	int n; cin >> n;
	vector<int> arr(n);

	const int k = 23;
	const int K = 1<<k; // shouldn't be too big
	const int active = K-1; // this should have all k bits set

	for(int i=0;i<n;i++){
		cin >> arr[i];
		assert(arr[i] < K);
	} 

	vector<int> maxx1(K, -1);
	vector<int> maxx2(K, -2);

	for(int i=0;i<n;i++){
		if(i > maxx1[arr[i]]){
			maxx2[arr[i]] = maxx1[arr[i]];
			maxx1[arr[i]] = i;
		}
	}


	for(int j=0;j<k;j++){
		for(int i=0;i<K;i++){
			if((1<<j) & i) continue;
			// now it's not set
			int x = i ^ (1<<j);
			if(maxx1[x] > maxx1[i]){
				maxx2[i] = max(maxx2[i], maxx1[i]);
				maxx1[i] = maxx1[x];
			}else if(maxx1[x] < maxx1[i]){
				maxx2[i] = max(maxx2[i], maxx1[x]);
			}
			maxx2[i] = max(maxx2[i], maxx2[x]);
			assert(maxx2[i]<maxx1[i]);
		}
	}

	int maxx = 0;
	for(int i=0;i<n;i++){
		int x = (~arr[i])&active;
		int p = 0; // the prefix
		int max1 = maxx1[0], max2 = maxx2[0]; // this is the case if none of the significant bits can be set
		for(int j=k-1;j>=0;j--){
			if((1<<j) & x){
				// it's set, that means it's a leading 1
				assert(!((1<<j)&p)); // should'nt be on the prefix yet
				p ^= (1<<j);
				if(maxx2[p] <= i){
					// there're no two behind i, so we cannot set this bit
					p ^= (1<<j);
				}else{
					// there're two behind i, so we can set this bit
					max1 = maxx1[p];
					max2 = maxx2[p]; // we overwrite directly because it's guaranteed larger
				}
			}
		}
		if(max2 > i && max1 > i){
			int z = arr[max1];
			int y = arr[max2];
			maxx = max(maxx, arr[i]|(y&z));
		}
	}

	print(maxx);
}













int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	solve();
}

