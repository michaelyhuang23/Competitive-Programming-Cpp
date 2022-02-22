#include<bits/stdc++.h>



using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define MOD 1000000009
#define print(x) cout<<x<<endl

vector<llong> primes;

llong power(llong base, llong pow){
	if(pow == 0) return 1;
	if(pow % 2 == 0){
		llong inter = power(base, pow/2);
		return (inter*inter)%MOD;
	}else{
		return (power(base, pow-1)*base)%MOD;
	}
}

unordered_map<llong,llong> prime_decompose(llong num){
	unordered_map<llong,llong> pp;
	for(llong p : primes){
		if(p*p > num){
			if(num>1){
				pp[num] = 1;
				num = 1;
			}
			break;
		}
		while(num % p == 0){
			if(pp.find(p) == pp.end()) pp[p] = 0;
			pp[p]++;
			num /= p;
		}
	}
	return pp;
}

void solve(){
	llong k, d, m; cin >> k;
	cin >> d >> m;
	unordered_map<llong,llong> pd = prime_decompose(d);
	unordered_map<llong,llong> pm = prime_decompose(m);
	
	set<llong> allP;
	for(auto& item : pd) allP.insert(item.first);
	for(auto& item : pm) allP.insert(item.first);

	llong total = 1;
	for(llong p : allP){
		llong low = 0, high = 0;
		if(pd.find(p) != pd.end()) low = pd[p];
		if(pm.find(p) != pm.end()) high = pm[p];
		if(low == high) {
			total *= 1;
			continue;
		}else if(low > high){
			total *= 0;
			break;
		}
		assert(high > low);
		llong x0 = high - low + 1;
		llong x1 = high - low;
		llong x2 = high - low;
		llong x3 = high - low - 1;
		llong cp = power(x0, k) - power(x1, k) - power(x2, k) + power(x3, k);
		cp = (cp+2*MOD)%MOD;
		total *= cp;
		total %= MOD;
	}
	print(total);
}




int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	primes = vector<llong>();
	primes.pb(2);
	primes.pb(3);
	for(llong i=1; i*6+1<=41622;i++){
		auto checkP = [&](llong num){
			bool isP = true;
			for(llong p : primes){
				if(p*p > num) break;
				if(num % p == 0){
					isP = false; 
					break;
				}
			}
			if(isP) primes.pb(num);
		};

		checkP(i*6-1);
		checkP(i*6+1);
	}

	//print(primes.size());

	llong tt; cin >> tt;
	while(tt--) solve();
}