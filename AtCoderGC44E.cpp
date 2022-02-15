#include<bits/stdc++.h>



using namespace std;

typedef long long llong;
typedef long double ddouble;
#define pb push_back

typedef complex<ddouble> point;
#define X real()
#define Y imag()
#define infinitesimal 1e-9
#define print(x) cout<<x<<endl

int N;
vector<llong> A;
vector<llong> B;
vector<ddouble> C;

ddouble cross(point x, point y){
	return (conj(x)*y).Y;
}

bool equal(ddouble x, ddouble y){
	return abs(x-y)<infinitesimal;
}

void solve(){
	cin >> N;
	cout.precision(20);
    A = vector<llong>(N);
    B = vector<llong>(N);
	for(int i=0;i<N;i++) cin >> A[i];
	for(int i=0;i<N;i++) cin >> B[i];
	int maxPos = 0;
	llong maxVal = 0;
	for(int i=0;i<N;i++) if(A[i]>maxVal) {
		maxVal = A[i];
		maxPos = i;
	}
	//deb(maxPos)
	rotate(A.begin(), A.begin()+maxPos, A.end());
	rotate(B.begin(), B.begin()+maxPos, B.end());
	A.pb(A[0]);
	B.pb(B[0]);
	// we have N-1 equations
	// we have N variables, so the first variable may be allowed free.
	// let it be 0 and the next be x.
	C = vector<ddouble>(N+1,0);
	vector<llong> C1(N+1,0);
	vector<llong> C0(N+1,0);
	C1[1]=1;
	for(int i=2;i<N+1;i++){
		C1[i] = 2*C1[i-1]-C1[i-2];
		C0[i] = 2*C0[i-1]+2*B[i-1]-C0[i-2];
	}
	ddouble x = -(ddouble)C0[N]/((ddouble)C1[N]);
	for(int i=0;i<N+1;i++) C[i] = x*C1[i]+C0[i];

	//deb(C)

	vector<ddouble> Ap(N+1,0);
	for(int i=0;i<N+1;i++) Ap[i] = (ddouble)A[i] - C[i];

	//deb(Ap)

	vector<ddouble> G(N+1,0);
	vector<point> hull;
	for(int i=0;i<N+1;i++){
		point np(i, Ap[i]);
		auto cond = [&](){
			if(hull.size()<2) return false;
			point oldline = hull[hull.size()-1]-hull[hull.size()-2];
			point newline = np - hull[hull.size()-1];
			return cross(oldline, newline)>=0;
		};
		while(cond()) hull.pop_back();
		hull.pb(np);
	}
	for(int i=0;i<N+1;i++){
		point cp(i, 0);
		auto it = lower_bound(hull.begin(), hull.end(), cp, [&](point x, point y){
			return x.X < y.X;
		});
		assert(it != hull.end() && next(it) != hull.begin());
		point fp = *it;
		if(equal(fp.X, i)) G[i] = fp.Y;
		else{
			assert(it != hull.begin());
			auto pi = prev(it);
			point pp = *pi;
			point np = *it;
			assert(pp.X<i && i<np.X);
			ddouble val = (np.Y*(i-pp.X) + pp.Y*(np.X-i))/(np.X-pp.X);
			G[i] = val;
		}
	}

	//deb(G)

	vector<ddouble> F(N+1, 0);
	for(int i=0;i<N+1;i++) F[i] = G[i] + C[i];
	//deb(F)
	ddouble total = 0;
	for(int i=0;i<N;i++) total += F[i];
	print(total/N);
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}