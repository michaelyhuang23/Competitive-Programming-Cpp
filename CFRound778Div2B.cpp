#include<bits/stdc++.h>

using namespace std;
#define print(x) cout<<x<<endl
#define inf 1000000000

void solve(){
	string s; cin >> s;
	vector<int> lastChar(26,inf);
	for(int i=0;i<s.size();i++){
		int c = s[i]-'a';
		lastChar[c]=i;
	}

	int firstlastchar = inf;
	for(int ci : lastChar) firstlastchar=min(firstlastchar,ci);

	if(s.size()==0) firstlastchar=0;
	assert(firstlastchar<inf);

	string output = s.substr(firstlastchar,s.size()-firstlastchar);

	print(output);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--)
		solve();
}