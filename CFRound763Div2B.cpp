#include<iostream>
#include<assert.h>
#include<vector>
#include<unordered_set>
#include<algorithm>

//#include "debughelp.hpp"

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl

vector<pair<int,int>> ranges;
int n;

bool contain(pair<int,int> a, pair<int,int> b){
	if(a.first>=b.first && a.second<=b.second) return true;
	else return false;
}

void solve_interval(int l, int r, int i){
	if(l==r) {
		cout<<l<<" "<<r<<" "<<l<<endl;
		return;
	}
	//deb(mp(l,r))
	//deb(ranges)
	while(i<n && !contain(ranges[i], mp(l,r))) i++;
	//deb(mp(i,n))
	assert(i<n);
	pair<int,int> leftInt = ranges[i];
	while(i<n && !(contain(ranges[i], mp(l,r)) && !contain(ranges[i],leftInt))) i++;
	//deb(mp(i,n))
	if(i>=n){
		// only one interval
		if(leftInt.first == l){
			assert(leftInt.second==r-1);
			cout<<l<<" "<<r<<" "<<r<<endl;
		}else if(leftInt.second == r){
			assert(leftInt.first==l+1);
			cout<<l<<" "<<r<<" "<<l<<endl;
		}else assert(false);
		return;
	}
	assert(i<n);
	pair<int,int> rightInt = ranges[i];
	assert(leftInt.first == l);
	assert(rightInt.second == r);
	assert(rightInt.first - leftInt.second == 2);

	cout<<l<<" "<<r<<" "<<rightInt.first-1<<endl;

}

void solve(){
	cin >> n;
	ranges = vector<pair<int,int>>(n);
	for(int i=0;i<n;i++) {
		int a, b; cin >> a >> b;
		ranges[i] = mp(a,b);
	}
	
	sort(ranges.begin(), ranges.end(), [&](pair<int,int> a, pair<int,int> b){
		if(a.first<=b.first && a.second>=b.second) return true;
		else return a.first<b.first;
	});
	//deb(ranges)
	for(int i=0;i<n;i++){
		solve_interval(ranges[i].first, ranges[i].second, i+1);
	}
	cout<<endl;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--) solve();
}