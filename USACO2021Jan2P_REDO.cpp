#include<iostream>
#include<assert.h>
#include<vector>
#include<algorithm>

using namespace std;

typedef long long llong;
#define mp make_pair
#define mt make_tuple
#define pb push_back

struct Function{
	int b, c; // we have bx + c or x^2 + bx + c
	bool isQuad = false;
	int xl, xh;
	Function(int b_, int c_, int isQuad_, int xl_, int xh_){
		b = b_; c = c_; isQuad = isQuad_; xl = xl_; xh = xh_;
	}
	int getTMax(int cy){
		int mid;
		if(isQuad){
			mid = (cy - b) / 4;
			auto deri = [&](int m){return 4*m - cy - b;}; 
			if(abs(deri(mid)) > abs(deri(mid+1))) // this deals with rounding
				mid++;
		}else{
			mid = (cy - b) / 2;
			auto deri = [&](int m){return 2*m - cy - b;};
			if(abs(deri(mid)) > abs(deri(mid+1))) 
				mid++;
		}
		return mid;
	}
	int eval(int x){
		assert(xl<=x && x<=xh);
		int result = b*x + c;
		if(isQuad) result+=x*x;
		return result;
	}
};



int N, M, Q;
vector<int> cys;
vector<vector<Function> > dp;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	cys = vector<int>(M);
	for(int i=0;i<M;i++) cin >> cys[i];

	dp = vector<vector<Function> >(M);
	for(int y=1;y<M;y++){
		int py = y-1;
		for(auto& f : dp[py]){
			int tmax = f.getTMax(cys[y]);

		}
	}

}



