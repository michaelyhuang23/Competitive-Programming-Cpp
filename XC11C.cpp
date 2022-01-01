#include<bits/stdc++.h>

//#include "debughelp.hpp"

using namespace std;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl
#define inf 1000000007

int n, k;
vector<int> arr;
vector<int> cc;
vector<int> tc;
vector<int> tracker;
vector<bool> has;
vector<int> pre;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> k;
	arr = vector<int>(n);
	for(int i=0;i<n;i++) cin >> arr[i];
	if(k<0){
		k *= -1;
		for(int i=0;i<n;i++) arr[i] *= -1;
	}

	int minn = inf;
	for(int i=0;i<n;i++) minn = min(minn, arr[i]);
	for(int i=0;i<n;i++) arr[i] = arr[i] - (minn-1);
	int maxx = 0;
	for(int i=0;i<n;i++) maxx = max(maxx, arr[i]);
	//deb(arr)
	unordered_set<int> all; 
	for(int i=0;i<n;i++) all.insert(arr[i]);
	has = vector<bool>(maxx+1,0);
	for(int i=0;i<=maxx;i++) {
		if(all.find(i+k) == all.end()) has[i]=false;
		else has[i]=true;
	}
	cc = vector<int>(maxx+1);
	pre = vector<int>(n);
	for(int i=0;i<n;i++){
		int c = arr[i];
		cc[c]++;
		if(!has[c]) continue;
		pre[i] = cc[c] - cc[c+k];
	}
	
	tracker = vector<int>(maxx+1,inf);
	tc = vector<int>(maxx+1,0);
	// consider l==r case alone
	int maxc = 0;
	for(int i=0;i<=maxx;i++) {
		if(cc[i] > maxc) {
			maxc = cc[i];
		}
	}
	if(k==0) {
		print(maxc);
		return 0;
	}
	for(int i=0;i<n;i++){
		int c = arr[i];
		if(has[c]){
			maxc = max(maxc, cc[c+k]+1);
		}
	}
	for(int r=0;r<n;r++){
		int c = arr[r];
		if(has[c]) {
			//deb(mp(r,c))
			tracker[c] = min(tracker[c], tc[c] - tc[c+k]);
			int best = pre[r] - tracker[c];
			//deb(best)
			//if(r==5) deb(tracker)
			maxc = max(maxc, cc[c+k]+best);
		}
		tc[c]++; // update after (exclusive)
	}
	print(maxc);
}






















