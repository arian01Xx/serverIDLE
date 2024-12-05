#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int networkBecomesIdle(vector<vector<int>>& edges, vector<int>& patience) {
        int n=patience.size();
        vector<vector<int>> graph(n);
        vector<int> time(n, -1);

        for(auto x: edges){
            graph[x[0]].push_back(x[1]);
            graph[x[1]].push_back(x[0]); //unidirectionally
        }

        queue<int> q;
        q.push(0);
        time[0]=0;

        while(q.size()){
            int node=q.front();
            q.pop();
            //registro del tiempo, no vector bool visited
            for(auto child: graph[node]){
                if(time[child]==-1){
                    time[child]=time[node]+1; //acumulación del tiempo
                    q.push(child);
                }
            }
        }

        int res=0;
        for(int i=1; i<n; i++){
            //calculo del tiempo ida y vuelta y 
            //los mensajes necesarios enviados por el servidor
            int extraPayload=(time[i]*2-1)/patience[i];

            //ultimo segundo en que el servidor envia un mensaje
            int lastOut=extraPayload*patience[i];

            //tiempo total, el ultimo segundo mas ida y vuelta
            int lastIn=lastOut+time[i]*2;
            res=max(res, lastIn);
        }

        return res+1;
    }
};

int main(){
    return 0;
}