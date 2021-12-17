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
#include <fstream>
#include <limits.h>

using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
typedef long int iint;
typedef unsigned long int uiint;
typedef long long int llong;
typedef unsigned long long int  ullong;
#define Mem(a, b) memset(a, (b), sizeof(a))
#define For(i, j) for (int i=0 ; i<j ; i++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (llong)LLONG_MAX/2
#define PI 3.1415926
#define MOD 1000000007

struct SegTree
{
    static llong pow_up(llong num){
        For(i,31) if(1<<i >= num) return 1<<i;
        return -1;
    }
    llong* tree;
    llong n;
    SegTree(llong* arr,llong size){
        n = pow_up(size);
        tree = new llong[2*n];
        copy(arr, arr+size, tree+n);
        fill(tree+n+size,tree+2*n,inf);
        build();
    }
    inline llong op(llong left, llong right){
        return min(left, right); // doesn't need to be commutative
    }
    inline void build(){
        for(llong i = n-1; i>=1; i--) tree[i] = op(tree[i<<1], tree[i<<1|1]);
    }
    inline void change(llong idx, llong val){
        tree[n+idx] = val; // force change
        for(llong i = (n+idx)>>1; i >= 1; i>>=1) tree[i] = op(tree[i<<1], tree[i<<1|1]);
    }
    inline llong getPtr(llong idx){return tree[n+idx];}
    inline llong query(llong left, llong right){
        // both inclusive
        llong sum = inf;
        left+=n, right+=n;
        for(;left<=right;left>>=1,right>>=1){
            if(left&1) sum=op(sum, tree[left++]);
            if(!(right&1)) sum=op(tree[right--], sum);
            if(left==right) break;
        }
        //end condition is correct because only 1 of these 2 can be true then
        return sum;
    }
};

int main(){
    //load data
    ifstream fin("slingshot.in");
    ofstream fout("slingshot.out");
    ios_base::sync_with_stdio(0);
    fin.tie(0);
    llong n, m; fin >> n >> m;
    vector<llong> allptrs((n+m)*2);
    vector<tuple<llong,llong,llong> > sl(n);
    for(llong i=0; i<n; i++){
        llong a, b, t;
        fin>>a>>b>>t;
        sl[i] = make_tuple(a,b,t);
        allptrs.pb(a); allptrs.pb(b);
    }
    vector<llong> mrT(m, inf);
    vector<tuple<llong,llong,llong> > mr(m);
    for(llong i=0;i<m;i++){
        llong a, b;
        fin>>a>>b;
        mr[i] = make_tuple(a,b, i);
        mrT[i] = abs(b-a);
        allptrs.pb(a); allptrs.pb(b);
    }
    sort(allptrs.begin(), allptrs.end());
    allptrs.resize(distance(allptrs.begin(), unique(allptrs.begin(), allptrs.end())));
    for(llong i=0; i<n; i++){
        llong bi = lower_bound(allptrs.begin(), allptrs.end(), get<1>(sl[i])) - allptrs.begin();
        llong ai = lower_bound(allptrs.begin(), allptrs.end(), get<0>(sl[i])) - allptrs.begin();
        sl[i] = make_tuple(ai, bi, get<2>(sl[i]));
    }
    for(llong i=0; i<m; i++){
        llong bi = lower_bound(allptrs.begin(), allptrs.end(), get<1>(mr[i])) - allptrs.begin();
        llong ai = lower_bound(allptrs.begin(), allptrs.end(), get<0>(mr[i])) - allptrs.begin();
        mr[i] = make_tuple(ai, bi, i);
    }

    sort(sl.begin(), sl.end());
    sort(mr.begin(), mr.end());

    llong* arr = new llong[allptrs.size()];
    fill(arr, arr+allptrs.size(), inf);
    SegTree left(arr, allptrs.size());
    llong* arr2 = new llong[allptrs.size()];
    fill(arr2, arr2+allptrs.size(), inf);
    SegTree right(arr2, allptrs.size());
    int j=0;
    for(llong i=0; i<m; i++){
        while(j<sl.size() && get<0>(sl[j])<=get<0>(mr[i])){
            llong sll = allptrs[get<0>(sl[j])];
            llong slr = allptrs[get<1>(sl[j])];
            left.change(get<1>(sl[j]), - sll - slr + get<2>(sl[j]));
            right.change(get<1>(sl[j]), - sll + slr + get<2>(sl[j]));
            j++;
        }
        llong mrl = allptrs[get<0>(mr[i])];
        llong mrr = allptrs[get<1>(mr[i])];
        llong minL = mrl + mrr + left.query(0, get<1>(mr[i]));
        llong minR = mrl - mrr + right.query(get<1>(mr[i]), allptrs.size()-1);
        mrT[get<2>(mr[i])] = min(mrT[get<2>(mr[i])], min(minL, minR));
    }

    arr = new llong[allptrs.size()];
    fill(arr, arr+allptrs.size(), inf);
    left = SegTree(arr, allptrs.size());
    arr2 = new llong[allptrs.size()];
    fill(arr2, arr2+allptrs.size(), inf);
    right = SegTree(arr2, allptrs.size());
    j = n-1;
    for(llong i=m-1; i>=0; i--){
        while(j>=0 && get<0>(sl[j])>get<0>(mr[i])){
            llong sll = allptrs[get<0>(sl[j])];
            llong slr = allptrs[get<1>(sl[j])];
            left.change(get<1>(sl[j]),sll - slr + get<2>(sl[j]));
            right.change(get<1>(sl[j]),sll + slr + get<2>(sl[j]));
            j--;
        }
        llong mrl = allptrs[get<0>(mr[i])];
        llong mrr = allptrs[get<1>(mr[i])];
        llong minL = -mrl + mrr + left.query(0, get<1>(mr[i]));
        llong minR = -mrl - mrr + right.query(get<1>(mr[i]), allptrs.size()-1);
        mrT[get<2>(mr[i])] = min(mrT[get<2>(mr[i])], min(minL, minR));
    }

    for(llong i=0; i<m; i++)
        fout<< mrT[i] <<endl;
    fout.close();
}










