
#include<bits/stdc++.h>


typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
using namespace std;

const llong D = 11; 
const llong Sep = 9; // only 10 numbers
// #warning "add 1 to the end if it's exactly 10^12"
llong power[11][15];

vector<vector<vector<llong>>> hists;

void preprocess(){
	hists = vector<vector<vector<llong>>>(D+1);
	for(llong d=1;d<=D;d++) hists[d].reserve(100000);
	for(llong i=0;i<=10;i++){
		power[i][0]=1;
		for(llong j=1;j<15;j++) power[i][j]=power[i][j-1]*i;
	}

	for(llong d=1;d<=D;d++){
		llong S = d+Sep;
		llong maxS = 1<<S;
		for(llong s=0;s<maxS;s++){
			llong cc = __builtin_popcount(s);
			if(cc!=Sep) continue;
			llong prevj = 0;
			vector<llong> ccs;
			for(llong j=0;j<S;j++){
				if((1<<j)&s){
					ccs.pb(j-prevj);
					prevj = j+1;
				}
			}
			ccs.pb(S-prevj);
			assert(ccs.size()==Sep+1);
			llong summ=0;
			for(llong i=0;i<=9;i++){
				summ+=ccs[i]*i;
			}
			if(summ==0) continue;
			llong prod=1;
			for(llong i=0;i<=9;i++){
				prod*=power[i][ccs[i]];
			}
			if(prod%summ == 0){
				hists[d].pb(ccs);
			}
		}
	}
}




llong solve(llong id){
	string A,B; cin >> A >> B;
	llong a = stoll(A);
	llong b = stoll(B);
	llong na = A.size();
	llong nb = B.size();
	llong counter = 0;
	if(nb==12 && na==12){
		return 1;
	}else if(nb==12){
		counter++;
		nb--;
	}

	// deb(hists[1])


	for(llong d=na;d<=nb;d++){
		llong low = max(a, power[10][d-1]);
		llong high = min(b, power[10][d]-1);


		vector<llong> vlow(d);
		llong ll = low;
		for(llong j=0;j<d;j++){
			vlow[j] = ll%10;
			ll/=10;
		}

		vector<llong> vhigh(d);
		llong hh = high;
		for(llong j=0;j<d;j++){
			vhigh[j] = hh%10;
			hh/=10;
		}
		// deb(vlow)
		// deb(vhigh)

		assert(vhigh.back()!=0 && vlow.back()!=0 && ll==0 && hh==0);

		for(vector<llong> sol : hists[d]){
			// vector<llong> sol = {0, 0, 0, 0, 1, 0, 2, 0, 0, 0};
			for(int i=0;i<10;i++) sol[i];
			vector<llong> pmul(10);
			pmul[0]=1;
			for(llong i=1;i<10;i++) pmul[i]=pmul[i-1]*(sol[i-1]+1);
			// exclusive prefix mul

			// deb(pmul)

			auto id2vec = [&](llong x){
				vector<llong> vec(10,0);
				for(llong i=10-1;i>=0;i--){
					llong p = x / pmul[i];
					x %= pmul[i];
					vec[i] = p;
				}
				return vec;
			};


			auto vec2id = [&](vector<llong>& vec){
				llong x=0;
				for(llong i=0;i<10;i++){
					x+=vec[i]*pmul[i];
				}
				return x;
			};


			llong maxX = vec2id(sol);
			// deb(maxX)
			// deb(sol)
			// deb(id2vec(maxX))
			vector<vector<vector<llong>>> dp(d+1, vector<vector<llong>>(maxX+1,vector<llong>(4,0)));
			// digit, usage state, 00: x=low=high, 01: low<x=high, 10: low=x<high, 11: low<x<high
			dp[d][0][0] = 1;
			for(llong i=d-1;i>=0;i--){
				for(llong x=0;x<=maxX;x++){
					vector<llong> vec = id2vec(x);
					// deb(vec)
					llong sum = 0;
					for(llong item : vec) sum+=item;
					if(sum != d-1-i+1) continue;

					// deb(vec)

					for(llong j=0;j<10;j++){
						if(vec[j]==0) continue;
						llong px = x-pmul[j];
						dp[i][x][3] += dp[i+1][px][3];
					}
					if(vlow[i]==vhigh[i] && vec[vlow[i]]>0){
						llong px = x-pmul[vlow[i]];
						dp[i][x][0] += dp[i+1][px][0];
					}else{
						llong j = vlow[i];
						if(vec[j]!=0){
							llong px = x-pmul[j];
							// 0 --> 2 covered
							// 2 --> 2
							dp[i][x][2] += dp[i+1][px][2];
							dp[i][x][2] += dp[i+1][px][0];
						} 

						j = vhigh[i];
						if(vec[j]!=0){
							llong px = x-pmul[j];
							// 1 --> 1
							dp[i][x][1] += dp[i+1][px][1];
							dp[i][x][1] += dp[i+1][px][0];
						} 
					}
					for(llong j=vlow[i]+1;j<vhigh[i];j++){
						if(vec[j]==0) continue;
						llong px = x-pmul[j];
						dp[i][x][3] += dp[i+1][px][0];
					}
					for(llong j=vlow[i]+1;j<10;j++){
						if(vec[j]==0) continue;
						llong px = x-pmul[j];
						// 2 --> 3
						dp[i][x][3] += dp[i+1][px][2];
					}
					for(llong j=0;j<vhigh[i];j++){
						if(vec[j]==0) continue;
						llong px = x-pmul[j];
						// 1 --> 3
						dp[i][x][3] += dp[i+1][px][1];
					}

					// deb(mp(i,x))
					// deb(dp[i][x])
				}
			}

			llong total = 0;
			for(llong i=0;i<4;i++)
				total+=dp[0][maxX][i];

			// deb(total)

			counter+=total;
		}
	}

	return counter;
}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong tt; cin >> tt;

	preprocess();

	for(llong i=0;i<tt;i++)
		cout<<"Case #"<<i+1<<": "<<solve(i+1)<<endl;
}