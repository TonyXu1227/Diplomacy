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
        void addLandEdge(Territory *a, Territory *b);
        //adds a water/coastal border to the map (where fleets can move)
        void addWaterEdge(Territory *a, Territory *b);

        bool landEdgeExists(Territory *a, Territory *b);

        bool coastEdgeExists(Territory *a, Territory *b);

        
};