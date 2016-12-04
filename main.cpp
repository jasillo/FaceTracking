#include <opencv2\core\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\objdetect.hpp>
#include <opencv2\imgproc.hpp>
#include <vector>
#include <string>
#include <direct.h>
using namespace cv;
CascadeClassifier face_cascade, eyes_cascade;
//std::vector<Rect> centerPositions;
//std::vector<int> colorIndex;
Scalar colors[] = { Scalar(255,0,0),Scalar(0,255,0), Scalar(0,0,255), Scalar(255,255,0), Scalar(0,255,255), Scalar(255,0,255) };


void detectFaces(Mat *frame)
{
	std::vector<Rect> faces;
	Mat frame_gray;
	cvtColor(*frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	//detectar caras
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 3, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

	//dibujamos los bounding boxes
	for (size_t i = 0; i < faces.size(); ++i)
	{
		Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);

		Mat face = frame_gray(faces[i]);
		std::vector<Rect> eyes;
		//eyes_cascade.detectMultiScale(face, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(10, 10));

		//if (eyes.size() > 0) {
			ellipse(*frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, colors[2], 4, 8, 0);
			//rectangle(frame,faces[i],Scalar(255,0,0),2,8,0);
		//}

	}	
}

int main()
{
	face_cascade.load("haarcascade_frontalface_alt.xml");
	//face_cascade.load("lbpcascade_frontalface.xml");
	//eyes_cascade.load("haarcascade_eye.xml");

	if (false) { //captura camara
		VideoCapture cap(0);
		Mat frame;
		while (cap.read(frame))
		{
			detectFaces(&frame);
			if (waitKey(30) >= 0)
				break;
		}
		imshow("imagen", frame);
	}
	else { //testeo		
		for (int i = 1; i <= 11; ++i) //numero de sujetos
		{			
			for (int j = 1; j <= 10; ++j) //numero de la imagen
			{
				Mat frame = imread("testeo/sujeto" + std::to_string(i) + "/" + std::to_string(j) + ".jpg");
				//Mat frame = imread("1.jpg");
				detectFaces(&frame);
				//debe existir las capertas previamente
				//tienen la misma estructura q la carpeta testeo
				imwrite("resultados/sujeto" + std::to_string(i) + "/" + std::to_string(j) + ".jpg", frame);				
			}
		}
	}
	
	waitKey(0);
	return 1;
}