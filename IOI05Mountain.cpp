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

#include "debughelp.hpp"

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
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007

struct node {
    llong val = 0, latent = 0, val_max = 0;
    node* left; node* right;
    const static llong defa = 0;
    const static llong range = 2147483647;
    node(){
        left = nullptr, right = nullptr, val = defa, latent = defa, val_max = defa;
    }
    llong op(llong a, llong b) { return max(a, b); }
    pair<llong, llong> query(llong lo, llong hi, llong L=0, llong R=range-1){
        if (hi < L || R < lo) return make_pair(defa, defa);
        push_down(L, R);
        if (lo <= L && R <= hi) return make_pair(val, val_max);
        llong M = (L+R)/2; llong ret = defa;
        auto retl = make_pair(defa, defa);
        if(left) retl = left->query(lo,hi,L,M);
        auto retr = make_pair(defa, defa);
        if(right) retr = right->query(lo,hi,M+1,R);
        llong vall = retl.first, valr = retr.first;
        llong val_maxl = retl.second, val_maxr = retr.second;
        llong rval = vall + valr;
        llong rval_max = max(val_maxl, vall + val_maxr);
        pull_up();
        return make_pair(rval, rval_max);
    }
    llong set_val(llong old, llong neww){ return neww; }
    void pull_up(){
        llong vall = defa; if(left) vall = left->val;
        llong valr = defa; if(right) valr = right->val;
        llong val_maxl = defa; if(left) val_maxl = left->val_max;
        llong val_maxr = defa; if(right) val_maxr = right->val_max;
        //deb(vall); deb(valr); deb(val_maxl); deb(val_maxr);
        val_max = max(val_maxl, vall + val_maxr);
        val = vall + valr;
        //deb(val_max); deb(val);
    }
    void push_down(llong L=0, llong R=range-1){
        if(latent == defa) return;
        if(L==R){ latent = defa; return; }
        llong M = (L+R)/2;
        if(!left) left = new node();
        if(!right) right = new node();
        left->val_max = latent * (M-L+1);
        left->val = latent * (M-L+1);
        right->val_max = latent * (R-M);
        right->val = latent * (R-M);
        left->latent = latent;
        right->latent = latent;
        latent = defa;
    }
    void update(llong lo, llong hi, llong v, llong L=0, llong R=range-1){
        push_down(L, R);
        if (L >= lo && R <= hi) {
            val_max = max(0LL,v*(R-L+1));
            val = v * (R-L+1);
            latent = v;
            if(L == R) latent = 0;
            return;
        }
        llong M = (L+R)/2;
        if (lo <= M) {
            if (!left) left = new node();
            left->update(lo, min(M, hi), v, L, M);
        }
        if (hi > M) {
            if (!right) right = new node();
            right->update(max(lo,M+1), hi, v,M+1,R);
        }
        val = defa;
        pull_up();
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    node root = node();
    cin.tie(0);
    llong n; cin >> n;
    for(iint i=0; i<1000000; i++){
        string token; cin >> token;
        if(token == "Q"){
            llong h; cin >> h;
            llong vali = root.query(0,0).second;
            if(h<vali) {
                cout<<0<<endl;
                continue;
            }
            llong left = 0; llong right = n-1; llong ans = n-1;
            while(left<=right){
                llong mid = (left+right)/2;
                llong val = root.query(0,mid).second;
                if(val<=h){ ans = mid; left = mid+1; }
                else right = mid-1;
            }
            cout<<ans+1<<endl;
        }else if (token == "I"){
            llong a, b, d; cin >> a >> b >> d;
            a--; b--;
            root.update(a,b,d);
        }else
            break;
    }
}