// #define _GLIBCXX_DEBUG 1
#include "debughelp.hpp"
#include<bits/stdc++.h>


using namespace std;
#define mt make_tuple
#define pb push_back
#define mp make_pair
#define inf 1000000000
#define print(x) cout<<x<<endl


struct BIT{
	vector<int> bits; // index start from 1
	int n;
	BIT(int n_){
		n = n_+2;
		bits = vector<int>(n,0);
	}
	int lowbit(int n){ return n&(-n); }
	void update(int idx, int val){
        idx++;
		for(int i=idx; i<n; i+=lowbit(i)) bits[i]+=val;
	}
	int get_sum(int idx){
		if(idx<0) return 0;
        idx++;
		int sum = 0;
		for(int i=idx; i>0; i-=lowbit(i)) sum += bits[i];
		return sum;
	}
};


int K, N;
vector<int> max_points, min_points;
vector<int> locs;
vector<vector<pair<bool,int>>> ptrs;
int totalD = 0;

void solve(){
	cin >> K >> N;

	totalD = 0;

	locs = vector<int>();
	max_points = vector<int>();
	min_points = vector<int>();
	for(int i=0;i<N;i++){
		int s, t; 
		char A, B;
		cin >> A >> s >> B >> t;
		
		if(A == B) {
			totalD += abs(s-t);
			continue;
		}
		totalD++;
		max_points.pb(max(s,t));
		min_points.pb(min(s,t));
		locs.pb(s);
		locs.pb(t);
	}

	// deb(totalD)
	sort(locs.begin(), locs.end());

	locs.erase(unique(locs.begin(), locs.end()),locs.end());

	int L = locs.size();

	unordered_map<int,int> loc2id;
	for(int i=0;i<L;i++) loc2id[locs[i]]=i;

	N = max_points.size();
	ptrs = vector<vector<pair<bool,int>>>(L, vector<pair<bool,int>>());

	for(int i=0;i<N;i++){
		int a = loc2id[min_points[i]];
		int b = loc2id[max_points[i]];

		if(a==b){
			ptrs[a].pb(mp(true, i));
			ptrs[a].pb(mp(false, i));
		}else{
			ptrs[a].pb(mp(false, i));
			ptrs[b].pb(mp(true, i));
		}
		min_points[i] = a;
		max_points[i] = b;
	}


	vector<int> maxPref(L,0);
	vector<int> maxDist(L,0);
	for(int l=0;l<L;l++){
		if(l>0) {
			maxPref[l] = maxPref[l-1];
			maxDist[l] = maxDist[l-1];
			maxDist[l] += 2*maxPref[l-1]*abs(locs[l]-locs[l-1]);
		}
		for(auto ptr : ptrs[l]){
			if(ptr.first) maxPref[l]++;
		}
	}

	vector<int> minPref(L,0);
	vector<int> minDist(L,0);
	for(int l=L-1;l>=0;l--){
		if(l<L-1) {
			minPref[l] = minPref[l+1];
			minDist[l] = minDist[l+1];
			minDist[l] += 2*minPref[l+1]*abs(locs[l]-locs[l+1]);
		}
		for(auto ptr : ptrs[l]){
			if(!ptr.first) minPref[l]++;
		}
	}

	deb(minDist)
	deb(maxDist)

	int minD = inf;
	for(int l=0;l<L;l++){
		minD = min(minD, minPref[l]+maxPref[l]);
	}

	// int a = 0;
	// int preva = 0;
	// int disttop = 0;
	// BIT minBIT(L);
	// int l = L-1;
	// for(l=L-1;l>=0;l--){
	// 	int b = maxPref[l];
	// 	for(auto ptr : ptrs[l]){
	// 		if(!ptr.first) a++;
	// 	}	
	// 	if(a>=b) break;
	// 	preva = a;
	// 	// for(int r=l+1;r<L;r++){

	// 	// }
	// 	// int ll=0, rr=l, k = 0;
	// 	// while(ll<=rr){
	// 	// 	int mid = (ll+rr)/2;
	// 	// 	int c = maxPref[mid];
	// 	// 	int b = minBIT.get_sum(L) - minBIT.get_sum(l-1);
	// 	// 	if(c<=b) {k = mid; ll=mid+1;}
	// 	// 	else rr=mid-1;
	// 	// }
	// }

	// int d1 = 0;
	// for(int i=0;i<N;i++){
	// 	d1 += abs(locs[max_points[i]]-locs[l]);
	// 	d1 += abs(locs[min_points[i]]-locs[l]);
	// }

	// int d2 = 0;
	// l++;
	// if(l<L){
	// for(int i=0;i<N;i++){
	// 	d2 += abs(locs[max_points[i]]-locs[l]);
	// 	d2 += abs(locs[min_points[i]]-locs[l]);
	// }
	// }

	// int dd = d1;
	// if(l<L) dd = min(dd, d2);

	print(minD+totalD);


}








int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}