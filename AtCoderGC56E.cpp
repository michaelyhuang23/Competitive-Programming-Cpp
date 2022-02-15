#include<bits/stdc++.h>


using namespace std;

typedef long long llong;
typedef long double ddouble;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define MOD 998244353LL
#define print(x) cout<<x<<endl

struct mint{
	llong x;
	mint() : x(0) {}
	mint(llong x_) : x(x_) { correct(); }
	void correct(){ x = (x+MOD)%MOD; }
	mint power(llong pow) {
		if(pow==0) return mint(1);
		if(pow%2==0){
			mint inter = power(pow/2);
			return inter*inter;
		}else{
			return (*this)*(power(pow-1)); 
		}
	}

	mint inverse() {
		if(x==2) return mint(499122177);
		if(x==499122177) return mint(2);
		return power(MOD-2);
	}

	mint operator+(mint other){ return mint(x+other.x); }
	mint operator-(mint other){ return mint(x-other.x); }
	mint operator*(mint other){ return mint(x*other.x); }
	mint operator/(mint other){ mint invert = other.inverse(); return (*this)*(invert); }
};

// struct mint{
// 	ddouble x;
// 	mint() : x(0) {}
// 	mint(ddouble x_) : x(x_) { correct(); }
// 	void correct(){ x = x; }
// 	mint power(llong pow) {
// 		if(pow==0) return mint(1);
// 		if(pow%2==0){
// 			mint inter = power(pow/2);
// 			return inter*inter;
// 		}else{
// 			return (*this)*(power(pow-1)); 
// 		}
// 	}

// 	mint inverse() {
// 		return mint(1.0/x);
// 	}

// 	mint operator+(mint other){ return mint(x+other.x); }
// 	mint operator-(mint other){ return mint(x-other.x); }
// 	mint operator*(mint other){ return mint(x*other.x); }
// 	mint operator/(mint other){ mint invert = other.inverse(); return (*this)*(invert); }
// };

ostream& operator <<( ostream& os, const mint& p ) {
	return os << p.x;
}

vector<vector<mint>> choice(42, vector<mint>(42, 0));


mint choose(int n, int k){
	if(k>n) return mint(0);
	if(choice[n][k].x != 0) return choice[n][k];
	mint total = 1;
	for(int i=n;i>k;i--){
		total = total * mint(i);
	}
	mint den = 1;
	for(int i=n-k;i>=1;i--){
		den = den * i;
	}
	choice[n][k] = total / den;
	return choice[n][k];
}

