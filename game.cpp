#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <map>
#include <stack>
#include <stdexcept>
#include <iomanip>
#include "game.h"

using namespace std;
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

vector<int> groupID;
vector<vector<int> > adjacencyMatrix;

int adjudicate(int phase, vector<int> *occupiers, vector<int> *owner, vector<int>,
    vector<order> orders, vector<int> groupID, vector<vector<int> > adjacencyMatrix, vector<int> SCmap) {
    if(phase == 0 || phase == 2) {
        int numTerr = (*occupiers).size();
        vector<vector<int> > moveVectors(numTerr, vector<int>(numTerr));
        
        for(int i = 0; i < numTerr; i++) {
            for(int j = 0; j < numTerr; j++) {
                if (i == j) {
                    moveVectors[i][j] = 1;
                } else {
                    moveVectors[i][j] = 0;
                }
            }
        }
        
        for (order o: orders) {
            if ((*occupiers)[o.startID] == -1) {
                continue;
            }
            if (o.typeID == HOLD_ID) {
                //process holds
                moveVectors[o.startID][o.startID] = 1;
            }
            if (o.typeID == MOVE_ID) {
                //process moves
                if (o.typeID == ARMY_ID && adjacencyMatrix[o.startID][o.endID] != 1) {
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
                    continue;
                }
                if (o.auxID == -1) {
                    moveVectors[o.endID][o.endID] += 1;
                } else {
                    if ((*occupiers)[o.auxID] > 0 && adjacencyMatrix[o.auxID][o.endID] != 1) {
                        moveVectors[o.auxID][o.endID] += 1;
                    }
                    if ((*occupiers)[o.auxID] < 0 && adjacencyMatrix[o.auxID][o.endID] != 2) {
                        moveVectors[o.auxID][o.endID] += 1;
                    }
                    if ((*occupiers)[o.auxID] == 0) {
                        continue;
                    }
                    
                }
            }
            if (o.typeID == CONVOY_ID) {
                //process convoys
            }
        }
        //adjudicate moves
        return phase + 1;
    }
    if(phase == 1 || phase == 3) {
        int numTerr = (*owner).size();
        vector<vector<int> > moveVectors(numTerr, vector<int>(numTerr));
        for (order o: orders) {
            if (o.typeID == MOVE_ID) {

            }
        }
        //adjudicate retreats
        return phase + 1;
    }
    if(phase == 4) {
        for (order o: orders) {
            if (o.typeID == BUILD_ID) {

            }
        }
        //adjudicate builds
        return phase + 1;
    }
    cout << "error encountered\n";
    return -1;
}
int main() {
    vector<int> owners(4);
    owners[0] = 1;
    owners[1] = 2;
    owners[2] = 0;
    owners[3] = 0;

    vector<int> SCmap(4);
    SCmap[0] = 1;
    SCmap[1] = 2;
    SCmap[2] = 0;
    SCmap[3] = -1;

    vector<int> occupiers(6);
    occupiers[0] = 1;
    occupiers[1] = 0;
    occupiers[2] = 2;
    occupiers[3] = 0;
    occupiers[4] = 0;
    occupiers[5] = 0;
    
    vector<int> groupID(6);
    groupID[0] = 0;
    groupID[1] = 0;
    groupID[2] = 1;
    groupID[3] = 1;
    groupID[4] = 2;
    groupID[5] = 3;

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
    adjMatrix[5][1] = 3;
    adjMatrix[5][2] = 1;
    adjMatrix[5][3] = 3;

    int phase = 0;

    cout << "Turn:" << phase << "\n\n";

    cout << "Owners:\n";
    for (int i = 0; i < owners.size(); i++) {
        cout << i << ": " << owners[i] << "\n";
    }
    cout << "\n";

    cout << "Occupiers:\n";
    for (int i = 0; i < occupiers.size(); i++) {
        cout << i << "(" << groupID[i] << "): " << occupiers[i] << "\n";
    }
    cout << "\n";

    cout << "done\n";
}