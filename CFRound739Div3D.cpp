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
    iint t; cin>>t;
    while(t--){
    	llong num; cin>>num;
    	string nums = to_string(num);
    	iint minElim = inf;
    	for(int k = 0; k<64; k++){
    		ullong pow = 1ull << k;
    		//llong pow = 65536;
    		string pows = to_string(pow);
    		//cout<<nums<<" "<<pows<<endl;
    		int j=0;
    		iint elim=-1;
    		for(int i=0;i<pows.length();i++){
    			while(j<nums.length() && nums[j]!=pows[i]) j++;
    			if(j>=nums.length()){
    				// i is num that has found partner
    				//cout<<nums.length()<<" "<<i<<" "<<pows.length()<<endl;
    				elim = nums.length()-i + pows.length()-i;
    				break;
    			}
    			j++;
    		}
    		if(elim == -1){
    			//cout<<nums.length()<<" "<<pows.length()<<endl;
    			elim = nums.length() - pows.length();
    		}
    		//cout<<pows<<" elim "<<elim<<endl;
    		minElim = min(minElim,elim);
    	}
    	cout<<minElim<<endl;
    }
}
/*
given string of number;
find subsequence of string that correspond to the digits of a 2^k

the number of operations we need:
the number of digits we skipped(del) + the number of digits we need 
to add to the end

upperbound of numbers is 10^18 (we need to add 9 zeros); why not just 
delete numbers down to 1?
*/






