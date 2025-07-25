#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <stdexcept>
#include <iomanip>
#include "game.h"

using namespace std;
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

vector<int> groupID;
vector<vector<int> > adjacencyMatrix;

/*
land - land: 1
coast - coast: 2
land - coast: 3
water - land: 3
coast - land: 3
*/


//orders must be in order of convoy, move, then support, with holds at either end
int adjudicate(int phase, vector<int> *occupiers, vector<int> *owner, vector<order> orders, vector<int> groupID,
    vector<vector<int> > adjacencyMatrix, vector<int> SCmap, vector<pair<int, int> > *retreats_needed) {
    int numTerr = (*occupiers).size();
    int numSpace = (*owner).size();
    int totalSCs = 0;
    for(int i = 0; i < numSpace; i++){
        if(SCmap[i] != 0) {
            totalSCs++;
        }
    }
    //move phase
    if(phase % 5 == 0 || phase % 5 == 2) {
        vector<vector<int> > moveVectors(numTerr, vector<int>(numTerr));
        vector<vector<int> > addedConvoys(numTerr, vector<int>(numTerr));
        vector<int> possibleConvoys;
        vector<int> convoyMatrix(numTerr);

        for(int i = 0; i < numTerr; i++) {
            for(int j = 0; j < numTerr; j++) {
                if (i == j && (*occupiers)[i] != 0) {
                    moveVectors[i][j] = 1;
                } else {
                    moveVectors[i][j] = 0;
                }
                addedConvoys[i][j] = 0;
            }
            convoyMatrix[i] = 0;
        }
        vector<set<int> > adjList(numTerr);
        //create adjacency list from adjacency matrix
        for(int i = 0; i < numTerr; i++) {
            for(int j = 0; j < numTerr; j++) {
                if(adjacencyMatrix[i][j] == 2 || adjacencyMatrix[i][j] == 3 ||
                    adjacencyMatrix[j][i] == 2 || adjacencyMatrix[j][i] == 3) {
                    adjList[i].insert(j);
                    adjList[j].insert(i);
                }
            }
        }
        
        /*for(int i = 0; i < numTerr; i++) {
            cout << i << ": ";
            for(auto &a: adjList[i]) {
                cout << a << " ";
            }
            cout << endl;
        }*/

        //process convoys only
        for (order o: orders) {
            if ((*occupiers)[o.startID] == -1) {
                continue;
            }
            if (o.typeID == HOLD_ID) {
                //process holds
                moveVectors[o.startID][o.startID] = 1;
            }
            if (o.typeID == CONVOY_ID) {
                //process convoys
                if (o.unitID != FLEET_ID) {
                    continue;
                }
                int src = o.auxID;
                int dest = o.endID;
                if (src == dest) {
                    continue;
                }
                bool found = false;
                for(auto &i : possibleConvoys) {
                    if(i == src * numTerr + dest) {
                        found = true;
                    }
                }
                if (!found) {
                    possibleConvoys.push_back(src * numTerr + dest);
                }
                int convoyID = src * numTerr + dest;
                convoyMatrix[o.startID] = convoyID;
            }
        }
        //BFS on all convoys
        for(int i : possibleConvoys) {
            int src = i/numTerr;
            int dest = i%numTerr;
            vector<int> visited(numTerr);
            queue<int> q;
            q.push(src);
            while(!q.empty()) {
                int t = q.front();
                q.pop();
                if(t == dest) {
                    addedConvoys[src][dest] = 1;
                    break;
                }
                for(int n : adjList[t]) {
                    if(convoyMatrix[n] == i) {
                        q.push(n);
                    }
                }
            }
        }

        //process all other orders
        for (order o: orders) {
            if (o.typeID == MOVE_ID) {
                //process moves
                if (o.typeID == ARMY_ID && adjacencyMatrix[o.startID][o.endID] != 1 && addedConvoys[o.startID][o.endID] != 1) {
                    continue;
                }
                if (o.typeID == FLEET_ID && adjacencyMatrix[o.startID][o.endID] != 2) {
                    continue;
                }
                moveVectors[o.startID][o.endID] = 1;
                moveVectors[o.startID][o.startID] = 0;
            }
            if (o.typeID == SUPPORT_ID) {
                //process supports
                if (adjacencyMatrix[o.startID][o.endID] == 0) {
                    //cout << "d";
                    continue;
                }
                if (o.auxID == -1) {
                    moveVectors[o.endID][o.endID] += 1;
                } else {
                    if ((*occupiers)[o.auxID] > 0 && moveVectors[o.auxID][o.endID] > 0) {
                        moveVectors[o.auxID][o.endID] += 1;
                    }
                    if ((*occupiers)[o.auxID] == 0) {
                        continue;
                    }
                    
                }
            }
        }

        //process move vector matrix
        vector<bool> visited(numTerr);
        vector<pair<int, int> > moves;
        for(int i = 0; i < numTerr; i++) {
            visited[i] = false;
        }
        for(int i = 0; i < numTerr; i++) {
            if(visited[i]) {
                continue;
            }
            int maxS = 0;
            int maxI = -1;
            int maxJ = -1;
            for(int j = 0; j < numTerr; j++) {
                if (visited[j]) {
                    continue;
                }
                if(groupID[i] == groupID[j]) {
                    visited[j] = true;
                    for(int a = 0; a < numTerr; a++) {
                        if (moveVectors[a][j] > maxS) {
                            maxS = moveVectors[a][j];
                            maxI = a;
                            maxJ = j;
                        }else if (moveVectors[a][j] == maxS) {
                            maxI = -1;
                        }
                    }
                    // maxI is start, maxJ is end
                    if (maxI != -1 && maxI != maxJ) {
                        pair<int, int> move(maxI, maxJ);
                        //cout << maxI << " " << maxJ << "\n";
                        moves.push_back(move);
                    }
                    //cout << i << j << " " << maxI << maxJ << maxS << "\n";
                }
            }
        }

        //process final move set
        vector<bool> staying (numTerr);
        vector<int> newOccupiers (numTerr);
        for(int i = 0; i < numTerr; i++) {
            staying[i] = true;
            newOccupiers[i] = 0;
        }
        /*for(int i = 0; i < numTerr; i++) {
            for(int j = 0; j < numTerr; j++) {cout << moveVectors[i][j];}
            cout << "\n";
        }*/
        for(int i = 0; i < moves.size(); i++) {
            bool duped = false;
            for(int j = 0; j < moves.size(); j++) {
                if(moves[i].first == moves[j].second && moves[i].second == moves[j].first) {
                    duped = true;
                    break;
                }
            }
            if(duped) {
                continue;
            }
            int origin = moves[i].first;
            int dest = moves[i].second;
            if(occupiers[origin] == occupiers[dest]) {
                continue;
            }
            staying[origin] = false;
            newOccupiers[dest] = (*occupiers)[origin];
        }
        //for (int i = 0; i < numTerr; i++) {cout << staying[i];} cout << "\n";

        //process occupancy
        for(int i = 0; i < numTerr; i++) {
            int thisocc = (*occupiers)[i];
            int retreatID = -1;
            for(int j = 0; j < numTerr; j++) {
                if(groupID[i] == groupID[j] && (*occupiers)[j] != 0) {
                    thisocc = (*occupiers)[j];
                    retreatID = j;
                }
            }
            if(thisocc != 0 && newOccupiers[i] != thisocc && newOccupiers[i] != 0) {
                //dislodge, make a retreat of form <territory, player>
                pair<int, int> dislodge(retreatID, thisocc);
                (*occupiers)[retreatID] = 0;
                (*retreats_needed).push_back(dislodge);
                (*occupiers)[i] = newOccupiers[i];
            } else if (!staying[i]) {
                (*occupiers)[i] = newOccupiers[i];
            } else if ((*occupiers)[i] == 0 && newOccupiers[i] != 0) {
                (*occupiers)[i] = newOccupiers[i];
            }
        }
        /*cout << moves.size() << "\n";
        for(int i = 0; i < numTerr; i++) {
            cout << (*occupiers)[i] << " ";
        }
        cout << "\n";*/
        return phase + 1;
    }
    //retreat phase
    if(phase % 5 == 1 || phase % 5 == 3) {
        int numTerr = (*owner).size();
        vector<vector<int> > moveVectors(numTerr, vector<int>(numTerr));
        vector<int> newOccupiers (numTerr);
        vector<int> retreatingTerr (numTerr);
        
        for(int i = 0; i < numTerr; i++) {
            retreatingTerr[i] = 0;
            newOccupiers[i] = 0;
        }
        for(int i = 0; i < (*retreats_needed).size(); i++) {
            retreatingTerr[i] = (*retreats_needed)[i].second;
        }

        for (order o: orders) {
            if (o.typeID == MOVE_ID) {
                if((*occupiers)[o.endID] == 0 && adjacencyMatrix[o.startID][o.endID] != 0 && adjacencyMatrix[o.startID][o.endID] != 3) {
                    moveVectors[o.startID][o.endID] = 1;
                }
            }
        }

        //determine if retreats succeed
        for (int i = 0; i < numTerr; i++) {
            int numMoves = 0;
            for (int j = 0; j < numTerr; j++) {
                if (moveVectors[j][i] != 0) {
                    numMoves++;
                    newOccupiers[i] = retreatingTerr[j];
                }
            }
            if(numMoves > 1) {
                newOccupiers[i] = 0;
            }
        }

        //combine successful retreats with original map
        for (int i = 0; i < numTerr; i++) {
            if(newOccupiers[i] != 0) {
                (*occupiers)[i] = newOccupiers[i];
            }
        }

        //adjudicate retreats
        return phase + 1;
    }

    //build phase
    if(phase % 5 == 4) {
        cout << "build phase adjudicating...\n";
        map<int, int> buildDiff;
        map<int, int> current_occ;
        map<int, int> current_unit;
        for(int i = 0; i < numTerr; i++) {
            if((*occupiers)[i] != 0) {
                int occupier = abs((*occupiers)[i]);
                current_unit[occupier]++;
            }
        }
        for(int id = 0; id < (*owner).size(); id++) {
            if(((*owner)[id]) != 0 && SCmap[id] != 0) {
                int occupier = abs((*owner)[id]);
                //cout << occupier << " " << id << "\n";
                current_occ[occupier]++;
            }
        }
        int winner = -1;
        for(auto& i: current_occ) {
            if(i.second >= 1+totalSCs/2) {
                winner = i.first;
            }
        }
        if(winner != -1) {
            cout << "Player " << winner << " wins!\nGG!\n";
        }
        for(auto& i: current_unit) {
            for(auto& j: current_occ) {

                if(i.first == j.first) {
                    buildDiff[i.first] = j.second - i.second;
                }
                //check if this set of SCs is in the list of existing units
                if(current_unit.find(j.first) == current_unit.end()) {
                    buildDiff[i.first] = j.second;
                }
            }
            //check if this set of units is in the list of existing SCs
            //cout << i.first << i.second<<endl;
            if(current_occ.find(i.first) == current_occ.end()) {
                buildDiff[i.first] = 0 - i.second;
            }
        }
        /*for (auto& i: buildDiff) {
            cout << i.first << ": " << i.second << "\n";
        }*/
        for (order o: orders) {
            if (o.typeID == BUILD_ID) {
                if (o.auxID > 0 && SCmap[groupID[o.startID]] == o.countryID) {
                    if(buildDiff[o.countryID] > 0) {
                        bool can = true;
                        int landID = -1;
                        for(int i = 0; i < numTerr; i++) {
                            if(groupID[i] == groupID[o.startID]) {
                                if(landID == -1) {
                                    landID = i;
                                }
                                if ((*occupiers)[i] != 0) {
                                    can = false;
                                }
                            }
                        }
                        if(can) {
                            buildDiff[o.countryID]--;
                            if(landID == o.startID) {
                                (*occupiers)[o.startID] = o.countryID;
                            } else {
                                (*occupiers)[o.startID] = -1 * o.countryID;
                            }
                        }
                    }
                } else {
                    if(buildDiff[o.countryID] < 0 && (*occupiers)[o.startID] != 0) {
                        (*occupiers)[o.startID] = 0;
                    }
                }
            }
        }

        //randomly delete undisbanded units
        for(auto& a: buildDiff) {
            if(a.second < 0) {
                vector<int> unitLocations;
                for(int i = 0; i < numTerr; i++) {
                    if(abs((*occupiers)[i]) == a.first) {
                        unitLocations.push_back(i);
                    }
                }
                set<int> deletions;
                for(int i = 0; i < (-1 * a.second); i++) {
                    int m = rand() % unitLocations.size();
                    while(deletions.find(m) != deletions.end()) {
                        m = rand() % unitLocations.size();
                    }
                    deletions.insert(m);
                }
                for(auto m: deletions) {
                    int loc = unitLocations[m];
                    (*occupiers)[loc] = 0;
                }
            }
        }
        //adjudicate builds
        return phase + 1;
    }
    cout << "error encountered\n";
    return -1;
}

