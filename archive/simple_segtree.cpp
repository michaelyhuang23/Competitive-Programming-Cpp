//#pragma once
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
#define For(i, j) for (int i = 0 ; i < j ; i ++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007

struct CHMinNode{
	llong val;
	CHMinNode() : val(inf) {}
	CHMinNode(llong val_) : val(val_) {}
	static CHMinNode merge(CHMinNode& ll, CHMinNode& rr){
		CHMinNode ret(min(ll.val, rr.val));
		return ret;
	}
	void pull_up(CHMinNode& ll, CHMinNode& rr){
		(*this) = merge(ll,rr);
	}
	void update(llong val_){
		val = min(val,val_);
	}
	llong ans() { return val; }
};

struct MinNode{
	llong val;
	MinNode() : val(inf) {}
	MinNode(llong val_) : val(val_) {}
	static MinNode merge(MinNode& ll, MinNode& rr){
		MinNode ret(min(ll.val, rr.val));
		return ret;
	}
	void pull_up(MinNode& ll, MinNode& rr){
		(*this) = merge(ll,rr);
	}
	void update(llong val_){
		val = val_;
	}
	llong ans() { return val; }
};

struct CHMaxNode{
	llong val;
	CHMaxNode() : val(-inf) {}
	CHMaxNode(llong val_) : val(val_) {}
	static CHMaxNode merge(CHMaxNode& ll, CHMaxNode& rr){
		CHMaxNode ret(max(ll.val, rr.val));
		return ret;
	}
	void pull_up(CHMaxNode& ll, CHMaxNode& rr){
		(*this) = merge(ll,rr);
	}
	void update(llong val_){
		val = max(val,val_);
	}
	llong ans() { return val; }
};


template<typename Node>
struct segtree{
	static llong pow_up(llong num){
		for(llong i=0;i<32;i++) if(1<<i >= num) return 1<<i;
		return -1;
	}
	vector<Node> tree;
	llong n;
	segtree(llong size){
		n = pow_up(size);
		tree = vector<Node>(n*2);
		build();
	}
	void build(){
		for(llong i = n-1; i>=1; i--) tree[i].pull_up(tree[i<<1], tree[i<<1|1]);
	}
	void rebuild(){
		fill(tree.begin()+n, tree.end(), Node());
		build();
	}
	void update(llong idx, llong val){
		tree[n+idx].update(val);
		for(llong i = (n+idx)>>1; i >= 1; i>>=1) tree[i].pull_up(tree[i<<1], tree[i<<1|1]);
	}
	llong query(llong left, llong right){
		// both inclusive
		Node ll, rr;
		left+=n, right+=n;
		for(;left<=right;left>>=1,right>>=1){
			if(left&1) ll=Node::merge(ll,tree[left++]);
			if(!(right&1)) rr=Node::merge(tree[right--],rr);
			if(left==right) break; 
		}
		//end condition is correct because only 1 of these 2 can be true then
		return Node::merge(ll,rr).ans();
	}
};