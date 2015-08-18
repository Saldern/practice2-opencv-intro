#pragma once

#include <string>
#include <iostream>
#include <opencv2/core/core.hpp>

#include "processing.hpp"

bool onButtonClicked(cv::Rect buttonPlace, int x, int y);
void onButtonsOnOffClick(int eventId, int x, int y, int flags, void *userData);

class Application
{
 public:
    enum WindowState
    {
        OnFilter,
        OffFilter
    };
    struct Parameters
    {
        std::string imgFileName;
    };
    struct GUIElementsState
    {
		FilterType filter;
        WindowState state;
		bool saveState;
        cv::Rect medianButtonPlace;
        cv::Rect offButtonPlace;
		cv::Rect saveButtonPlace;
		cv::Rect greyButtonPlace;
		cv::Rect pxlButtonPlace;
		cv::Rect cannyButtonPlace;
    };
    int parseArguments(int argc, const char **argv, Parameters &params);
    int getFrame(const std::string &fileName, cv::Mat& src);
    int processFrame(const cv::Mat& src, cv::Mat& dst);
    int showFrame(const std::string &caption, 
                  const cv::Mat& src, cv::Mat& dst);
    friend void onButtonsOnOffClick(int eventId, int x, int y, 
                                    int flags, void *userData);
    Application() 
    { 
		guiState.filter = MEDIAN;
        guiState.state = OnFilter;
		guiState.saveState = false;
    };

 private:
    Processing processor;
    GUIElementsState guiState;

    int drawButtons(cv::Mat &display);
    
    friend bool onButtonClicked(cv::Rect buttonPlace, int x, int y);
};
