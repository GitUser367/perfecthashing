#include "psh.h"



using namespace std;
using namespace cimg_library;

int main() {
    cout << "=====================================================" << endl
         << "          Welcome in PSH demo program" << endl
         << "=====================================================" << endl << endl;

	CImg<unsigned char> image("../data/sample.bmp");

	PSH psh_example(image);
	psh_example.perform();


    cout << "=====================================================" << endl
         << "     That's the end folks, I hope you enjoyed it!" << endl
         << "=====================================================" << endl << endl;


    return 0;

}

