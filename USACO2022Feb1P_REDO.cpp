// #include "debughelp.hpp"
#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define mt make_tuple
#define mp make_pair
#define pb push_back
#define inf 1000000000LL
#define print(x) cout<<x<<endl

struct Rect{
	llong xmin, xmax, ymin, ymax;
	Rect(){}
	Rect(llong x1, llong y1, llong x2, llong y2): xmin(x1), xmax(x2), ymin(y1), ymax(y2){}
};

struct UFDS{
	vector<llong> finder;
	UFDS(){}
	UFDS(llong n){
		finder = vector<llong>(n);
		iota(finder.begin(), finder.end(), 0);
	}
	llong find(llong a){
		llong olda = a;
		for(;finder[a]!=a;a=finder[a]);
		for(;finder[olda]!=a;){
			llong newa = finder[olda];
			finder[olda] = a;
			olda = newa;
		} 
		return a;
	}
	void merge(llong a,llong b){
		llong fa = find(a);
		llong fb = find(b);
		if(fa == fb) return;
		finder[fa] = fb;
	}
};


struct NodeS{
	llong val, pd; 
	NodeS():val(0), pd(0){};
	NodeS(llong val_):val(val_), pd(0){}
	void update(llong val_){
		val += val_;
		pd += val_;
	}
	static NodeS merge(NodeS& ll, NodeS& rr){
		NodeS mm;
		mm.val = ll.val + rr.val;
		return mm;
	}
	void pull_up(NodeS& ll, NodeS& rr){
		(*this) = merge(ll, rr);
	}
	void push_down(NodeS& ll, NodeS& rr){
		if(pd == 0) return;
		ll.update(pd);
		rr.update(pd);
		pd = 0;
	}
	llong ans() {return val;}
};

struct NodeP{
	llong cco, cce, ll, rr, pd;
	NodeP(llong val_) : pd(0), cco(0), cce(0), ll(val_), rr(val_) {
		if(val_&1) cco = 1;
		else cce = 1;
	}
	NodeP() : pd(0), cco(0), cce(0), ll(0), rr(0) {} // this is dubious
	static NodeP merge(NodeP& left, NodeP& right){
		NodeP ret; 
		ret.ll = left.ll;
		ret.rr = right.rr;
		ret.cco = left.cco + right.cco;
		ret.cce = left.cce + right.cce;
		if(left.rr == right.ll){
			if(left.rr&1) ret.cco--;
			else ret.cce--;
		} 
		return ret;
	}
	void update(llong val_){
		if(abs(val_)&1){ // changes color
			swap(cco,cce);
		}
		ll += val_;
		rr += val_;
		pd += val_;
	}

	void pull_up(NodeP& left, NodeP& right){
		(*this) = merge(left, right);
	}

	void push_down(NodeP& left, NodeP& right){
		left.update(pd);
		right.update(pd);
		pd = 0;
	}

	tuple<llong,llong, llong, llong> ans(){ return mt(cco,cce,ll,rr); } // odd, even
};

template<typename Node>
struct segtree {
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
	segtree(llong size, bool init){
		n = pow_up(size);
		tree = vector<Node>(n*2,0);
		build();
	}
	void build(){
		for(llong i = n-1; i>=1; i--) tree[i].pull_up(tree[i*2], tree[i*2+1]);
	}
	void update(llong idx, llong ts, llong te, llong left, llong right, llong val){
		if(left>right) return;
		if(ts == left && te == right){ tree[idx].update(val); return; }
		tree[idx].push_down(tree[idx*2], tree[idx*2+1]);
		llong tm = (ts+te)/2;
		if(left<=tm)
			update(idx*2,ts,tm,left,min(right,tm),val);
		if(right>tm)
			update(idx*2+1,tm+1,te,max(tm+1,left),right,val);
		tree[idx].pull_up(tree[idx*2], tree[idx*2+1]);
	}
	void update(llong left, llong right, llong val){ update(1,0,n-1,left,right,val); }
	Node query(llong idx, llong ts, llong te, llong left, llong right){
		if(left>right) return Node();
		if(ts == left && te == right) return tree[idx];
		llong tm = (ts+te)/2;
        tree[idx].push_down(tree[idx*2], tree[idx*2+1]);
		if(left<=tm && right>tm){
			Node ll = query(idx*2,ts,tm,left,min(right,tm));
			Node rr = query(idx*2+1,tm+1,te,max(tm+1,left),right);
			return Node::merge(ll,rr);
		}
		if(left<=tm)
			return query(idx*2,ts,tm,left,min(right,tm));
		if(right>tm)
			return query(idx*2+1,tm+1,te,max(tm+1,left),right);
		tree[idx].pull_up(tree[idx*2], tree[idx*2+1]);
		return Node(); 
	}
	Node query(llong left, llong right){ 
		return query(1,0,n-1,left,right);
	}
};



