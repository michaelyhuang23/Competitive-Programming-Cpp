
#include<bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000
#define print(x) cout<<x<<endl

const int MAXSIZE = 10000000;



vector<vector<pair<int,int>>> adj;



int lefts[MAXSIZE], rights[MAXSIZE];
int counter = 0;

void connectVtx(int vtx1, int vtx2, int w = 0){
	if(vtx1 < 0 || vtx2 < 0) return;
	adj[vtx1].pb(mp(vtx2,w)); 
	//assert(counter < MAXSIZE);
}

struct GraphVersionSegtree{
	int n, froot;
	GraphVersionSegtree(int n_, vector<int>& init, int w) : n(n_) {
		assert(n_ == init.size());
		froot = build(++counter, init, w, 0, n-1);
	}
	int build(int idx, vector<int>& init, int w, int ts, int te){
		if(ts == te){ connectVtx(idx, init[ts], w); return idx; }
		int tm = (ts+te)/2;
		lefts[idx]=build(++counter, init, w, ts, tm);
		rights[idx]=build(++counter, init, w, tm+1, te);
		connectVtx(idx, lefts[idx]);
		connectVtx(idx, rights[idx]);
		return idx;
	}
	void copy_node(int to, int from){
		lefts[to] = lefts[from];
		rights[to] = rights[from];
	}
	void connect(int idx, int vtx, int w, int ll, int rr, int ts, int te){
		if(ll == ts && rr == te) { 
			connectVtx(vtx, idx, w); return; 
		}
		int tm = (ts+te)/2;
		if(ll <= tm) connect(lefts[idx], vtx, w, ll, min(rr,tm), ts, tm);
		if(rr > tm) connect(rights[idx], vtx, w, max(ll,tm+1),rr,tm+1,te);
	}
	void connect(int idx, int vtx, int w, int ll, int rr){
		connect(idx, vtx, w, ll, rr, 0, n-1);
	}
	int change(int idx, int loc, int vtx, int w, int ts, int te){
		int nidx = ++counter;
		copy_node(nidx, idx);
		if(loc==ts && loc==te){ connectVtx(nidx, vtx, w); return nidx; }
		int tm = (ts+te)/2;
		if(loc <= tm) {
			lefts[nidx] = change(lefts[nidx], loc, vtx, w, ts, tm);
			connectVtx(nidx, lefts[nidx]);
			connectVtx(nidx, rights[idx]);
		}else{
			rights[nidx] = change(rights[nidx], loc, vtx, w, tm+1, te);
			connectVtx(nidx, rights[nidx]);
			connectVtx(nidx, lefts[idx]);
		}
		return nidx;
	}
	int change(int idx, int loc, int vtx, int w){
		return change(idx, loc, vtx, w, 0, n-1);
	}
};



















struct Block{
	int r, c;
	int ri, ci;
	int topv, botv, lefth, righth;
	Block() : topv(-1), botv(-1), lefth(-1), righth(-1) {}
	Block(int r_, int c_) : r(r_), c(c_), topv(-1), botv(-1), lefth(-1), righth(-1) {}
};

struct Segment{
	int rmin, rmax, cmin, cmax;
	Segment(int r1, int r2, int c1, int c2){
		rmin = r1; rmax = r2; cmin = c1; cmax = c2;
	}// these are ids, not values
};

ostream& operator << ( ostream& os, const Segment & s ) {
    return os << "(" << s.rmin<<", "<<s.rmax<<", "<<s.cmin <<", "<<s.cmax<< ")";
}


int n, m, k, q;
int R, C, RR, CC;
vector<vector<int>> H, V;
vector<int> Hr, Vc;
vector<Block> blocks;
vector<Segment> segs;
vector<vector<int>> hsegs, vsegs;
vector<int> dist;
int MAXNODE;

void BFS(int segh, int segv){
	dist = vector<int>(MAXNODE, inf);
	deque<int> pq;
	segh+=MAXSIZE;
	segv+=MAXSIZE;
	pq.pb(segh);
	pq.pb(segv);
	dist[segh] = 0;
	dist[segv] = 0;
	while(!pq.empty()){
		int id = pq.front(); pq.pop_front();
		for(auto& edge : adj[id]){
			int son = edge.first;
			int w = edge.second;
			if(dist[son] > dist[id]+w){
				dist[son] = dist[id]+w;
				if(w == 0) pq.push_front(son);
				else pq.push_back(son);
			}
		}
	}
}


