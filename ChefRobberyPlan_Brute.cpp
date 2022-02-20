#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define mt make_tuple
#define mp make_pair
#define pb push_back
#define print(x) cout<<x<<endl
#define inf 1000000000000LL

llong N, K, W;
vector<llong> values;

vector<llong> solve(llong k, llong a, llong b){ // a, b are weights
	if(k == 1){
		vector<llong> ret(b-a+1, -inf);
		for(llong w=a;w<=b;w++) ret[w-a]=values[w];
		return ret;
	}
	if(k%2==0){
		llong st = max(0LL, (a-N)/2); // maybe add 1 to both ranges?
		llong ed = min((b+N)/2+(((b+N)%2==1)?1:0), W);
		vector<llong> sol = solve(k/2, st, ed); 
		vector<llong> ret(b-a+1, -inf);
		for(llong w=a; w<=b; w++){
			for(llong i=0; i<=N/2; i++){
				llong ll = w/2 - i;
				if(ll<0) continue;
				llong rr = w/2 + ((w%2)?1:0) + i;
				if(rr>W) continue;
				// assert(ll + rr == w);
				// assert(ll >= st);
				// assert(rr <= ed);
				//deb(mt(ll,rr,sol[ll-st]+sol[rr-st]))
				ret[w-a] = max(ret[w-a], sol[ll-st] + sol[rr-st]);
			}
		}
		//deb(mt(k,a,b))
		//deb(ret)
		return ret;
	}else{
		vector<llong> ret(b-a+1, -inf);
		vector<llong> sols = solve(k-1, 0, b-1);
		for(llong w=a; w<=b; w++){
			for(llong i=1; i<=N && i<=w; i++){
				//deb(mt(w,sols[w-i],values[i]))
				ret[w-a] = max(ret[w-a], sols[w-i] + values[i]);
			}
		}
		//deb(mt(k,a,b))
		//deb(ret)
		return ret;
	}
}

void solution(){
	cin >> N >> K >> W;
	values = vector<llong>(N*2,-inf);
	for(llong i=1;i<=N;i++) cin >> values[i];
	vector<llong> sol = solve(K, W, W);
	print(sol[0]);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solution();
}


