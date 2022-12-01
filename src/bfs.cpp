#include "bfs.h"

unordered_map<std::string, Graph::Node*> BFS::abbrMap() {
    return NodeMap;
}

BFS::Node* Graph::abbr(std::string abbr){
    return NodeMap.at(abbr);
}

vector<string> BFS:: shortestDist(string from, string dest){
    queue<string> queue;
    unordered_set<string> beVisited;
    unordered_map<string, string> pre;

    queue.push(from);
    beVisited.insert(from);

    while(!queue.empty()){
        string current = queue.front();
        queue.pop();
        if(current = dest){
            break;
        }

        Node* AbbCurrent = abbr(current);
        for(Edge* i : ){
            if(beVisited.count(i -> dest -> abbr)){
                beVisited.insert(i -> dest -> abbr)
                queue.push(i -> dest -> abbr);
                pre[i -> dest -> abbr] = AbbCurrent -> abbr;
            }
        }
    }

    vector<string> result;
    string current = dest;
    result.push_back(current);
    while(pre.count(current)){
        current = pre[current];
        result.push_back(current);
    }
    reverse(result.begin(), result.end());

    return result;
}