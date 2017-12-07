#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


void detectText(const char *filePath) {
    Mat srcImage = imread(filePath);
    imshow(filePath, srcImage);
    Mat rgb;

//    Rect rect = srcImage
    pyrDown(srcImage, rgb);
//    pyrDown(rgb, rgb);

    imshow("rgb", srcImage);

    Mat small;
    cvtColor(rgb, small, CV_BGR2GRAY);

    imshow("small", small);
    waitKey(0);

    Mat grad;
    Mat morphKernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
    morphologyEx(small, grad, MORPH_GRADIENT, morphKernel);
    // binarize
    Mat bw;
    threshold(grad, bw, 0.0, 255.0, THRESH_BINARY | THRESH_OTSU);
    // connect horizontally oriented regions
    Mat connected;
    morphKernel = getStructuringElement(MORPH_RECT, Size(9, 1));
    morphologyEx(bw, connected, MORPH_CLOSE, morphKernel);
    // find contours
    Mat mask = Mat::zeros(bw.size(), CV_8UC1);
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(connected, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    // filter contours
    for (int idx = 0; idx >= 0; idx = hierarchy[idx][0]) {
        Rect rect = boundingRect(contours[idx]);
        Mat maskROI(mask, rect);
        maskROI = Scalar(0, 0, 0);
        // fill the contour
        drawContours(mask, contours, idx, Scalar(255, 255, 255), CV_FILLED);

        RotatedRect rrect = minAreaRect(contours[idx]);
        double r = (double) countNonZero(maskROI) / (rrect.size.width * rrect.size.height);

        Scalar color;
        int thickness = 1;
        // assume at least 25% of the area is filled if it contains text
        if (r > 0.25 &&
            (rrect.size.height > 8 && rrect.size.width > 8) // constraints on region size
            // these two conditions alone are not very robust. better to use something
            //like the number of significant peaks in a horizontal projection as a third condition
                ) {
            thickness = 2;
            color = Scalar(0, 255, 0);
        } else {
            thickness = 1;
            color = Scalar(0, 0, 255);
        }

        Point2f pts[4];
        rrect.points(pts);
        for (int i = 0; i < 4; i++) {
            line(rgb, Point((int) pts[i].x, (int) pts[i].y), Point((int) pts[(i + 1) % 4].x, (int) pts[(i + 1) % 4].y),
                 color, thickness);
            printf("%f %f\n", pts[i].x, pts[i].y);
        }
        puts("");


    }

    imwrite("/Users/fanzhengchen/Desktop/rect.jpg", rgb);
}

int main() {


    string path = "/Users/fanzhengchen/Desktop/web";

    detectText(path.c_str());
    return 0;
}