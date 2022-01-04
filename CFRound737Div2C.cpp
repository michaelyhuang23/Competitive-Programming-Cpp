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

llong modulo_pow(llong base,llong exp) {
    llong result=1;
    while(exp > 0){
        if(exp%2 == 1){
            result=(result*base)%MOD; //getting rid of the odd term
        }
        base = (base*base)%MOD; // squaring the base
        exp /= 2;
    }
    return (llong) result%MOD;
}

llong invert(llong num){
	return modulo_pow(num, MOD-2);
}

llong choose(llong a, llong b){
	llong numer = 1;
	for(llong i = a; a-i<b; i--){
		numer *= i; 
		numer %= MOD;
	}
	llong denom = 1;
	for(llong i=1;i<=b;i++){
		denom *= invert(i);
		denom %= MOD;
	}
	return (numer*denom)%MOD;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--){
    	iint n,k;
    	cin >> n >> k;
    	if(n%2==1){
    		llong count = 0; // choices for each digit
    		// For(i, n/2+1){
    		// 	iint p = i*2;
    		// 	count += choose(n,p);
    		// 	count %= MOD;
    		// }
    		count = (modulo_pow(2, n)*invert(2))%MOD;
    		count += 1; // be full
    		count %= MOD;
    		cout<<modulo_pow(count, k)<<endl;
    	}else{
    		llong counte = 0;
    		// For(i, n/2){ // not the last cuz not full
    		// 	iint p = i*2;
    		// 	counte += choose(n,p);
    		// 	counte %= MOD;
    		// }
    		counte = (modulo_pow(2, n)*invert(2)-1)%MOD;
    		//cout <<"counte "<< counte<< endl;
    		llong totalChoices = 0;
    		for(iint i=k-1; i>=0; i--){
    			llong evenchoice = modulo_pow(counte, k-1-i);
    			llong otherchoice = modulo_pow(2, (llong)n*(llong)i);
    			llong choices = (evenchoice * otherchoice)%MOD;
    			totalChoices += choices;
    			totalChoices %= MOD;
    		}
    		totalChoices += modulo_pow(counte, k);
    		totalChoices %= MOD;
    		cout<<totalChoices<<endl;
    	}
    }
}

/*

Question: given n, k, find all arrays with size n and max elmen<2^k such that
sum of & >= sum of $
The only surviving parts of sum of & is the parts where all are 1.
These parts become 0 if n is even else if n is odd, it's 1
so if n is even, that part is guaranteed greater or equal. 
if n is odd, that part (and all parts) are smaller or equal.

odd is simple:
if there's odd 1s, that gives 1, condition not satisfied
if there's even 1s, they will pair out to zeros, now that gives 0, condition satisfied
so each number must have even 1s. (except the full 1s)

even is harder:
we have to check if there's a single one above these shared parts
if there's odd 1s, it gives 1
if there's even 1s, it gives 0
so all digits above the higest shared must be even 1s

how to find the highest shared. we don't! we decide!




*/

