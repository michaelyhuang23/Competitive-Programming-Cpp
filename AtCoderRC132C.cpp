#include<iostream>
#include<vector>
#include<set>
#include<bitset>

using namespace std;
typedef long long llong;
#define pb push_back
#define print(x) cout<<x<<endl
#define MOD 998244353

void printb(int num){
	bitset<5> b(num); print(b);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, d; cin >> n >> d;
	vector<int> arr(n+1);
	for(int i=1;i<=n;i++) cin >> arr[i];
	int dd = d*2+1;
	int maxS = 1<<dd;
	int mask = maxS-1;

	int init = 0;
	for(int i=1;i<=min(n,d);i++) init ^= 1<<(d-i);
	
	vector<vector<llong>> dp(n+1, vector<llong>(1<<dd,0));

	dp[0][init] = 1;
	for(int i=0;i<n;i++){
		for(int s=0;s<maxS;s++){
			int ns = (s<<1)&mask;
			if(i+1 + d <= n) ns|=1;
			// deb(i);
			// printb(s); 
			// deb(dp[i][s]);
			if(arr[i+1] == -1){
				for(int j=0;j<dd;j++){
					if((1<<j) & ns){
						int nns = ns ^ (1<<j);
						dp[i+1][nns] += dp[i][s];
						dp[i+1][nns] %= MOD;
					}
				}
			}else{
				int c = arr[i+1]-(i+1)+d;
				//deb(c);
				c = 2*d-c;
				//deb(c);
				if(ns & (1<<c)){
					ns^=(1<<c);
					//printb(ns);
					dp[i+1][ns] += dp[i][s];
					dp[i+1][ns] %= MOD;
				}
			}
		}
	}
	llong total = 0;
	for(int s=0;s<maxS;s++){
		total += dp[n][s];
		total %= MOD;
	}
	print(total);
}








/*

Given A, we want to compute the number of P such that 
P is a permutation of [1, n] and satisfy p[i] = a[i] unless
a[i] = -1
further |p[i]-i|<=d

Consider tiling by target sequence (most obvious way)
issues are the -1s

consider a seq of the positions of -1s (1 based)

consider the set of ints we can use to match with it. 

we need to find a matching such that |position - int|<=d

why don't we record directly what this int-position is. 

then we need to go back 10 slots to make sure the int is not taken. 
That seems nontrivial



Consider the simplified problem where everywhere is -1

consider tiling by the sequence of source

consider squeezing by the sequence of source: not wise because the d condition is indeterminate


Consider as graph matching problem?

consider the window of length 10
If we record everything in the window, that should be fine?
2^10 = 1000

then the transition is simply left shifting the window! 



*/