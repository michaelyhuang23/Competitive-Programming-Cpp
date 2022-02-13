#include<bits/stdc++.h>


using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define print(x) cout<<x<<endl
#define MOD 1000000007LL


llong Pow(llong num, llong pow){
	if(pow==0) return 1;
	if(pow%2==0){
		llong inter = Pow(num, pow/2);
		return ((inter*inter)%MOD+MOD)%MOD;
	}else{
		return ((Pow(num, pow-1)*num)%MOD+MOD)%MOD;
	}
}

llong inverse(llong num){
	return Pow(num, MOD-2);
}



vector<llong> permute(1000005, 0);
vector<llong> prefA(1000005,0);

void solve(){
	llong n, m; cin >> n >> m;
	llong count = 0;
	// contained in the middle
	count += ((permute[m]*permute[n-m])%MOD)*(n-m+1);
	count %= MOD;

	//deb(count)

	// contained on the edge
	llong count2 = (permute[m]*permute[n-m])%MOD;
	count2 *= (m-1);
	count2 %= MOD;
	count2 -= prefA[m];

	count2 = (count2+MOD)%MOD;

	// for(llong i=1;i<m;i++){
	// 	llong j = m-i;
	// 	llong count3 = (choose(m, i)*permute(j))%MOD;
	// 	count3 *= (((permute(n-m)*permute(i))%MOD-1)+MOD)%MOD;
	// 	count3 %= MOD;
	// 	count2 += count3;
	// 	count2 %= MOD;
	// }


	//deb(count2)

	print((count + count2)%MOD);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	prefA[1] = 0;
	prefA[2] = 2;
	prefA[3] = 9;

	for(llong i=2; i<1000001; i++){
		prefA[i+1] = (prefA[i]+1)*(i+1);
		prefA[i+1] %= MOD;
	}

	permute[0]=1;
	for(llong i=1; i<1000001; i++){
		permute[i] = permute[i-1]*i;
		permute[i] %=MOD;
	}

	assert(prefA[3] == 9);

	llong tt; cin >> tt;
	while(tt--) solve();
}




