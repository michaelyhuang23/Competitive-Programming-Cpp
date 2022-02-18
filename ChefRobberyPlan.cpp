#include<bits/stdc++.h>

using namespace std;


#define pb push_back


int N, K, W;
vector<int> values;

vector<int> solve(int k, int a, int b){ // a, b are weights
	if(k == 1){
		vector<int> ret(b-a+1);
		for(int w=a;w<=b;w++) ret[w-a]=values[w];
		return ret;
	}
	if(k%2==0){
		int st = max(0, a/2-N); // maybe add 1 to both ranges?
		int ed = min(b/2+((b%2==1)?1:0)+N, W);
		vector<int> sol = solve(k/2, st, ed); 
		for(int w = a; w<=b; w++){
			
		}
	}else{

	}
}

void solution(){
	cin >> N >> K >> W;
	values = vector<int>(N);
	for(int i=0;i<N;i++) cin >> values[i];
	solve(K, W, W);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solution();
}