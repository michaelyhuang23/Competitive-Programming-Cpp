#include "debughelp.hpp"

#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple

#define print(x) cout<<x<<endl

#define inf 10000000000000000LL
#define MAXSIZE 9458380
#define RANGE 32000000900000LL
#define HRANGE 0
//RANGE/2

struct Node{
	llong val, pd;
	Node() : val(0), pd(0) {}
	void update(llong val_){
		val = val_;
		pd = val_;
	}
	static Node merge(Node& left, Node& right){
		Node mid;
		mid.val = max(left.val, right.val);
		return mid;
	}
	void push_down(Node& left, Node& right){
		left.update(pd);
		right.update(pd);
		pd = 0;
	}
	void pull_up(Node& left, Node& right){
		(*this) = merge(left, right);
	}
    bool latent(){
        return pd != 0;
    }
};

Node nodes[MAXSIZE];
llong lefts[MAXSIZE], rights[MAXSIZE];
llong counter = 0;
struct DynamicSegtree{
	DynamicSegtree(){
		fill(nodes, nodes+MAXSIZE, Node());
		fill(lefts, lefts+MAXSIZE, -1);
		fill(rights, rights+MAXSIZE, -1);
	}
	void pull_up(llong idx){
		Node leftNode, rightNode;
		if(lefts[idx]!=-1) leftNode = nodes[lefts[idx]];
		if(rights[idx]!=-1) rightNode = nodes[rights[idx]];
		nodes[idx].pull_up(leftNode, rightNode);
	}
	void push_down(llong idx){
        if(!nodes[idx].latent()) return;
		if(lefts[idx]==-1) lefts[idx] = ++counter;
		if(rights[idx]==-1) rights[idx] = ++counter;
		nodes[idx].push_down(nodes[lefts[idx]], nodes[rights[idx]]);
	}
	Node query(llong ll, llong rr, llong idx=0, llong ts=0, llong te=RANGE){
		if(ll == ts && rr == te) return nodes[idx];
		llong tm = (ts+te)/2;
		push_down(idx);
		Node leftNode, rightNode;
		if(lefts[idx]!=-1 && ll <= tm)
			leftNode = query(ll, min(rr,tm), lefts[idx], ts, tm);
		if(rights[idx]!=-1 && rr > tm)
			rightNode = query(max(ll,tm+1),rr,rights[idx],tm+1,te);
		return Node::merge(leftNode, rightNode);
	}
	void update(llong ll, llong rr, llong val, llong idx=0, llong ts=0, llong te=RANGE){
		if(ll==ts && rr==te){ nodes[idx].update(val); return; }
		llong tm = (ts+te)/2;
		push_down(idx);
		if(ll <= tm){
			if(lefts[idx]==-1) lefts[idx] = ++counter; // instantiate
			update(ll, min(rr,tm), val, lefts[idx], ts, tm);
		}
		if(rr > tm){
			if(rights[idx]==-1) rights[idx] = ++counter; // instantiate
			update(max(ll,tm+1), rr, val, rights[idx], tm+1, te);
		}
		pull_up(idx);
	}

	llong search(llong loc, llong leftMax, llong idx=0, llong ts=0, llong te=RANGE){
		assert(loc >= ts);
		//deb(mp(ts,te))
		//deb(mp(loc,leftMax))
		if(ts == te){
			if(leftMax <= loc-ts+loc) return ts;
		}
		llong tm = (ts+te)/2;
		llong ll = tm+1;
		if(ll > loc) return search(loc, leftMax, (idx==-1)?(-1):(lefts[idx]), ts, tm);
		llong d = loc - ll;
		llong rr = loc + d;
		// [ll, rr] is your range
		llong nleftMax = max(leftMax, (idx==-1 || lefts[idx]==-1)?(0):(nodes[lefts[idx]].val));
		//deb(nleftMax)
		if(nleftMax <= rr){ // ok, move to the right
			return max(ll, search(loc, nleftMax, (idx==-1)?(-1):(lefts[idx]), tm+1, te));
		}else{ // not ok, move to the left
			return search(loc, leftMax, (idx==-1)?(-1):(lefts[idx]), ts, tm);
		}
	}

	// llong search(llong loc, llong leftMax, llong idx=0, llong ts=0, llong te=RANGE){
	// 	// we want the minimum D such that there's no crossover
	// 	deb(mp(loc,leftMax))
	// 	deb(mp(ts,te))

	// 	if(ts == te){ // we have pinned it to a point
	// 		llong ll = ts;
	// 		llong d = loc-ll;
	// 		llong rr = loc+d;
	// 		assert(leftMax <= rr);
	// 		return loc - ts;
	// 	}
	// 	// base case
	// 	llong tm = (ts+te)/2;
 //        //print(idx);
	// 	push_down(idx);
	// 	if(loc <= tm) {
	// 		if(lefts[idx]==-1) assert(false); // shouldn't happen
	// 		return search(loc, leftMax, lefts[idx], ts, tm);
	// 	}
	// 	assert(loc > tm);
	// 	// now we try to cut at tm+1
	// 	// that means our prefix is [0,tm]
	// 	llong ll = tm+1;
	// 	llong d = loc-ll;
	// 	llong rr = loc+d;
	// 	deb(mp(ll,rr))
	// 	assert(leftMax <= rr);
	// 	if(lefts[idx] == -1){
	// 		return min(d, search(loc,leftMax,rights[idx],tm+1,te));
	// 	}
	// 	llong nleftMax = max(leftMax, nodes[lefts[idx]].val);
	// 	deb(nleftMax)
	// 	if(nleftMax > rr){
	// 		// this means it's bad, there's a trespasser
	// 		// we need to broaden the range, so we move to left branch
	// 		return search(loc,leftMax,lefts[idx],ts,tm);
	// 	}else{
	// 		// this means it's an answer

