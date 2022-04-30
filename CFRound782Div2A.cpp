#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define print(x) cout<<x<<endl;

void solve(){
	int n, r, b; cin >> n >> r >> b;

	int rep = r/(b+1);
	rep++;

	int repc = r-(rep-1)*(b+1);
	assert(repc < (b+1));

	vector<char> ret;

	for(int i=0;i<b+1;i++){
		if(i<repc){
			for(int j=0;j<rep;j++)
				ret.pb('R');
		}else{
			for(int j=0;j<rep-1;j++)
				ret.pb('R');
		}

		if(i!=b){
			ret.pb('B');
		}
	}



	assert(ret.size() == n);

	for(int i=0;i<n;i++){
		cout<<ret[i];
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