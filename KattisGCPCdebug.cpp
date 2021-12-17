#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <fstream>

using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
typedef long int iint;
typedef unsigned long int uiint;
typedef long long int llong;
typedef unsigned long long int  ullong;
#define Mem(a, b) memset(a, (b), sizeof(a))
#define For(i, j) for (int i=0 ; i<j ; i++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007

ofstream fout("output2");
ifstream fin("input");

int main(){
    ios_base::sync_with_stdio(0);
    fin.tie(0);
    iint n,m;
    fin >> n >> m;
    pair<iint,iint>* scores = new pair<iint,iint>[n];
    For(i,n) scores[i] = make_pair(0,0);
    For(i,m){
        iint t, p;
        fin >> t >> p;
        t = n-t;
        iint s = get<0>(scores[t]);
        iint pen = get<1>(scores[t]);
        s++; pen-=p;
        scores[t] = make_pair(s,pen);
        iint front=0;
        For(i,n-1){
            if(scores[i]>scores[n-1])
                front++;
        }
        fout<<front+1<<endl;
    }
}