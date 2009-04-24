#include "psh.h"



using namespace std;
using namespace cimg_library;

int main() {
    cout << "=====================================================" << endl
         << "          Welcome in PSH demo program" << endl
         << "=====================================================" << endl << endl;

	CImg<unsigned char> image("../data/heron.bmp");
/*
	CImg<unsigned char> image("../data/Color dots.bmp");

    // Thresholding maison (pour des images plus sparses! ^^)
    for (unsigned int x=0;x<image.height;x++){
        for (unsigned int y=0;y<image.width;y++){
            for (unsigned int k=0;k<image.dim;k++){
                if (image(int(x),int(y),int(k))>100)
                    image(int(x),int(y),int(k))=255;
            }
        }
    }

*/
	PSH psh_example(image);
	psh_example.perform();
	//psh_example.display();
	psh_example.save("Heron");


    cout << "=====================================================" << endl
         << "     That's the end folks, I hope you enjoyed it!" << endl
         << "=====================================================" << endl << endl;


    return 0;

}

