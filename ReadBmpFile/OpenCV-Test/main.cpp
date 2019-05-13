#include "opencv2\opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	cout << "Hello OpenCV" << CV_VERSION << endl;

	Mat img;//mat 클래스 타입 변수 img 선언
	img = imread("seventeen.bmp");//imread: 영상 읽기

	if (img.empty()) {//seventeen.bmp 파일을 제대로 불러오지 못했을 경우의 예외처리
		cerr << "Image load fialed.." << std::endl;//empty 함수 true 반환 시
		return -1;
	}

	namedWindow("image");//영상을 화면에 나타내기 위한 "image"라는 새로운 창 생성
	imshow("image", img);//"image" 창에 seventeen.bmp 영상 출력

	waitKey();//사용자의 키보드 입력을 기다리는 함수, 키보드 누를 시 프로그램 종료

	return 0;
}