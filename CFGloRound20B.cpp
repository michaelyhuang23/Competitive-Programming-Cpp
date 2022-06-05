#include<bits/stdc++.h>

using namespace std;

#define print(x) cout<<x<<endl


void solve(){
	string s; cin >> s;
	int ac = 0, bc = 0;
	for(int i=0;i<s.size();i++){
		if(s[i] == 'A') ac++;
		if(s[i] == 'B') bc++;

		if(bc > ac){
			print("NO");
			return;
		}
	}
	if(s[s.size() - 1] == 'B')
		print("YES");
	else
		print("NO");
}





int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--)
		solve();
}