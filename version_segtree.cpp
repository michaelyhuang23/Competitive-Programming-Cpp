#include<bits/stdc++.h>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000
#define print(x) cout<<x<<endl


struct Node{

};

Node nodes[MAXSIZE];
int lefts[MAXSIZE], rights[MAXSIZE];
int counter = 0;
struct DynamicVersionSegtree{
    DynamicVersionSegtree(){}
    void pull_up(int idx){
        Node& leftNode, rightNode;
        if(lefts[idx]!=-1) leftNode = nodes[lefts[idx]];
        if(rights[idx]!=-1) rightNode = nodes[rights[idx]];
        nodes[idx].pull_up(leftNode, rightNode);
    }
    void copy_node(int to, int from){
    	lefts[to] = lefts[from];
    	rights[to] = rights[from];
    	nodes[to] = nodes[from];
    }
    void push_down(int idx){ // push_down shouldn't create new node. It's the old stuffs
        if(lefts[idx]==-1) lefts[idx] = ++counter;
        if(rights[idx]==-1) rights[idx] = ++counter;
        nodes[idx].push_down(nodes[lefts[idx]], nodes[rights[idx]]);
    }
    Node query(int idx, int ll, int rr, int ts=0, int te=RANGE){
        if(ll == ts && rr == te) return nodes[idx];
        int tm = (ts+te)/2;
        push_down(idx);
        Node leftNode, rightNode;
        if(lefts[idx]!=-1 && ll <= tm)
            leftNode = query(lefts[idx], ll, min(rr,tm), ts, tm);
        if(rights[idx]!=-1 && rr > tm)
            rightNode = query(rights[idx], max(ll,tm+1),rr,tm+1,te);
        return Node::merge(leftNode, rightNode);
    }
    int update(int idx, int ll, int rr, int val, int ts=0, int te=RANGE){
    	int nidx = ++counter;
    	if(idx == -1) idx = nidx;
        else { push_down(idx); copy_node(nidx, idx); }
    	if(ll==ts && rr==te){ nodes[nidx].update(val); return nidx; }
        int tm = (ts+te)/2;
        if(ll <= tm)
        	lefts[nidx] = update(lefts[nidx], ll, min(ll, tm), val, ts, tm);
        if(rr > tm)
        	rights[nidx] = update(rights[nidx], max(ll,tm+1), rr, tm+1, te);
        pull_up(nidx);
    }
};