llong N, T, K, F, CC, totalBlack, totalWhite;
llong RANGE1, RANGE2;
vector<Rect> rects;
vector<tuple<llong,llong,llong>> ptrs;
UFDS cctracker;
// x value, type (0: cc ptr, 1: left, 2: right), id









struct NodeCC{
	llong numFill;
	llong iddown;
	NodeCC():numFill(0), iddown(-1){}
	void insert(llong id){
		assert(iddown == -1); // only happens at leaf level
		iddown = cctracker.find(id);
		numFill = 1;
	}
	void remove(){
		iddown = -1;
		numFill = 0;
	}
	void mergedown(llong id){
		if(numFill>0){
			if(iddown == -1){
				iddown = cctracker.find(id);
			}else{
				cctracker.merge(iddown, id);
				iddown = cctracker.find(iddown);
			}
		}else assert(iddown == -1);
	}
	static NodeCC mergeup(NodeCC& ll, NodeCC& rr){
		NodeCC mm;
		mm.numFill = ll.numFill + rr.numFill;
		return mm;
	}
	void pull_up(NodeCC& ll, NodeCC& rr){
		(*this) = mergeup(ll,rr);
	}
	void push_down(NodeCC& ll, NodeCC& rr){
		if(iddown == -1) return;
		ll.mergedown(iddown);
		rr.mergedown(iddown);
		iddown = -1;
	}
};


struct segtreeCC {
	static llong pow_up(llong num){
		for(llong i=0;i<32;i++) if(1<<i >= num) return 1<<i;
		return -1;
	}
	vector<NodeCC> tree;
	llong n;
	segtreeCC(llong size){
		n = pow_up(size);
		tree = vector<NodeCC>(n*2);
		build();
	}
	void build(){
		for(llong i = n-1; i>=1; i--) tree[i].pull_up(tree[i*2], tree[i*2+1]);
	}
	void merge(llong idx, llong ts, llong te, llong left, llong right, llong val){
		if(left>right) return;
		if(ts == left && te == right){ tree[idx].mergedown(val); return; }
		tree[idx].push_down(tree[idx*2], tree[idx*2+1]);
		llong tm = (ts+te)/2;
		if(left<=tm)
			merge(idx*2,ts,tm,left,min(right,tm),val);
		if(right>tm)
			merge(idx*2+1,tm+1,te,max(tm+1,left),right,val);
		tree[idx].pull_up(tree[idx*2], tree[idx*2+1]);
	}
	void merge(llong left, llong right, llong val){ merge(1,0,n-1,left,right,val); }

	void insert(llong idx, llong ts, llong te, llong left, llong right, llong val){
		if(left>right) return;
		if(ts == left && te == right){ tree[idx].insert(val); return; }
		tree[idx].push_down(tree[idx*2], tree[idx*2+1]);
		llong tm = (ts+te)/2;
		if(left<=tm)
			insert(idx*2,ts,tm,left,min(right,tm),val);
		if(right>tm)
			insert(idx*2+1,tm+1,te,max(tm+1,left),right,val);
		tree[idx].pull_up(tree[idx*2], tree[idx*2+1]);
	}
	void insert(llong left, llong right, llong val){ insert(1,0,n-1,left,right,val); }

	void remove(llong idx, llong ts, llong te, llong left, llong right){
		if(left>right) return;
		if(ts == left && te == right){ tree[idx] = NodeCC(); return; }
		tree[idx].push_down(tree[idx*2], tree[idx*2+1]);
		llong tm = (ts+te)/2;
		if(left<=tm)
			remove(idx*2,ts,tm,left,min(right,tm));
		if(right>tm)
			remove(idx*2+1,tm+1,te,max(tm+1,left),right);
		tree[idx].pull_up(tree[idx*2], tree[idx*2+1]);
	}
	void remove(llong left, llong right){ remove(1,0,n-1,left,right); }
};


void preprocess(){
	rects = vector<Rect>(N);
	ptrs = vector<tuple<llong,llong,llong>>(); ptrs.reserve(2*N);
	RANGE1 = 2*N+5;
	RANGE2 = 2*RANGE1;
	for(llong i=0;i<N;i++){
		llong x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		rects[i] = Rect(x1,y1,x2,y2);
		ptrs.pb(mt(x1, 1, i));
		ptrs.pb(mt(x2, 2, i));
	}
}

