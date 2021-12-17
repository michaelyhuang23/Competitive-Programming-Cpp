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
#include <unordered_set>

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
    iint tt; cin >> tt;
    while(tt--){
    	iint n; cin >> n;
    	vector<vector<iint>> edgeTo(n);
    	vector<iint> inDeg(n);
    	For(i,n) {
    		iint k; cin >> k;
    		For(j,k) {
    			int num; cin >> num; num--;
    			edgeTo[num].pb(i);
    			inDeg[i]++; 
    		}
    	}// read into adj list
    	//cout<<"hello"<<endl;
    	//deb(edgeTo);
    	priority_queue<iint, vector<iint>, greater<iint> > pq;
    	For(i,n){
    		assert(inDeg[i]>=0);
    		if(inDeg[i]==0) pq.push(i);
    	}//handle -1 case
        if(pq.empty()){
            cout<<-1<<endl;
            continue;
        }
    	iint iter = 0;
        iint insertC = 0;
    	vector<iint> delIter(n,-1);
    	while(!pq.empty()){
    		iter++;
    		unordered_set<iint> newPQ;
    		while(!pq.empty()){
    			iint v = pq.top(); pq.pop();
                assert(delIter[v]==-1);
                assert(inDeg[v] == 0);
    			delIter[v] = iter;
    			for(iint u : edgeTo[v]){
    				inDeg[u]--;
    				if(inDeg[u]==0){
                        assert(u!=v);
	    				if(u<v) {
                            insertC++;
                            newPQ.insert(u);
                        }else{
                            pq.push(u);
                        }
	    			}
    			}
    		}
    		for(iint v : newPQ)
    			pq.push(v);
    	}
    	bool suc = true;
    	For(i,n) if(delIter[i]==-1) suc=false;
    	if(!suc){
    		cout<<-1<<endl;
    		continue;
    	}
    	iint maxIter = 0;
    	For(i,n) maxIter = max(maxIter, delIter[i]);
//        if(maxIter == 1){
//           // For(i,n) for(iint v : edgeTo[i]) if(v<=i) assert(insertC>0);
//        }
    	cout<<maxIter<<endl;

    }
}





