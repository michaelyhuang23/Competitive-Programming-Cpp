#include<bits/stdc++.h>

#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define pb push_back
#define print(x) cout<<x<<endl
#define inf 1000000000LL
#define mp make_pair

void solve(){
	llong n; cin >> n;
	vector<llong> arr(n,0);
	vector<llong> brr(n,0);
	for(llong i=0;i<n;i++) cin >> arr[i];
	for(llong i=0;i<n;i++) cin >> brr[i];
	
	llong sM = (1<<n);
	llong minC = inf;

	vector<int> minA, minB;
	for(int s = 0; s<sM; s++){
		vector<int> A(n), B(n);
		for(int i=0;i<n;i++){
			if(s & (1<<i)){
				A[i] = brr[i];
				B[i] = arr[i];
			}else{
				A[i] = arr[i];
				B[i] = brr[i];
			}
		}
		llong cost = 0;
		for(int l = 0;l<n;l++){
			for(int r=l+1; r<n; r++){
				cost += (A[l] + A[r])*(A[l] + A[r]);
				cost += (B[l] + B[r])*(B[l] + B[r]);
			}
		}
		if(cost<minC){
			minC = cost;
			minA = A;
			minB = B;
		}
		minC = min(minC, cost);
	}
	print(minC);
	deb(minA)
	deb(minB)
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	llong tt; cin >> tt;
	while(tt--) solve();
}