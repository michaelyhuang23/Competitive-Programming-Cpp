#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl

const llong RANGE = 1000000;

vector<llong> primes;

void preprocess(){
	primes = vector<llong>(); primes.reserve(80000);
	primes.pb(2); primes.pb(3);
	for(llong i=1;i*6-1<RANGE;i++){
		auto add_prime = [&](llong x){
			bool suc = true;
			for(llong p : primes){
				if(p*p > x) break;
				if(x%p == 0) suc=false;
			}
			if(suc) primes.pb(x);
		};

		add_prime(i*6-1);
		add_prime(i*6+1);
	}
}












vector<llong> A;
vector<llong> P;

const int dim = 18;
int n, Q;
llong S;

void solve(){
	preprocess();

	// deb(primes)

	cin >> n;
	A = vector<llong>(n);
	for(int i=0;i<n;i++) cin >> A[i];

	cin >> Q;

	P = vector<llong>(n); // only from 0 to n-1
	P[0] = A[0];
	for(int i=1;i<n;i++) P[i] = P[i-1] + A[i];

	S = P[n-1];

	// deb(S)

	for(int i=0;i<n-1;i++) P[i] = gcd(P[i], S);

	// deb(S)
	vector<llong> prs;
	vector<int> crs(dim,0);
	auto prime_decompose = [&](llong x){
		for(llong p : primes){
			llong cc = 0;
			while(x%p == 0) {x/=p; cc++;}
			if(cc==0) continue;
			prs.pb(p);
		 	crs[prs.size()-1] = cc;
		}
		return x;
	};


	llong Sx = prime_decompose(S);

	auto prime_decompose_hint = [&](llong x, vector<int>& crp){
		for(llong i=0;i<prs.size();i++){
			llong p = prs[i];
			int cc = 0;
			while(x%p == 0) {x/=p; cc++;}
			if(cc==0) continue;
			crp[i] = cc;
		}
		return x;
	};

	// deb(P)
	// deb(prs)
	int D = prs.size();

	vector<vector<int>> vecs(n-1, vector<int>(dim,0));
	vector<llong> R(n);
	for(int i=0;i<n-1;i++){
		llong Px = prime_decompose_hint(P[i], vecs[i]);
		R[i] = Px;
	}

	R[n-1] = Sx;

	// deb(prs)
	// deb(crs)

	set<llong> rems;
	for(int i=0;i<n;i++){
		if(R[i]==1) continue;
		rems.insert(R[i]);
	}


	llong p = 0;
	llong q = 0;

	if(rems.size()==0){

	}else if(rems.size()==1){
		D++;
		p = *rems.rbegin();
		prs.pb(p);
		if(Sx == p) crs[D-1] = 1;
		for(int i=0;i<n-1;i++)
			if(R[i] == p) vecs[i][D-1] = 1;
	}else {
		// assert(rems.size()==2 || rems.size()==3);
		llong pq = *rems.rbegin(); // the double most exist ofc
		p = *rems.begin();
		q = pq / p; // p < q
		if(p>q) swap(p,q);
		// deb(rems)
		if(p == q){
			D+=1;
			prs.pb(p);
			if(Sx % pq == 0) crs[D-1] = 2;
			else if(Sx % p == 0) crs[D-1] = 1;

			for(int i=0;i<n-1;i++){
				if(R[i] % pq == 0) vecs[i][D-1] = 2;
				else if(R[i] % p == 0) vecs[i][D-1] = 1;
			}
		}else{
			D+=2;
			prs.pb(p);
			prs.pb(q);
			if(Sx % p == 0) crs[D-2] = 1;
			if(Sx % q == 0) crs[D-1] = 1;

			for(int i=0;i<n-1;i++){
				if(R[i] % p == 0) vecs[i][D-2] = 1;
				if(R[i] % q == 0) vecs[i][D-1] = 1;
			}
		}
	}


	assert(D<=dim);
	// deb(mp(prs, D))
	assert(prs.size()==D);

	vector<int> ss = crs;
	for(int i=0;i<dim;i++) ss[i]++;

	vector<int> pms(dim);
	pms[0] = 1;
	for(int i=1;i<dim;i++) pms[i] = pms[i-1] * ss[i-1];
	auto id2vec = [&](int x){
		vector<int> vec(dim,0);
		for(int i=dim-1;i>=0;i--){
			int p = x / pms[i];
			x %= pms[i];
			vec[i] = p;
		}
		return vec;
	};

	// deb(ss)

	auto vec2id = [&](vector<int>& vec){
		int x=0;
		for(int i=0;i<dim;i++){
			x+=vec[i]*pms[i];
		}
		return x;
	};

	// deb(crs)

	int maxX = vec2id(crs);
	vector<int> suffix_arr(maxX+1,0);

	// deb(maxX)

	for(int i=0;i<n-1;i++){
		vector<int>& vec = vecs[i];
		int x = vec2id(vec);
		suffix_arr[x]++;
	}

	for(int i=0;i<dim;i++){
		for(int x=maxX;x>=0;x--){
			int pp = x+1;
			if(i+1<dim) pp = pms[i+1];
			if((x%pp)/pms[i]==0) continue;
			int nx = x - pms[i]*1;
			suffix_arr[nx] += suffix_arr[x];
		}
	}

	for(int i=0;i<Q;i++){
		llong qq; cin >> qq;
		if(S % qq != 0){
			print(-1);
			continue;
		}
		vector<int> crq(dim,0);
		llong Qx = prime_decompose_hint(qq, crq);

		int x = vec2id(crq);

		int count = suffix_arr[x];

		llong k = S/qq;
		print((llong)n+k-2-2*count);

	}
}





































int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}