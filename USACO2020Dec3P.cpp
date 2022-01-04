#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define MOD 1000000007LL;

int N,K,KB,B;
vector<pair<int,int> > ranges;
llong dp[32][2][2][2][2][2][2][2][2][2];

void query(int l1, int r1, int l2, int r2, int l3, int r3){
	// 1 stands for equal
	for(int i = B; i>=0; i--){
		int a1,a2,a3;
		for(a1=0; a1<2; a1++)
			for(a2=0; a2<2; a2++)
				for(a3=0; a3<2; a3++){
					if(a1 > (l1&(1<<i))) ;
					dp[i][]
				}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> K;
	ranges = vector<pair<int,int> >(N);
	for(int i=0;i<N;i++) {
		int a, b; cin >> a >> b;
		ranges[i] = mp(a,b);
	}
	KB = 1;
	B = 0;
	while(KB<K) KB *= 2; B++;
	sort(ranges.begin(), ranges.end());
	for(int a=0;a<ranges.size();a++){
		for(int b=a+1;b<ranges.size();b++){
			if(ranges[a].second/KB != ranges[b].first/KB) continue;
			int cb = ranges[a].second/KB;
			int sl = max(ranges[a].first, cb*KB);
			int sr = min(ranges[b].second, cb*KB+KB-1);
			//query(sl, ranges[a].second, ranges[b].first, sr);
		}
	}
}




















