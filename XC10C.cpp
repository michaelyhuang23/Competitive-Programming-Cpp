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

void solve(){
    llong a, b; cin >> a >> b;
    if(a>b) swap(a,b);
    llong c = b-a;
    pp = vector<pair<llong,llong>>(); pp.pb(mp(0,0));
    find_primes(c);
    //deb(pp)
    ss = pp.size()-1;
    assert(ss<=10);
    llong maxS = 1;
    for(pair<llong,llong> p : pp) maxS *= p.second + 1;
    pre = vector<llong>(ss+1, 1);
    for(llong i=1;i<=ss;i++) pre[i] = pre[i-1] * (pp[i].second + 1);

    //deb(pre)

    vector<vector<llong>> dp(maxS, vector<llong>(2,inf));
    dp[0][0] = 0;
    // init!
    vector<llong> cas(maxS);
    for(llong s=0;s<maxS;s++){
        //deb(s)
        auto decs = decomp(s);
        //deb(decs)
        llong ca = a;
        //deb(pp[ss])
        //deb(decs[ss])
        for(llong i=1;i<=ss;i++) ca /= power(pp[i].first, decs[i]);
        cas[s] = ca;
        //deb(ca)
    }
    //deb(cas)

    for(llong s=1;s<maxS;s++){
        auto decs = decomp(s);
        llong ca = cas[s]; // no matter how we round, it's always off by 1 at most
        llong ca1 = ca + 1;
        for(llong i=1;i<=ss;i++){
            if(decs[i] == 0) continue;
            llong ps = s - pre[i-1];
            llong cap = cas[ps];
            llong cap1 = cap+1;

            llong rounddown0 = cap - (cap / pp[i].first) * pp[i].first;
            llong roundup0 = pp[i].first - rounddown0;
            if(roundup0 == pp[i].first) roundup0 = 0;

            llong rounddown1 = cap1 - (cap1 / pp[i].first) * pp[i].first;
            llong roundup1 = pp[i].first - rounddown1;
            if(roundup1 == pp[i].first) roundup1 = 0;

            dp[s][0] = min(dp[s][0],dp[ps][0] + rounddown0 + 1);

            if(rounddown1 > 0)
                dp[s][0] = min(dp[s][0],dp[ps][1] + rounddown1 + 1);

            // if(cap1 / pp[i].first == ca1) // special case
            //     dp[s][1] = min(dp[s][1],dp[ps][1] + rounddown1 + 1);
            // else
            //     dp[s][0] = min(dp[s][0],dp[ps][1] + rounddown1 + 1);

            // if(s==3) {
            //     deb(ps)
            //     deb(cap)
            //     deb(ca)
            //     deb(roundup0)
            //     deb(roundup1)
            //     deb(dp[ps][0])
            //     deb(dp[ps][1])
            // }

            if(roundup0 > 0)
                dp[s][1] = min(dp[s][1],dp[ps][0] + roundup0 + 1);

            dp[s][1] = min(dp[s][1],dp[ps][1] + roundup1 + 1);
        }
    }
    //deb(dp)
    llong mintotal = inf;
    for(llong s=0;s<maxS;s++){
        llong ca = cas[s];
        // if(dp[s][1] + (ca+1-1) == 2){
        //     deb(dp[s][1])
        //     deb(ca+1)
        //     deb(s)
        // }
        if(ca>=1) mintotal = min(mintotal, dp[s][0] + (ca-1));
        mintotal = min(mintotal, dp[s][1] + (ca + 1 - 1));
    }
    print(mintotal);
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
