#include<bits/stdc++.h>

using namespace std;
#define print(x) cout<<x<<endl

void solve(){
	string s; cin >> s;
	char c; cin >> c;
	bool suc = false;
	for(int i=0;i<s.size();i++){
		if(s[i] == c){
			if((i+1)%2==1) suc = true;
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