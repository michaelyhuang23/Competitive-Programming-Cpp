#include <iostream>
#include <fstream>
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

ofstream fout("seating.out");
ifstream fin("seating.in");

struct SegTree
{
	enum UpdateType{ None, Add, Remove };
	static iint pow_up(iint num){
		For(i,65) if(1<<i >= num) return 1<<i;
		return -1;
	}
	iint* mt = nullptr;
	iint* ml = nullptr;
	iint* mr = nullptr;
	iint* le = nullptr;
	iint* rs = nullptr;
	UpdateType* pd = nullptr;
	iint n;
	SegTree(iint* arr,iint size){
		n = pow_up(size);
		mt = new iint[n*2];
		ml = new iint[n*2];
		mr = new iint[n*2];
		le = new iint[n*2];
		rs = new iint[n*2];
		pd = new UpdateType[n*2];
		fill(rs,rs+2*n,-1);
		fill(le,le+2*n,-1);
		For(i,n){
			if(i<size){
				rs[i+n]=i;
				le[i+n]=i;
			}
		}

		fill(pd,pd+n*2,None);
		copy(arr, arr+size, mt+n);
		copy(arr, arr+size, ml+n);
		copy(arr, arr+size, mr+n);
		fill(mr+n+size,mr+2*n,0);
		fill(ml+n+size,ml+2*n,0);
		fill(mt+n+size,mt+2*n,0);
		build();
	}
	inline void pull_up(iint i){
		mt[i] = max(mt[i<<1],mt[i<<1|1]);
		mt[i] = max(mt[i], mr[i<<1] + ml[i<<1|1]);
		ml[i] = ml[i<<1];
		mr[i] = mr[i<<1|1];
		le[i] = le[i<<1];
		rs[i] = rs[i<<1|1];
		if(le[i<<1]>-1 && rs[i<<1]>-1 && le[i<<1]>=rs[i<<1]){ //connectivity (le if doesn't exist should be to the left of ls, rs if doesn't exist should be to the right of re)
			ml[i] = ml[i<<1] + ml[i<<1|1];
			if(le[i<<1|1]>-1)
				le[i] = le[i<<1|1];
		}
		if(le[i<<1|1]>-1 && rs[i<<1|1]>-1 && rs[i<<1|1]<=le[i<<1|1]){
			mr[i] = mr[i<<1|1] + mr[i<<1];
			if(rs[i<<1]>-1)
				rs[i] = rs[i<<1];
		}
		mt[i] = max(mt[i],max(ml[i],mr[i]));
	}
	inline void build(){
		for(iint i = n-1; i>=1; i--){ pull_up(i); }
	}
	inline void update(iint idx, iint ts, iint te, iint left, iint right,bool add){
		//cout<<"call update: "<<idx<<" "<<ts<<" "<<te<<" "<<left<<" "<<right<<" "<<add<<endl; 
		if(left>right) return;
		if(ts == left && te == right){ 
			//fout<<"updating "<<idx<<" "<<ts<<" "<<te<<" "<<mt[1]<<endl;
			if(add){
				mt[idx]=te-ts+1; 
				ml[idx]=te-ts+1;
				mr[idx]=te-ts+1;
				le[idx]=te;
				rs[idx]=ts;
				pd[idx]=Add;
			}else{
				mt[idx]=0;
				ml[idx]=0;
				mr[idx]=0;
				le[idx]=-1;
				rs[idx]=-1;
				pd[idx]=Remove;
			}
			return;
		}
		push_down(idx, ts, te); //update to most current for backtrace reupdate
		iint tm = (ts+te)>>1;
		if(left<=tm)
			update(idx<<1,ts,tm,left,min(right,tm),add);
		if(right>tm)
			update(idx<<1|1,tm+1,te,max(tm+1,left),right,add);
		// reupdate values upstream
		pull_up(idx);
		//fout<<"bt "<<idx<<" "<<ts<<" "<<te<<" "<<mt[idx]<<" "<<mt[1]<<" "<<rs[idx]<<" "<<le[idx]<<endl;
		//fout<<mt[3]<<" "<<rs[3]<<" "<<le[3]<<endl;
		// cout<<idx<<" "<<mt[idx]<<" "<<ml[idx]<<" "<<mr[idx]<<" "<<le[idx]<<" "<<rs[idx]<<endl;
		// cout<<idx*2<<" "<<mt[idx*2]<<" "<<ml[idx*2]<<" "<<mr[idx*2]<<" "<<le[idx*2]<<" "<<rs[idx*2]<<endl;
		// cout<<idx*2+1<<" "<<mt[idx*2+1]<<" "<<ml[idx*2+1]<<" "<<mr[idx*2+1]<<" "<<le[idx*2+1]<<" "<<rs[idx*2+1]<<endl;
	}
	inline void update(iint left, iint right, bool add){ 
		//push_all_down(1, 0, n-1);
		//build();
		update(1,0,n-1,left,right,add); 
	}
	inline void push_down(iint idx, iint ts, iint te){
		if(idx>=n || pd[idx]==None) return;
		iint tm = (ts+te)>>1;
		assert(tm!=te);
		if(pd[idx]==Add){
			mt[idx<<1] = tm-ts+1, ml[idx<<1] = tm-ts+1, mr[idx<<1] = tm-ts+1;
			mt[idx<<1|1] = te-tm, ml[idx<<1|1] = te-tm, mr[idx<<1|1] = te-tm;
			le[idx<<1] = tm, le[idx<<1|1] = te;
			rs[idx<<1] = ts; rs[idx<<1|1] = tm+1;
		}else{
			mt[idx<<1] = 0, ml[idx<<1] = 0, mr[idx<<1] = 0;
			mt[idx<<1|1] = 0, ml[idx<<1|1] = 0, mr[idx<<1|1] = 0;
			le[idx<<1] = -1, le[idx<<1|1] = -1;
			rs[idx<<1] = -1; rs[idx<<1|1] = -1;
		}
		pd[idx<<1] = pd[idx];
		pd[idx<<1|1] = pd[idx];
		pd[idx] = None;
	}
	inline llong query(iint idx, iint ts, iint te, iint cutoff){
		// both inclusive; ts, te indicate the coverage of this index
		if(ts==te){
			if(mt[idx]>=cutoff) return ts;
			else assert(false);
		}
		push_down(idx,ts,te);

		iint tm = (ts+te)>>1;
		if(mt[idx<<1]>=cutoff)
			return query(idx<<1,ts,tm,cutoff);
		else if(mr[idx<<1] + ml[idx<<1|1] >= cutoff && mr[idx<<1]>0){
			return rs[idx<<1];
		}else
			return query(idx<<1|1,tm+1,te,cutoff);
	}
	inline llong query(iint cutoff){
		//push_all_down(1, 0, n-1);
		//build();
		//fout<<mt[1]<<endl;
		if(mt[1]<cutoff) return -1;
		return query(1,0,n-1,cutoff);
	}
	inline void push_all_down(iint idx, iint ts, iint te){
		if(idx>=n) return;
		push_down(idx, ts, te);
		iint tm = (ts+te)>>1;
		push_all_down(idx<<1, ts, tm);
		push_all_down(idx<<1|1, tm+1, te);
	}
	inline void push_all_down(iint idx){
		push_all_down(1, 0, n-1);
	}
};

