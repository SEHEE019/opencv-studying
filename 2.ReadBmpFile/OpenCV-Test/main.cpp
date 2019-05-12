#include "opencv2\opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	cout << "Hello OpenCV" << CV_VERSION << endl;

	Mat img;//mat Ŭ���� Ÿ�� ���� img ����
	img = imread("seventeen.bmp");//imread: ���� �б�

	if (img.empty()) {//seventeen.bmp ������ ����� �ҷ����� ������ ����� ����ó��
		cerr << "Image load fialed.." << std::endl;//empty �Լ� true ��ȯ ��
		return -1;
	}

	namedWindow("image");//������ ȭ�鿡 ��Ÿ���� ���� "image"��� ���ο� â ����
	imshow("image", img);//"image" â�� seventeen.bmp ���� ���

	waitKey();//������� Ű���� �Է��� ��ٸ��� �Լ�, Ű���� ���� �� ���α׷� ����

	return 0;
}