void solve1(){
	sort(ptrs.begin(), ptrs.end());
	cctracker = UFDS(N);

	auto findCC = [&](){
		segtreeCC cctree(RANGE1);

		for(auto& ptr : ptrs){
			llong id = get<2>(ptr);
			llong type = get<1>(ptr);
			if(type == 1){ // left border
				cctree.merge(rects[id].ymin, rects[id].ymax, id); 
				// this is NOT query, it's merging
				cctree.insert(rects[id].ymin, rects[id].ymin, id);
				cctree.insert(rects[id].ymax, rects[id].ymax, id);
			}else{ // right border
				cctree.remove(rects[id].ymin, rects[id].ymin); // -1 for removal
				cctree.remove(rects[id].ymax, rects[id].ymax);
				cctree.merge(rects[id].ymin, rects[id].ymax, id);
				// this is merging
			}
		}
	};

	findCC();

	unordered_set<llong> CCs;
	for(llong i=0;i<N;i++){
		llong pi = cctracker.find(i);
		CCs.insert(pi);
	}

	CC = CCs.size();

	auto findIntersection = [&](){
		segtree<NodeS> stree(RANGE1);
		llong total = 0;
		for(auto& ptr : ptrs){
			llong id = get<2>(ptr);
			llong type = get<1>(ptr);
			if(type == 1){ // left border
				total+=stree.query(rects[id].ymin+1, rects[id].ymax-1).ans();
				stree.update(rects[id].ymin, rects[id].ymin, 1);
				stree.update(rects[id].ymax, rects[id].ymax, 1);
			}else{ // right border
				stree.update(rects[id].ymin, rects[id].ymin, -1);
				stree.update(rects[id].ymax, rects[id].ymax, -1);
				total+=stree.query(rects[id].ymin+1, rects[id].ymax-1).ans();
			}
		}
		return total;
	};

	K = findIntersection();

	F = 1 + K + CC;
}


void solve2(){
	auto countBlackRegion = [&](){
		segtree<NodeP> ctree(RANGE2,true);
		llong ocount = 0;
		for(auto& ptr : ptrs){
			llong id = get<2>(ptr);
			llong type = get<1>(ptr);

			auto ret = ctree.query(rects[id].ymin*2, rects[id].ymax*2).ans();
			llong co=get<0>(ret), ce=get<1>(ret), ll=get<2>(ret), rr=get<3>(ret);
			// deb(ptr)
			// deb(mt(co,ce,ll,rr))
			if(co == 1 && ce == 0){ // a split is possible
				llong lb = get<2>(ctree.query(rects[id].ymin*2-1, rects[id].ymin*2-1).ans());
				llong rb = get<3>(ctree.query(rects[id].ymax*2+1, rects[id].ymax*2+1).ans());
				assert((ll&1) && (rr&1));
				if(lb == ll && rb == rr) // both blead over --> split into 2
					ocount--;
				else if(lb != ll && rb != rr) // both not equal --> successful kill
					ocount++;
			}else{
				llong lb = get<2>(ctree.query(rects[id].ymin*2-1, rects[id].ymin*2-1).ans());
				llong rb = get<3>(ctree.query(rects[id].ymax*2+1, rects[id].ymax*2+1).ans());
				// deb(mp(lb,rb))
				if(lb == ll && (ll&1)) co--;
				if(rb == rr && (rr&1)) co--;
				ocount += co;
			}
			// deb(ocount)

			if(type == 1){ // left border
				ctree.update(rects[id].ymin*2, rects[id].ymax*2, 1);
			}else{ // right border
				ctree.update(rects[id].ymin*2, rects[id].ymax*2, -1);
			}
		}

		return ocount;
	};


	llong blackCount = countBlackRegion();

	//deb(blackCount)

	vector<llong> minXMin(N, inf);
	vector<llong> minI(N, inf);
	for(llong i=0;i<N;i++){
		llong pi = cctracker.find(i);
		if(rects[i].xmin < minXMin[pi]){
			minXMin[pi] = rects[i].xmin;
			minI[pi] = i;
		}
	}

	for(llong i=0;i<N;i++){
		if(minXMin[i] > inf/2) continue;
		// deb(mt(minXMin[i],0,minI[i]))
		ptrs.pb(mt(minXMin[i],0,minI[i]));
	}

	sort(ptrs.begin(), ptrs.end());

	auto countBlackCC = [&](){
		vector<llong> coverages(N,0);
		segtree<NodeS> stree(RANGE1);

		for(auto& ptr : ptrs){
			llong id = get<2>(ptr);
			llong type = get<1>(ptr);
			if(type == 0){
				llong pi = cctracker.find(id);
				// deb(mp(id,pi))
				coverages[pi] = stree.query(rects[id].ymin, rects[id].ymin).ans();
			}else if(type == 1){ // left border
				stree.update(rects[id].ymin, rects[id].ymax, 1);
			}else{ // right border
				stree.update(rects[id].ymin, rects[id].ymax, -1);
			}
		}

		// deb(coverages)

		llong oddC = 0;
		for(llong i=0;i<N;i++){
			if(coverages[i]&1) oddC++;
		}
		return oddC;
	};


	llong blackCC = countBlackCC();

	// deb(blackCC)
	// deb(blackCount)

	totalBlack = blackCount + blackCC;
	totalWhite = F - totalBlack;
}





































int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> T;
	preprocess();
	if(T==1){
		solve1();
		print(F);
	}else {
		solve1();
		solve2();
		cout<<totalWhite<<" "<<totalBlack<<endl;
	}
}