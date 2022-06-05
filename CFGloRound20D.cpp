#include<bits/stdc++.h>

using namespace std;
#define mp make_pair
#define print(x) cout<<x<<endl


void solve(){
	int n; cin >> n;
	vector<int> A(n), B(n);
	for(int i=0;i<n;i++) cin >> A[i];
	for(int i=0;i<n;i++) cin >> B[i];

	vector<int> delay(n+1, 0);
	int j=n-1;
	bool suc = true;
	for(int i=n-1;i>=0;i--){
		if(B[i] == A[j]){
			j--;
		}else{
			if(i+1<n && B[i] == B[i+1]){ // from a pair/sequence, delayable
				delay[B[i]]++;
			}else{
				if(delay[A[j]] > 0){
					delay[A[j]]--;
					j--;
					i++;
				}else{
					suc = false;
					break;
				}
			}
		}
	}
	while(j >= 0){
		if(delay[A[j]] > 0){
			delay[A[j]]--;
			j--;
		}else{ // shouldn't happen
			suc = false;
			break;
		}
	}

	if(suc) print("YES");
	else print("NO");
}





int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--)
		solve();
}