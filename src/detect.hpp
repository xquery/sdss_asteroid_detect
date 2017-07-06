/*
 * Copyright 2017 James Fuller
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <wchar.h>
#include <vector>
#include <map>
#include <cassert>

#include <opencv2/opencv.hpp>

#include "utils.hpp"

namespace ad {

    using namespace cv;
    using namespace std;

    struct hough_circle_params {
        double dp = 1.0;
        double minDist = 5;
        double param1=40;
        double param2=10;
        int minRadius=1;
        int maxRadius=35;
    };

    int naive_detect(string imagefilename, SimpleBlobDetector::Params params, hough_circle_params cparams ){

        check_file_exists(imagefilename);

        Mat src, empty_image;
        src = imread(imagefilename,CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);

        if(src.empty()){
            return -1;
        }

        vector<Mat> spl;
        split(src,spl);

        empty_image = Mat::zeros(src.rows, src.cols, CV_8UC1);
        Mat result_blue(src.rows, src.cols, CV_8UC3); // notice the 3 channels here!
        Mat result_green(src.rows, src.cols, CV_8UC3); // notice the 3 channels here!
        Mat result_red(src.rows, src.cols, CV_8UC3); // notice the 3 channels here!

        // Create blue channel
        Mat in1[] = { spl[0], empty_image, empty_image };
        int from_to1[] = { 0,0, 1,1, 2,2 };
        mixChannels( in1, 3, &result_blue, 1, from_to1, 3 );

        // Create green channel
        Mat in2[] = { empty_image, spl[1], empty_image };
        int from_to2[] = { 0,0, 1,1, 2,2 };
        mixChannels( in2, 3, &result_green, 1, from_to2, 3 );

        // Create red channel
        Mat in3[] = { empty_image, empty_image, spl[2]};
        int from_to3[] = { 0,0, 1,1, 2,2 };
        mixChannels( in3, 3, &result_red, 1, from_to3, 3 );

        Mat img1,img2,img3;

        cvtColor(result_blue,img1,CV_RGB2GRAY);
        cvtColor(result_red,img2,CV_RGB2GRAY);
        cvtColor(result_green,img3,CV_RGB2GRAY);

        Mat result = img1-img2-img3;

        vector<KeyPoint> keypoints;
        Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);
        detector->detect( result, keypoints );

        Mat im_with_keypoints;
        drawKeypoints( result, keypoints, im_with_keypoints, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

        Mat gray;
        cvtColor(im_with_keypoints, gray, CV_BGR2GRAY);

        std::vector<Vec3f> circles;

        HoughCircles(
                gray,                // InputArray image
                circles,             // OutputArray circles
                CV_HOUGH_GRADIENT,   // int method
                cparams.dp,          // double dp
                cparams.minDist,     // double minDist
                cparams.param1,      // double param1=100
                cparams.param2,      // double param2=100
                cparams.minRadius,   // int minRadius=0
                cparams.minRadius    // int maxRadius=0
        );

        if(!circles.empty() ){
            LOG_S(INFO) << "hits:" << circles.size();
            imwrite(imagefilename + ".candidate.jpg", im_with_keypoints );
        }else{
            LOG_S(INFO) << "no hits";
        }

        return 0;
    }

    int naive_detect(string imagefilename ) {
        SimpleBlobDetector::Params params;

        //params.minDistBetweenBlobs = 1.0f;
        params.filterByInertia = false;
        params.filterByConvexity = false;
        params.filterByColor = false;
        params.filterByCircularity = false;
        params.filterByArea = true;
        params.minArea = 1.0f;
        params.maxArea = 20.0f;
        params.minThreshold = .01;
        //params.maxThreshold = 150;

        hough_circle_params cparams;

        naive_detect(imagefilename, params, cparams );
    }

}