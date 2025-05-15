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
};

typedef struct Terr{
    string name;
    int coast;
    bool isSC;
    struct Terr *group;
    Country owner;
} Territory;

typedef struct unit{
    string name;
    Territory *location;
    Country owner;
} Unit;

typedef struct order{
    Unit source;
    Unit aux;
    Action act;
    Territory *start;
    Territory *end;
} Order;