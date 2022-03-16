// #include "debughelp.hpp"
#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000
#define print(x) cout<<x<<'\n'

#define MAXSIZE 20804820
#define RANGE 400005


struct vector3{
	int v, e, f;
	vector3():v(0),e(0),f(0){}
	vector3(int num):v(num),e(num),f(num){}
	vector3(int v_, int e_, int f_):v(v_),e(e_),f(f_){}
	vector3 operator+(const vector3& other){
		vector3 ret;
		ret.v = v + other.v;
		ret.e = e + other.e;
		ret.f = f + other.f;
		return ret;
	}
	vector3 operator-(const vector3& other){
		vector3 ret;
		ret.v = v - other.v;
		ret.e = e - other.e;
		ret.f = f - other.f;
		return ret;
	}
	vector3& operator+=(const vector3& other){
		(*this) = (*this) + other;
		return *this;
	}
};

vector3 nodes[MAXSIZE];
int lefts[MAXSIZE], rights[MAXSIZE];
int DIR[4][2] = {{1,1},{-1,1},{1,-1},{-1,-1}};
int MOV[4][2] = {{2,0},{-2,0},{0,2},{0,-2}};
int counter = 0;

int updateIdx;
vector3 updateVal;
struct DynamicSegtree{
	static void init(){ // must call before use
		fill(nodes, nodes+MAXSIZE, 0);
		fill(lefts, lefts+MAXSIZE, -1);
		fill(rights, rights+MAXSIZE, -1);
		counter = 0;
	}
	DynamicSegtree(){}
	void pull_up(int idx){
		nodes[idx] = vector3();
		if(lefts[idx]!=-1) nodes[idx] += nodes[lefts[idx]];
		if(rights[idx]!=-1) nodes[idx] += nodes[rights[idx]];
	}
	vector3 query(int idx, int ll, int rr, int ts=0, int te=RANGE){
		if(ll>rr) return vector3();
		if(ll == ts && rr == te) return nodes[idx];
		int tm = (ts+te)/2;
		vector3 leftNode, rightNode;
		if(lefts[idx]!=-1 && ll <= tm)
			leftNode = query(lefts[idx], ll, min(rr,tm), ts, tm);
		if(rights[idx]!=-1 && rr > tm)
			rightNode = query(rights[idx], max(ll,tm+1),rr,tm+1,te);
		return leftNode + rightNode;
	}
	void update(int idx, int ts=0, int te=RANGE){
		if(updateIdx==ts && updateIdx==te){
			// deb(mp(updateIdx,idx))
			nodes[idx]+=updateVal;
			return;
		}
		int tm = (ts+te)/2;
		if(updateIdx <= tm){
			if(lefts[idx]==-1) 
				lefts[idx] = ++counter;
			update(lefts[idx], ts, tm);
		}else{
			if(rights[idx]==-1) 
				rights[idx] = ++counter;
			update(rights[idx], tm+1, te);
		}
		pull_up(idx);
	}
};

struct BIT2D{
	vector<int> bits;
	DynamicSegtree tree;
	int n;
	BIT2D(int n_){
		n = n_+2; // safety
		bits = vector<int>(n);
		for(int i=0;i<n;i++) bits[i] = ++counter;
	}

	inline int low_bit(int num){
	    return num & (-num);
	}
	vector3 query(int xp, int yp){ // idx starts at 1
		xp++; // shift index
	    vector3 sum = 0;
	    for(int x = xp; x>0; x -= low_bit(x))
	    	sum += tree.query(bits[x], 0, yp);
	    return sum;
	}
	void update(int xp, int yp, vector3 val){
		xp++; // shift index
	    for(int x = xp; x<=bits.size()-1; x+= low_bit(x)){
	    	updateIdx = yp;
	    	updateVal = val;
	    	tree.update(bits[x]); 
	    }
	}
};




