#include<iostream>
#include<vector>
#include<assert.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--){
		string s; cin >> s;
		int nc = 0;
		for(int i=0;i<s.size();i++) if(s[i] == 'N') nc++;
		if(nc == 1) cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
	}
}