void printTurn(int phase, vector<int> occupiers, vector<int> owner, vector<int> groupID,
    vector<pair<int, int> > retreats_needed) {
    cout << "Turn: " << phase << "\n\n";

    cout << "Owners:\n";
    for (int i = 0; i < owner.size(); i++) {
        cout << i << ": " << owner[i] << "\n";
    }
    cout << "\n";

    cout << "Occupiers:\n";
    for (int i = 0; i < occupiers.size(); i++) {
        cout << i << "(" << groupID[i] << "): " << occupiers[i] << "\n";
    }
    cout << "\n";

    cout << "Retreats:\nTerr:\tPlayer\n";
    for(int i = 0; i < retreats_needed.size(); i++) {
        cout << retreats_needed[i].first << " " << retreats_needed[i].second << "\n";
    }

    cout << "-----\n";
}

int main() {
    //populate the map
    vector<int> owners(4);
    owners[0] = 1;
    owners[1] = 1;
    owners[2] = 0;
    owners[3] = 0;

    vector<int> SCmap(4);
    SCmap[0] = 1;
    SCmap[1] = 2;
    SCmap[2] = 0;
    SCmap[3] = -1;

    vector<int> occupiers(6);
    occupiers[0] = 0;
    occupiers[1] = 0;
    occupiers[2] = 0;
    occupiers[3] = -1;
    occupiers[4] = 2;
    occupiers[5] = 0;
    
    vector<int> groupID(6);
    groupID[0] = 0;
    groupID[1] = 0;
    groupID[2] = 1;
    groupID[3] = 1;
    groupID[4] = 2;
    groupID[5] = 3;

    //create adjacency graph
    vector<vector<int> > adjMatrix(6, vector<int> (6));
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            adjMatrix[i][j] = 0;
        }
    }
    adjMatrix[0][2] = 1;
    adjMatrix[0][5] = 1;
    adjMatrix[0][3] = 3;

    adjMatrix[1][3] = 2;
    adjMatrix[1][2] = 3;
    adjMatrix[1][4] = 2;

    adjMatrix[2][0] = 1;
    adjMatrix[2][5] = 1;
    adjMatrix[2][1] = 3;

    adjMatrix[3][1] = 2;
    adjMatrix[3][0] = 3;
    adjMatrix[3][4] = 2;

    adjMatrix[4][0] = 3;
    adjMatrix[4][1] = 2;
    adjMatrix[4][2] = 3;
    adjMatrix[4][3] = 2;

    adjMatrix[5][0] = 1;
    adjMatrix[5][2] = 1;

    int phase = 2;

    //make orders
    vector<order> orders;
    orders.push_back({BUILD_ID, ARMY_ID, 1, 0, 1, 1});
    //orders.push_back({SUPPORT_ID, ARMY_ID, 5, 2, 0, 2});
    
    vector<pair<int, int> > retreats;

    printTurn(phase, occupiers, owners, groupID, retreats);
    
    phase = adjudicate(phase, &occupiers, &owners, orders, groupID, adjMatrix, SCmap, &retreats);

    printTurn(phase, occupiers, owners, groupID, retreats);
}