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

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint t;
    cin >> t;
    while(t--){
    	iint n;
    	cin >> n;
    	bool* conn=new bool[n];
    	For(i,n) cin >> conn[i];
    	// is true: connect from n+1 to i
    	if(conn[n-1]==false){
    		For(i,n) cout<<i+1<<" ";
    		cout<<n+1<<endl;// test special cases!
    		continue;;
    	}
    	if(conn[0]==true){
    		cout<<n+1<<" ";
    		For(i,n-1) cout<<i+1<<" ";
    		cout<<n<<endl;// test special cases!
    		continue;;
    	}
    	iint idx=-1;
    	For(i,n-1) if(conn[i]==0 && conn[i+1]==1){ idx=i; break; }
    	if(idx==-1){ cout<<-1<<endl; continue; }
    	For(i,idx+1) cout<<i+1<<" ";
    	cout<<n+1<<" ";
    	for(iint i=idx+1; i<n-1; i++) cout<<i+1<<" ";
    	cout<<n<<endl;
    }
}
/*
start at 1 or n+1
if start at n+1, n+1 --> 1
if end at n+1 n-->n+1

if start at 1
n+1 is just a jump that is used exactly once
We can't jump more than 1 step forward (else we can't backtrack).
so there must be a transition from 0 to 1! else fail
*/