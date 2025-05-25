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
    //make a queue of convoy orders
    vector<Order> convoys;
    //make a queue of move orders
    vector<Order> move;
    //make a queue of support orders
    vector<Order> supports;
    //create a list of moves and strengths for moves
    for (Order o : orders) {
        if (o.act == CONVOY) {
            convoys.push_back(o);
        }
        if (o.act == MOVE || o.act == RETREAT) {
            move.push_back(o);
        }
        if (o.act == SUPPORT) {
            move.push_back(o);
        } 
    }

    for (Order o : convoys) {
        //process convoys
    }

    for (Order o : convoys) {
        //process moves
    }

    for (Order o : convoys) {
        //process supports
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