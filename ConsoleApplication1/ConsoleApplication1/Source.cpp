#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat image = imread("C:\\1.jpg", IMREAD_GRAYSCALE);
	Mat imageNormalised;
	Mat imageEqualised;

	int histSize = 256;
	vector <int> hist(histSize, 0);
	vector <int> histGraph(histSize, 0);
	vector <int> histNorm(histSize, 0);

	int h = image.size().height;
	int w = image.size().width;

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int color = image.at <unsigned char>(y, x);
			hist[color]++;
		}
	}

	int hist_w = 512, hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize); 

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0)); 
	normalize(hist, histGraph, 0, h, NORM_MINMAX, -1, Mat());
	
	for (int i = 1; i < histSize; i = i++)
	{
		line(histImage, Point(bin_w*(i-1), hist_h - cvRound(histGraph.at(i-1))),
			Point(bin_w*(i), hist_h - cvRound(histGraph.at(i))),
			Scalar(255, 0, 0), 2, 8, 0);
	}

	equalizeHist(image, imageEqualised); 
	normalize(image, imageNormalised, 1, 0, NORM_MINMAX, CV_32F); 

	imshow("Original image", image);
	imshow("Histogram", histImage);
	imshow("Equalized image", imageEqualised);
	imshow("Normalized image", imageNormalised);
	waitKey(0);
	return 0;
}
