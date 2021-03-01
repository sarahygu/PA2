#include "treasureMap.h"
#include "queue.h"
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
    PNG *map = new PNG(base);

    vector<vector<bool>> visited (map->height(), vector<bool> (map->width(), 0));
    vector<vector<int>> distances (map->height(), vector<int> (map->width(), 0));
    Queue<pair<int,int>> *locations = new Queue<pair<int,int>>();

    visited[start.first][start.second] = 1;
    distances[start.first][start.second] = 0;
    setLOB(*map, * new pair<int, int>(start.first, start.second), distances[start.first][start.second]);
    locations->enqueue(start);

    while (!locations->isEmpty()) {
        pair<int,int> curr = locations->dequeue();
        vector<pair<int,int>> neighbours = neighbors(curr);
        for (unsigned int i = 0; i < neighbours.size(); i++) {
            pair<int,int> p = neighbours[i];
            if (good(visited, curr, p)) {
                visited[p.first][p.second] = 1;
                distances[p.first][p.second] = distances[curr.first][curr.second] + 1;
                setLOB(*map, p, distances[p.first][p.second]);
                locations->enqueue(p);
            }
        }
    }
    return *map;
 
}


PNG treasureMap::renderMaze(){

/* YOUR CODE HERE */

}

bool treasureMap::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){

/* YOUR CODE HERE */

}

vector<pair<int,int>> treasureMap::neighbors(pair<int,int> curr) {

/* YOUR CODE HERE */

}

