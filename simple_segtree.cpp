#include<bits/stdc++.h>

using namespace std;

int pow_up(int num){
    for(int i=0;i<32;i++) if((1<<i)>=num) return 1<<i;
    return -1;
}

template<typename Node>
struct segtree{
    vector<Node> tree;
    int n;
    segtree(int n_){
        n = pow_up(n_);
        tree = vector<Node>(2*n);
        build();
    }
    void build(){
        for(int i=n-1;i>=1;i--) tree[i].pull_up(tree[i*2], tree[i*2+1]);
    }
    void update(int idx, int val){
        idx += n;
        tree[idx].update(val);
        for(idx/=2; idx>=1; idx/=2) tree[idx].pull_up(tree[i*2], tree[i*2+1]);
    }
    Node query(int ll, int rr){
        Node ln, rn;
        for(ll+=n, rr+=n; ll<=rr; ll/=2, rr/=2){
            if(ll&1) ln = Node::merge(ln, tree[ll++]);
            if(!(rr&1)) rn = Node::merge(tree[rr--], rn);
            if(ll == rr) break;
        }
        return Node::merge(ln, rn);
    }
};


template<typename Node>
struct segtreeRecurse{
    vector<Node> tree;
    int n; 
    segtreeRecurse(int n_){
        n = pow_up(n_);
        tree = vector<Node>(n*2);
        build();
    }
    void build(){
        for(int i=n-1;i>=1;i--) tree[i].pull_up(tree[i*2], tree[i*2+1]);
    }
    void update(int idx, int val, int ts, int te, int ll, int rr){
        if(ts == ll && te == rr) {tree[i].update(val); return;}
        int tm = (ts+te)/2;
        tree[i].push_down(tree[i*2], tree[i*2+1]);
        if(ll<=tm) update(idx*2, val, ts, tm, ll, min(rr, tm));
        if(rr>tm) update(idx*2+1, val, tm+1, te, max(ll, tm+1), rr);
        tree[i].pull_up(tree[i*2], tree[i*2+1]);
    }
    Node query(int idx, int ts, int te, int ll, int rr){
        if(ts==ll && te==rr) return tree[i];
        int tm = (ts+te)/2;
        tree[idx].push_down(tree[idx*2], tree[idx*2+1]);
        Node ln, rn; 
        if(ll<=tm) ln=query(idx*2, ts, tm, ll, min(rr, tm));
        if(rr>tm) rn=query(idx*2+1, tm+1, te, max(ll, tm+1), rr);
        tree[idx].pull_up(tree[idx*2], tree[idx*2+1]);
        return Node::merge(ln, rn);
    }
};






int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

}