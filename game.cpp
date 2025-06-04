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

int adjudicate(int phase, vector<int> *occupiers, vector<int> *owner, vector<int>, vector<order> orders, vector<int> groupID){
    if(phase == 0 || phase == 2) {
        int numTerr = (*owner).size();
        vector<vector<int> > moveVectors(numTerr, vector<int>(numTerr));
        fill(moveVectors.begin(), moveVectors.end(), 0);
        
        for(int i = 0; i < numTerr; i++) {
            moveVectors[i][i] = 1;
        }

        for (order o: orders) {
            if (o.typeID == HOLD_ID) {

            }
            if (o.typeID == MOVE_ID) {
                moveVectors[groupID[o.startID]][groupID[o.endID]] = 1;
                moveVectors[groupID[o.startID]][groupID[o.startID]] = 0;
            }
            if (o.typeID == SUPPORT_ID) {

            }
            if (o.typeID == CONVOY_ID) {
                
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