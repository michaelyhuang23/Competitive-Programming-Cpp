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

struct SMatrix{ // square matrix
	iint n;
	vector<vector<llong> > A;
	SMatrix(iint n_, iint num){ n = n_; A = vector<vector<llong> >(n); For(i,n) A[i] = vector<llong>(n,num); }
	SMatrix(iint n_){
		n=n_;
		A = vector<vector<llong> >(n); For(i,n) A[i] = vector<llong>(n,0);
		for(iint r=0;r<n;r++) for(iint c=0;c<n;c++) if(r==c) A[r][c]=1; 
	}
	SMatrix() : SMatrix(130){}
	SMatrix mul(SMatrix o){
		assert(n == o.n); // A@o.A
		SMatrix p(n,0);
		for (iint r = 0; r < n; r++)
			for (iint c = 0; c<n; c++)
				for(iint i = 0; i<n; i++) {
					p.A[r][c] += o.A[i][c]*A[r][i];
					p.A[r][c] %= MOD;
				}
		return p;
	}
};

SMatrix mexp(SMatrix p, iint n){
    iint maxbit = 0;
    for(maxbit=0; maxbit<64; maxbit++) if((1L<<maxbit)>n) break;
    maxbit++;
	vector<SMatrix> p2s(maxbit);
	p2s[0] = p;
	for(iint i=1; i<maxbit; i++)
		p2s[i] = p2s[i-1].mul(p2s[i-1]);
	SMatrix final(p.n);
	for(iint i=0; i<maxbit; i++){
		if(((1L<<i) & n)) final = final.mul(p2s[i]);
	}
	return final;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    llong n, m; // n is max value
    cin >> n >> m;
    SMatrix co(26,1);
    For(i,m){
    	char a,b; iint c;
    	cin >> a >> b >> c;
    	a -= 'a';
    	b -= 'a';
    	co.A[a][b] = c;
    	co.A[b][a] = c;
    }
    SMatrix tr(131,0);
    for(iint c = 0; c < 130; c++){
    	iint step = c / 26 + 1;
    	iint let = c%26;
    	if(step == 5) break;
    	for(iint r = 0; r < 130; r++){
    		iint istep = r / 26 + 1;
    		iint ilet = r%26;
    		if(istep != step+1) continue;
    		if(ilet==let) tr.A[r][c] = 1;
    	}
    }
    for(iint c = 0; c < 130; c++){
    	iint step = c / 26 + 1;
    	iint let = c % 26;
    	if(step != 5) continue;
    	for(iint r = 0; r < 130; r++){
    		iint istep = r / 26 + 1;
    		iint ilet = r % 26;
    		if(co.A[ilet][let] == 6-istep) tr.A[r][c]+=1;
    	}
    }
    for(iint c = 26*4; c < 130; c++){
        for(iint r = 0; r < 130; r++){
            tr.A[r][130] += tr.A[r][c];
            tr.A[r][130] %= MOD;
        }
    }
    tr.A[130][130]=1;
    SMatrix final = mexp(tr, n);
    vector<llong> I(131,0);
    for(iint i=0; i<130; i++) if(i/26+1 == 5) I[i]=1;
    I[130] = 26;
    vector<llong> result(131,0);
    for(iint c=0; c<131; c++) {
    	llong summ = 0;
    	for(iint r=0; r<131; r++) {summ+=I[r]*final.A[r][c]; summ%=MOD;}
    	result[c] = summ;
    }
    llong summ = result[130];
	cout<<summ<<endl;
}


//    vector<vector<llong> > dp(21);
//    For(i, 21) dp[i] = vector<llong>(26,0);
//    dp[0] = vector<llong>(26,1);
//    for(iint i=1; i<21; i++){
//        for(iint j=max(0L,i-5); j<i; j++){
//            for(iint jlet = 0; jlet<26; jlet++){
//                for(iint ilet=0; ilet<26; ilet++){
//                    if(co.A[ilet][jlet] == i-j){
//                        dp[i][ilet] += dp[j][jlet];
//                        dp[i][ilet] = (dp[i][ilet]+MOD)%MOD;
//                    }
//                }
//            }
//        }
//    }
//    vector<iint> fresult(26);
//    For(i,26) fresult[i] = result[26*4+i];
//    deb(fresult);
//    deb(dp[20]);
//    For(i,26) assert(fresult[i] == dp[20][i]);
