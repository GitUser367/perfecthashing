#include "psh.h"



using namespace std;
using namespace cimg_library;

int main(int argc, char** argv) {
    cout << "=====================================================" << endl
         << "          Welcome in PSH demo program" << endl
         << "=====================================================" << endl << endl
         << "usage: " << endl
		 << argv[0] << " input output_prefix" << endl
		 << argv[0] << " input output_hashmap output_offset output_coverage" << endl << endl;

    string core_name = "Color dots";
    string filename = "../data/"+core_name + ".bmp";
	if (argc >= 2)
		filename = argv[1];
	CImg<unsigned char> image(filename.c_str());

    // Thresholding maison (pour des images plus sparses! ^^)
	/*
    for (unsigned int x=0;x<image.height;x++){
        for (unsigned int y=0;y<image.width;y++){
            for (unsigned int k=0;k<image.dim;k++){
                if (image(int(x),int(y),int(k))>100)
                    image(int(x),int(y),int(k))=255;
            }
        }
    }
	*/
	CImg<unsigned char> coverage(image.dimx(), image.dimy(), image.dimz(), image.dimv(), 0);
	
    for (int x=0;x<image.dimx();x++){
        for (int y=0;y<image.dimy();y++){
        	for (int z=0;z<image.dimz();z++){
				bool blank = true;
            	for (int v=0;v<image.dimv();v++){
                	if (image(x,y,z,v)<255){
						blank = false;
						break;
					}
				}
            	for (int v=0;v<image.dimv();v++){
                	if (blank)
						coverage(x,y,z,v) = 0;
					else
						coverage(x,y,z,v) = 255;
				}
            }
        }
    }
	if (argc == 3)
	{
		core_name = argv[2];
		string fname = core_name + "_coverage.bmp";
		coverage.save(fname.c_str());
	}
	else if (argc == 5)
		coverage.save(argv[4]);

	PSH psh_example(image);
	psh_example.perform();
	psh_example.display();
	if (argc < 3)
		psh_example.save(core_name.c_str());
	else if (argc == 3)
	{
		core_name = argv[2];
		psh_example.save(core_name);
	}
	else if (argc == 5)
	{
		psh_example.save(argv[2], argv[3]);
	}


    cout << endl << "=====================================================" << endl
                 << "     That's the end folks, I hope you enjoyed it!" << endl
                 << "=====================================================" << endl << endl;


    return 0;

}

