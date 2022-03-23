// #include "debughelp.hpp"
#include<bits/stdc++.h>

using namespace std;
typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000000000LL
#define print(x) cout<<x<<endl


struct NodeS{
    llong sum, pd, ts, te;
    NodeS(llong val_, llong ts_, llong te_):sum(val_),pd(0),ts(ts_),te(te_){}
    NodeS(llong ts_, llong te_):sum(0),pd(0),ts(ts_),te(te_){}
    NodeS():sum(0),pd(0),ts(inf),te(-inf){}
    static NodeS merge(NodeS& ll, NodeS& rr){
        llong nts = min(ll.ts, rr.ts);
        llong nte = max(ll.te, rr.te);
        llong nsum = ll.sum + rr.sum;
        return NodeS(nsum,nts,nte);
    }
    void pull_up(NodeS& ll, NodeS& rr){
        (*this) = merge(ll,rr);
    }
    void push_down(NodeS& ll, NodeS& rr){
        ll.update(pd);
        rr.update(pd);
        pd = 0;
    }
    void update(llong val_){
        sum+=val_*(te-ts+1);
        pd+=val_;
    }
    llong ans(){return sum;}
};


struct Node0{
    llong sum;
    Node0(llong val_):sum(val_){}
    Node0():sum(0){}
    static Node0 merge(Node0& ll, Node0& rr){
        Node0 mm(ll.sum+rr.sum);
        return mm;
    }
    void pull_up(Node0& ll, Node0& rr){
        (*this) = merge(ll,rr);
    }
    void update(llong val_){
        sum+=val_;
    }
    llong ans(){return sum;}
};


struct Node1{
    llong val, sum, ts, te;
    Node1(llong val_, llong ts_, llong te_):val(val_),sum(val_),ts(ts_),te(te_){}
    Node1(llong ts_, llong te_):val(0),sum(0),ts(ts_),te(te_){}
    Node1():val(0),sum(0),ts(inf),te(-inf){}
    static Node1 merge(Node1& ll, Node1& rr){
        if(ll.ts == inf || ll.te == -inf) return rr;
        if(rr.ts == inf || rr.te == -inf) return ll;
        llong nts = min(ll.ts, rr.ts);
        llong nte = max(ll.te, rr.te);
        llong nsum = ll.sum + rr.sum;
        llong nval = ll.val + rr.val + (ll.te-ll.ts+1)*rr.sum;
        Node1 mm(nval,nts,nte);
        mm.sum=nsum;
        return mm;
    }
    void pull_up(Node1& ll, Node1& rr){
        (*this) = merge(ll,rr);
    }
    void update(llong val_){
        val+=val_*0;
        sum+=val_;
    }
    llong ans(){return val;}
};




template<typename Node>
struct segtreeRecurse{
    static llong pow_up(llong num){
        for(llong i=0;i<63;i++) if(1<<i >= num) return 1LL<<i;
        return -1;
    }
    vector<Node> tree;
    llong n;
    segtreeRecurse(){}
    segtreeRecurse(llong size){
        n = pow_up(size);
        tree = vector<Node>(n*2);
        for(llong i=n;i<2*n;i++) tree[i] = Node(i-n,i-n);
        build();
    }
    void build(){
        for(llong i = n-1; i>=1; i--) tree[i].pull_up(tree[i<<1], tree[i<<1|1]);
    }
    void update(llong idx, llong ts, llong te, llong left, llong right, llong val){
        if(left>right) return;
        if(ts == left && te == right){ tree[idx].update(val); return;}
        tree[idx].push_down(tree[idx<<1], tree[idx<<1|1]); //update to most current for backtrace reupdate
        llong tm = (ts+te)>>1;
        if(left<=tm) update(idx<<1,ts,tm,left,min(right,tm),val);
        if(right>tm) update(idx<<1|1,tm+1,te,max(tm+1,left),right,val);
        tree[idx].pull_up(tree[idx<<1], tree[idx<<1|1]);
    }
    void update(llong left, llong right, llong val){ update(1,0,n-1,left,right,val); }
    Node query(llong idx, llong ts, llong te, llong loc){
        if(ts == loc && te == loc) return tree[idx];
        tree[idx].push_down(tree[idx<<1], tree[idx<<1|1]);
        llong tm = (ts+te)>>1;
        if(loc<=tm)
            return query(idx<<1,ts,tm,loc);
        else
            return query(idx<<1|1,tm+1,te,loc);
    }
    llong get_val(llong loc){ return query(1,0,n-1,loc).ans(); }
};


