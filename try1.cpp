#include <opencv2/opencv.hpp>
#include <iostream>

cv::Point2f calculateWeightedAveragePosition(const cv::Mat& image) {
    int totalWeight = 0;
    float weightedSumX = 0.0f;
    float weightedSumY = 0.0f;

    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            cv::Vec3b color = image.at<cv::Vec3b>(y, x);
            int blue = color[0];
            int green = color[1];
            int red = color[2];

            if (red > 150 && green < 100 && blue < 100) {
                int weight = red;
                weightedSumX += x * weight;
                weightedSumY += y * weight;
                totalWeight += weight;
            }
        }
    }

    if (totalWeight == 0) {
        std::cout << "No red pixels found in the image." << std::endl;
        return cv::Point2f(-1, -1);
    }

    float avgX = weightedSumX / totalWeight;
    float avgY = weightedSumY / totalWeight;

    return cv::Point2f(avgX, avgY);
}

int main() {
    cv::Mat image = cv::imread("test1.bmp");

    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        return -1;
    }

    cv::resize(image, image, cv::Size(160, 120));
    cv::Point2f weightedAvgPos = calculateWeightedAveragePosition(image);

    if (weightedAvgPos.x >= 0 && weightedAvgPos.y >= 0) {
        cv::circle(image, weightedAvgPos, 1, cv::Scalar(0, 255, 0), -1); 
        cv::line(image, cv::Point(weightedAvgPos.x - 5, weightedAvgPos.y), cv::Point(weightedAvgPos.x + 5, weightedAvgPos.y), cv::Scalar(0, 255, 0), 2);
        cv::line(image, cv::Point(weightedAvgPos.x, weightedAvgPos.y - 5), cv::Point(weightedAvgPos.x, weightedAvgPos.y + 5), cv::Scalar(0, 255, 0), 2);

        cv::imwrite("output2.bmp", image);
    }
    return 0;
}