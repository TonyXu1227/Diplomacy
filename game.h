#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <map>
#include <unordered_map>
#include <stack>
#include <stdexcept>
#include <iomanip>

#define HOLD_ID (0)
#define MOVE_ID (1)
#define SUPPORT_ID (2)
#define CONVOY_ID (3)
#define BUILD_ID (4)

#define ARMY_ID (1)
#define FLEET_ID (-1)

typedef struct Order {
    int typeID;
    int unitID;
    int startID;
    int endID;
    int auxID;
} order;