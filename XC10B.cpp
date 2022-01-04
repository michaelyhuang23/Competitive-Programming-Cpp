#include<bits/stdc++.h>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl
#define inf 100000000000000LL

int n,m,k;
vector<int> bl;
vector<int> sinks;
vector<vector<pair<int,llong>>> adj;
vector<vector<llong>> dists;
vector<llong> dist;
vector<bool> visited;

void solve(){
    cin >> n >> m >> k;
    bl = vector<int>(n,0);
    sinks = vector<int>(k);
    dists = vector<vector<llong>>(n);
    dist = vector<llong>(n,inf);
    visited = vector<bool>(n,0);
    for(int i=0;i<k;i++) cin >> sinks[i];
    for(int i=0;i<k;i++) sinks[i]--;
    for(int i=0;i<n;i++) cin >> bl[i];
    adj = vector<vector<pair<int,llong>>>(n);
    for(int i=0;i<m;i++){
        int a,b,w; cin >> a >> b >> w;
        a--; b--;
        adj[a].pb(mp(b,w));
        adj[b].pb(mp(a,w));
    }
    priority_queue<pair<llong,int>, vector<pair<llong,int>>, greater<pair<llong,int>>> pq;
    for(int i=0;i<k;i++){
        int s = sinks[i];
        dist[s] = 0;
        pq.push(mp(0,s));
    }
    // init conditions
    while(!pq.empty()){
        auto cc = pq.top(); pq.pop();
        int cur = cc.second;
        if(visited[cur]) continue;
        visited[cur] = true;
        for(auto edge : adj[cur]){
            int son = edge.first;
            llong w = edge.second;
            if(dist[cur]+w < dist[son] && !visited[son]){
                vector<int> temp;
                while(!dists[son].empty() && dists[son].back() > dist[cur]+w) {
                    temp.pb(dists[son].back());
                    dists[son].pop_back();
                }
                dists[son].pb(dist[cur]+w);
                while(dists[son].size()<=bl[son] && !temp.empty()){
                    dists[son].pb(temp.back()); 
                    temp.pop_back();
                }
                if(bl[son]<dists[son].size() && dists[son][bl[son]]<dist[son]){
                    dist[son] = dists[son][bl[son]];
                    pq.push(mp(dist[son], son));
                }
            }
        }
    }
    // deb(dists)
    // deb(dist)
    if(dist[0]>inf/2)
        print(-1);
    else
        print(dist[0]);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tt; cin >> tt;
    while(tt--) solve();
}
