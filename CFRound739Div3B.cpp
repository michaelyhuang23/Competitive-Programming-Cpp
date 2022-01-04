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
    int t;
    cin>>t;
    while(t--){
    	iint a,b,c;
    	cin >> a >> b >> c;
    	iint half = max(a,b)-min(a,b);
    	if(min(a,b)>half || max(a,b)<=half){
    		cout<<-1<<endl; continue;
    	}
    	if(c>2*half || c<1){
    		cout<<-1<<endl; continue;
    	}
    	if(c>half){
    		cout<<c-half<<endl; continue;
    	}else{
    		cout<<c+half<<endl; continue;
    	}
    }
}