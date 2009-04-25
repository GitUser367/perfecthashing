#include "psh.h"



using namespace std;
using namespace cimg_library;

int main() {
    cout << "=====================================================" << endl
         << "          Welcome in PSH demo program" << endl
         << "=====================================================" << endl << endl;

    string core_name = "Color dots";
    string filename = "../data/"+core_name + ".bmp";
	CImg<unsigned char> image(filename.c_str());

    // Thresholding maison (pour des images plus sparses! ^^)
    for (unsigned int x=0;x<image.height;x++){
        for (unsigned int y=0;y<image.width;y++){
            for (unsigned int k=0;k<image.dim;k++){
                if (image(int(x),int(y),int(k))>100)
                    image(int(x),int(y),int(k))=255;
            }
        }
    }


	PSH psh_example(image);
	psh_example.perform();
	psh_example.display();
	psh_example.save(core_name.c_str());


    cout << endl << "=====================================================" << endl
                 << "     That's the end folks, I hope you enjoyed it!" << endl
                 << "=====================================================" << endl << endl;


    return 0;

}

