#include<bits/stdc++.h>
 
using namespace std;
typedef long long llong;
#define inf 100000000000000000LL
#define mp make_pair
#define pb push_back
 
llong n,m,D;
llong xr;
llong maxE;
vector<vector<pair<llong,llong>>> adj;
vector<llong> dist, counter, indeg;
 
bool check(){
    if(xr <= maxE) return false;
    dist = vector<llong>(n,0); // small side mistakes!
    dist[0] = 0;
    counter = vector<llong>(n, 0);
    for(llong i=0;i<n;i++){
        for(auto edge : adj[i]){
            llong to = edge.first; llong w = edge.second; assert(dist[to]<xr);
            if(counter[i] < counter[to]){
                if(counter[i] == counter[to]-1 && dist[i]+w>=xr) dist[to] = max(dist[to], w);
            }else if(counter[i]==counter[to]){
                dist[to] = max(dist[to], dist[i]+w); // (count, dist)
                if(dist[to]>=xr) {
                    dist[to] = w;
                    counter[to]++;
                }
            }else{
                counter[to]=counter[i];
                dist[to] = dist[i]+w;
                if(dist[to]>=xr){
                    dist[to] = w;
                    counter[to]++;
                }
            }
        }
    }
    
   // for(llong i=0;i<n;i++) cout<<counter[i]<<" ";
    //cout<<endl;
    for(llong i=0;i<n;i++) {
        if(counter[i]+1 > D) return false;
    }
    return true;
}
 
void solve(){
    cin >> n >> m >> D;
    adj = vector<vector<pair<llong,llong>>>(n);
    indeg = vector<llong>(n, 0);
    maxE = 0;
    for(llong i=0;i<m;i++){
        llong a, b, c; cin >> a >> b >> c; a--; b--;
        if(a>b) swap(a,b);
        adj[a].pb(mp(b, c));
 
        maxE = max(maxE, c);
    }
 
    
    
    llong ll = 2, rr = inf, ans = 0;
    while(ll<=rr){
        xr = (ll+rr)/2;
        if(check()) {rr = xr-1; ans = xr;}
        else ll = xr+1;
    }
    //xr = 20;
    //cout<<check()<<endl;
    cout<<ans<<endl;
}
 
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
}