#include<bits/stdc++.h>


#define deb(x) cout << #x << " = " << x << endl;

using namespace std;

typedef long long llong;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000LL
#define print(x) cout<<x<<endl



struct Node{
	llong cco, cce, ll, rr, pd;
	Node(llong val_, llong id) : pd(0), cco(0), cce(0), ll(val_), rr(val_) {
		if(val_ % 2 == 1) cco = 1;
		else cce = 1;
	}
	Node() : pd(0), cco(0), cce(0), ll(0), rr(0) {} // this is dubious

	static Node merge(Node& left, Node& right){
		Node ret; 
		ret.ll = left.ll;
		ret.rr = right.rr;
		ret.cco = left.cco + right.cco;
		ret.cce = left.cce + right.cce;
		if(left.rr == right.ll){
			if(left.rr % 2 == 1) ret.cco--;
			else ret.cce--;
		} 
		return ret;
	}

	void change(llong val_){
		if(abs(val_) % 2 == 1){ // changes color
			swap(cco,cce);
		}
		ll += val_;
		rr += val_;
		pd += val_;
	}

	void pull_up(Node& left, Node& right){
		(*this) = merge(left, right);
	}

	void push_down(Node& left, Node& right){
		left.change(pd);
		right.change(pd);
		pd = 0;
	}

	pair<llong,llong> ans(){ return mp(cco,cce); } // odd, even
};

struct segtree {
	static llong pow_up(llong num){
		for(llong i=0;i<32;i++) if(1<<i >= num) return 1<<i;
		return -1;
	}

	vector<Node> tree;
	llong n;

	segtree(vector<llong>& arr,llong size){
		n = pow_up(size);
		tree = vector<Node>(n*2);
		for(llong i=0;i<size;i++) 
			tree[n+i] = Node(arr[i],i);
		build();
	}

	void build(){
		for(llong i = n-1; i>=1; i--) tree[i].pull_up(tree[i*2], tree[i*2+1]);
	}

	void update(llong idx, llong ts, llong te, llong left, llong right, llong val){
		if(left>right) return;
		if(ts == left && te == right){ tree[idx].change(val); return; }
		tree[idx].push_down(tree[idx*2], tree[idx*2+1]);
		llong tm = (ts+te)>>1;
		if(left<=tm)
			update(idx*2,ts,tm,left,min(right,tm),val);
		if(right>tm)
			update(idx*2+1,tm+1,te,max(tm+1,left),right,val);
		tree[idx].pull_up(tree[idx*2], tree[idx*2+1]);

	}

	void update(llong left, llong right, llong val){ update(1,0,n-1,left,right,val); }

	Node query(int idx, int ts, int te, int left, int right){
		if(left>right) return Node();

		if(ts == left && te == right) return tree[idx];
		int tm = (ts+te)>>1;
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
		return Node(); // let's hope the initialization works
	}

	pair<llong,llong> query(int left, int right){ 
		Node ret = query(1,0,n-1,left,right);
		return ret.ans();
	}

	llong query_point(int idx, int ts, int te, int loc){
		if(loc < ts || loc > te) return 0;
		if(ts == loc && te == loc) return tree[idx].ll;
		int tm = (ts+te)>>1;
        tree[idx].push_down(tree[idx*2], tree[idx*2+1]);
		if(loc<=tm)
			return query_point(idx*2,ts,tm,loc);
		else
			return query_point(idx*2+1,tm+1,te,loc);
	}

	llong query_point(int loc){
		return query_point(1,0,n-1,loc);
	}
};


struct Rect{
	llong xmin, ymin, xmax, ymax;
	Rect(){}
	Rect(int x1, int y1, int x2, int y2){
		xmin = x1;
		ymin = y1;
		xmax = x2;
		ymax = y2;
	}
};

void solve(){
	int N, T;
	cin >> N >> T;
	// assume type 2
	vector<Rect> rects(N);
	vector<tuple<llong,llong,llong>> ptrs;
	for(int i=0;i<N;i++){
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		x1--; y1--; x2--; y2--;
		x1 *= 2;
		y1 *= 2;
		x2 *= 2;
		y2 *= 2;
		rects[i] = Rect(x1,y1,x2,y2);
		ptrs.pb(mt(x1,y1,i));
		ptrs.pb(mt(x2,y2,i));
	}

	sort(ptrs.begin(), ptrs.end()); // default sorting is fine


	assert(ptrs.size() == 2*N);

	vector<llong> emptyArr(4*N,0);
	segtree tracker(emptyArr, 4*N);


	// deb(tracker.query(1,2))
	// deb(tracker.query(1,3))

	// deb(tracker.query_point(2))

	llong totalo = 0;
	llong totale = 0; // add one at the end
	for(int i=0;i<2*N;i++){
		auto ptr = ptrs[i];
		Rect rect = rects[get<2>(ptr)];


		// deb(ptr)
		// deb(mp(rect.ymin, rect.ymax))

		auto ret = tracker.query(rect.ymin, rect.ymax);
		llong counto = ret.first;
		llong counte = ret.second;

		//deb(mp(counto, counte))
		// the interval needs to be self contained as well
		//deb(count)

		// move by 1 is too far, when ending it's guaranteed to change color
		// when beginning it's guaranteed the two ends are contaguous
		llong yminm1 = tracker.query_point(rect.ymin-1);
		llong yminm = tracker.query_point(rect.ymin);
		llong ymaxp1 = tracker.query_point(rect.ymax+1);
		llong ymaxp = tracker.query_point(rect.ymax);

		if(yminm1 == yminm){
			if(yminm % 2 == 0) counte--;
			else counto--;
		}

		if(ymaxp1 == ymaxp){
			if(ymaxp % 2 == 0) counte--;
			else counto--;
		}

		//deb(mp(counto, counte))

		totalo += max(0LL,counto); // correct for over-subtraction
		totale += max(0LL,counte);


		//deb(ptr)
		// we retrieve values at the begin point before making modifications 
		// we retrieve values at the end point before making modifications
		if(get<0>(ptr) == rect.xmin){ // begin point
			tracker.update(rect.ymin, rect.ymax, 1);
		}else{ // end point
			tracker.update(rect.ymin, rect.ymax, -1);
		}
	}

	totale++; // plus background
	if(T==1){
		print(totalo + totale);
	}else{
		cout<<totale<<" "<<totalo<<endl;
	}
}












int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}