#include<bits/stdc++.h>

//#include "debughelp.hpp"

using namespace std;
typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl
#define inf 1000000007LL*2LL

struct segtree{
	vector<llong> tree;
	int n;
	int pow_up(int num){
		for(int i=0;i<32;i++) if((1<<i) >= num) return (1<<i);
		return -1;
	}
	segtree(){}
	segtree(int n_){
		n = pow_up(n_);
		tree = vector<llong>(2*n,inf);
		build();
	}
	void build(){
		for(int i=n-1;i>=1;i--) pull_up(i);
	}
	llong op(llong l, llong r) { return min(l, r); }
	void pull_up(int idx){
		tree[idx] = op(tree[idx*2], tree[idx*2+1]);
	}
	void update(int idx, llong val){
		tree[idx+n] = op(tree[idx+n],val);
		for(idx/=2;idx>=1;idx/=2){
			pull_up(idx);
		}
	}
	llong query(int l, int r){
		llong sum = inf;
		for(l+=n, r+=n; l<=r; l/=2, r/=2){
			if(l&1) sum = op(sum, tree[l++]);
			if(!(r&1)) sum = op(sum, tree[r--]);
			if(l==r) break;
		}
		return sum;
	}
};

llong n;
vector<pair<llong,llong>> ptrs;
llong minn;

llong dist(llong xl, llong xr, llong yu, llong yd){
	return xr - xl + yu - yd + min(abs(xl), abs(xr)) + min(abs(yu), abs(yd));
}


void solve_side(function<bool(llong, llong, llong, llong)> cond){
	llong l = 0, r = n-1;
	llong prevxl = -1;
	llong prevxr = inf;
	set<llong> ly, ry; 
	for(l=0;l<n;l++){
		llong xl = ptrs[l].first;
		llong yl = ptrs[l].second;
		if(xl>0) break;
		if(xl > prevxl){
			// we will now deal with xl
			llong maxyl = 0, minyl = 0;
			if(ly.rbegin() != ly.rend())
				maxyl = *ly.rbegin();
			if(ly.begin() != ly.end())
				minyl = *ly.begin(); // what if we don't have smth?
			while(r>=0){
				llong xr = ptrs[r].first;
				llong yr = ptrs[r].second;
				if(xr<0) break;
				if(xr < prevxr){
					// now we deail with xr
					llong maxyr = 0, minyr = 0;
					if(ry.rbegin() != ry.rend())
						maxyr = *ry.rbegin();
					if(ry.begin() != ry.end())
						minyr = *ry.begin(); // what if we don't have smth
//					deb(mp(xl, xr))
//					deb(ry)
//					deb(mp(maxyl, minyl))
//					deb(mp(maxyr, minyr))
					// maybe we need to run from both sides?
					minn = min(minn,dist(xl, xr, max(maxyl, maxyr), min(minyl, minyr)));
					if(cond(maxyr, maxyl, minyr, minyl)) break; // always under shadow
					prevxr = xr;
					r--;
				}else r--;
				ry.insert(yr);
			}
			prevxl = xl;
		}
		ly.insert(yl);
	}
}

