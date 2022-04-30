#include<bits/stdc++.h>
using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define inf 100000000000000LL


llong random(llong st, llong ed){
	if(st==ed) return st;
	return rand()%(ed-st+1)+st;
}


vector<vector<int>> choices;
void solve(llong tt){
	int val = 0;
	auto query = [&](int v){
		bitset<8> bi(v);
		cout<<bi<<endl;
		cout.flush();
		int n; cin >> n;
		return n;
	};
	int n;
	for(int i=0;i<300;i++){
		n = query(val);
		if(n == 0 || n == 8) break;
		int k = choices[n].size();
		int j = random(0, k-1);
		val = choices[n][j];
	}
	if(n == 8) n=query(255);
	assert(n == 0);
}


int rotate(int x){
	if(x&1)
		return (x>>1) | (1<<7);
	else
		return (x>>1);
}




int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	choices = vector<vector<int>>(8);
	for(int c=1;c<=7;c++){
		unordered_set<int> used;
		for(int i=1;i<255;i++){
			bitset<8> bi(i);
			if(bi.count() != c) continue;
			int pi = i; bool avail = true;
			for(int j=0;j<=8;j++){
				if(used.find(pi) != used.end()) avail = false;
				pi = rotate(pi);
			}
			if(avail){
				used.insert(i);
				choices[c].pb(i);
			}
		}
	}

	llong tt; cin >> tt;
	for(llong i=1;i<=tt;i++)
		solve(i);
}