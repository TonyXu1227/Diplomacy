#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <map>
#include <stack>
#include <stdexcept>
#include <iomanip>
#include "diplo.h"
#include "orders.h"
#include "map.h"

using namespace std;
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))f

vector<Order> readOrders() {
    vector<Order> set;
    return set;
}

int adjudicate(vector<Order> orders, GameMap map) {
    vector<Territory *> Territories = map.getTerritories();
    int numTerr = map.getSize();
    vector<vector<int> > moveVectors(numTerr, vector<int>(numTerr));
    //make a queue of convoy orders
    vector<Order> convoys;
    //make a queue of move orders
    vector<Order> moves;
    //make a queue of support orders
    vector<Order> supports;
    //create a list of moves and strengths for moves
    for (Order o : orders) {
        if (o.act == CONVOY) {
            convoys.push_back(o);
        }
        if (o.act == MOVE || o.act == RETREAT) {
            moves.push_back(o);
        }
        if (o.act == SUPPORT) {
            supports.push_back(o);
        } 
    }

    for (Order o : convoys) {
        //process convoys
    }

    for (Order o : moves) {
        moveVectors[o.start->groupID][o.start->groupID] = 0;
        if(map.landEdgeExists(o.start, o.end) && o.type == ARMY) {
            moveVectors[o.start->groupID][o.end->groupID] = 1;
        }
        if(map.coastEdgeExists(o.start, o.end) && o.type == FLEET) {
            moveVectors[o.start->groupID][o.end->groupID] = 1;
        }
        //Convoy shenanigans
    }

    for (Order o : supports) {
        int endTerrID = o.end->groupID;
        if(o.aux == NULL) {
            if(moveVectors[endTerrID][endTerrID] != 0) {
                moveVectors[endTerrID][endTerrID]++;
            }
        } else {
            int auxTerrID = o.aux->groupID;
            if(moveVectors[auxTerrID][endTerrID] != 0) {
                moveVectors[endTerrID][endTerrID]++;
            }
        }
    }
    vector<int> newCoast(numTerr); //-1 if army, 0 if unoccupied.
    vector<Country> newOcc(numTerr);
    for(int it = 0; it < moveVectors.size(); it++) {
        vector<int> v = moveVectors[it];
        int maxStrength = 0;
        int maxI = -1;
        for(int i = 0; i < v.size(); i++) {
            if (v[i] > maxStrength) {
                maxI = i;
                maxStrength = v[i];
            }
            if (v[i] == maxStrength) {
                maxI = -1;
            }
        }
        if(maxI != -1) {
            for (Territory *t : Territories) {
                if(t->groupID == maxI && t->occupier != NON) {
                    newOcc[it] = t->occupier;
                    newCoast[it] = t->coast;
                }
            }
        }
    }
    //deteremine which ones succede
    //cycle term
    if (true) {
        return 1;
    }
    return 0;
}

int main() {
    cout << "adjudicating...\n";
    GameMap map;
    vector<Order> orderset = readOrders();
    int v = adjudicate(orderset, map);
    if (v) {
        cout << "adjudicated\n";
    }
    cout << "finished adjudication!\n";
    return 0;
}