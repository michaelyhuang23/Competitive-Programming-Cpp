#include<bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl

void solve(int tt){
	string s; cin >> s;
	vector<char> chr;
	vector<int> counts;
	int n = s.size();
	for(int i=0;i<n;i++){
		if(!chr.empty() && chr.back() == s[i]) counts.back()++;
		else {
			chr.pb(s[i]);
			counts.pb(1);
		}
	}

	int k = chr.size();

	vector<int> ncounts(k,0);


	for(int i=0;i<k;i++){
		if(i+1 == k || chr[i] > chr[i+1]){
			ncounts[i] = counts[i];
		}else{
			assert(chr[i]<chr[i+1]);
			ncounts[i] = counts[i]*2;
		}
	}

	vector<char> result;
	for(int i=0;i<k;i++){
		for(int j=0;j<ncounts[i];j++)
			result.pb(chr[i]);
	}

	string sr(result.begin(), result.end());

	cout<<"Case #"<<tt<<": "<<sr<<endl;
}













int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	for(int t = 1; t <= tt; t++)
		solve(t);
}