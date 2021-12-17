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

class Line{
    public:
    int a,b;
    Line(){}
    Line(int a_, int b_){
        if(a_>b_){b = a_; a = b_;}
        else{a = a_; b = b_;}
    }
    bool within(int a, int b, int c){return (a<c && c<b) || (b<c && c<a);}
    bool intersect(const Line& other){
        if(within(a,b,other.a) && !within(a,b,other.b))
            return true;
        if(within(a,b,other.b) && !within(a,b,other.a))
            return true;
        return false;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--){
        int n,k;
        cin>>n>>k;
        Line lines[n];
        bool taken[2*n];
        Mem(taken,false);
        For(i, k){
            int a,b;
            cin >> a >> b;
            a--;
            b--;
            lines[i] = Line(a,b);
            taken[a] = true; taken[b] = true;
        }
        vector<int> pos; 
        For(i,2*n) if(!taken[i]) pos.pb(i);
        For(i,n-k){
            //cout<<"line: "<<pos[i]<<" "<<pos[i+n-k]<<'\n';
            lines[i+k] = Line(pos[i], pos[i+n-k]);
        }
        int intersect = 0;
        For(i,n){
            For(j,i){
                if(lines[i].intersect(lines[j]))
                    intersect++;
            }
        }
        cout<<intersect<<'\n';
    }
}