template<typename Node>
struct segtreeSimple{
    static llong pow_up(llong num){
        for(llong i=0;i<63;i++) if(1<<i >= num) return 1LL<<i;
        return -1;
    }
    vector<Node> tree;
    llong n;
    segtreeSimple(){}
    segtreeSimple(llong size){
        n = pow_up(size);
        tree = vector<Node>(n*2);
        build();
    }
    segtreeSimple(llong size, bool init){
        n = pow_up(size);
        tree = vector<Node>(n*2);
        if(init) for(llong i=n;i<2*n;i++) tree[i] = Node(i-n,i-n);
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
        if(left>right) return Node().ans();
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































segtreeRecurse<NodeS> weights;
segtreeSimple<Node0> kvals;
segtreeSimple<Node0> klins;



llong n;

vector<vector<pair<llong,llong>>> adj;
vector<llong> parent, depth, sizes, ins, outs, head, tail, ins2id;


llong t=0;

void dfs_process(llong cur, llong par){
    if(cur==par) depth[cur]=0;
    sizes[cur]=1;
    parent[cur]=par;
    for(auto& edge : adj[cur]){
        llong son = edge.first;
        if(son == par) continue;
        depth[son]=depth[cur]+edge.second;
        dfs_process(son, cur);
        sizes[cur]+=sizes[son];

        if(adj[cur][0].first == par || sizes[son] > sizes[adj[cur][0].first]) 
            swap(edge, adj[cur][0]);
    }
}


void dfs_hld(llong cur, llong par){
    if(adj[cur].size()==1) tail[cur]=cur;
    if(cur==par) head[cur]=cur;
    ins[cur]=t++;
    ins2id[ins[cur]]=cur;
    for(auto& edge : adj[cur]){
        llong son = edge.first;
        if(son == par) continue;
        head[son] = (edge==adj[cur][0] ? head[cur] : son);
        dfs_hld(son, cur);
        if(edge==adj[cur][0])
            tail[cur]=tail[son];
    }
    outs[cur]=t;
}

llong ans = inf;
llong tw = 0;

void find_centroid(llong cur, llong par, llong cost){
    // deb(mt(cur,par,cost))
    ans = min(ans, cost);
    llong d=-1, c=-1;
    for(auto& edge : adj[cur]){
        llong son = edge.first;
        if(son == par) continue;
        if(weights.get_val(ins[son])*2>tw){
            c = son;
            d = edge.second;
        }
    }
    if(c == -1) return;
    llong wc = weights.get_val(ins[c]);
    // deb(mp(c,wc))
    if(c != adj[cur][0].first){
        find_centroid(c, cur, cost+d*(tw-wc)-d*wc);
        return;
    }

    llong ll=ins[c], rr=ins[tail[c]];
    // deb(mp(ll,rr))
    llong vi = 0;
    while(ll<=rr){
        llong mid=(ll+rr)/2;
        if(weights.get_val(mid)*2>=tw){vi=mid;ll=mid+1;}
        else rr=mid-1;
    }
    llong v = ins2id[vi];
    // deb(mp(v,vi))
    llong L=depth[v]-depth[cur];
    llong wv = weights.get_val(vi);
    llong costv=cost+(tw-wc)*L-wv*L;
    // deb(costv)
    // deb(mp(ins[c],vi-1))
    costv+=L*kvals.query(ins[c],vi-1);
    // deb(costv)
    costv-=2*klins.query(ins[c],vi-1);
    // deb(costv)

    ans = min(ans, costv);
    if(vi<ins[tail[c]]){
        llong wvv = weights.get_val(vi+1);
        llong costvv = costv+(tw-wvv)*adj[v][0].second-wvv*adj[v][0].second;
        // deb(costvv)
        ans = min(ans, costvv);
    }

    llong nc = -1, nd = -1;
    for(llong i=1;i<adj[v].size();i++){
        llong son = adj[v][i].first;
        if(son == parent[v]) continue;
        llong w = adj[v][i].second;
        if(weights.get_val(ins[son])*2>tw){
            nc = son;
            nd = w;
        }
    }
    if(nd==-1) return;
    llong wn = weights.get_val(ins[nc]);
    // deb(mp(nc,wn))
    llong ncost = costv + (tw-wn)*nd - wn*nd;
    find_centroid(nc,v,ncost);
}


void updateW(llong cur, llong addw){
    while(true){
        weights.update(ins[head[cur]], ins[cur], addw);
        if(parent[head[cur]] == head[cur]) break; // reached root
        cur=parent[head[cur]];
    }
}

void updateK0(llong cur, llong addW){
    kvals.update(ins[cur], addW);
    cur = head[cur];
    while(parent[cur]!=cur){
        kvals.update(ins[parent[cur]], addW);
        cur = head[parent[cur]];
    }
}

void updateK1(llong cur, llong addW){
    llong pad = depth[cur] - depth[head[cur]];
    klins.update(ins[cur], addW*pad);
    cur = head[cur];
    while(parent[cur]!=cur){
        llong pad = depth[parent[cur]] - depth[head[parent[cur]]];
        klins.update(ins[parent[cur]], addW*pad);
        cur = head[parent[cur]];
    }
}



void solve(){
    llong q;
    cin >> n >> q;
    parent=vector<llong>(n);
    depth=vector<llong>(n);
    sizes=vector<llong>(n);
    ins=vector<llong>(n);
    outs=vector<llong>(n);
    head=vector<llong>(n);
    tail=vector<llong>(n);
    ins2id=vector<llong>(n);
    adj = vector<vector<pair<llong,llong>>>(n);

    for(llong i=0;i<n-1;i++){
        llong a, b, c; cin >> a >> b >> c;
        a--; b--;
        adj[a].pb(mp(b,c));
        adj[b].pb(mp(a,c));
    }
    t = 0;
    dfs_process(0,0);
    dfs_hld(0,0);

    // deb(depth)
    // deb(parent)
    // deb(ins)
    // deb(head)

    tw = 0;
    llong rcost = 0;

    weights = segtreeRecurse<NodeS>(t+1);
    kvals = segtreeSimple<Node0>(t+1);
    klins = segtreeSimple<Node0>(t+1);

    for(llong i=0;i<q;i++){
        llong u, e; cin >> u >> e; u--;
        tw += e;
        rcost += depth[u]*e;
        updateW(u,e);
        updateK0(u,e);
        updateK1(u,e);

        ans = inf;
        find_centroid(0,0,rcost);
        print(ans);    
        
    }
    
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