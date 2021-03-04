#include "decoder.h"
#include "queue.h"
#include "stack.h"
using namespace std;

decoder::decoder(const PNG & tm, pair<int,int> s)
   :start(s),mapImg(tm) {

/* YOUR CODE HERE */
    
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

bool decoder::good(vector<vector<bool>> & v, vector<vector<int>> & d, pair<int,int> curr, pair<int,int> next){

/* YOUR CODE HERE */

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

/* YOUR CODE HERE */

}