	// 		// to find a smaller d, which is what we want to achieve
	// 		// let's search into the right branch
	// 		llong minD = d;
	// 		if(rights[idx] == -1){
	// 			llong nd = nleftMax - loc;
	// 			llong nll = loc - nd; 
	// 			nll = min(nll, te+1);
	// 			minD = min(minD, loc - nll); // we can cut there
	// 		}else
	// 			minD = min(minD, search(loc,nleftMax,rights[idx],tm+1,te));
	// 		return minD;
	// 	}
	// }
};

struct Store{
	llong x,k,t1,t2;
	Store(){}
	Store(llong x_, llong k_, llong t1_, llong t2_) : x(x_), k(k_), t1(t1_), t2(t2_) {}
};

void solve(){
	llong n, k, q; cin >> n >> k >> q;
	vector<Store> stores(n);
	vector<tuple<llong,llong,bool,llong>> ptrs; // optim here
	// time, is query, id
	for(llong i=0;i<n;i++){
		llong x,type,t1,t2; cin >> x >> type >> t1 >> t2; type--;
		x = x*(k+1) + type;
		x+=HRANGE;
		
		stores[i] = Store(x,type,t1,t2);
		ptrs.pb(mt(t1,0,false,i));
		ptrs.pb(mt(t2,inf,false,i));
	}
	vector<llong> queries(q);
	for(llong i=0;i<q;i++){
		llong x, t; cin >> x >> t;
		x = x*(k+1) + k;
		x+=HRANGE;
		queries[i] = x;
		ptrs.pb(mt(t,100,true,i));
	}
	sort(ptrs.begin(), ptrs.end());

	vector<map<llong,llong>> tracker(k);

	DynamicSegtree tree;
	for(int i=0;i<k;i++){
		tree.update(i,i,inf); 
		tracker[i][i] = 1;
	}
	
	vector<llong> answers(q);
	for(auto& ptr : ptrs){
		if(counter>MAXSIZE/2){
			deb(counter)
			assert(false);
		}
		llong t = get<0>(ptr);
		//deb(ptr)
		deb(tracker)
		// for(llong i=0;i<=15;i++)
		// 	cout<<tree.query(i,i).val<<" ";
		// cout<<endl;


		if(get<2>(ptr)){
			// query
			llong x = queries[get<3>(ptr)];

			llong ll = (tree.search(x+k,0)-k);
			if(ll<=0) answers[get<3>(ptr)] = -1;
			else{
				llong MASSIVE = (HRANGE/(k+1)+1)*(k+1);
				MASSIVE = 0;
				llong px = (x-HRANGE+MASSIVE)/(k+1);
				llong pll = (ll-HRANGE+MASSIVE)/(k+1);
				llong d = px-pll;
				deb(mp(px,pll))
				deb(mp((x-HRANGE+MASSIVE)%(k+1), (ll-HRANGE+MASSIVE)%(k+1)))
				deb(mp(x,ll))
				//deb(x-ll)
				answers[get<3>(ptr)] = d;
			}
		}else{
			// update
			llong id = get<3>(ptr);
			llong type = stores[id].k;
			llong x = stores[id].x;
			if(stores[id].t1 == t){
				// begin
				auto it = tracker[type].upper_bound(x+k);
				llong topi = inf;
				if(it != tracker[type].end()) topi = (*it).first;
                //deb(mt(x,x,topi))
				tree.update(x+k,x+k,topi);
                //deb("finish")

				it = tracker[type].lower_bound(x+k);
				if(it != tracker[type].begin()){
					llong boti = (*(prev(it))).first;
                    //deb(mt(boti,boti,x))
					tree.update(boti,boti,x+k);
                    //deb("finish")
				}
				if(tracker[type].find(x+k) == tracker[type].end())
					tracker[type][x+k]=1;
				else
					tracker[type][x+k]++;
			}else{
				assert(stores[id].t2 == t);
				// end
                //deb(mt(x,x,0))
                bool onlychild = tracker[type][x+k]==1;
                if(onlychild)
					tree.update(x+k,x+k,-inf);
                //deb("finish")
				auto it = tracker[type].lower_bound(x+k);
				llong topi = inf;
				if(next(it) != tracker[type].end()) topi = (*next(it)).first;

				if(it != tracker[type].begin() && onlychild){
					llong boti = (*(prev(it))).first;
                    //deb(mt(boti,boti,topi))
					tree.update(boti,boti,topi);
                    //deb("finish")
				}
				if(onlychild) tracker[type].erase(x+k);
				else tracker[type][x+k]--;
			}
		}
	}

	for(int ans : answers) print(ans);
}















int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}




