int main(){
    ios_base::sync_with_stdio(0);
    fin.tie(0);

    iint n,m;
    fin >> n >> m;
    iint* arr = new iint[n];
    fill(arr,arr+n,1);
    SegTree tr(arr,n);
    iint fail=0;
    For(i,m){
    	string type;
    	fin >> type;
    	if(type=="A"){
    		iint p;
    		fin >> p;
    		//fout<<"real: "<<overallSuc<<endl;
    		iint ret = tr.query(p);
    		//fout<<"ret: "<<ret<<endl;
    		//fout<<tr.mt[1]<<endl;
    		if(ret==-1)
    			fail++;
    		else
    			tr.update(ret, ret+p-1, false);
    		//fout<<tr.mt[1]<<" "<<ret<<" "<<ret+p-1<<endl;
    		// tr.push_all_down(1);
    		// //fout<<tr.mt[1]<<endl;
    		// tr.build();
    		//fout<<tr.mt[1]<<endl;
    		//fout<<"stop"<<endl;
    				
    	}else{
    		iint a,b;
    		fin >> a >> b;
    		a--;
    		b--;
    		tr.update(a,b,true);
    		//fout<<tr.mt[1]<<endl;
    	}
    }
    fout<<fail<<'\n';
}


/*
	1. keep a list of intervals which are open sorted by lowest index (there can be no overlap)
	binary search interval in [a,b], merge them into a large interval
	This can be achievable with treeset (nope you can deal with the cutoff size)

	2. each node store the largest contiguous block-size
	each node stores:
	a. largest contaguous block
	b. left block
	c. right block
	d. connectivity of the three
	this can enable recursive search for the earliest contaguous block

	range update is possible because update on a large block determines the update of its children blocks
	
*/





















