#include "treasureMap.h"
#include "queue.h"
#include <cstdlib>
using namespace std;

treasureMap::treasureMap(const PNG & baseim, const PNG & mazeim, pair<int,int> s)
{

/* YOUR CODE HERE */
    base = baseim;
    maze = mazeim;
    start = s;

}

void treasureMap::setGrey(PNG & im, pair<int,int> loc){

/* YOUR CODE HERE */

    RGBAPixel *pixel = im.getPixel(loc.first, loc.second);
    int rVal = pixel->r;
    int gVal = pixel->g;
    int bVal = pixel->b;
    pixel->r = 2*(rVal/4);
    pixel->g = 2*(gVal/4);
    pixel->b = 2*(bVal/4);

}

void treasureMap::setLOB(PNG & im, pair<int,int> loc, int d){

/* YOUR CODE HERE */
    int value = d % 64;
    RGBAPixel *pixel = im.getPixel(loc.first, loc.second);
    int bVal = value & 3; // 3 = 11
    int tempB = pixel->b & 252;
    pixel->b = tempB | bVal;
    
    int gVal = (value >> 2) & 3; 
    int tempG = pixel->g & 252;
    pixel->g = tempG | gVal;

    int rVal = (value >> 4) & 3; 
    int tempR = pixel->r & 252;
    pixel->r = tempR | rVal;
    


}

PNG treasureMap::renderMap(){

/* YOUR CODE HERE */
    PNG *map = new PNG(base);

    vector<vector<bool>> visited (map->height(), vector<bool> (map->width(), 0));
    vector<vector<int>> distances (map->height(), vector<int> (map->width(), 0));
    Queue<pair<int,int>> *locations = new Queue<pair<int,int>>();

    visited[start.second][start.first] = 1;
    distances[start.second][start.first] = 0;
    setLOB(*map, start, distances[start.second][start.first]);
    locations->enqueue(start);

    while (!locations->isEmpty()) {
        pair<int,int> curr = locations->dequeue();
        vector<pair<int,int>> neighbours = neighbors(curr);
        for (unsigned int i = 0; i < neighbours.size(); i++) {
            pair<int,int> p = neighbours[i];
            if (good(visited, curr, p)) {
                visited[p.second][p.first] = 1;
                distances[p.second][p.first] = distances[curr.second][curr.first] + 1;
                setLOB(*map, p, distances[p.second][p.first]);
                locations->enqueue(p);
            }
        }
    }
    return *map;
 
}


PNG treasureMap::renderMaze(){

/* YOUR CODE HERE */
    PNG *render = new PNG(base);
    vector<vector<bool>> visited (render->height(), vector<bool> (render->width(), 0));
    Queue<pair<int,int>> locations = Queue<pair<int,int>>();
    visited[start.second][start.first] = 1;
    setGrey(*render, start);
    locations.enqueue(start);

    while (!locations.isEmpty()) {
        pair<int,int> curr = locations.dequeue();
        vector<pair<int,int>> neighbours = neighbors(curr);
        for (unsigned int i = 0; i < neighbours.size(); i++) {
            pair<int,int> p = neighbours[i];
            if (good(visited, curr, p)) {
                visited[p.second][p.first] = 1;
                setGrey(*render,  p);
                locations.enqueue(p);
            }
        }
    }

   for (int k = (start.second - 3); k <= (start.second + 3); k++) {
       for (int l = (start.first - 3); l <= (start.first + 3); l++) {
           if ((k >= 0) && (k < (int)render->height()) && (l >=0) && (l < (int)render->width())) {
               RGBAPixel *pixel = render->getPixel(l,k);
               pixel->r = 255;
               pixel->g = 0;
               pixel->b = 0;
           }
       }
   }

    return *render;

}

bool treasureMap::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){

/* YOUR CODE HERE */
    if (!(next.first >=0 && next.first < (int)base.width() && next.second >= 0 && next.second < (int)base.height())) {
        return false;
    }
    if (v[next.second][next.first] == 1) {
        return false;
    }
    RGBAPixel *currP = maze.getPixel(curr.first, curr.second);
    RGBAPixel *nextP = maze.getPixel(next.first, next.second);
    if (!(currP->r == nextP->r && currP->g == nextP->g && currP->b == nextP->b)) {
        return false;
    } 

    return true;

}

vector<pair<int,int>> treasureMap::neighbors(pair<int,int> curr) {

/* YOUR CODE HERE */
    vector<pair<int,int>> adjacent;
    adjacent.push_back(*new pair<int,int> (curr.first - 1, curr.second));
    adjacent.push_back(*new pair<int,int> (curr.first, curr.second - 1));
    adjacent.push_back(*new pair<int,int> (curr.first + 1, curr.second ));
    adjacent.push_back(*new pair<int,int> (curr.first, curr.second + 1));

    return adjacent;
}

