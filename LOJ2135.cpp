#include<bits/stdc++.h>

using namespace std;

int n;

vector<vector<pair<int,int>>> adj;
vector<int> parent, depth, sizes, ins, outs, head, tail, ins2id;

segtree<Node0> weights;
segtree<Node0> kvals;
segtree<Node1> klins;

int t=0;

void dfs_process(int cur, int par){
    if(cur==par) depth[cur]=0;
    sizes[cur]=1;
    parent[cur]=par;
    for(auto& edge : adj[cur]){
        int son = edge.first;
        if(son == par) continue;
        depth[son]=depth[cur]+edge.second;
        dfs_process(son, cur);
        sizes[cur]+=sizes[son];

        if(adj[cur][0].first == par || sizes[son] > sizes[adj[cur][0].first]) 
            swap(edge, adj[cur][0]);
    }
}


void dfs_hld(int cur, int par){
    if(adj[cur].size()==1) tail[cur]=cur;
    ins[cur]=t++;
    ins2id[ins[cur]]=cur;
    for(auto& edge : adj[cur]){
        int son = edge.first;
        if(son == par) continue;
        head[son] = (edge==adj[cur][0] ? head[cur] : son);
        if(edge==adj[cur][0])
            tail[cur]=tail[son];
    }
    outs[cur]=t;
}

int ans = inf;
int tw = 0;

void find_centroid(int cur, int par, int cost){
    ans = min(ans, cost);
    int d, c=-1;
    for(auto& edge : adj[cur]){
        int son = edge.first;
        if(son == par) continue;
        if(weights.get_val(ins[son])*2>tw){
            c = son;
            d = edge.second;
        }
    }
    if(c == -1) return;
    int wc = weights.get_val(ins[c]);
    if(c != adj[cur][0].first){
        find_centroid(son, cur, cost+d*(tw-wc)-d*wc);
        return;
    }

    int ll=ins[c], rr=ins[tail[c]];
    int vi = 0;
    while(ll<=rr){
        int mid=(ll+rr)/2;
        if(weights.get_val(mid)*2>=tw){vi=mid;ll=mid+1;}
        else rr=mid-1;
    }
    int v = ins2id[vi];
    int L=depth[v]-depth[cur];
    int wv = weights.get_val(vi);
    int costv=cost+(tw-wc)*L-wv*L;
    costv+=L*kvals.query(ins[c],vi-1);
    costv-=2*klins.query(ins[c],vi-1);

    ans = min(ans, costv);
    if(vi<rr){
        int wvv = weights.get_val(vi+1);
        int costvv = costv+(tw-wvv)*adj[v][0].second-wvv*adj[v][0].second;
        ans = min(ans, costvv);
    }

    int nc = -1, nd = -1;
    for(int i=1;i<adj[v].size();i++){
        int son = adj[v][i].first;
        int w = adj[v][i].second;
        if(weights.get_val(ins[son])*2>tw){
            nc = son;
            nd = w;
        }
    }
    if(nd==-1) return;
    int wn = weights.get_val(ins[nc]);
    int ncost = costv + (tw-wn)*nd - wn*nd;
    find_centroid(nc,v,ncost);
}



void solve(){
    int q;
    cin >> n >> q;
    parent=vector<int>(n);
    depth=vector<int>(n);
    sizes=vector<int>(n);
    ins=vector<int>(n);
    outs=vector<int>(n);
    head=vector<int>(n);
    tail=vector<int>(n);
    ins2id=vector<int>(n);
    adj = vector<vector<pair<int,int>>>(n);

    for(int i=0;i<n-1;i++){
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        adj[a].pb(mp(b,c));
        adj[b].pb(mp(a,c));
    }

    dfs_process(0,0);
    dfs_hld(0,0);
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
}


/*

TODOs:
1. implement updates
2. implement segtrees
3. debug the hell out of it

*/