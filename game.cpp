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
    vector<order> orders, vector<int> groupID, vector<vector<int> > adjacencyMatrix) {
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
                if (adjacencyMatrix[o.startID][o.endID] == -1) {
                    continue;
                }
                if(o.auxID == -1 && moveVectors[groupID[o.endID]][groupID[o.endID]] != 0) {
                    moveVectors[o.endID][o.endID] += 1;
                } else {
                    if ((*occupiers)[o.auxID] < 0 && adjacencyMatrix[o.auxID][o.endID] != 1) {
                        moveVectors[o.auxID][o.endID] += 1;
                    }
                    if ((*occupiers)[o.auxID] > 0 && adjacencyMatrix[o.auxID][o.endID] != 2) {
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
        return 0;
    }
    cout << "error encountered\n";
    return -1;
}
int main() {
    cout << "ddd\n";
}