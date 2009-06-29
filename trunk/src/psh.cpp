#include "psh.h"




PSH::PSH(CImg<unsigned char> image) {
    this->image = image;

    //Random values generator initialization
	srand(time(NULL));

	// Resizing to a square picture, filling with white pixels...

	if (image.width != image.height) {
        this->image.resize(max(image.width, image.height),max(image.width, image.height),1,image.dim,0);
        if (image.width<image.height){
            for (unsigned int i=image.width;i<image.height;i++) {
                for (unsigned int j=0;j<image.height;j++){
                    for (unsigned int k=0;k<image.dim;k++)
                        this->image(i,j,k) = 255;
                }
            }

        } else {
            for (unsigned int i=0;i<image.width;i++) {
                for (unsigned int j=image.height;j<image.width;j++){
                    for (unsigned int k=0;k<image.dim;k++)
                        this->image(i,j,k) = 255;
                }
            }

        }
	}

	//this->image.display();


}



int PSH::perfect_hashing(CImg<unsigned char> &hash, CImg<unsigned char> &offsets, int &n, int &m, int &u, int &r){
    /**
     * Main algorithm
     * @image: original image
     * @hash: hash table
     * @offsets: offset table
     * @n: non-0 data size
     * @m: hash table size
     * @u: original image size
     * @r: offset table size
     **/

	//Hashing table initialization
	hash.fill(255);
	for (int z = 0; z < hash.dimz(); z++)
		for (int y = 0; y < hash.dimy(); y++)
			for (int x = 0; x < hash.dimx(); x++)
				for (int v = 0; v < hash.dimv(); v++)
				{	
				//	hash(x,y,z,v) = (v & 1) ? 0 : 255; // green
				}

	//Offset table declaration
	assert((u <= m*r) && (pgcd(m,r) == 1));								// Otherwise no injectivity of S -> (h0, h1) !
	offsets.assign(r, r, 1, 3, 0);
	for (int z = 0; z < offsets.dimz(); z++)
		for (int y = 0; y < offsets.dimy(); y++)
			for (int x = 0; x < offsets.dimx(); x++)
				offsets(x,y,z,2) = 255; // set the blue, it will be cleared when filled 
				
	cout << "Offset table: " << r << "x" << r << endl;

	//Calcul des cardinaux des ensembles h1^(-1)(q)
	CImg<int> cards(r, r, 1, 1, 0);
	for (int i=0; i<u; ++i){
		for (int j=0; j<u; ++j){
			if (non_white_pixel(image,i,j))
				cards(i%r, j%r)++;
		}
	}

	////Verification (sum over all coefficients of cards should be equal to n)
	//int sum = 0;
	//for (int i=0; i<r; ++i)
	//{
	//	for (int j=0; j<r; ++j)
	//	{
	//		sum += cards(i,j);
	//	}
	//}
	//cout << endl << "SUM: " << sum << " Correct value: " << n << endl;


	//Sort cardinals
	CImg<int> perms = cards;
	perms.fill(0);
	CImg<int> sort = cards.get_sort(perms, false);


	//Loop over sorted cardinals
	if (VERBOSE)
	{
		cout << "---------------------------------------------" << endl;
		cout << "               Main loop" << endl;
		cout << "---------------------------------------------" << endl;
	}
	std::vector<Point> points;	//Positions in hash table
	std::vector<Point> valid_translations;
	int nb_points = 0;
	vector<unsigned char> col;
	col.resize(image.dim);
	for (int j=0; j<r; ++j)
	{
		for (int i=0; i<r; ++i)
		{
			int pos = perms(i,j);

			//Position in the offset table
			int x = pos%r;
			int y = pos/r;

			if (VERBOSE)
				cout << "Position in offset table: " << x << " " << y << endl;

			//Search all points of h^(-1)(x,y)
			points.clear();
			for (int k=x; k<u; k+=r){
				for (int l=y; l<u; l+=r){
				    if (non_white_pixel(image,k,l)) {
						points.push_back(Point(k, l));
				    }
				}
			}
			if (VERBOSE)
				cout << "\t" << points.size() << " points found" << endl;
			nb_points += points.size();

			//Search for possible translations (the ones with no collisions)
			valid_translations.clear();
			int max_value = min(m, 255);
			for (int k=0; k<max_value; ++k){
				for (int l=0; l<max_value; ++l){
					// Is (k,l) a valid translation?
					bool valid = true;
					for (unsigned int s=0; s<points.size(); ++s){
						Point p = points[s];
                        if (non_white_pixel(hash,(p.x+k)%m, (p.y+l)%m)){
                            valid = false;
                            break;
                        }

					}

					if (valid)
						valid_translations.push_back(Point(k,l));
				}
			}
			if (VERBOSE)
				cout << "\t" << valid_translations.size() << " valid translations found" << endl;

			//No valid translation found !!
			if (valid_translations.size() == 0)
			{
				cout << nb_points << "/" << n << " points compressed..." << endl;
				return 0;
			}

			//Random selection of a valid translation
			int rand_index = rand()%valid_translations.size();
			Point offset = valid_translations[rand_index];
			if (VERBOSE)
				cout << "Translation taken: " << offset.x << " " << offset.y << endl;

			//Offset assignment
			int off_x = offset.x;
			int off_y = offset.y;
			if (off_x > 255 || off_y > 255)
			{
				cout << "unsigned char overflow for pixel" << endl;
			}
			offsets(x,y,0,0) = off_x;
			offsets(x,y,0,1) = off_y;
			offsets(x,y,0,2) = 0; // clear the blue to mark as filled

			//Hash table assignment
			for (unsigned int s=0; s<points.size(); ++s)
			{
				Point p = points[s];
				for (unsigned int k=0;k<image.dim;k++){
                    hash((p.x+off_x)%m, (p.y+off_y)%m,int(k)) = image(p.x,p.y,k);
				}
			}

			if (VERBOSE)
			{
				cout << endl;
				getchar();
			}
		}
	}

	cout << "Perfect hashing succeeded !!" << endl;

	return 1;
}





