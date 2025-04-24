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

typedef struct Terr{
    string name;
    int coast;
    Country owner;
} Territory;

typedef struct unit{
    string name;
    int coast;
    Country owner;
} Unit;