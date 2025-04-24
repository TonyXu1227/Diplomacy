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

typedef struct Terr{
    string name;
    int coast;
    int unit;
    
} Territory;


class GameMap {
    map<Territory *, vector<Territory *> > landBorders;
    map<Territory *, vector<Territory *> > coastBorders;

    public:
        void addLandEdge(Territory *a, Territory *b) {
            
        }


};