void solve(){
	cin >> n;
	ptrs = vector<pair<llong,llong>>(n);
	bool has = 0;
	minn = inf*8;
	for(llong i=0;i<n;i++) {
		llong a, b; cin >> a >> b;
		ptrs[i] = mp(a,b);
		if(a==0 && b==0) has = 1;
	}
	if(!has) ptrs.pb(mp(0,0));
	sort(ptrs.begin(), ptrs.end());
	n = ptrs.size();
	
	solve_side([&](llong maxyr, llong maxyl, llong minyr, llong minyl){
		return maxyr > maxyl || minyr < minyl;
	});

	solve_side([&](llong maxyr, llong maxyl, llong minyr, llong minyl){
		return maxyr > maxyl && minyr < minyl;
	});

	// now we tackle the special cases
	vector<vector<segtree>> tops(2, vector<segtree>(2, segtree(n+5)));
    vector<vector<segtree>> bots(2, vector<segtree>(2, segtree(n+5)));

    set<llong> ly;
	vector<llong> ymax(n,inf);
	vector<llong> ymin(n,inf);
	llong prevx = -1;
	for(int i=0;i<n;i++){
		llong x = ptrs[i].first;
		llong y = ptrs[i].second;
		if(x>0) break;
		if(x>prevx){
			llong maxy = 0, miny = 0;
			if(ly.rbegin() != ly.rend())
				maxy = *ly.rbegin();
			if(ly.begin() != ly.end())
				miny = *ly.begin(); // what if we don't have smth?

			prevx = x;

			llong topd = max(0LL,maxy);
			tops[0][0].update(i, topd + abs(x));
			tops[0][1].update(i, topd*2 + abs(x));
			tops[1][0].update(i, topd + abs(x)*2);
			tops[1][1].update(i, topd*2 + abs(x)*2);

			llong botd = max(0LL,-miny);
			bots[0][0].update(i, botd + abs(x));
			bots[0][1].update(i, botd*2 + abs(x));
			bots[1][0].update(i, botd + abs(x)*2);
			bots[1][1].update(i, botd*2 + abs(x)*2);

			ymax[i] = topd;
			ymin[i] = botd;
		}
		ly.insert(y);
	}

	set<llong> ry;
	prevx = inf;
	for(int i=n-1;i>=0;i--){
		llong x = ptrs[i].first;
		llong y = ptrs[i].second;
		if(x<0) break;
		if(x<prevx){
			llong maxy = 0, miny = 0;
			if(ry.rbegin() != ry.rend())
				maxy = *ry.rbegin();
			if(ry.begin() != ry.end())
				miny = *ry.begin(); // what if we don't have smth?
			llong topd = max(0LL,maxy);
			llong botd = max(0LL,-miny);

			auto lb = lower_bound(ymin.begin(), ymin.end(), botd);
			int lbi = distance(ymin.begin(), lb);
			// good for exclusive upperbound
			auto tb = upper_bound(ymax.begin(), ymax.end(), topd);
			int tbi = distance(ymax.begin(), tb);
			// good for inclusive lowerbound

			auto xb = upper_bound(ptrs.begin(), ptrs.end(), mp(-x,inf));
			int xbi = distance(ptrs.begin(), xb);
			// good for exclusive upperbound
			auto yb = upper_bound(ymax.begin(), ymax.end(), botd);
			int ybi = distance(ymax.begin(), yb);
			// good for exclusive upperbound

			if(tbi<lbi){
				{// [0][0]
					int ub = min({xbi, ybi, lbi});
					if(tbi<ub) 
						minn=min(minn,tops[0][0].query(tbi, ub-1) + botd*2 + x*2);
				}
				{// [1][0]
					int ub = min({ybi, lbi});
					int bb = max({tbi, xbi+1});
					if(bb<ub) 
						minn=min(minn,tops[1][0].query(bb, ub-1) + botd*2 + x);
				}
				{// [0][1]
					int ub = min({xbi, lbi});
					int bb = max({tbi, ybi+1});
					if(bb<ub) 
						minn=min(minn,tops[0][1].query(bb, ub-1) + botd + x*2);
				}
				{// [1][1]
					int ub = lbi;
					int bb = max({tbi, ybi+1, xbi+1});
					if(bb<ub)
						minn=min(minn,tops[1][1].query(bb, ub-1) + botd + x);
				}
			}
			prevx = x;
		}
		ry.insert(y);
	}



	ry = set<llong>();
	prevx = inf;
	for(int i=n-1;i>=0;i--){
		llong x = ptrs[i].first;
		llong y = ptrs[i].second;
		if(x<0) break;
		if(x<prevx){
			llong maxy = 0, miny = 0;
			if(ry.rbegin() != ry.rend())
				maxy = *ry.rbegin();
			if(ry.begin() != ry.end())
				miny = *ry.begin(); // what if we don't have smth?
			llong topd = max(0LL,maxy);
			llong botd = max(0LL,-miny);

			auto lb = lower_bound(ymax.begin(), ymax.end(), topd);
			int lbi = distance(ymax.begin(), lb);
			// good for exclusive upperbound
			auto tb = upper_bound(ymin.begin(), ymin.end(), botd);
			int tbi = distance(ymin.begin(), tb);
			// good for inclusive lowerbound

			auto xb = upper_bound(ptrs.begin(), ptrs.end(), mp(-x,inf));
			int xbi = distance(ptrs.begin(), xb);
			// good for exclusive upperbound
			auto yb = upper_bound(ymin.begin(), ymin.end(), topd);
			int ybi = distance(ymin.begin(), yb);
			// good for exclusive upperbound

			if(tbi<lbi){
				{// [0][0]
					int ub = min({xbi, ybi, lbi});
					if(tbi<ub) 
						minn=min(minn,bots[0][0].query(tbi, ub-1) + topd*2 + x*2);
				}
				{// [1][0]
					int ub = min({ybi, lbi});
					int bb = max({tbi, xbi+1});
					if(bb<ub) 
						minn=min(minn,bots[1][0].query(bb, ub-1) + topd*2 + x);
				}
				{// [0][1]
					int ub = min({xbi, lbi});
					int bb = max({tbi, ybi+1});
					if(bb<ub) 
						minn=min(minn,bots[0][1].query(bb, ub-1) + topd + x*2);
				}
				{// [1][1]
					int ub = lbi;
					int bb = max({tbi, ybi+1, xbi+1});
					if(bb<ub)
						minn=min(minn,bots[1][1].query(bb, ub-1) + topd + x);
				}
			}
			prevx = x;
		}
		ry.insert(y);
	}

	print(minn);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong tt; cin >> tt;
	while(tt--) solve();
}