int PSH::perform()
{
    int u = image.width;

	//Finds number of non-white pixels
	int n = 0;
	for (int i=0; i<u; ++i){
		for (int j=0; j<u; ++j){
            if (non_white_pixel(image,i,j))
                n++;
		}
	}

	cout << "Image " << u << "x" << u << "x" << image.dim << "  " << n << "/" << u*u << " non white pixels." << endl;


	//Hashing table declaration
	int m = (int)ceil(sqrt((double) n));
	if (m > 255) // the 8 bit offsets will limit the range in the hash table
		m = (int)ceil(sqrt((double) n * 1.01)); // make the table slightly larger, section 4.1 of the paper
	cout << "Hashing table: " << m << "x" << m << endl << endl;
	hash.assign(m, m, 1, image.dim, 255);

	//Initialization of r
	int r = (int)ceil(sqrt(1.*n/4));
	while (pgcd(r, m) != 1)
		r++;

#ifndef COMPACT
	//Geometric increase of r
	while (perfect_hashing(hash, offsets, n, m, u, r) == 0)
	{
		cout << endl;
		r = (int)ceil(r*1.2);
		while (pgcd(r, m) != 1)
			r++;
	}
	cout << endl << "Optimal offset table size for compact construction: r=" << r << endl;
#else
	//Dichotomic search (we want to find the lowest acceptable r so that perfect hashing succeeds)
	int r_min = 2;
	while (pgcd(r_min, m) != 1)
		r_min++;

	int best_r = INT_MAX;
	CImg<unsigned char> best_hash;
	CImg<unsigned char> best_offset;

	bool finished = false;
	while (!finished)
	{
		//Test of success with r
		bool success = false;
		int i;
		for (i=0; i<MAX_ESSAIS_COMPACT; ++i)
		{
			if (perfect_hashing(hash, offsets, n, m, u, r) == 1)
			{
				success = true;
				cout << endl;
				break;
			}
			else
				continue;
		}
		if (i == 5)
			cout << endl;

		//Ca n'a pas marche
		if (!success)
		{
			r_min = r;

			//Si on n'a pas encore trouvé de bon r, on augmente r
			if (best_r == INT_MAX)
			{
				r = ceil(r*1.2);
				while (pgcd(r, m) != 1)
					r++;
			}
			//Sinon, on fait la moyenne entre le r courant et le best_r qui marche
			else
			{
				int old_r = r;
				r = (best_r + r)/2;
				int mid_r = r;
				while ((pgcd(r, m) != 1) && (r != old_r))
					r--;
				if (r == old_r)
				{
					r = mid_r;
					while ((pgcd(r, m) != 1) && (r != best_r))
						r++;
					if (r == best_r || r == old_r)
					{
						cout << "Optimal offset table size for compact construction: r=" << best_r << endl;
						finished = true;
					}
				}

			}

		}

		//Si ça a marche
		else
		{
			int old_r = r;
			r = (r_min + r)/2;
			int mid_r = r;
			while ((pgcd(r, m) != 1) && (r != r_min))
				r--;
			if (r == r_min)
			{
				r = mid_r;
				while ((pgcd(r, m) != 1) && (r != old_r))
					r++;
				if (r == old_r || r == r_min)
				{
					cout << "Optimal offset table size for compact construction: r=" << old_r << endl;
					finished = true;
				}
			}

			best_r = old_r;
			best_offset = offsets;
			best_hash = hash;
		}


	}

#endif


	//getchar();
	return 0;
}


void PSH::display(){
    CImgList<unsigned char> list(image,hash,offsets);
    CImgDisplay disp(list,"Image - Hash Table - Offset Table");
    while (!disp.is_closed)
    #if defined(WIN32) || defined(WIN64)
        Sleep(1);
    #else
        usleep(1000);
    #endif
    }

void PSH::save(const char* hash_fname, const char* offsets_fname)
{
	hash.save(hash_fname);	
	offsets.save(offsets_fname);
}

void PSH::save(string prefix){
    string filename = prefix+" - Hash Table.bmp";
    hash.save(filename.c_str());
    filename = prefix+ " - Offset Table.bmp";
    offsets.save(filename.c_str());
}



inline bool PSH::non_white_pixel(CImg<unsigned char> &img, int i,int j){
    for (unsigned int k=0;k<img.dim;k++){
        if (img(i,j,k)!=255)
            return true;
    }
    return false;

}
