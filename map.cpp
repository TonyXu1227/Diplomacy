#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <map>
#include <unordered_map>
#include <stack>
#include <stdexcept>
#include <iomanip>

#include "diplo.h"
using namespace std;
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

class GameMap {
    map<Territory *, vector<Territory *> > landBorders;
    map<Territory *, vector<Territory *> > coastBorders;

    public:
        //adds a land border to the map (where armies can move)
        void addLandEdge(Territory *a, Territory *b) {
            landBorders[a].push_back(b);
            landBorders[b].push_back(a);
        }

        //adds a water/coastal border to the map (where fleets can move)
        void addWaterEdge(Territory *a, Territory *b) {
            landBorders[a].push_back(b);
            landBorders[b].push_back(a);
        }

        bool landEdgeExists(Territory *a, Territory *b) {
            if (landBorders.find(a) == landBorders.end()) {
                return false;
            }
            for(auto neighbor : landBorders[a]) {
                if (neighbor == b) {
                    return true;
                }
            }
            return false;
        }

        bool coastEdgeExists(Territory *a, Territory *b) {
            if (coastBorders.find(a) == coastBorders.end()) {
                return false;
            }
            for(auto neighbor : coastBorders[a]) {
                if (neighbor == b) {
                    return true;
                }
            }
            return false;
        }

        

        bool isValidMove(Order *o) {
            if (o->act == HOLD) {
                return true;
            }
            
        }
};