#include "opencv2/opencv.hpp"
#include <iostream>
#include <opencv2\highgui.hpp>

#define nonMouse "Non MouseEvent"
#define useMouse "Mouse Event"

using namespace cv;
using namespace std;

void camera_in();
void video_in();
void camera_in_video_out();


int main(void)
{
	//camera_in();
	video_in();
	//camera_in_video_out();

	return 0;
}

void onMouseEvent(int event, int x, int y, int flags, void* dstImage)
{
	int playSeconds = time(0);
	string fileName;

	Mat mouseImage = *(Mat*)dstImage;

	if (event == EVENT_LBUTTONDOWN)
	{
		fileName = format("capture%03d.bmp", playSeconds);
		imwrite(fileName.c_str(), mouseImage);
	}


	imshow(useMouse, mouseImage);
}

void camera_in()
{
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}

	cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;

	Mat frame, inversed;
	while (true) {
		cap >> frame;
		if (frame.empty())
			break;

		inversed = ~frame;

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(10) == 27) // ESC key
			break;
	}

	destroyAllWindows();
}

void video_in()
{
	VideoCapture cap("seventeen100.avi"); //���� �ҷ��ͼ� cap ��ü ����

	if (!cap.isOpened()) {
		cerr << "Video open failed!" << endl;
		return;
	}

	//cvSetCaptureProperty(data->capture, CV_CAP_PROP_FRAME_WIDTH, 1920);
	//cvSetCaptureProperty(data->capture, CV_CAP_PROP_FRAME_HEIGHT, 1080);

	cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl; //������ ���� ũ��
	cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl; // ������ ���� ũ��
	cout << "Frame count: " << cvRound(cap.get(CAP_PROP_FRAME_COUNT)) << endl; //��ü ������ �� ���

	double fps = cap.get(CAP_PROP_FPS); //�ʴ� ������ ��

	cout << "FPS: " << fps << endl;

	int delay = cvRound(1000 / fps); //�� ������ ������ �ð� ���� ���

	Mat frame, inversed;
	while (true) {
		cap >> frame; //������ �޾ƿͼ� frame�� ����
		if (frame.empty()) 
			break;

		//frame�� inversed�� ����� ���� ���� ���
//		imshow("frame", frame); 
//		imshow("inversed", inversed);
		imshow(nonMouse, frame);
		imshow(useMouse, frame);

		setMouseCallback(useMouse, onMouseEvent, (void*)&frame);

		if (waitKey(delay) == 27) // ESC key
			break;
	}

	destroyAllWindows();
}

void camera_in_video_out()
{
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}

	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
	double fps = cap.get(CAP_PROP_FPS);

	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
	int delay = cvRound(1000 / fps);

	VideoWriter outputVideo("output.avi", fourcc, fps, Size(w, h));

	if (!outputVideo.isOpened()) {
		cout << "File open failed!" << endl;
		return;
	}

	Mat frame, inversed;
	while (true) {
		cap >> frame;
		if (frame.empty())
			break;

		inversed = ~frame;
		outputVideo << inversed;

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27)
			break;
	}

	destroyAllWindows();
}
