#include <iostream>
#include <opencv2\opencv.hpp>
#include <math.h>
using namespace std;
using namespace cv;
Mat src, tmp, dst;
Mat tmp1;
VideoCapture cam(0);
void Call_back(int, void*);
int leng=10;

int main(int argc, char** argv) {
	namedWindow("src", WINDOW_AUTOSIZE);
	createTrackbar("var","src", &leng,255, Call_back);
	//float i = 3;
	//cout <<  ;
	while (waitKey(20)!='c') {
		
		Call_back(0, 0);
		imshow("tmp", tmp);
		imshow("src", src);
	}
	
	return 0;
}
void Call_back(int, void*) {
	cam >> src;
	vector<Vec4f> line_arry;

	GaussianBlur(src, tmp, Size(3, 3), 0, 0);//¸ßË¹ÂË²¨
	cvtColor(tmp, tmp, CV_RGB2GRAY);
	medianBlur(tmp,tmp,11);
	tmp.copyTo(tmp1);

	/****************************/
	Canny(tmp, tmp, 100, 200);
	HoughLinesP(tmp, line_arry, 1, CV_PI / 180.0, 150, src.cols / 4, 10);

	/*************************************/
	vector<Vec3f> Circles;
	HoughCircles(tmp1, Circles,CV_HOUGH_GRADIENT,1,tmp.rows,100,30,20,50);
	Scalar color_line = Scalar(0, 0, 255);//
	Scalar color_Circle = Scalar(255, 0, 0);
	Vec4f Max_line=Vec4f(0,0,0,0);
	for each(Vec4f var in line_arry)
	{

		//float jieguo=sqrtf( powf(line_arry[var][2]-line_arry[var][0],2)+powf(line_arry[var][3]-line_arry[var][1],2));
	/*	float x, y;
		x =line_arry[var][2] - line_arry[var][0];
		y =line_arry[var][3] - line_arry[var][1];
		
		float jieguo1= sqrtf(powf(Max_line[2] - Max_line[0], 2) + powf(Max_line[3] - Max_line[1], 2));*/
		//if (jieguo1 < jieguo)Max_line = line_arry[var];
		//float tmp =  sqrtf();
		line(src, Point(var[0], var[1]), Point(var[2], var[3]), color_line, 2, LINE_8);
		//line();
	}
	//line(src, Point(Max_line[0], Max_line[1]), Point(Max_line[2], Max_line[3]), color_line, 3, LINE_8);
	Vec3f Max_circle = Vec3f(0,0,0);
	for each(Vec3f v in  Circles) {

		//if (Circles[v][2] > Max_circle[2])Max_circle = Circles[v];
		circle(src,Point(v[0], v[1]), v[2], color_Circle,3,8);
	}
	
	//line(src,Point(line_arry[0],line_arry[1]),Point(line_arry[2],line_arry[3]),Scalar(0,0,255));
//	namedWindow("src", WINDOW_AUTOSIZE);
	imshow("tmp", tmp);
	imshow("tmp1", tmp1);
	imshow("src", src);
}