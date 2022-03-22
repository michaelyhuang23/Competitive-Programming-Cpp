#include<bits/stdc++.h>

using namespace std;
typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000000LL

struct Node0{
    int val, pd;
    Node0(int val_):val(val_),pd(0){}
    Node0():val(0),pd(0){}
    static Node0 merge(Node0& ll, Node0& rr){
        return Node0(ll.val+rr.val);
    }
    void pull_up(Node0& ll, Node0& rr){
        (*this) = merge(ll,rr);
    }
    void update(int val_){
        val+=val_;
        pd+=val_;
    }
    void push_down(Node0& ll, Node0& rr){
        ll.update(pd);
        rr.update(pd);
        pd = 0;
    }
    int ans(){return val;}
};


struct Node1{
    int val, sum, ts, te;
    Node1(int val_, int ts_, int te_):val(val_),sum(val_),ts(ts_),te(te_){}
    Node1(int ts_, int te_):val(0),sum(0),ts(ts_),te(te_){}
    Node1(){}
    static Node1 merge(Node1& ll, Node1& rr){
        int nts = min(ll.ts, rr.ts);
        int nte = max(ll.te, rr.te);
        int nsum = ll.sum + rr.sum;
        int nval = ll.val + rr.val + (ll.te-ll.ts+1)*rr.sum;
        Node1 mm(nval,nts,nte);
        mm.sum=nsum;
        return mm;
    }
    void pull_up(Node1& ll, Node1& rr){
        (*this) = merge(ll,rr);
    }
    void update(int val_){
        val+=val_*0;
        sum+=val_;
    }
    int ans(){return val;}
};




template<typename Node>
struct segtreeRecurse{
    static int pow_up(int num){
        for(int i=0;i<65;i++) if(1<<i >= num) return 1<<i;
        return -1;
    }
    vector<Node> tree;
    int n;
    segtreeRecurse(int size){
        n = pow_up(size);
        tree = vector<Node>(n*2);
        build();
    }
    void build(){
        for(int i = n-1; i>=1; i--) tree[i] = tree[i<<1] + tree[i<<1|1];
    }
    void update(int idx, int ts, int te, int left, int right, int val){
        if(left>right) return;
        if(ts == left && te == right){ tree[idx].update(val); return;}
        tree[idx].push_down(tree[idx<<1], tree[idx<<1|1]); //update to most current for backtrace reupdate
        int tm = (ts+te)>>1;
        if(left<=tm) update(idx<<1,ts,tm,left,min(right,tm),val);
        if(right>tm) update(idx<<1|1,tm+1,te,max(tm+1,left),right,val);
        tree[idx].pull_up(tree[idx<<1], tree[idx<<1|1]);
    }
    void update(int left, int right, int val){ update(1,0,n-1,left,right,val); }
    Node query(int idx, int ts, int te, int left, int right){
        if(left>right) return 0;
        tree[idx].push_down(tree[idx<<1], tree[idx<<1|1]);
        if(ts == left && te == right) return tree[idx];
        int tm = (ts+te)>>1;
        Node ll, rr;
        if(left<=tm)
            ll=query(idx<<1,ts,tm,left,min(right,tm));
        if(right>tm)
            rr=query(idx<<1|1,tm+1,te,max(tm+1,left),right);
        return Node::merge(ll,rr);
    }
    int query(int left, int right){ return query(1,0,n-1,left,right).ans(); }
};


template<typename Node>
struct segtreeSimple{
    static llong pow_up(llong num){
        for(llong i=0;i<32;i++) if(1<<i >= num) return 1<<i;
        return -1;
    }
    vector<Node> tree;
    llong n;
    segtreeSimple(llong size){
        n = pow_up(size);
        tree = vector<Node>(n*2);
        build();
    }
    void build(){
        for(llong i = n-1; i>=1; i--) tree[i].pull_up(tree[i<<1], tree[i<<1|1]);
    }
    void update(llong idx, llong val){
        tree[n+idx].update(val);
        for(llong i = (n+idx)>>1; i >= 1; i>>=1) tree[i].pull_up(tree[i<<1], tree[i<<1|1]);
    }
    llong query(llong left, llong right){
        Node ll, rr;
        left+=n, right+=n;
        for(;left<=right;left>>=1,right>>=1){
            if(left&1) ll=Node::merge(ll,tree[left++]);
            if(!(right&1)) rr=Node::merge(tree[right--],rr);
            if(left==right) break; 
        }
        return Node::merge(ll,rr).ans();
    }
};































segtreeRecurse<Node0> weights;
segtreeSimple<Node0> kvals;
segtreeSimple<Node1> klins;



int n;

vector<vector<pair<int,int>>> adj;
vector<int> parent, depth, sizes, ins, outs, head, tail, ins2id;


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


void updateW(int cur, int addw){
    while(true){
        weights.update(ins[head[cur]], ins[head], addw);
        if(parent[head[cur]] == cur) break; // reached root
        cur=parent[head[cur]];
    }
}

void updateK0(int cur, int addW){
    int d = dist[cur];
    cur = head[cur];
    while(parent[cur]!=cur){
        int pad = dist[parent[cur]];
        kvals.update(ins[parent[cur]], addW*(d-pad));
        cur = head[parent[cur]];
    }
}

void updateK1(int cur, int addW){
    int d = dist[cur];
    cur = head[cur];
    while(parent[cur]!=cur){
        int pad = dist[parent[cur]];
        klins.update(ins[parent[cur]], addW*(d-pad));
        cur = head[parent[cur]];
    }
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