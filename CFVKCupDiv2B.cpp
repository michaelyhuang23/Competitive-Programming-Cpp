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
    while(tt--){
    	set<iint> ks;
    	iint a, b;
    	cin >> a >> b;
    	// say AAAABBB...
    	//     aaabbbb
    	//.    bbbaaaa
    	//.    bbbbbaa
    	iint n = a+b;
    	iint B,A;
    	if(n%2==1){
    		B = n/2;
    		A = n/2+1;
    	}else{
    		B = n/2;
    		A = n/2;
    	}
    	iint most = n-max((A-b), (B-a));
		iint least = max((A-a), (B-b));
		//cout<<most<<" "<<least<<endl;
		assert((most-least)%2==0);
		for(iint k=least; k<=most; k+=2){
			//cout<<"inserting "<<k<<endl;
			ks.insert(k);
		}

		// say BBBBAAA
		if(n%2==1){
    		B = n/2+1;
    		A = n/2;
    	}else{
    		B = n/2;
    		A = n/2;
    	}
    	most = n-max((A-b), (B-a));
		least = max((A-a), (B-b));
		//cout<<most<<" "<<least<<endl;
		assert((most-least)%2==0);
		for(iint k=least; k<=most; k+=2){
			ks.insert(k);
			//cout<<"inserting "<<k<<endl;
		} 

		cout<<ks.size()<<endl;
		//deb(ks);
		vector<iint> ksvec;
		for(iint k : ks) ksvec.pb(k);
		for(iint i=0; i<ksvec.size()-1; i++)
			cout<<ksvec[i]<<" ";
		cout<<ksvec[ksvec.size()-1]<<endl;
    }
}

/*

seq doesn't matter
either alice serve first or borys
ABABABABABABAB
bbabababbbbbbb

ABA
aba
BAB
aab

AB
ba
*/








