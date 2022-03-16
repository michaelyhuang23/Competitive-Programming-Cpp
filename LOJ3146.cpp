#include<bits/stdc++.h>

//#include "debughelp.hpp"

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000
#define print(x) cout<<x<<endl

struct AddNode{
	int val, pd;
	int ts, te;
	AddNode() : val(0), pd(0), ts(inf), te(-inf) {}
	AddNode(int ts_, int te_) : val(0), pd(0), ts(ts_), te(te_) {}
	static AddNode merge(AddNode ll, AddNode rr){
		AddNode m(min(ll.ts, rr.ts), max(ll.te, rr.te));
		m.val = ll.val + rr.val;
		return m;
	}
	void pull_up(AddNode& ll, AddNode& rr){
		(*this) = merge(ll, rr);
	}
	void push_down(AddNode& ll, AddNode& rr){
		ll.update(pd);
		rr.update(pd);
		pd = 0;
	}
	void update(int num){
		val += num*(te-ts+1);
		pd += num;
	}
	int ans(){
		return val;
	}
	bool latent(){
		return pd!=0;
	}
};

template<class Node>
struct DynamicNode{
	const static int n = 1000000;
	Node node;
	DynamicNode<Node>* left=nullptr;
	DynamicNode<Node>* right=nullptr;
	DynamicNode(int ts = 0, int te = n-1){
		node = Node(ts, te);
		left = nullptr;
		right = nullptr;
	}
	void push_down(int ts, int te){
		int tm = (ts+te)/2;
		if(!node.latent() || ts==te) return;
		if(!left) left = new DynamicNode(ts,tm);
		if(!right) right = new DynamicNode(tm+1,te);
		node.push_down(left->node, right->node);
	}
	void pull_up(){
		Node leftNode, rightNode;
		if(left) leftNode = left->node;
		if(right) rightNode = right->node;
		node.pull_up(leftNode, rightNode);
	}
	Node query(int ll, int rr, int ts=0, int te=n-1){
		if(ll > rr) return Node(); // default
		if(ll == ts && rr == te) return node;
		push_down(ts, te);
		int tm = (ts+te)/2;
		Node leftNode, rightNode;
		if(left && ll <= tm) 
			leftNode = left->query(ll,min(rr,tm),ts,tm);
		if(right && rr > tm)
			rightNode = right->query(max(ll,tm+1),rr,tm+1,te);
		pull_up();
		return Node::merge(leftNode, rightNode);
	}
	void update(int ll, int rr, int val, int ts=0, int te=n-1){
		if(ll>rr) return;
		if(ll==ts && rr==te){
			node.update(val);
			return;
		}
		push_down(ts, te);
		int tm = (ts+te)/2;
		if(ll <= tm){
			if(!left) left = new DynamicNode(ts, tm);
			left->update(ll,min(tm,rr),val,ts,tm);
		}
		if(rr > tm){
			if(!right) right = new DynamicNode(tm+1, te);
			right->update(max(tm,ll),rr,val,tm+1,te);
		}
		pull_up();
	}
};

struct segtree2D{ // 2D range query is fine but pushdown range update is impossible
	int n;
	vector<DynamicNode<AddNode>> tree;
	int pow_up(int num){
		for(int i=0;i<32;i++) if((1<<i)>=num) return 1<<i;
		return -1;
	}
	segtree2D(int n_){
		n = pow_up(n_);
		tree = vector<DynamicNode<AddNode>>(2*n, DynamicNode<AddNode>());
	}

	void update(int idx, int ts, int te, int x, int y, int val){
		if(ts <= x && te >= x){
			tree[idx].update(y, y, val);
			if(ts==te) return;
		}
		int tm = (ts+te)/2;
		if(x<=tm) update(idx*2, ts, tm, x, y, val);
		else update(idx*2+1, tm+1, te, x, y, val);
	}

	void update(int x, int y, int val) { update(1,0,n-1,x,y,val); }

	AddNode query(int idx, int ts, int te, int x1, int x2, int y1, int y2){
		if(x1>x2) return AddNode();
		if(ts == x1 && te == x2){
			return tree[idx].query(y1, y2);
		}
		int tm = (ts+te)/2;
		AddNode leftNode, rightNode;
		if(x1<=tm)
			leftNode = query(idx*2, ts, tm, x1, min(x2,tm), y1, y2);
		if(x2>tm)
			rightNode = query(idx*2+1, tm+1, te, max(x1,tm+1), x2, y1, y2);
		return AddNode::merge(leftNode, rightNode);
	}

	int query(int x1, int x2, int y1, int y2){  return query(1,0,n-1,x1,x2,y1,y2).ans(); }
};


void solve(){
	int n, q; cin >> n >> q;
	string s; cin >> s;
	vector<bool> open(n);
	for(int i=0;i<n;i++){
		open[i] = s[i] == '1';
	}
	set<pair<int,int>> intervals;
	int px = -1;
	for(int i=0;i<n;i++){
		if(i==0 && open[i] || open[i] && !open[i-1]){
			px = i; // start
		}
		if(i==n-1 && open[i] || open[i] && !open[i+1]){
			intervals.insert(mp(px, i)); // end
		}
	}

	//deb(intervals)

	segtree2D tracker(n+5);
	segtree2D sumtracker(n+5);

	auto updateRect = [&](segtree2D& tree, int x1, int x2, int y1, int y2, int val){
		tree.update(x1,y1,val);
		tree.update(x1,y2+1,-val);
		tree.update(x2+1,y1,-val);
		tree.update(x2+1,y2+1,val);
	};

	for(auto& elem : intervals){
		int a = elem.first;
		int b = elem.second;
		for(int i=a;i<=b;i++){
			// goto [i,b]
			updateRect(tracker, i, i, i, b, 1);
			updateRect(sumtracker, i, i, i, b, q);
		}
	}

	for(int i=1;i<=q;i++){
		string type; cin >> type;
		// deb(i)
		// deb(tracker.query(0,1,0,4))
		// deb(intervals)
		if(type == "query"){
			int l, r; cin >> l >> r; r--;
			l--; r--; // r decrease by 2 because it's exclusive
			int state = tracker.query(0, l, 0, r);
			int sum = sumtracker.query(0, l, 0, r);
			//deb(mp(state, sum))
			print(sum - state*(q-i));
		}else{
			int x; cin >> x;
			x--;
			int updateTracker = 0;
			int updateSum = 0;
			if(open[x]){
				auto it = intervals.upper_bound(mp(x,inf));
				assert(it != intervals.begin());
				it--;
				pair<int,int> interv = *it;
				int left = interv.first;
				int right = interv.second;

				updateRect(tracker, left,x,x,right, -1);
				updateRect(sumtracker, left,x,x,right, -(q-i));

				intervals.erase(it);
				if(left<=x-1)
					intervals.insert(mp(left,x-1));
				if(x+1<=right)
					intervals.insert(mp(x+1,right));
			}else{
				auto top = intervals.upper_bound(mp(x,inf));
				int right = x;
				if(top != intervals.end() && (*top).first==x+1){
					right = (*top).second;
					intervals.erase(top);
				}
				auto bot = intervals.upper_bound(mp(x,inf)); 
				int left = x;
				if(bot != intervals.begin()){
					bot--;
					if((*bot).second==x-1){
						left = (*bot).first;
						intervals.erase(bot);
					}
				}

				updateRect(tracker, left,x,x,right, 1);
				updateRect(sumtracker, left,x,x,right, (q-i));

				intervals.insert(mp(left,right));
			}

			open[x] = open[x]^1;
		}
	}

}









int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}





