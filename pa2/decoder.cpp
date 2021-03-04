#include "decoder.h"
#include "queue.h"
#include "stack.h"
using namespace std;

decoder::decoder(const PNG & tm, pair<int,int> s)
   :start(s),mapImg(tm) {

    
}

PNG decoder::renderSolution(){

/* YOUR CODE HERE */

}

PNG decoder::renderMaze(){

/* YOUR CODE HERE */

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

/* YOUR CODE HERE */

}

int decoder::pathLength(){

/* YOUR CODE HERE */

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

 if (!(next.first >=0 && next.first < (int)base.width() && next.second >= 0 && next.second < (int)base.height())) {
        return false;
    }
    if (v[next.second][next.first] == 1) {
        return false;
    }
    int currD =  d[curr.second][curr.first];
    RGBAPixel *nextP;

    if (!(compare(nextP, (currD + 1) % 64))) {
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
   int maze_value = ((p->r % 4) * 16) + ((p->g % 4) * 4) + (p->b % 4);
   return maze_value == (d + 1) % 64;
/* YOUR CODE HERE */

}
