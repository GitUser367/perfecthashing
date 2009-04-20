#include "CImg.h"

#include <math.h>
#include <assert.h>
#include <time.h>

#include <vector>
#include <iostream>


#include "point.h"

//Enable / Disable debug statements
#define VERBOSE 0

//Maximum of attempts of the algorithm for compact mode (5 in the article)
#define MAX_ESSAIS_COMPACT 5

//Enable binary research (to find minimal size)
//#define COMPACT

#include "math_tools.h"

//Enable / Disable output saving
#define SAVE_OUTPUT 1

using namespace std;
using namespace cimg_library;

class PSH {
public:
    CImg<unsigned char> image;

    PSH(CImg<unsigned char> image);

    int perform();





private:

    int perfect_hashing(CImg<unsigned char> &hash, CImg<unsigned char> &offsets, int &n, int &m, int &u, int &r);











};
