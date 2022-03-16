//#include "debughelp.hpp"

#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple

#define print(x) cout<<x<<endl

#define inf 1000000000000LL
#define HRANGE 110000004LL


vector<llong> locs;
map<pair<llong,llong>, llong> loc2id;

llong toloc(llong id){
	if(id>=locs.size()) return inf;
	else return locs[id];
}
llong toid(llong loc){
	auto it = loc2id.upper_bound(mp(loc,inf));
	if(it == loc2id.begin()) return 0;
	return (*prev(it)).second;
}

struct segtree{
	static llong pow_up(llong num){
		for(int i=0;i<64;i++) if(1<<i >= num) return 1<<i;
		return -1;
	}
	vector<llong> tree;
	llong n;
	segtree(llong n_){
		n = pow_up(n_);
		tree = vector<llong>(2*n,0);
		build();
	}
	inline void build(){
		for(llong i = n-1; i>=1; i--) tree[i] = max(tree[i<<1], tree[i<<1|1]);
	}
	inline void update(llong idx, llong val){
		tree[n+idx] = val;
		for(llong i = (n+idx)>>1; i >= 1; i>>=1) tree[i] = max(tree[i<<1], tree[i<<1|1]);
	}
	inline llong query(llong left, llong right){
		// both inclusive
		llong maxx = 0;
		left+=n, right+=n;
		for(;left<=right;left>>=1,right>>=1){
			if(left&1) maxx=max(maxx,tree[left++]);
			if(!(right&1)) maxx=max(maxx,tree[right--]);
			if(left==right) break; 
		}
		return maxx;
	}
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
	set<pair<llong,llong>> horizontals;
	for(llong i=0;i<n;i++){
		llong x,type,t1,t2; cin >> x >> type >> t1 >> t2; type--;
		if(t1>t2) swap(t1,t2);
		horizontals.insert(mp(x+HRANGE,type));
		stores[i] = Store(x+HRANGE,type,t1,t2);
		ptrs.pb(mt(t1,0,false,i));
		ptrs.pb(mt(t2,inf,false,i));
	}

	vector<llong> queries(q);
	for(llong i=0;i<q;i++){
		llong x, t; cin >> x >> t;
		horizontals.insert(mp(x+HRANGE,inf));
		queries[i] = x+HRANGE;
		ptrs.pb(mt(t,100,true,i));
	}

	for(llong i=0;i<k;i++) horizontals.insert(mp(i,i));

	//deb(horizontals)

	llong jj = 0;
	for(auto pp : horizontals){
		loc2id[pp] = jj++;
		locs.pb(pp.first);
	}
	for(llong i=0;i<n;i++){
		stores[i].x = loc2id[mp(stores[i].x, stores[i].k)];
	}

	for(llong i=0;i<q;i++){
		queries[i] = loc2id[mp(queries[i],inf)];
	}

	//deb(locs)

	//deb(loc2id)


	sort(ptrs.begin(), ptrs.end());

	vector<map<llong,llong>> tracker(k);

	llong RANGE = locs.size()+5;
	segtree tree(RANGE);
	for(llong i=0;i<k;i++){
		llong x = loc2id[mp(i,i)];
		tree.update(x,inf); 
		tracker[i][x] = 1;
	}

	vector<llong> answers(q);
	

	for(auto& ptr : ptrs){
		llong t = get<0>(ptr);

		if(get<2>(ptr)){
			// query
			llong id = get<3>(ptr);
			llong ix = queries[id];
			llong x= locs[ix];
			llong lb = k, rb = x;
			llong ans = inf;
			//deb(x)
			while(lb <= rb){
				llong mid = (lb+rb)/2;
				llong d = x-mid;
				llong rr = x+d;
				//print(d);
				llong mm = toid(mid-1);
				//deb(mp(mid-1,mm))
				llong pref = tree.query(0, mm);
				//deb(mp(pref, rr))
				//deb(mt(0,mid-1,pref))
				if(pref <= rr){
					ans = min(ans, d);
					lb = mid+1;
				}else
					rb = mid-1;
			}

			if(ans>inf/2) answers[id] = -1;
			else{
				//assert(tree.query(0, x-ans-1).val <= x+ans);
				answers[id] = ans;
			}
			// llong ll = tree.search(x,0);
			// deb(mp(ll,x))
			// if(ll<=0) answers[id] = -1;
			// else{
			// 	llong d = x-ll;
			// 	answers[id] = d;
			// }
		}else{
			// update
			llong id = get<3>(ptr);
			llong type = stores[id].k;
			llong x = stores[id].x;
			if(get<1>(ptr) == 0){
				// begin
				if(tracker[type].find(x) != tracker[type].end()){
					tracker[type][x]++;
					continue;
				}
				// this is now new added child
				auto it = tracker[type].upper_bound(x);
				llong topi = inf;
				if(it != tracker[type].end()) {
					topi = locs[(*it).first];
				}
                //deb(mt(x,x,topi))
				tree.update(x,topi);
                //deb("finish")

				if(it != tracker[type].begin()){
					llong boti = (*(prev(it))).first;
                    //deb(mt(boti,boti,x))
					tree.update(boti,locs[x]);
                    //deb("finish")
				}
				tracker[type][x]=1;
			}else{
				assert(stores[id].t2 == t);
				// end
                //deb(mt(x,x,0))
                bool onlychild = tracker[type][x]==1;
                if(!onlychild) {
                	tracker[type][x]--;
                	continue;
                }

				tree.update(x,-inf);
                //deb("finish")
				auto it = tracker[type].lower_bound(x);
				llong topi = inf;
				if(next(it) != tracker[type].end()) topi = (*next(it)).first;

				if(it != tracker[type].begin()){
					llong boti = (*(prev(it))).first;
                    //deb(mt(boti,boti,topi))
					tree.update(boti,(topi<inf)?locs[topi]:inf);
                    //deb("finish")
				}
				tracker[type].erase(it);
			}
		}
	}

	for(llong q : answers) print(q);
}















int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}




















