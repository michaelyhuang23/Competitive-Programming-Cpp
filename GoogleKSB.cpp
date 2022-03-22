#include<bits/stdc++.h>

#define pb push_back
#define mp make_pair
using namespace std;



void solve(int id){
	string N; cin >> N;

	int sum = 0;
	for(int i=0;i<N.size();i++){
		sum += N[i]-'0';
	}

	sum %= 9;
	int num = 9-sum;
	if(num==9) num=0;

	char chr = (char)(num+'0');
	vector<char> str;
	bool used = false;
	for(int i=0;i<N.size();i++){
		int x = N[i]-'0';
		if(x>num && (num>0 || str.size()>0) && !used){str.pb(chr); used=true;}
		str.pb(N[i]);

	}
	if(!used) str.pb(chr);
	string output(str.begin(), str.end());

	cout<<"Case #"<<id<<": "<<output<<endl;
}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	for(int i=0;i<tt;i++)
		solve(i+1);
}