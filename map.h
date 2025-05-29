#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <map>
#include <unordered_map>
#include <stack>
#include <stdexcept>
#include <iomanip>

using namespace std;
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

class GameMap {
    Phase phase;
    int size;
    vector<Territory *> Territories;
    map<Territory *, vector<Territory *> > landBorders;
    map<Territory *, vector<Territory *> > coastBorders;

    public:
        GameMap() {
            cout << "Constructor called!";
        }

        ~GameMap() {
            cout << "Destructor called!";
        }

        vector<Territory *> getTerritories() {
            return Territories;
        }

        int getSize() {
            return size;
        }

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
            if (o->player != o->start->occupier) {
                return true;
            }
            if (o->act == HOLD) {
                return true;
            }
            if (o->act == CONVOY) {
                if (o->type == ARMY) {
                    return false;
                }
                if (o->type == FLEET){
                    return true;
                }
            }
            if (o->act == MOVE) {
                if (o->type == ARMY) {
                    if(landEdgeExists(o->start, o->end)) {
                        return true;
                    }
                }
                if (o->type == FLEET) {
                    if(coastEdgeExists(o->start, o->end)) {
                        return true;
                    }
                }
            }
            if (o->act == SUPPORT) {
                if(o->type == ARMY) {
                    if (!landEdgeExists(o->start, o->end)) {
                        return false;
                    }
                    if (o->aux != NULL) {
                        if(!landEdgeExists(o->aux, o->end) && !coastEdgeExists(o->aux, o->end)) {
                            return false;
                        }
                    }
                    return true;
                }
                if(o->type == FLEET) {
                    if(!coastEdgeExists(o->start, o->end)) {
                        return false;
                    }
                    if(!landEdgeExists(o->aux, o->end) && !coastEdgeExists(o->aux, o->end)) {
                        return false;
                    }
                    return true;
                }
            }
            if (o->act == RETREAT) {
                if (o->type == ARMY) {
                    if(landEdgeExists(o->start, o->end)) {
                        return true;
                    }
                }
                if (o->type == FLEET) {
                    if(coastEdgeExists(o->start, o->end)) {
                        return true;
                    }
                }
            }
            return false;
        }
};