#include<iostream>
#include<assert.h>
#include<vector>
#include<bitset>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define MOD 998244353
#define inf 1000000000
#define mp make_pair
#define pb push_back
#define mt make_tuple

llong lowbit(llong n){ return n&(-n); }

llong n;
vector<vector<llong>> hist;
vector<vector<llong>> cc;
vector<llong> dp;
llong maxS, maxI;
vector<llong> pc;

llong count_pos(llong num){
	for(llong i=0;i<n;i++) if((1<<i) & num) return i;
	return -1;
}

llong bit_count(llong num){
	llong count = 0;
	for(llong i=0;i<n;i++) if((1<<i) & num) count++;
	return count;
}

int gH[8388609][26];
llong g[8388609];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
    maxS = 1<<n;
    maxI = n;
    llong allOn = (1<<n) - 1;
    pc = vector<llong>(maxS,0);

    for(llong i=0;i<maxS;i++){
    	pc[i] = bit_count(i);
    }

    for(llong i=0;i<maxS;i++) fill(gH[i], gH[i]+26, inf);

	vector<vector<int> > hist(maxI, vector<int>(26, 0));
	for(llong i=0;i<n;i++){
		string ss; cin >> ss;
		for(llong j=0;j<ss.size();j++){
			llong let = ss[j] - 'a';
			hist[i][let]++; 
		}
	}
    //vector<vector<llong>> gH(maxS,vector<llong>(26,inf));
	//vector<llong> g(maxS, 0);
	fill(g, g+maxS, 0);

	for(llong s=0;s<maxS;s++){
        //cout<<lb<<" "<<lbi<<" "<<ps<<endl;
        llong lb = lowbit(s);
        llong ps = s - lb;
        llong lbi = count_pos(lb);
		llong prod = 1;
		if((s & allOn) == 0) prod = 0;
		else{
			for(llong k=0;k<26;k++){
	            gH[s][k] = min(gH[ps][k], hist[lbi][k]);
				prod *= (llong)(gH[s][k]) + 1LL;
				prod %= MOD;
			}
		}
		if(pc[s]&1) {
           // bitset<4> bit(s);
            //deb(bit) deb(prod)
            g[s] = prod;
        }else {
            //bitset<4> bit(s);
            //deb(bit) deb(-prod)
            g[s] = (MOD-prod)%MOD;
        }
	}

	for(llong i=0;i<maxI;i++){
		for(llong s=0;s<maxS;s++){
			if(s & (1<<i)){
				g[s] += g[s ^ (1<<i)];
				g[s] %= MOD;
			}
		}
	}

	llong result = 0;
	for(llong s=0;s<maxS;s++){
		llong c = 0;
		for(llong i=0;i<maxI;i++){
			if((1<<i) & s) c+=i+1; 
		}
        //deb(s) deb(c) deb(g[s]) deb(bit_count(s))
		llong num = g[s]*pc[s]*c;
        //deb(num)
		result ^= num;
	}
	cout<<result<<endl;

}


/*

f(T) is hard to compute
But g(T) (the number of strings that are subseq of all t in T) is easier to compute

g(T) = prod(a_min, b_min, c_min, ...)

So how can we compute f(T) given g(T)?
PIE
T=[t1,t2,t3,...,tn]
f(T) = g(t1) + g(t2) + g(t3) + g(t4) ... - g(t1,t2) - g(t2,t3) - ... + g(t1,t2,t3) ... 

This is an alternating sum over all subsets of T, and we need to compute it for all T, so we use SOS DP


*/







