#include<bits/stdc++.h>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl
#define inf 1000000007


llong power(llong num, llong pow){
	if(pow==0) return 1;
	if(pow%2==0){
		llong inter = power(num, pow/2);
		return inter*inter;
	}else{
		return num*power(num, pow-1);
	}
}

vector<llong> primes;
vector<pair<llong,llong>> pp;
vector<llong> pre;
llong ss;
void find_primes(llong num){
    for(llong p : primes){
        if(p * p > num) {
            if(num > 1) pp.pb(mp(num, 1));
            break;
        }
        llong count = 0;
        while(num % p == 0) { num /= p; count++; }
        if(count>0) pp.pb(mp(p, count));
    }
}

vector<llong> decomp(llong s){
    vector<llong> dec(ss+1);
    llong ts = s;
    for(llong i=ss; i>=1; i--) {
        dec[i] = ts / pre[i-1];
        ts %= pre[i-1];
    }
    return dec;
}
int minc = inf;

void dfs(llong a, vector<llong> ps, int count){
    if(a == 1) {minc = min(minc, count); return;}
    if(count>14) return;
    for(int i=1;i<=ss;i++) {
        if(a%pp[i].first == 0 && ps[i]>0) {
            vector<llong> pps = ps;  pps[i]--;
            dfs(a/pp[i].first, pps, count+1);
        }
    }
    dfs(a+1, ps, count+1);
    dfs(a-1, ps, count+1);
}

void solve(){
    llong a, b; cin >> a >> b;
    if(a>b) swap(a,b);
    llong c = b-a;
    minc = inf;
    pp = vector<pair<llong,llong>>(); pp.pb(mp(0,0));
    find_primes(c);
    ss = pp.size()-1;
    vector<llong> ps(ss+1);
    for(int i=1;i<=ss;i++) ps[i] = pp[i].second;
    dfs(a, ps, 0);
    print(minc);
}
















void gen_primes(llong n){
    for(llong i=3; i*i<=n; i+=2){
        bool suc = true;
        for(llong p : primes) if(i % p == 0) {suc = false; break;}
        if(suc) primes.pb(i);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    primes = vector<llong>(); primes.pb(2);
    gen_primes(1000000000);
    llong tt; cin >> tt;
    while(tt--) solve();
}
