#include<bits/stdc++.h>

using namespace std;

#define print(x) cout<<x<<endl


void solve(){
	int N; cin >> N;
	unordered_map<int,int> minR, maxL;
	vector<int> X(N), Y(N), D(N);
	unordered_set<int> YS;
	for(int i=0;i<N;i++){
		cin >> X[i] >> Y[i];
		YS.insert(Y[i]);
	}
	string s; cin >> s;

	for(int i=0;i<N;i++){
		if(s[i]=='R') D[i]=1;
		else D[i]=-1;
	}

	for(int i=0;i<N;i++){
		if(D[i]==1){
			// right
			if(minR.find(Y[i])==minR.end()) minR[Y[i]]=X[i];
			else minR[Y[i]] = min(minR[Y[i]],X[i]);
		}else{
			// left
			if(maxL.find(Y[i])==maxL.end()) maxL[Y[i]]=X[i];
			else maxL[Y[i]] = max(maxL[Y[i]],X[i]);
		}
	}

	bool free = true;
	for(int y : YS){
		if(maxL.find(y)==maxL.end() || minR.find(y)==minR.end()) continue;
		free &= maxL[y] < minR[y];
	}
	if(free) print("No");
	else print("Yes");
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}