// This file is part of CNCSVision, a computer vision related library
// This software is developed under the grant of Italian Institute of Technology
//
// Copyright (C) 2011 Carlo Nicolini <carlo.nicolini@iit.it>
//
//
// CNCSVision is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//f
// Alternatively, you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// CNCSVision is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License or the
// GNU General Public License for more details.
//

// You should have received a copy of the GNU Lesser General Public
// License and a copy of the GNU General Public License along with
// CNCSVision. If not, see <http://www.gnu.org/licenses/>.

/*******  Define screen resolution, (width,height )in pixel and (widht, height )in millimeters *******/
#include <Eigen/Core>

//#define TIMER_MS 13 // 75 hz... these are incorrect for this set up
//#define SCREEN_WIDTH  1024      // pixels
//#define SCREEN_HEIGHT 768       // pixels
#define TIMER_MS 11                               // 85 hz
#define SCREEN_WIDTH  1024                 // 1024 pixels //Was set to max 1280x1024 but cannot reach 85hertz
#define SCREEN_HEIGHT 768                  // 768 pixels
extern const double SCREEN_WIDE_SIZE = 363; //361.0;    // millimeters
extern const double SCREEN_HEIGHT_SIZE = 272;//269.0;    // millimeters

/********* CALIBRATION  This coordinate represents the origin (0.0, 0.0, 0.0) in the reference frame **/
static const Vector3d calibration(263.0, -531.6, 529.8); //(160,179,-75);
extern const Eigen::Vector3d frameOrigin = calibration;
// Alignment between optotrak z axis and screen z axis
double parallel_indicator = 0;
double alignmentX = 0; //23;//33.5; EVAN CHANGED THIS -- BLAME HIM
double alignmentY = 0; //42.5;//33; THINGS WERE NOT ALIGNED
double homeFocalDistance = -340, focalDistance = homeFocalDistance, baseFocalDistance = homeFocalDistance;

// Optotrak alignment file , this is a relative path
extern char LastAlignedFile[] = "standard.cam";

// This is the width of chin rest in millimeters which is needed to calibrate the two eyes
static const double ChinRestWidth = 215.0;
static const char GAME_MODE_STRING[] = "1024x1024:32@60";

// Some Optotrak local variables for the Trieste setup. 
// See Optotrak,Optotrak2 classes to understand their meaning
static const int OPTO_NUM_MARKERS = 28;
static const float OPTO_FRAMERATE = 75.0f;
static const float OPTO_MARKER_FREQ = 3000.0f;
static const float OPTO_DUTY_CYCLE = 0.4f;
static const float OPTO_VOLTAGE = 8.0f;

/***** matrices and vectors for calibration ****/

MatrixXd calibrationM(3, 3), calibrationM_tr(3, 3), referenceM(3, 3), rotationM(3, 3);
Vector3d origin_raw(0.0, 0.0, 0.0);
//The difference between the designated eye center and the origin (marker 1)
Vector3d calibration_offset = Vector3d(-398.5, 557.5, 682.1);

// this ReferenceM is needed if we use Carlo's method.
void initReferenceM()
{
    //referenceM << -80.95, 2.64, -0.208, //x     -81.772
    //   0.158, 106.012, 3.595, //y     113.874
    //  -0.331, 0.75, -82.19; //z
    //referenceM << 80.39, 0, 0, //x    
     //   0, 157.43, 0, //y     113.874
      //  0, 0, 82.73 ;
/*
    referenceM << 82.458,     3.350,        0.037, //x    80.39
                  -0.906,     157.655,      -0.588, //y     113.874
                  -1.986,     2.128,        82.742; //z

    referenceM << 82.27,    1.457,    0, //x    80.39
                  0,        157.68,   0, //y     113.874
                  -2.051,   1.043,    82.738; //z
*/
    // cout << "referenceM oo" << endl;
}
