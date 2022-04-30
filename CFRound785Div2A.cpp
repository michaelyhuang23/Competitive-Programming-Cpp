#include<bits/stdc++.h>

using namespace std;
#define print(x) cout<<x<<endl

void solve(){
	string s; cin >> s;
	if(s.size() == 1){
		cout<<"Bob "<<(s[0]-'a'+1)<<endl;
		return;
	}

	if(s.size() % 2 == 0){
		int count = 0;
		for(int i=0;i<s.size();i++) count+=s[i]-'a'+1;
		cout<<"Alice "<<count<<endl;
		return;
	}

	assert(s.size()%2 == 1);

	int count = 0;
	for(int i=0;i<s.size();i++) count+=s[i]-'a'+1;

	int bob = min(s[0], s[s.size()-1])-'a'+1;
	int alice = count - bob;
	assert(alice > bob);
	cout<<"Alice "<<(alice-bob)<<endl;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--) solve();
}