void solve(){
	int R, C, M, Q; cin >> R >> C >> M >> Q;
	int sr, sc; cin >> sr >> sc;
	R*=2; C*=2;
	sr--; sc--; // change to 0 based
	sr*=2; sc*=2; // double grid size
	string s; 
	if(M>0)
		cin >> s;

	BIT2D tree(RANGE);

	auto queryBox = [&](BIT2D& tree2D, int r1, int r2, int c1, int c2){
		if(r1>r2) return vector3();
		if(c1>c2) return vector3();
		return tree2D.query(r2,c2) - tree2D.query(r1-1, c2) - tree2D.query(r2, c1-1) + tree2D.query(r1-1, c1-1);
	};

	tree.update(sr, sc, vector3(1,0,0));

	set<pair<int,int>> traversed;
	traversed.insert(mp(sr,sc));
	// assume we never move out of the page
	for(int i=0;i<M;i++){
		if(s[i] == 'N'){
			sr-=2;
		}else if(s[i] == 'S'){
			sr+=2;
		}else if(s[i] == 'W'){
			sc-=2;
		}else if(s[i] == 'E'){
			sc+=2;
		}else assert(false);

		// now let's update vertices
		if(traversed.find(mp(sr,sc))==traversed.end()){
			// deb("vertex")
			// deb(mp(sr,sc))
			tree.update(sr, sc, vector3(1,0,0));
			traversed.insert(mp(sr,sc));
		}
	}

	set<pair<int,int>> traversedB;
	for(auto point : traversed){
		for(int i=0;i<4;i++){
			int newr = point.first + DIR[i][0];
			int newc = point.second + DIR[i][1];
			if(newr<0 || newr>=R || newc<0 || newc>=C) continue;
			// (newr,newc) is our candidate center
			bool suc = true;
			for(int j=0;j<4;j++){
				int nnr = newr + DIR[j][0];
				int nnc = newc + DIR[j][1];
				suc |= traversed.find(mp(nnr, nnc))!=traversed.end();
			}
			if(suc){
				// found a center!
				if(traversedB.find(mp(newr,newc)) == traversedB.end()){
					traversedB.insert(mp(newr,newc));
					tree.update(newr, newc, vector3(0,0,1));
				}
			}
		}
	}

	// deb(traversed)

	set<pair<int,int>> traversedE;

	for(auto point : traversed){
		int r = point.first;
		int c = point.second;
		for(int i=0;i<4;i++){
			int newr = r + MOV[i][0];
			int newc = c + MOV[i][1];
			if(newr < 0 || newr>=R || newc < 0 || newc>=C) continue;
			// (newr,newc) is a neighbor
			// we can find it
			int er = (newr+r)/2;
			int ec = (newc+c)/2;
			if(traversedE.find(mp(er,ec)) == traversedE.end()){
				tree.update(er,ec,vector3(0,1,0));
				traversedE.insert(mp(er,ec));
			}
		}
	}

	// deb(traversedB)
	// deb(traversedE)
	// deb(traversed)


	for(int i=0;i<Q;i++){
		llong r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
		r1--; c1--; r2--; c2--;
		r1*=2; c1*=2; r2*=2; c2*=2;

		// let's deal with degenerate ones separately

		auto countV = [&](llong r1, llong r2, llong c1, llong c2){
			llong av = ((r2-r1)/2+1)*((c2-c1)/2+1);
			return av-queryBox(tree, r1, r2, c1, c2).v;
		};
		llong v = countV(r1, r2, c1, c2);

		auto countE = [&](llong r1, llong r2, llong c1, llong c2){
			llong ae = ((r2-r1)/2+1)*(c2-c1)/2 + (r2-r1)/2*((c2-c1)/2+1);
			return ae-queryBox(tree, r1, r2, c1, c2).e;
		};
		llong e = countE(r1, r2, c1, c2);

		auto countB = [&](llong r1, llong r2, llong c1, llong c2){ 
			llong ab = (r2-r1)/2*(c2-c1)/2;
			// a white region must either encircle emptiness (a 2x2 square) or black region, in which case we should check if the boundaries are all white
			int vtop = queryBox(tree, r1, r1, c1, c2).v;
			int vbot = queryBox(tree, r2, r2, c1, c2).v;
			int vleft = queryBox(tree, r1, r2, c1, c1).v;
			int vright = queryBox(tree, r1, r2, c2, c2).v;
			int iv = queryBox(tree, r1,r2,c1,c2).v;
			if(vtop+vbot+vleft+vright == 0 && iv != 0) // boundary is all white and there's black inside
				ab++;
			return ab-queryBox(tree, r1, r2, c1, c2).f+1; // +1 for the outer face
		}; 
		llong f = countB(r1, r2, c1, c2);

		llong cc = v - e + f - 1;
		assert(counter<MAXSIZE);
		// if(cc<0){
		// 	deb(mt(r1,r2,c1,c2))
		// 	deb(mt(v,e,f))
		// }
		assert(cc>=0);
		print(cc);
	}
	

}



int main(){
	DynamicSegtree::init();
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
	//print(counter);
}



/*


// int evs = ((r2 - r1)/2 + 1)*2 + ((c2 - c1)/2 + 1)*2 - 4;
			// if(r1 == r2) evs = c2 - c1 + 1;
			// if(c1 == c2) evs = r2 - r1 + 1;


// int ees = (r2-r1)/2 * 2 + (c2-c1)/2 * 2;
			// if(r1 == r2) ees = c2 - c1;
			// if(c1 == c2) ees = r2 - r1;






*/