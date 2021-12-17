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
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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

typedef tree<tuple<iint,iint,iint>,null_type,greater<tuple<iint,iint,iint>>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint n,m;
    cin >> n >> m;
    ordered_set scoreboard;
    pair<iint,iint>* scores = new pair<iint,iint>[n];
    For(i,n) scores[i] = make_pair(0,0);
    For(i,m){
    	iint t, p;
    	cin >> t >> p;
		t = n-t;
		iint s = get<0>(scores[t]);
		iint pen = get<1>(scores[t]);
		auto prev_score = make_tuple(s,pen,t);
		//cout<<"old "<<s<<" "<<pen<<" "<<t<<endl;
		if(scoreboard.find(prev_score) != scoreboard.end()){
    		scoreboard.erase(prev_score);
    		//cout<<"found"<<endl;
		}
		s++; pen-=p;
		scores[t] = make_pair(s,pen);
    	auto full_score = make_tuple(s,pen,t);
    	scoreboard.insert(full_score);
    	//cout<<"new "<<s<<" "<<pen<<" "<<t<<endl;
    	auto t_score = make_tuple(get<0>(scores[n-1]),get<1>(scores[n-1]),n-1);
    	//cout<<"cur "<<get<0>(scores[n-1])<<" "<<get<1>(scores[n-1])<<" "<<n-1<<endl;
    	// for(auto f : scoreboard){
    	// 	cout<<get<0>(f)<<" "<<get<1>(f)<<" "<<get<2>(f)<<endl;
    	// }
    	if(scoreboard.find(t_score) == scoreboard.end()){
    		cout<<scoreboard.size()+1<<endl;
    	}else{
    		cout<<scoreboard.order_of_key(t_score)+1<<endl;
    	}
    }
}


