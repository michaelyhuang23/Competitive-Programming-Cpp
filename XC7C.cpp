#include<iostream>
#include<assert.h>
#include<vector>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl

int n, m;
vector<llong> c5 = {0, 0, 0, 0, 0, 4320, 0, 0, 0, 0};
vector<llong> c4 = {0, 0, 0, 0, 24336, 4320, 0, 0, 0, 0};
vector<llong> c3 = {0, 0, 0, 3198, 13176, 27000, 13680, 15120, 0, 0};
vector<llong> c2 = {0, 0, 66, 390, 1800, 6120, 13680, 15120, 0, 0};


llong modulo_pow(llong base,llong exp) {
    llong result=1;
    while(exp > 0){
        if(exp%2 == 1){
            result=(result*base)%MOD; //getting rid of the odd term
        }
        base = (base*base)%MOD; // squaring the base
        exp /= 2;
    }
    return (llong) result%MOD;
}

llong invert(llong num){
	return modulo_pow(num, MOD-2);
}

void solve(){
	int a, b; cin >> a >> b;
	if(a>b) swap(a,b);

	if(a==1){
		print(0);
		return;
	}

	llong all = modulo_pow(3, a*b);
	llong cut = 0;
	if(a==2 && b<=9){
		cut = c2[b];
	}
	if(a==3 && b<=8){
		cut = c3[b];
	}
	if(a==4 && b<=6){
		cut = c4[b];
	}
	if(a==5 && b<=5){
		cut = c5[b];
	}
	llong final = (all-cut+MOD)%MOD;
	print(final);
}

llong dfs(vector<vector<int>> state, int r, int c){
	if(r>=n) return 1;
	llong count = 0;
	for(int i=0;i<3;i++){
		bool suc = true;
		for(int rp=0;rp<r;rp++){
			for(int cp=0;cp<c;cp++){
				if(i == state[rp][c] && state[r][cp] == state[rp][cp])
					suc = false;
				if(i == state[r][cp] && state[rp][c] == state[rp][cp])
					suc = false;
				if(!suc) break;
			}
			if(!suc) break;
		}
		if(suc){
			state[r][c] = i;
			if(c==m-1)
				count+=dfs(state, r+1, 0);
			else
				count+=dfs(state, r, c+1);
		}
	}
	return count;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	// c5 = vector<llong>(10,0);
	// c4 = vector<llong>(10,0);
	// c3 = vector<llong>(10,0);
	// c2 = vector<llong>(10,0);


	// n = 5;
	// for(m=5;m>=5;m--){
	// 	vector<vector<int>> state(5, vector<int>(m,-1));
	// 	c5[m] = dfs(state, 0, 0);
	// }

	// n = 4;
	// for(m=6;m>=4;m--){
	// 	vector<vector<int>> state(4, vector<int>(m,-1));
	// 	c4[m] = dfs(state, 0, 0);
	// }

	// n = 3;
	// for(m=8;m>=3;m--){
	// 	vector<vector<int>> state(3, vector<int>(m,-1));
	// 	c3[m] = dfs(state, 0, 0);
	// }

	// n = 2;
	// for(m=9;m>=2;m--){
	// 	vector<vector<int>> state(2, vector<int>(m,-1));
	// 	c2[m] = dfs(state, 0, 0);
	// }

	// deb(c2)
	// deb(c3)
	// deb(c4)
	// deb(c5)

	int tt; cin >> tt;
	while(tt--) solve();
}


/*

compute the number of ways to color such that there's no rectangle

How bout we compute the probability that there's no rectangle if we use
random color?

Nope

apparently, when n>9 or m>9, it automatically must have a rectangle
 because of pigeonhole principle

so maybe we can use bitmask DP that records for all rows above it,
is there a pattern of same colors like 00100101 or smth

try all 3^5 ways of coloring, then compare against the mask.

But this doesn't handle the case of vertical pairs.

we can't possibly go through all 3^25 permutations. pruning?

// 1 : fail
// 2 : <=9
// 3 : <=8  --> could be stricter?
// 4 : <=6
// 5 : <=5

*/
