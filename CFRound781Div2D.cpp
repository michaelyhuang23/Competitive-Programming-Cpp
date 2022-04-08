#include<bits/stdc++.h>


using namespace std;
typedef long long llong;
#define print(x) cout<<x<<endl



void solve(){
	llong tail = 0;
	auto query = [&](llong a, llong b){
		cout<<"? "<<a<<" "<<b<<endl;
		cout.flush();
		llong v; cin >> v;
		return v;
	};
	for(llong i=0;i<=29;i++){
		llong a = (1LL<<(i)) - tail;
		llong b = (1LL<<(i)) + (1LL<<(i+1)) - tail;
		llong ret = query(a,b);
		if(ret % (1LL<<(i+1)) == 0){
			tail ^= (1LL<<i);
		}else{
		}
	}

	cout<<"! "<<tail<<endl;
	cout.flush();
}




int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong tt; cin >> tt;
	while(tt--) solve();
}