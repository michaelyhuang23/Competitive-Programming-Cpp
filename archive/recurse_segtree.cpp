//#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/

#define mp make_pair
#define pb push_back
#define inf 2147483647
#define PI 3.1415926
#define MOD 1000000007

template<typename Node>
struct segtreeRecurse{
    static int pow_up(int num){
        for(int i=0;i<65;i++) if(1<<i >= num) return 1<<i;
        return -1;
    }
    vector<Node> tree;
    int n;
    segtreeRecurse(){}
    segtreeRecurse(int size){
        n = pow_up(size);
        tree = vector<Node>(n*2);
        build();
    }
    void build(){
        for(int i = n-1; i>=1; i--) tree[i].pull_up(tree[i<<1], tree[i<<1|1]);
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
        if(left>right) return Node();
        if(ts == left && te == right) return tree[idx];
        tree[idx].push_down(tree[idx<<1], tree[idx<<1|1]);
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

int main(){
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    // int n = 100000;
    // iint arr[n];
    // For(i,n) arr[i]=rand()%1000000;
    // SegTree tr1(arr,n);
    // For(i,10000){
    // 	iint queryL = rand()%n;
    // 	iint queryR = rand()%n;
    // 	if(queryR<queryL) swap(queryR,queryL);
    // 	int ret1 = tr1.query(queryL,queryR);
    // 	int sum = 0;
    // 	for(iint i=queryL; i<=queryR; i++)
    // 		sum+=arr[i];
    // 	assert(ret1==sum);
    // 	iint updateL = rand()%n;
    // 	iint updateR = rand()%n;
    // 	if(updateR<updateL) swap(updateL,updateR);
    // 	iint updateVal = rand()%n;
    // 	//cout<<"change: "<<updatePos<<" "<<updateVal<<endl;
    // 	tr1.update(updateL, updateR, updateVal);
    // 	for(iint i=updateL;i<=updateR;i++)
    // 		arr[i] += updateVal;
    // }
}