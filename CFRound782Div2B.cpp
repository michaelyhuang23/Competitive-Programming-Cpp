#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define print(x) cout<<x<<endl;


void solve(){
	int n,k; cin >> n >> k;
	string s; cin >> s;
	vector<bool> arr(n);
	vector<bool> brr(n,0);
	for(int i=0;i<n;i++)
		arr[i] = s[i]=='1';
	
	int uk = 0;
	vector<int> usage(n,0);

	if(k&1){
		for(int i=0;i<n;i++){
			if(uk < k && arr[i]){
				uk++;
				usage[i]+=1;
				brr[i] = 1;
			}else{
				brr[i] = !arr[i];
			}
		}
		if(uk < k){
			usage[n-1]+=k-uk;
			if((k-uk) % 2 == 1)
				brr[n-1] = brr[n-1]^1;
		}
	}else{
		for(int i=0;i<n;i++){
			if(uk < k && !arr[i]){
				uk++;
				usage[i]+=1;
				brr[i] = 1;
			}else{
				brr[i] = arr[i];
			}
		}
		if(uk < k){
			usage[n-1]+=k-uk; // u can't control the parity of this
			if((k-uk) % 2 == 1)
				brr[n-1] = brr[n-1]^1;
		}		
	}


	for(int i=0;i<n;i++)
		cout<<brr[i];
	cout<<endl;

	for(int i=0;i<n;i++){
		cout<<usage[i]<<" ";
	}
	cout<<endl;
}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--)
		solve();
}