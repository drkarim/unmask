#include "mirtk/Common.h"
#include "mirtk/Options.h"
#include "mirtk/IOConfig.h"
#include "mirtk/GenericImage.h"

using namespace mirtk;

void UnMask(GreyImage* img1, GreyImage* img2, char* out_img_fn) {
	
	
	for (int i=0;i<img1->GetX();i++)
	{
		for (int j=0;j<img1->GetY();j++)
		{
			for (int k=0;k<img1->GetZ();k++)
			{
				if (img2->Get(i,j,k) <= 0)
				{
					img1->Put(i,j,k, 0);				// negate
				}
				
			}
		}
	}

	img1->Write(out_img_fn);	
	
	
}

int main(int argc, char **argv)
{
	int optind;
	bool foundArgs=false;
			
	GreyImage img1; 
	char* input_f1="", *input_f2="", *output_f="", *output_txt="";

	if (argc >= 1) 
	{
		int optind=1;
		
		while ((optind < argc) && (argv[optind][0]=='-')) {
			
			string sw = argv[optind];
			
			if (sw == "-i1") {
				optind++;
				input_f1 = argv[optind]; 
				foundArgs = true;	
			}
			
			if (sw == "-i2") {
				optind++;
				input_f2= argv[optind]; 
				foundArgs = true;	
			}
			
			else if (sw == "-o") {
				optind++;
				output_f = argv[optind]; 
			}

			optind++; 
		}
	}
	
	if (foundArgs == false)
	{
		cout << "\n\nUsage: mirtk evaluate-un-mask \n\n\t-i1 <grey-level image> \n\t-i2 <binary mask>\n\t-o <output image>" << endl; 
		exit(0); 
	}

	else
	{
		InitializeIOLibrary();
		//GreyImage img1(input_f1);
		//GreyImage img2(input_f2); 

		UniquePtr<BaseImage> img1(BaseImage::New(input_f1));
		UniquePtr<BaseImage> img2(BaseImage::New(input_f2));
		
		
		UnMask(new GenericImage<short>(*img1), new GenericImage<short>(*img2), output_f);
		
	}

}
