#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define inf 1000000000
#define print(x) cout<<x<<endl
#define MOD 998244353LL


void solve(){
	int N, H; cin >> N >> H;
	vector<pair<int,int>> trees(N);
	for(int i=0;i<N;i++){
		int x, h; cin >> x >> h;
		trees[i] = mp(x,h);
	}
	sort(trees.begin(), trees.end());

	int maxS = 0;
	int pi = -1; // the last breaking point

	vector<int> cuts;
	int start = 1;

	if(N==0){
		print(0);
		return;
	}


	int end = trees[trees.size()-1].first;

	for(int i=0;i<N;i++){
		int x = trees[i].first;
		int h = trees[i].second;
		if(h<=H){
		}else{
			cuts.pb(x);
			// if(pi > -1){ 
			// 	int len = trees[i].first-1 - (trees[pi].first+1);
			// 	maxS = max(maxS, len);
			// }
			// pi = i;
		}
	}

	if(cuts.size()==0){
		print(end-start);
		return;
	}

	for(int i=1;i<cuts.size();i++){
		maxS = max(maxS, (cuts[i]-1)-(cuts[i-1]+1));
	}
	if(cuts[0]!=start)
		maxS = max(maxS, (cuts[0]-1) - (start));
	if(cuts[cuts.size()-1]!=end)
		maxS = max(maxS, (end) - (cuts[cuts.size()-1]+1));
	// int head = 0;
	// for(int i=0;i<N;i++){
	// 	if(trees[i].second > H) {
	// 		head = trees[i].first-1 - trees[0].first;
	// 		break;
	// 	}
	// }

	// int tail = 0;
	// for(int i=N-1;i>=0;i--){
	// 	if(trees[i].second > H) {
	// 		tail = trees[trees.size()-1].first - (trees[i].first+1);
	// 		//deb(tail)
	// 		break;
	// 	}
	// }

	// print(head);
	// print(tail);


	print(max(0,maxS));
}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}