#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<assert.h>
#include<fstream>
//#include "debughelp.hpp"

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple

vector<vector<int> > adj;

int dfs(int pa, int cur, int k){
	if(adj[cur].size() == 1){
		//is leaf
		return 1;
	}
	vector<int> bss;
	for(int son : adj[cur]){
		if(son == pa) continue;
		int bs = dfs(cur, son, k); // returns the max branch size
		//deb(son+1); deb(bs);
		if(bs == -1) return -1;
		bss.pb(bs);
	}
	sort(bss.begin(), bss.end());

	set<pair<int,int> > bset;
	int cc = 0;
	for(int i : bss)
		bset.insert(mp(i, cc++));
	int found = -1;
	//deb(bset); // we can't use a freaking set!
	//deb(bss);
    // if(cur == 0)
    //     cout<<"hello"<<endl;
	for(int i = 0; i<bss.size(); i++){
		int bs = bss[i];
		if(bset.find(mp(bs,i)) == bset.end()) continue;
		if(bset.size() == 1) {
			if(found == -1) found = bs;
			else if(bs<k) found = -2; // if >= k, good, just remove it
			break;
		} // smth not right here
		if(bs>=k) {bset.erase(mp(bs,i)); continue;}
		bset.erase(mp(bs,i));
		auto partner = bset.lower_bound(mp(k-bs,0)); // can't find itself!!!
		if(partner == bset.end()) {
			if(found == -1) found = bs;
			else{ found = -2; break; }
		}else{
			bset.erase(*partner);
		}
	}
	if(found == -1) return 1; // not ret, ret 0
	if(found == -2) return  -1;
	else return found+1;
}

bool check(int k){
	int ret = dfs(0,0,k);
	//cout<<"final ret "<<ret<<endl;
	if(ret == -1) return false;
	ret--;
	if(ret >= k || ret == 0) return true; // ret == 0 means everything is matched
	else return false;
}


int main(){
	ios_base::sync_with_stdio(0);
	ifstream fin("deleg.in");
	ofstream fout("deleg.out");
	fin.tie(0);
	int n; fin >> n;
	adj = vector<vector<int> >(n);
	for(int i = 0; i < n-1; i ++) {
		int a, b; fin >> a >> b;
		a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	int le = 0, ri = n+1, ans = -1;
	while(le<=ri){
		int mid = (le+ri)/2;
		if(check(mid)){ ans = mid; le = mid + 1; }
		else ri = mid - 1;
	}
	fout<<ans<<endl;
	fout.close();
}