void solve(){
	cin >> n >> m >> k >> q;


	auto preprocess = [&](){
		blocks = vector<Block>(k);
		vector<tuple<int,int,int>> ptrs(k);
		for(int i=0;i<k;i++){
			int r, c;
			cin >> r >> c; r--; c--;
			ptrs[i] = mt(r,c,i);
			blocks[i] = Block(r,c);
		}

		sort(ptrs.begin(), ptrs.end()); 

		for(auto& ptr : ptrs){
			int r = get<0>(ptr);
			int i = get<2>(ptr);
			if(!Hr.empty() && Hr.back() == r){
				H.back().pb(i);
			}else{
				Hr.pb(r);
				H.pb({i});
			}
		}

		auto compc = [&](tuple<int,int,int>& p1, tuple<int,int,int>& p2){
			if(get<1>(p1) == get<1>(p2)){
				return get<0>(p1) < get<0>(p2);
			}
			return get<1>(p1) < get<1>(p2); 
		};

		sort(ptrs.begin(), ptrs.end(), compc);

		for(auto& ptr : ptrs){
			int c = get<1>(ptr);
			int i = get<2>(ptr);
			if(!Vc.empty() && Vc.back() == c){
				V.back().pb(i);
			}else{
				Vc.pb(c);
				V.pb({i});
			}
		}

		R = Hr.size();
		C = Vc.size();
		RR = R*2+1;
		CC = C*2+1;


		for(int i=0;i<k;i++){
			int r = blocks[i].r;
			int c = blocks[i].c;
			int ri = distance(Hr.begin(),lower_bound(Hr.begin(), Hr.end(), r));
			int ci = distance(Vc.begin(), lower_bound(Vc.begin(), Vc.end(), c));
			ri = ri*2+1;
			ci = ci*2+1;
			blocks[i].ri = ri;
			blocks[i].ci = ci;
		}
	};



	preprocess();

	int hh = 0;
	segs = vector<Segment>();
	auto segmentHori = [&](){
		hsegs = vector<vector<int>>(RR);
		int prevr = -1;
		int prevri = -1;
		for(int ri=0;ri<R;ri++){
			int r = Hr[ri];
			int rii = ri*2+1;
			if(r - prevr > 1){ // there's space
				hsegs[rii-1].pb(hh++);
				assert(prevri+1<=rii-1);
				segs.pb(Segment(prevri+1, rii-1, 0, CC-1));
			}

			int prevci = -1;
			int prevc = -1;
			for(int i=0;i<H[ri].size();i++){
				Block& bl = blocks[H[ri][i]];
				int ci = bl.ci;
				int c = bl.c;
				if(c - prevc > 1){
					bl.lefth = hh;
					if(i>0) blocks[H[ri][i-1]].righth = hh;
					hsegs[rii].pb(hh++);
					segs.pb(Segment(rii, rii, prevci+1, ci-1));
				}
				prevci = ci;
				prevc = c;
			}

			if(m - prevc > 1){
				blocks[H[ri].back()].righth = hh;
				hsegs[rii].pb(hh++);
				assert(prevci+1<=CC-1);
				segs.pb(Segment(rii, rii, prevci+1, CC-1));
			}

			prevr = r;
			prevri = rii;
		}

		if(n - prevr > 1){
			hsegs.back().pb(hh++);
			assert(prevri+1<=RR-1);
			segs.pb(Segment(prevri+1, RR-1, 0, CC-1));
		}
	};

	segmentHori();

	int cutptr = hh;



	auto segmentVerti = [&](){
		vsegs = vector<vector<int>>(CC);
		int prevc = -1;
		int prevci = -1;
		for(int ci=0;ci<C;ci++){
			int c = Vc[ci];
			int cii = ci*2+1;
			if(c - prevc > 1){ // there's space
				vsegs[cii-1].pb(hh++);
				assert(prevci+1<=cii-1);
				segs.pb(Segment(0, RR-1, prevci+1, cii-1));
			}

			int prevri = -1;
			int prevr = -1;
			for(int i=0;i<V[ci].size();i++){
				Block& bl = blocks[V[ci][i]];
				int ri = bl.ri;
				int r = bl.r;
				if(r - prevr > 1){
					bl.botv = hh;
					if(i>0) blocks[V[ci][i-1]].topv = hh;
					vsegs[cii].pb(hh++);
					segs.pb(Segment(prevri+1, ri-1, cii, cii));
				}
				prevri = ri;
				prevr = r;
			}

			if(n - prevr > 1){
				blocks[V[ci].back()].topv = hh;
				vsegs[cii].pb(hh++);
				assert(prevri+1<=RR-1);
				segs.pb(Segment(prevri+1, RR-1, cii, cii));
			}

			prevc = c;
			prevci = cii;
		}

		if(m - prevc > 1){
			vsegs.back().pb(hh++);
			assert(prevci+1<=CC-1);
			segs.pb(Segment(0, RR-1, prevci+1, CC-1));
		}
	};


	segmentVerti();

	// deb(segs)

	// deb(hsegs)
	// deb(vsegs)

	// for(Block& bl : blocks){
	// 	assert(bl.topv >= 0 && bl.botv >= 0 && bl.lefth >= 0 && bl.righth >= 0);
	// }

	MAXNODE = MAXSIZE+hh;

	adj = vector<vector<pair<int,int>>>(MAXNODE);

	auto buildHori = [&](){
		vector<int> initVSegs(CC,-1);
		for(int c=0;c<CC;c++) 
			if(!vsegs[c].empty() && segs[vsegs[c].front()].rmin==0) initVSegs[c] = vsegs[c].front()+MAXSIZE;
		GraphVersionSegtree vertiPST(CC, initVSegs, 0); 
		vector<int> roots; roots.pb(vertiPST.froot);
		for(int r=0;r<RR;r++){
			for(int i : hsegs[r]){
				vertiPST.connect(roots.back(), MAXSIZE+i, 1, segs[i].cmin, segs[i].cmax);
			}
			if(r&1){
				int ri = r/2;
				for(int i=0;i<H[ri].size();i++){
					Block& bl = blocks[H[ri][i]];
					if(bl.topv != -1)
						roots.pb(vertiPST.change(roots.back(), bl.ci, MAXSIZE+bl.topv, 0));
				}
			}
		}
	};
	
	buildHori();


	auto buildVerti = [&](){
		vector<int> initHSegs(RR,-1);
		for(int r=0;r<RR;r++)
			if(!hsegs[r].empty() && segs[hsegs[r].front()].cmin==0) initHSegs[r] = hsegs[r].front()+MAXSIZE;
		GraphVersionSegtree horiPST(RR, initHSegs, 0);
		vector<int> roots; roots.pb(horiPST.froot);
		// initialize 
		for(int c=0;c<CC;c++){
			for(int i : vsegs[c]){
				horiPST.connect(roots.back(), i+MAXSIZE, 1, segs[i].rmin, segs[i].rmax);
			}
			if(c&1){
				int ci = c/2;
				for(int i=0;i<V[ci].size();i++){
					Block& bl = blocks[V[ci][i]];
					if(bl.righth != -1)
						roots.pb(horiPST.change(roots.back(), bl.ri, bl.righth+MAXSIZE, 0));
				}
			}
		}
	};

	buildVerti();



	int sr, sc; cin >> sr >> sc;
	sr--; sc--;

	auto findLoc = [&](int r, int c){
		int ri = -1, ci = -1;

		auto it = lower_bound(Hr.begin(), Hr.end(), r);
		if(it == Hr.end()) ri = RR-1;
		else if(*it == r) ri = distance(Hr.begin(), it)*2+1;
		else ri = distance(Hr.begin(), it)*2+1-1;

		it = lower_bound(Vc.begin(), Vc.end(), c);
		if(it == Vc.end()) ci = CC-1;
		else if(*it == c) ci = distance(Vc.begin(), it)*2+1;
		else ci = distance(Vc.begin(), it)*2+1-1;

		return mp(ri,ci);
	};

	// deb(Hr)


	auto findHSeg = [&](int ri, int ci){
		assert(hsegs[ri].size()>0);
		int ll = 0, rr = hsegs[ri].size()-1, ans = -1; // maximize ans
		while(ll<=rr){
			int mid = (ll+rr)/2;
			if(segs[hsegs[ri][mid]].cmin <= ci) { ans = mid; ll = mid+1; }
			else rr = mid - 1;
		}
		assert(segs[hsegs[ri][ans]].cmin <= ci && segs[hsegs[ri][ans]].cmax >= ci);
		return hsegs[ri][ans];
	};


	auto findVSeg = [&](int ri, int ci){
		assert(vsegs[ci].size()>0);
		int ll = 0, rr = vsegs[ci].size()-1, ans = -1; // maximize ans
		while(ll<=rr){
			int mid = (ll+rr)/2;
			if(segs[vsegs[ci][mid]].rmin <= ri) { ans = mid; ll = mid+1; }
			else rr = mid - 1;
		}
		assert(segs[vsegs[ci][ans]].rmin <= ri && segs[vsegs[ci][ans]].rmax >= ri);
		return vsegs[ci][ans];
	};


	auto ret = findLoc(sr, sc);
	int sri = ret.first;
	int sci = ret.second;
	int shseg = findHSeg(sri, sci);
	int svseg = findVSeg(sri, sci);


	// deb(segs)

	// deb(mp(shseg, svseg))

	// deb(adj[MAXSIZE+0])

	BFS(shseg, svseg);
    
	// deb(dist)

	for(int i=0;i<q;i++){
		int tr, tc; cin >> tr >> tc; tr--; tc--;
		ret = findLoc(tr, tc);
		int tri = ret.first;
		int tci = ret.second;
		int thseg = findHSeg(tri, tci);
		int tvseg = findVSeg(tri, tci);

		if(thseg == shseg || tvseg == svseg){ // same block: no blocade in mid
			if(tr == sr) print(0);
			else if(tc == sc) print(0);
			else print(1);
			continue;
		}

		// deb(mp(thseg, tvseg))

		int minD = min(dist[thseg+MAXSIZE], dist[tvseg+MAXSIZE]);
		if(minD > inf/2) print(-1);
		else print(minD);
	}
}










































int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}