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

iint maxPrime[1000000];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(maxPrime, maxPrime+1000000, 1);

    for(iint i=2; i<1000000; i++){
    	if(maxPrime[i]==1)
	    	for(iint p=1; p*i<1000000; p++)
	    		maxPrime[p*i] = i;
    }
    maxPrime[1] = 0;
    assert(maxPrime[2]==2);
    assert(maxPrime[13]==13);
    assert(maxPrime[24]==3);

    int tt; cin >> tt;
    while(tt--){
    	int k; cin>>k;
    	int arr[k];
    	string n; cin>>n;
    	assert(n.length() == k);
    	For(i,k) arr[i] = n[i] - '0';
    	int foundDigit = 0;
    	For(i,k) if(maxPrime[arr[i]] != arr[i]) foundDigit=arr[i];
    	if(foundDigit>0){
	    	cout<<1<<endl;
	    	cout<<foundDigit<<endl;
	    	continue;
	    }
    	int digitCount[10];
    	fill(digitCount,digitCount+10,0);
    	For(i,k) digitCount[arr[i]]++;
    	// For(i,10) cout<<digitCount[i]<<" ";
    	// cout<<endl;
    	foundDigit=0;
    	for(int i=1; i<10; i++) if(digitCount[i]>1) foundDigit=i;
    	if(foundDigit>0){
    		cout<<2<<endl;
    		cout<<foundDigit<<foundDigit<<endl;
    		continue;
    	}
    	assert(k<5);
    	iint range = 1<<k;
    	string foundNum;
    	for(iint i = 0; i<range; i++){
    		//cout<<"runing "<<i<<endl;
    		vector<int> num;
    		For(j,k)
    			if(i & 1<<j) num.pb(arr[j]);
    		string snum;
    		for(int j=0; j<num.size(); j++){
    			snum = snum + to_string(num[j]);
    		}
    		//deb(snum);
    		if(snum.length()<1) continue;
    		iint nn = stol(snum);
    		if(maxPrime[nn] != nn){
    			foundNum = snum;
    			break;
    		}
    	}
    	cout<<foundNum.length()<<endl;
    	cout<<foundNum<<endl;
    }
}

/*

how many digits to keep at worst? if k>=10, pigeonhole: 1 repeat
so 2 digits is max in this case

if k<10; try all possibilities

2,3,5,7
if k>=5, 1 repeat
else k<5: use sieve to check

*/









