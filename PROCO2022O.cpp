#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define inf 1000000000
#define print(x) cout<<x<<endl
#define MOD 1000000007LL

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
		return power(MOD-2);
	}

	mint operator+(mint other){ return mint(x+other.x); }
	mint operator-(mint other){ return mint(x-other.x); }
	mint operator*(mint other){ return mint(x*other.x); }
	mint operator/(mint other){ mint invert = other.inverse(); return (*this)*(invert); }
};

ostream& operator <<( ostream& os, const mint& p ) {
	return os << p.x;
}

mint permute(llong num){
	mint total = 1;
	for(int i = 1;i<=num;i++){
		total = total * mint(i);
	}
	return total;
}

void solve(){
	string s; cin >> s;
	vector<int> hist(26,0);
	for(int i=0;i<s.size();i++){
		hist[s[i]-'a']++;
	}
	mint total = s.size();

	//deb(total)

	mint numer = permute(total.x);
	mint denom = 1;

	// deb(numer)
	// deb(denom)


	for(int i=0;i<26;i++){
		denom = denom * permute(hist[i]);
	}

	//deb(denom)

	mint counter = 0;
	for(int i=0;i<s.size();i++){
		// imagine we put something else
		for(char c=s[i]+1; c<='z'; c++){
			if(hist[c-'a']==0) continue;
			mint numerP = numer/total;
			// total --
			mint denomP = denom/mint(hist[c-'a']);
			// hist[c] --
		//	mint ret = numerP/denomP;
		//deb(ret)
			counter = counter + (numerP/denomP);
		}

		
		numer = numer/total;
		total = total - 1;
		denom = denom/mint(hist[s[i]-'a']);
		hist[s[i]-'a']--;
	}


	print(counter.x);

}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();	
}