/* MNIST Digit Extractor
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <strings.h>

using namespace cv;
using namespace std;

int reverseDigit(int i)
{
	unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

void readMNIST(int opt)
{
	int idx = 0;
	Mat img;
	ifstream file;
	if(opt == 0)
	{
		cout<<"\n Training...";
		
		file.open("train-images.idx3-ubyte");
	}
	else
	{
		cout<<"\n Test...";
		
		file.open("t10k-images.idx3-ubyte");
	}
	
	if(!file.is_open())
	{
		cout << "\n File Not Found!";
		exit(2);
	}
	else
	{
		int magic_number=0;
		int number_of_images=0;
		int n_rows=0;
		int n_cols=0;
		
		file.read((char*)&magic_number,sizeof(magic_number)); 
		magic_number= reverseDigit(magic_number);
		file.read((char*)&number_of_images,sizeof(number_of_images));
		number_of_images= reverseDigit(number_of_images);
		file.read((char*)&n_rows,sizeof(n_rows));
		n_rows= reverseDigit(n_rows);
		file.read((char*)&n_cols,sizeof(n_cols));
		n_cols= reverseDigit(n_cols);
		cout << "\n No. of images:" << number_of_images;
		for(long int i=0;i<number_of_images;++i)
		{	
			img.create(n_rows,n_cols, CV_8UC1);
			for(int r=0;r<n_rows;++r)
			{
				for(int c=0;c<n_cols;++c)
				{
					unsigned char temp=0;
					file.read((char*)&temp,sizeof(temp));
					img.at<uchar>(r,c) = temp;

				}
			}
			//img.create(n_rows,n_cols, CV_8UC1, (void*)temp);
			ostringstream convert;
			convert << idx;
			string imgName;
			if(opt==0)
				imgName ="Train/"+ convert.str() + ".jpg";
			else
				imgName ="Test/"+ convert.str() + ".jpg";	
			/*
			imshow("img",img);
			waitKey(0);
			*/ 
			imwrite(imgName, img);
			img.release();
			idx++;
			
			
		}
	}
	file.close();
}

			


int main(int argc, char ** argv)
{

	
	if(argc!=2)
	{
		std::cout<<"\n Usage: ./digitExtractor Train/Test";
		exit(1);
	}
	
	if(strcasecmp(argv[1],"train") == 0)
	{
		readMNIST(0);
	}
	
	else
	{
		readMNIST(1);
	}
	
	return 0;
}
	
	
