#include<bits/stdc++.h>

using namespace std;

#define print(x) cout<<x<<endl


void solve(){
	int n; cin >> n;
	vector<int> A(n);
	vector<int> B(n);
	for(int i=0;i<n;i++) cin >> A[i];
	for(int i=0;i<n;i++) cin >> B[i];

	unordered_set<int> AS(A.begin(), A.end());
	int cc = 0;
	for(int i=0;i<n;i++){
		if(AS.find(B[i]) != AS.end()) cc++;
	}
	int cn = 0;
	for(int i=0;i<n;i++) if(A[i]==B[i]) cn++;
	int cm = cc - cn;
	print(cn);
	print(cm);
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}