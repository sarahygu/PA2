#include "decoder.h"
#include "queue.h"
#include "stack.h"
using namespace std;

decoder::decoder(const PNG & tm, pair<int,int> s)
   :start(s),mapImg(tm) {
    mapImg = tm;
    start = s;
    
    vector<vector<bool>> visited (mapImg.height(), vector<bool> (mapImg.width(), 0));
    vector<vector<int>> distances (mapImg.height(), vector<int> (mapImg.width(), 0));
    Queue<pair<int,int>> *locations = new Queue<pair<int,int>>();
    

    vector<vector<pair<int,int>>> last_location (mapImg.height(), vector<pair<int,int>> (mapImg.width(), make_pair(-1, -1)));
    pair<int,int> max_dist_location (start.first,start.second); 

    visited[start.second][start.first] = 1;
    distances[start.second][start.first] = 0;
    last_location[start.second][start.first] = make_pair(0, 0);



    locations->enqueue(start);

    while (!locations->isEmpty()) {
        pair<int,int> curr = locations->dequeue();
        vector<pair<int,int>> neighbours = neighbors(curr);
        for (unsigned int i = 0; i < neighbours.size(); i++) {
            pair<int,int> p = neighbours[i];
            if (good(visited, distances, curr, p)) {
                visited[p.second][p.first] = 1;
                distances[p.second][p.first] = distances[curr.second][curr.first] + 1;
                last_location[p.second][p.first] = curr;
                
                if (distances[p.second][p.first] > distances[max_dist_location.second][max_dist_location.first]) {
                    max_dist_location.first = p.first;
                    max_dist_location.second = p.second;

                }

                locations->enqueue(p);
            }
        }
    }
    Stack<pair<int,int>> *path_stack = new Stack<pair<int,int>>();
    pair<int,int> prev_location;
    pair<int,int> curr_location(max_dist_location.first, max_dist_location.second);

    while (!((prev_location.first == start.first) && (prev_location.second == start.second))) {
        prev_location = last_location[curr_location.second][curr_location.first];
        path_stack->push(curr_location);
        curr_location = prev_location;
    }
    pathPts.push_back(start);
    while(!path_stack->isEmpty()) {
         pathPts.push_back(path_stack->pop());
    }

}

PNG decoder::renderSolution(){
  PNG *solution = new PNG(mapImg);

  for(unsigned int i = 0; i < pathPts.size(); i++) {
    pair<int,int> path_point = pathPts[i];
    RGBAPixel *pixel = solution->getPixel(path_point.first, path_point.second);
    pixel->r = 255;
    pixel->g = 0;
    pixel->b = 0;

}
return *solution;
}

PNG decoder::renderMaze(){

/* YOUR CODE HERE */
    PNG *render = new PNG(mapImg);
    vector<vector<bool>> visited (render->height(), vector<bool> (render->width(), 0));
    vector<vector<int>> distances (mapImg.height(), vector<int> (mapImg.width(), 0));

    Queue<pair<int,int>> locations = Queue<pair<int,int>>();
    visited[start.second][start.first] = 1;
    distances[start.second][start.first] = 0;

    setGrey(*render, start);
    locations.enqueue(start);

    while (!locations.isEmpty()) {
        pair<int,int> curr = locations.dequeue();
        vector<pair<int,int>> neighbours = neighbors(curr);
        for (unsigned int i = 0; i < neighbours.size(); i++) {
            pair<int,int> p = neighbours[i];
            if (good(visited, distances, curr, p)) {
                visited[p.second][p.first] = 1;
                distances[p.second][p.first] = distances[curr.second][curr.first] + 1;

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

void decoder::setGrey(PNG & im, pair<int,int> loc){


    RGBAPixel *pixel = im.getPixel(loc.first, loc.second);
    int rVal = pixel->r;
    int gVal = pixel->g;
    int bVal = pixel->b;
    pixel->r = 2*(rVal/4);
    pixel->g = 2*(gVal/4);
    pixel->b = 2*(bVal/4);

}

pair<int,int> decoder::findSpot(){
return pathPts[pathPts.size() - 1];
}

int decoder::pathLength(){
    return pathPts.size();
}

    // tests a neighbor (adjacent vertex) to see if it is 
    // 1. within the image, 2. unvisited, and 3. coloured so that
    // lower order bits fit the pattern prescribed by the encoder.
    // An entry in table v is true if a cell has previously been 
    // visited. table d contains the shortest distance from each location
    // back to the start. the (r,g,b) colour of position next must have lower order
    // bits (XX,XX,XX) that, when interpreted as an integer between 0 and 63,
    // inclusive, is d[curr.second][curr.first] + 1 (mod 64).
bool decoder::good(vector<vector<bool>> & v, vector<vector<int>> & d, pair<int,int> curr, pair<int,int> next){

 if (!(next.first >=0 && next.first < (int)mapImg.width() && next.second >= 0 && next.second < (int)mapImg.height())) {
        return false;
    }
    if (v[next.second][next.first] == 1) {
        return false;
    }
    int currD =  d[curr.second][curr.first];
    RGBAPixel *nextP = mapImg.getPixel(next.first, next.second);
    if (!(compare(*nextP, currD))) {
        return false;
    } 

    return true;
}

vector<pair<int,int>> decoder::neighbors(pair<int,int> curr) {

    vector<pair<int,int>> adjacent;
    adjacent.push_back(*new pair<int,int> (curr.first - 1, curr.second));
    adjacent.push_back(*new pair<int,int> (curr.first, curr.second - 1));
    adjacent.push_back(*new pair<int,int> (curr.first + 1, curr.second ));
    adjacent.push_back(*new pair<int,int> (curr.first, curr.second + 1));

    return adjacent;

}


bool decoder::compare(RGBAPixel p, int d){
   int maze_value = ((p.r % 4) * 16) + ((p.g % 4) * 4) + (p.b % 4);
   return maze_value == (d + 1) % 64;
/* YOUR CODE HERE */

}
