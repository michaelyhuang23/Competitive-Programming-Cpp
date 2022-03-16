#include<bits/stdc++.h>


using namespace std;

typedef long double ddouble;
#define pb push_back
#define mp make_pair
#define inf 1000000000
#define print(x) cout<<x<<endl
#define MOD 998244353LL


void solve(){
	int N, L; cin >> N >> L;
	vector<int> st(N);
	vector<int> ed(N);
	for(int i=0;i<N;i++){
		cin >> st[i];
		cin >> ed[i];
		ed[i] += st[i];
	}

	bool suc = true;
	for(int i=1;i<N;i++){
		if(st[i] - ed[i-1] > 4) suc = false;
	}
	if(!suc){
		print(0);
		return;
	}

	//deb("begin")

	vector<vector<bool>> reachable(N, vector<bool>(4,0));
	// ith end ith end-1 ith end-2, ith end-3, are reachable
	int stA = min(3,ed[0]-st[0]);
	for(int k = stA; k>=0; k--)
		reachable[0][k] = 1;
	for(int i=0;i<N-1;i++){
		for(int j=0;j<4;j++){
			if(!reachable[i][j]) continue;
			int end = ed[i]-j;
			for(int p = i+1;p<min(N,i+6);p++){
				if(st[p] - end <= 4){
					// crossable
					// but where does it end
					int eend = end+4;
					int rev = min(3,ed[p]-eend);
					if(rev>=0 && rev<=3){
						for(int k=rev; k>=0; k--)
							reachable[p][k] = true;
					}
				}
			}
		}

		if(reachable[i][0]){
			// special case walk directly onto next platform
			if(st[i+1] == ed[i]){
				int eend = st[i+1];
				int rev = min(3, ed[i+1]-eend);
				if(rev>=0 && rev<=3){
					for(int k=rev; k>=0; k--)
						reachable[i+1][k] = true;
				}
			}
		}
	}

	//deb(reachable)

	if(reachable[N-1][1]) print(1);
	else print(0);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}