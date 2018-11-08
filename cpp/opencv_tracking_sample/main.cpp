#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include <vector>

const std::string VIDEO_FILE = "iStock-911535028.mov";
const std::string OUTPUT_FILE = "output.avi";

struct Tracker {
	std::string name;
	cv::Ptr<cv::Tracker> tracker;
	cv::Scalar color;
	cv::Rect2d roi;

	Tracker(std::string n, cv::Ptr<cv::Tracker> t, cv::Scalar c) : name(n), tracker(t), color(c) {}
};

int main() {
	std::vector<Tracker> trackers;

	trackers.push_back(Tracker("Boosting", cv::TrackerBoosting::create(), cv::Scalar(0, 255, 0)));
	trackers.push_back(Tracker("KCF", cv::TrackerKCF::create(), cv::Scalar(0, 255, 255)));
	trackers.push_back(Tracker("MedianFlow", cv::TrackerMedianFlow::create(), cv::Scalar(0, 0, 255)));
	trackers.push_back(Tracker("MIL", cv::TrackerMIL::create(), cv::Scalar(255, 0, 255)));
	trackers.push_back(Tracker("MOSSE", cv::TrackerMOSSE::create(), cv::Scalar(255, 0, 0)));
	trackers.push_back(Tracker("TLD", cv::TrackerTLD::create(), cv::Scalar(255, 255, 0)));
 
    cv::VideoCapture cap(VIDEO_FILE);
	if (!cap.isOpened()) {
        std::cerr << "Input file is not found." << std::endl;
        return -1;
    }

	cv::Mat frame;
    cap >> frame;
 
	cv::Rect2d roi = cv::selectROI("tracker", frame);
    if (roi.width == 0 || roi.height == 0){
        return -1;
    }

	cv::Mat target(frame, roi);
	std::cout << "(x, y, width, height) = (" << roi.x << "," << roi.y << "," << roi.width << "," << roi.height << ")" << std::endl;
 
	for (auto& t : trackers) {
		t.roi = roi;
		t.tracker->init(frame, t.roi);
	}
 
    double fps = cap.get(CV_CAP_PROP_FPS);
	cv::Size size = cv::Size(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    const int fourcc = cv::VideoWriter::fourcc('X', 'V', 'I', 'D');
    cv::VideoWriter writer(OUTPUT_FILE, fourcc, fps, size);
 
    printf("Start the tracking process, press ESC to quit.\n");
    for (;;) {
        cap >> frame;
        if (frame.rows == 0 || frame.cols == 0){
            break;
        }
 
		int y = 0;
		for (auto& t : trackers) {
			t.tracker->update(frame, t.roi);
			cv::rectangle(frame, t.roi, t.color, 1, 1);
			cv::putText(frame, "- " + t.name, cv::Point(5 + 60 * y++, 20), cv::FONT_HERSHEY_SIMPLEX, .5, t.color, 1, CV_AA);
		}

        rectangle(frame, roi, cv::Scalar(255, 0, 0), 2, 1);
        writer << frame;
        imshow("tracker", frame);
 
        //ESCを押したら終了
        if (cv::waitKey(1) == 0x1b){
            break;
        }
    }
    return 0;
}

