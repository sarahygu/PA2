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
    pixel->r = 2 * pixel->r/ 4;
    pixel->g = 2 * pixel->g/ 4;
    pixel->b = 2 * pixel->b/ 4;
    

}

void treasureMap::setLOB(PNG & im, pair<int,int> loc, int d){

/* YOUR CODE HERE */
    int value = d % 64;
    RGBAPixel *pixel = im.getPixel(loc.first, loc.second);
    pixel->r = value & 3;
    pixel->g = value & 12;
    pixel->b = value & 48;

}

PNG treasureMap::renderMap(){

/* YOUR CODE HERE */
    PNG map = renderMaze();

    vector<vector<bool>> visited (map.height(), vector<bool> (map.width(), 0));
    vector<vector<int>> distances (map.height(), vector<int> (map.width(), 0));
    Queue<pair<int,int>> *locations = new Queue<pair<int,int>>();

    visited[start.first][start.second] = 1;
    distances[start.first][start.second] = 0;
    setLOB(map, * new pair<int, int>(start.first, start.second), distances[start.first][start.second]);
    locations->enqueue(start);

    while (!locations->isEmpty()) {
        pair<int,int> curr = locations->dequeue();
        vector<pair<int,int>> neighbours = neighbors(curr);
        for (unsigned int i = 0; i < neighbours.size(); i++) {
            pair<int,int> p = neighbours[i];
            if (good(visited, curr, p)) {
                visited[p.second][p.first] = 1;
                distances[p.second][p.first] = distances[curr.second][curr.first] + 1;
                setLOB(map, p, distances[p.second][p.first]);
                locations->enqueue(p);
            }
        }
    }
    return map;
 
}


PNG treasureMap::renderMaze(){

/* YOUR CODE HERE */
    PNG render = PNG(base);
    for (unsigned int i = start.second; i < base.height(); i ++) {
        for(unsigned int j = start.first; j < base.width(); j++) {
            if (render.getPixel(j,i) == maze.getPixel(j,i)) {
                setGrey(render, * new pair<int,int> (i,j));
            }
        }
    }

   for (unsigned int k = start.first - 7; k < render.width(); k++) {
       for (unsigned int l = start.second - 7; l < render.height(); l++) {
           if (k >= 0 && l >=0 && (abs((int)k - start.first) == 7 || abs((int)l-start.second) == 7)) {
               RGBAPixel *pixel = render.getPixel(k,l);
               pixel->r = 255;
               pixel->g = 0;
               pixel->b = 0;
           }
       }
   }

    return render;

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

