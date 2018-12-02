#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
using namespace std;

const int maxN = 18;
const int DEGREE = 3;

typedef bitset<maxN> bts;

bool mark[maxN];
int parent[maxN];
vector<int> adj[maxN];
int n = maxN, m;
int g[maxN][maxN], deg[maxN];


bool dfs(int v, bts b) {
	//cout << v << ' ' << b << endl;
	mark[v] = true;
	bool temp = true;
	int cnt = 0;
	for (int i = 0; i < adj[v].size(); ++i) {
		int u = adj[v][i];
	    if (b[u] == 0)
			continue;
		++cnt;
		if (mark[u] and (parent[v] != u)) {
			//cout << "OOPS " << u << ' ' << parent[u] << endl;
			return false;
		}
		if (!mark[u]) {
			parent[u] = v;
			temp &= dfs(u, b);
		}
	}
	if (cnt > 2)
		temp = false;
	return temp;
}


int main() {
	fill(parent, parent + maxN, -1);
    string gg;
    int ans, number;
    int minAns = 1000;
    ans = number = 0;
    bool read = true;
    while (getline(cin, gg)) {
        stringstream strstream;
        strstream << gg;

        if (gg[0] == 'G') {
            read = true;
            for (int i = 0; i < maxN; ++i)
                adj[i].clear();
            n = 0;
            continue;
        }
        if (!read)
            continue;
        if (gg[0] == 'T') {
            read = false;
        }
        if (gg.size() == 0)
            continue;
        if (read) {
            int v;
            strstream >> v;
            --v;
            n = max(n, v + 1);
            string chert;
            strstream >> chert;
            int u;
            while (strstream >> u) {
                --u;
                adj[v].push_back(u);
                //adj[u].push_back(v);
            }
            continue;
        }
      	int save = 0, cont;
		for (int cnt = 0; cnt < (1 << n); ++cnt) {
			fill(mark, mark + maxN, false);
			fill(parent, parent + maxN, -1);
			bts t = bts(cnt);
			vector<int> ver;
			for (int i = 0; i < n; ++i)
				if (t[i])
					ver.push_back(i);
			bool ret = true;
			for (int i = 0; i < ver.size(); ++i) {
				if (t[i] and !mark[ver[i]])
					ret &= dfs(ver[i], t);
			}
			if (ret) {
				int num = __builtin_popcount(cnt);
				if (num > save) 
					save = num, cont = cnt;
			}
			
			//for (long long int  i = 0; i < (long long) 1e9; ++i)
			//	;
		}
		
    	//ans += save;
        ans = max(ans, save);
        minAns = min(minAns, save);
		number++;
        //cout << n << endl;
		cout << endl;
		for (int i = 0; i < n; ++i, cout << endl)
	  		for (int j = 0; j < adj[i].size(); ++j)
  				cout << adj[i][j] << ' ';
  		cout << endl;
  		bts ret = cont;
		//cout << (double) save << ' ' << 2 * bound << ' ' << ((double) save >= 2 * bound) << endl;
		cout << ret << ' ' << save << endl;// << ret[0] << ' ' << ret[1] << ' ' << ret[2] << ' ' << "THE END\n";
		//return 0;

  	}
  	cout << ans << ' ' << minAns << endl;
	return 0;
}