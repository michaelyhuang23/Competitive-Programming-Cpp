#include<bits/stdc++.h>


using namespace std;



void solve(int id){
	string T, P; cin >> T >> P;

	int counter = 0;
	int j = 0;
	bool suc =true;
	for(int i=0;i<T.size();i++){
		char c = T[i];
		while(j<P.size() && P[j]!=c) {
			j++; counter++;
		}
		j++;
		if(j>P.size()){suc=false;break;}
	}

	counter += P.size()-j;

	if(suc) {
		cout<<"Case #"<<id<<": "<<counter<<endl;
	}else{
		cout<<"Case #"<<id<<": IMPOSSIBLE"<<endl;
	}
}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	for(int i=0;i<tt;i++)
		solve(i+1);
}