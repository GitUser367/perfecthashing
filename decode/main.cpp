#include "psh.h"



using namespace std;
using namespace cimg_library;

int main(int argc, char** argv) {
    cout << "=====================================================" << endl
         << "          Welcome in PSH decode demo program" << endl
         << "=====================================================" << endl << endl
         << "usage: " << endl
		 << argv[0] << " hash offset coverage-map output" << endl << endl;

	if (argc != 5){
		printf("Invalid arguments: see correct usage above\n");
		return 0;
	}
	CImg<unsigned char> hash(argv[1]);
	CImg<unsigned char> offset(argv[2]);
	CImg<unsigned char> coverage(argv[3]);
	CImg<unsigned char> output(coverage.dimx(), coverage.dimy(), coverage.dimz(), hash.dimv(), 0);


	// iterate through the pixels in the coverage map and recover the value of that pixel
	for (int z=0;z<coverage.dimz();z++){	
    	for (int y=0;y<coverage.dimy();y++){
    		for (int x=0;x<coverage.dimx();x++){
				bool full = true;
            	for (int v=0;v<coverage.dimv();v++){
                	if (coverage(x,y,z,v) < 255){
						full = false;
						break;
					}
				}
				if (full){ // this is an active pixel
					// compute the actual value from the offset and hash
					int rx = x % offset.dimx();
					int ry = y % offset.dimy();
					int rz = z % offset.dimz();
					int offx = offset(rx, ry, rz, 0);
					int offy = offset(rx, ry, rz, 1);
					int offz = 0;
					if (coverage.dimz() != 1)
					{
						offz = offset(rx, ry, rz, 2);
					}
					int px = (x + offx) % hash.dimx();
					int py = (y + offy) % hash.dimy();
					int pz = (z + offz) % hash.dimz();
					for (int v=0;v<hash.dimv();v++){
						output(x,y,z,v) = hash(px,py,pz,v);
					}
				}
				else{
					for (int v=0;v<hash.dimv();v++){
						output(x,y,z,v) = 255;
					}
				}
            }
        }
    }

	output.save(argv[4]);
/*
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
	else if (argc == 4)
		psh_example.save(argv[2], argv[3]);
*/


    cout << endl << "=====================================================" << endl
                 << "     That's the end folks, I hope you enjoyed it!" << endl
                 << "=====================================================" << endl << endl;


    return 0;

}

