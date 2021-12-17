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
#include <unordered_map>
#include <unordered_set>
#include <fstream>

using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
typedef long int iint;
typedef unsigned long int uiint;
typedef long long int llong;
typedef unsigned long long int ullong;
#define Mem(a, b) memset(a, (b), sizeof(a))
#define For(i, j) for (int i=0 ; i<j ; i++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007

struct Fraction {
    llong a, b;
    Fraction(){
        a = 1; b = 1;
    }
    Fraction(llong x, llong y){
        a = x; b = y;
        assert(b!=0);
        reduce();
    }
    Fraction operator+(Fraction s) const{
        Fraction p(a*s.b+b*s.a, s.b * b);
        p.reduce();
        return p;
    }
    inline void reduce(){
        llong gc = gcd(a,b);
        a /= gc;
        b /= gc;
    }
    Fraction inv() const{
        assert(a!=0);
        return Fraction(b,a);
    }
};

Fraction op(Fraction x, Fraction y){
    return x + y.inv();
}

vector<Fraction> arr;
vector<Fraction> ans;
vector<iint> lfs;
vector<iint> rts;

void divGet(iint l, iint r, vector<iint>& idx){
    if(l==r){
        return; //assume query length >=2
    }
    iint m = (l+r)/2;
    vector<Fraction> left(m+1), right(r+1);
    left[m] = arr[m];
    right[m+1] = arr[m+1];
    for(iint i=m-1; i>=0; i--) left[i] = op(arr[i], left[i+1]);
    for(iint i=m+2; i<=r; i++) right[i] = op(right[i-1], arr[i]);
    vector<iint> lidx, ridx;
    for(iint& i : idx){
        iint li = lfs[i], ri = rts[i];
        assert(li>=l);
        assert(ri<=r);
        if(li<=m && ri>m){
            ans[i] = op(left[li], right[ri]);
            continue;
        }
        if(ri<=m) lidx.pb(i);
        else ridx.pb(i);
    }
    divGet(l, m, lidx);
    divGet(m+1, r, ridx);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint N, Q;
    cin >> N >> Q;
    arr = vector<Fraction>(N);
    lfs = vector<iint>(Q);
    rts = vector<iint>(Q);
    ans = vector<Fraction>(Q);
    For(i,N){
        iint a;
        cin >> a;
        arr[i] = Fraction(a,1LL);
    }
    For(i,Q) {
        iint l, r; cin >> l >> r;
        lfs[i] = l-1; rts[i] = r-1;
    }
    vector<iint> idx;
    For(i, Q){
        if(lfs[i] == rts[i]) {ans[i] = arr[i]; continue;}
        idx.pb(i);
    }

    divGet(0, N-1, idx);

    For(i, Q){
        cout<<ans[i].a<<" "<<ans[i].b<<endl;
    }
}