llong solve_one(llong N, vector<mint>& probs, vector<vector<mint>>& ring_dp){
	vector<mint> suffix(N+1,mint(0));
	for(int i=N;i>=1;i--){
		if(i==N) suffix[i] = probs[i];
		else suffix[i] = suffix[i+1] + probs[i];
	}

	vector<mint> probPasses(43);
	for(int i=0;i<43;i++){
		probPasses[i] = mint(1)/mint(2).power(i);
	}

	// deb("first stage finished")
	//deb(ring_dp)

	// now we must move all cheese to the location 1
	auto pushCheese = [&](){
		vector<vector<vector<mint>>> dp(N+2, vector<vector<mint>>(N, vector<mint>(N,0)));
		// onto ith location (before ith mouse), 
		// j cheese at the ready at this point, 
		// k more cheese to distribute
		// initialize it

		// we always want the first mouse to survive so start from 2

		dp[1][0][N-1] = 1; 

		for(int i=1;i<=N;i++){
			mint prob = probs[i]/suffix[i];
			for(int j=0;j<=N-1;j++){
				for(int k=0;k<=N-1;k++){
					if(j+k>N-1) continue; // invalid state
					if(dp[i][j][k].x == 0) continue;
					//deb(mp(i,prob))
					for(int x=0;x<=k;x++){// distribute x cheese at this point
						mint probDistribute = prob.power(x)*(mint(1)-prob).power(k-x)*choose(k,x);
						int nj = j + x;
						int nk = k - x;
						mint probPass = probPasses[nj];
						mint probNot = mint(1) - probPass;

						// if(dp[i][j][k].x>0){
						// 	deb(mt(i,j,k))
						// 	deb(x)
						// 	deb(dp[i][j][k])
						// 	deb(mp(probPass, probNot))
						// 	deb(probDistribute)
						// }

						probPass = probPass * probDistribute;
						dp[i+1][nj][nk] = dp[i+1][nj][nk] + dp[i][j][k]*probPass;

						probNot = probNot * probDistribute;
						if(i+1 != 2 && nj!=0) // if 2, well then 1 must survive, so we can't cut it
							dp[i+1][nj-1][nk] = dp[i+1][nj-1][nk] + dp[i][j][k]*probNot;
					}
				}
			}
		}

		// before N+1 mouse
		vector<mint> ans(N);
		for(int j=0;j<=N-1;j++){
			ans[j] = dp[N+1][j][0];
		}

		mint survive = 0;
		for(int j=0;j<=N-1;j++){
			mint prob = probs[1]/suffix[1];
			mint probPass = mint(1)/mint(2).power(j);
			survive = survive + prob*probPass;
		}

		// deb(dp)
		// deb(ans)
		// deb(survive)

		return ans;
	};

	vector<mint> push_ans = pushCheese();

	mint totalTotalProb = 0;
	for(int j=0;j<=N-1;j++){
		// cheese you end up after one loop
		int k = j+1; // number of surviving mouse is always 1+j
		mint probRingSurv = ring_dp[k][1];
		mint probInitialPush = push_ans[j];

		mint totalProb = probRingSurv*probInitialPush;
		totalTotalProb = totalTotalProb + totalProb;
	}
	return totalTotalProb.x;
}

vector<mint> rotate_prob(vector<mint> probs){
	vector<mint> probs2(probs.size());
	for(int i=1;i<probs.size()-1;i++){
		probs2[i] = probs[i+1];
	}
	probs2[probs.size()-1] = probs[1];
	return probs2;
}

void solve(){
	llong N; cin >> N;
	vector<mint> probs(N+1,mint(0));
	for(llong i=1;i<=N;i++) {
		int x; cin >> x;
		probs[i] = mint(x)/mint(100);
	}

	auto ringContract = [&](){
		vector<vector<mint>> dp(N+1,vector<mint>(N+1,0));
		// number of mouse, interested in ith mouse : probability of it surviving
		dp[1][1] = mint(1);
		for(llong n=2;n<=N;n++){
			for(llong i=1;i<=n;i++){
				for(llong k=1;k<=n;k++){ // first mouse to be killed, we will contract it
					if(k==i) continue;
					llong previ = 0;
					if(i>k) previ = i-k;
					else previ = n-(k-i)-1+1;
					mint probPass = mint(1)/mint(2).power(n-1);
					mint prob = probPass.power(k-1)*(mint(1)-probPass);
					mint probLoopOnce = probPass.power(n);
					mint probLoopAll = mint(1)/(mint(1)-probLoopOnce);
					// deb(mt(probPass, probLoopOnce, n))
					prob = prob * probLoopAll;
					// deb(mp(i,k))
					// deb(mt(n, previ, prob))
					dp[n][i] = dp[n][i] + dp[n-1][previ]*prob;
				}
			}
		}
		return dp;
	};

	vector<vector<mint>> ring_dp = ringContract();

	vector<mint> solutions(N);

	for(int i=1;i<=N;i++){
		//if(i==2) break;
		llong solution = solve_one(N, probs, ring_dp);
		probs = rotate_prob(probs);
		solutions[i-1] = solution;
		cout<<solution<<" ";
	}
	cout<<endl;

	// mint total = 0;
	// for(int i=0;i<N;i++) total = total + solutions[i];
	// assert(total.x == 1);
	//deb(solutions)
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}

