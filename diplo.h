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

enum Country {
    NON,
    ENG,
    FRA,
    GER,
    ITA,
    AUS,
    TUR,
    RUS
};

enum Action {
    HOLD,
    MOVE,
    SUPPORT,
    CONVOY,
    RETREAT
};

enum Phase {
    SRING_MOVE,
    SRING_RETREAT,
    FALL_MOVE,
    FALL_RETREATE,
    WINTER
};

typedef struct Terr{
    string name;
    int coast;
    bool isSC;
    int groupID;
    Country owner;
    Country occupier;
} Territory;

enum Unit {
    ARMY,
    FLEET
};

typedef struct order{
    Unit type;
    Country player;
    Action act;
    Territory *start;
    Territory *aux;
    Territory *end;
} Order;