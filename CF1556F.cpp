#include<iostream>
#include<assert.h>
#include<vector>
#include<numeric>
#include<bitset>

#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define mt make_tuple

template<class C>
void print(C& obj){cout<<obj<<endl;}

struct Fraction {
    llong a, b;
    Fraction(){
        a = 0; b = 1;
    }
    Fraction(llong x, llong y){
        a = x; b = y;
        assert(b!=0);
        reduce();
    }
    Fraction operator+(Fraction s) const{
        Fraction p(a*s.b+b*s.a, s.b * b);
        p.reduce();
        return p;
    }
    Fraction operator*(Fraction s) const{
        Fraction p(a*s.a, b*s.b);
        p.reduce();
        return p;
    }
    inline void reduce(){
        llong gc = gcd(a,b);
        a /= gc;
        b /= gc;
    }
    Fraction inv() const{
        assert(a!=0);
        return Fraction(b,a);
    }
};

ostream& operator << ( ostream& os, const Fraction & p ) {
	return os << "(" << p.a << " / " << p.b << ")";
}


llong Pow(llong num, int pow){
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

int n;
vector<int> arr;
vector<vector<Fraction>> cp;



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	arr = vector<int>(n);
	cp = vector<vector<Fraction>>(n, vector<Fraction>(n));
	for(int i=0;i<n;i++) cin >> arr[i];
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			cp[i][j] = Fraction(arr[i],1)*Fraction(1,arr[i] + arr[j]);// i defeats j
			cp[j][i] = Fraction(arr[j],1)*Fraction(1,arr[i] + arr[j]);
		}
	}
	Fraction total(0,1);
	for(int i=0;i<n;i++){
		int maxS = 1<<n;
		vector<Fraction> dp(maxS);
		dp[1<<i] = Fraction(1,1);
		for(int s=(1<<i)+1;s<maxS;s++){
			if(((1<<i)&s) == 0) continue;
			for(int j=0;j<n;j++){ // which state it comes from
				if((1<<j) & s){
					int ps = s ^ (1<<j);
					Fraction pr = Fraction();
					for(int k=0;k<n;k++) if((1<<k)&ps) pr = pr+cp[k][j]; 
					bitset<5> br(s);
					bitset<5> br2(ps);
					deb(mp(br2,br))
					deb(dp[ps])
					deb(pr)
					deb(dp[ps]*pr)
					dp[s] = dp[s] + dp[ps] * pr;
					deb(dp[s])
				}
			}
		}
		deb(dp[maxS-1])
		total = total + dp[maxS-1];
	}
	deb(total)
	llong x = (total.a * inverse(total.b))%MOD;
	print(x);
}







