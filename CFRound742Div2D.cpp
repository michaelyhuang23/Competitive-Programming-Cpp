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
    int tt; cin >> tt;
    vector<llong> pow10(15);
    pow10[0]=1;
    for(int i=1; i<15; i++) pow10[i] = pow10[i-1]*10;
    while(tt--){
    	string s;
    	int n;
    	cin >> s >> n;
    	llong num = stol(s);
    	llong redun = 0;
    	if(n==1){
    		cout<<s<<endl;
    		continue;
    	}
    	for(int i=s.length()-1; i>=0 ; i--){
    		int v = s[i] - '0';
    		redun += v*pow10[s.length()-1-i];
    		if(redun>=n-1){
    			if(num - redun == 0){
    				for(int j=0; j<n-1; j++)
	    				cout<< 1 << " ";
	    			cout<<redun - (n-1)<<endl;
	    			break;
    			}
    			cout<< num-redun << " ";
    			for(int j=0; j<n-2; j++)
    				cout<< 1 << " ";
    			cout<<redun - (n-2)<<endl;
    			break;
    		}
    	}
    }
}


/*

we don't want any decomposition that demotes/removes a digit
especially higher digits!

so we decompose from the unit digit
if that isn't enough, we move to tenth digit


!!!!! Failed
This isn't good enough
when we break a digit, we should try to make it into smaller parts 
that preserve as many digits as possible. 
91 --> 71 10 10
instead of 
91 --> 89 1 1
*/