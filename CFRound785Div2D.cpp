#include<bits/stdc++.h>

using namespace std;
typedef long long llong;
#define pb push_back
#define mp make_pair
#define print(x) cout<<x<<endl
#define MOD 1000000007

vector<llong> primes;

void gen_primes(llong m){
	auto check_prime = [&](llong p){
		for(llong prime : primes){
			if(prime * prime > p) break;
			if(p%prime == 0) return false;
		}
		return true;
	};
	for(llong i=1;i*6-1<=m;i++){
		if(check_prime(i*6-1)) primes.pb(i*6-1);
		if(i*6+1<=m && check_prime(i*6+1)) primes.pb(i*6+1);
	}
}

llong power(llong num, llong ex){
	if(ex == 0) return 1;
	if(ex % 2 == 1) return power(num, ex-1)*num;
	else {
		llong inter = power(num, ex/2);
		return inter*inter;
	}
}

void solve(){
	llong s0, d0, c0, s1, d1, c1;
	cin >> s1 >> d1 >> c1;
	cin >> s0 >> d0 >> c0;

	llong f0 = s0 + d0*(c0-1);
	llong f1 = s1 + d1*(c1-1);

	if((s0 - s1)%d1 != 0 || d0%d1!=0) {
		print(0); return;
	}

	if(s0 < s1 || f0 > f1){
		print(0); return;
	}

	if(s0 - d0 < s1 || f0 + d0 > f1) {
		print(-1);
		return;
	}


	vector<llong> crs, prs;
	auto prime_decompose = [&](llong x){
		for(llong p : primes){
			llong count = 0;
			while(x % p == 0) {x/=p; count++;}
			if(count>0){
				prs.pb(p);
				crs.pb(count);
			}
		}
		if(x != 1){
			prs.pb(x);
			crs.pb(1);
		}
	};

	prime_decompose(d0);

	llong n = crs.size();
	vector<llong> prods(n,1);
	for(llong i=1;i<n;i++) prods[i] = prods[i-1]*(crs[i-1]+1);

	auto compute_num = [&](llong id){
		llong total = 1;
		for(llong i=n-1;i>=0;i--){
			llong x = id/prods[i];
			total *= power(prs[i], x);
			id -= prods[i]*x;
		}
		return total;
	};


	llong total = 0;

	llong maxi = prods[n-1]*(crs[n-1]+1)-1;
	for(llong i=0;i<=maxi;i++){
		llong num = compute_num(i);

		if(lcm(num, d1) == d0){
			total += (d0*d0/num/num);
			total %= MOD;
		}
	}

	print(total);
}


int main(){
	primes = vector<llong>();
	primes.pb(2); primes.pb(3);
	gen_primes(32000);

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong tt; cin >> tt;
	while(tt--) solve();
}