#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define mt make_tuple
#define mp make_pair
#define pb push_back
#define print(x) cout<<x<<endl
#define inf 20000000000000005LL

llong N, K, W;
vector<llong> values;

int cc;

vector<llong> solve(llong k, llong a, llong b){ // a, b are weights
	cc++;
	vector<llong> ret(b-a+1,-inf);
	if(k == 1){
		//print(b-a);
		//deb(mt(k,a,b))
		for(llong w=a;w<=b;w++) ret[w-a]=values[w];
		//deb(mt(k,a,b))
		//deb(ret)
		return ret;
	} 
	if(k%2==0){
		llong st = max(0LL, (a-N+1)/2 + (a-N+1)%2); // maybe add 1 to both ranges?
		llong ed = min((b+N-1)/2, W);

		//deb(mt(k,a,b))
		vector<llong> sol = solve(k/2, st, ed); 
		for(llong w=a; w<=b; w++){
			llong ll, rr;
			for(llong i=0; i<=N && (ll=(w-i+1)/2 + (w-i+1)%2)>=0 && (rr=(w+i-1)/2) <= W; i++){
				ret[w-a] = max(ret[w-a], sol[ll-st] + sol[rr-st]);
			}
		}
		//deb(mt(k,a,b))
		//deb(ret)
		return ret;
	}else{
		//print(b-a);
		//deb(mt(k,a,b))
		llong st = max(0LL,a - N);
		llong ed = b-1;
		vector<llong> sols = solve(k-1, st, ed); 
		for(llong w=a; w<=b; w++){
			for(llong i=1; i<=N && i<=w-st; i++){
				//deb(mt(w,sols[w-i],values[i]))
				ret[w-a] = max(ret[w-a], sols[w-i-st] + values[i]);
			}
		}
		//deb(mt(k,a,b))
		//deb(ret)
		return ret;
	}
}

void solution(){
	cin >> N >> K >> W;
	cc = 0;
	values = vector<llong>(N*2,-inf);
	for(llong i=1;i<=N;i++) cin >> values[i];
	vector<llong> sol = solve(K, W, W);
	print(sol[0]);
	//print(cc);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solution();
}


