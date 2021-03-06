#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <time.h>
#include <queue>
#include <string>
#include <ctime>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "raspicam/raspicam_cv.h"
#include "area.hpp"

#define WIDTH 320
#define HEIGHT 240


int GoalBall = 0;
bool isBall;
bool isGoal_blue;
bool isGoal_yellow;
typedef struct
{
  int H_MIN;
  int H_MAX;
  int S_MIN;
  int S_MAX;
  int V_MIN;
  int V_MAX;
  int M_MID_high;
  int M_MID_low;
  int M_SIDE_high;
  int M_SIDE_low;
  //int THOLD;
  //int TCENTER;
}calPar_t;

calPar_t ball;
calPar_t goal_blue;
calPar_t goal_yellow;

cv::Mat frame; // Original image
cv::Mat hsv; // HSV Image
cv::Mat filtered; // Color filtered image and mask
cv::Mat gray;
cv::Mat canny;


cv::VideoWriter vidOut;


bool loadCalibration(bool isBall, bool isGoal_yellow, calPar_t *par);

int main(int argc, char** argv)
{
  calPar_t par;
	//printf("%d %s", argc, argv[1]);
	if( !loadCalibration(true, false, &ball) ) return 0;
  if( !loadCalibration(false, true, &goal_yellow) ) return 0;
  if( !loadCalibration(false, false, &goal_blue) ) return 0;
  memcpy( &par, &goal_blue, sizeof( calPar_t ) );
	
	// Create sliders
	cv::namedWindow( "Slider" );
	cv::createTrackbar( "goal_blue/goal_yellow/Ball", "Slider", &GoalBall, 2 );
	cv::createTrackbar( "H_MIN", "Slider", &par.H_MIN, 255 );
	cv::createTrackbar( "H_MAX", "Slider", &par.H_MAX, 180 );
	cv::createTrackbar( "S_MIN", "Slider", &par.S_MIN, 255 );
	cv::createTrackbar( "S_MAX", "Slider", &par.S_MAX, 255 );
	cv::createTrackbar( "V_MIN", "Slider", &par.V_MIN, 255 );
	cv::createTrackbar( "V_MAX", "Slider", &par.V_MAX, 255 );
	cv::createTrackbar( "M_MID_high", "Slider", &par.M_MID_high, HEIGHT );
	cv::createTrackbar( "M_MID_low", "Slider", &par.M_MID_low, HEIGHT );
	cv::createTrackbar( "M_SIDE_high", "Slider", &par.M_SIDE_high, HEIGHT );
	cv::createTrackbar( "M_SIDE_low", "Slider", &par.M_SIDE_low, HEIGHT );
	
	//cv::createTrackbar( "THOLD", "Slider", &par.THOLD, 300 );
	//cv::createTrackbar( "TCENTER", "Slider", &par.TCENTER, 300 );
	goal_blue.M_MID_high = par.M_MID_high;
	goal_yellow.M_MID_high = par.M_MID_high;
	ball.M_MID_high = par.M_MID_high;
	
	goal_blue.M_MID_low = par.M_MID_low;
	goal_yellow.M_MID_low = par.M_MID_low;
	ball.M_MID_low = par.M_MID_low;
	
	goal_blue.M_SIDE_high = par.M_SIDE_high;
	goal_yellow.M_SIDE_high = par.M_SIDE_high;
	ball.M_SIDE_high = par.M_SIDE_high;
	
	goal_blue.M_SIDE_low = par.M_SIDE_low;
	goal_yellow.M_SIDE_low = par.M_SIDE_low;
	ball.M_SIDE_low = par.M_SIDE_low;
  
	// Camera object
	raspicam::RaspiCam_Cv cam;
	cam.set( CV_CAP_PROP_FRAME_HEIGHT, HEIGHT );
	cam.set( CV_CAP_PROP_FRAME_WIDTH, WIDTH );
	cam.set( CV_CAP_PROP_FORMAT, CV_8UC3 );
	cam.set( CV_CAP_PROP_FPS, 60 );
	cam.set( CV_CAP_PROP_WHITE_BALANCE_RED_V, -1 );
	cam.set( CV_CAP_PROP_WHITE_BALANCE_BLUE_U, -1 );
	
	printf( "[*] Open Camera\n" );
	if( !cam.open() ) {
		printf( "[*] Failed to open camera!\n" );
		return -1;
	}
	
	printf( "[*] Waiting for camera to stabilize\n" );
	usleep( 3 * 1000000);
	printf( "[*] Ready for capturing\n" );
	
	char vidName[50];
	time_t t = time(0);
	struct tm* now = localtime( &t );
	sprintf( vidName, "%d.%d.%d-%d_%d.avi", now->tm_mday, now->tm_mon+1, now->tm_year+1900, now->tm_hour, now->tm_min );
	
	//vidOut.open( vidName, CV_FOURCC('H','2','6','4') , 30, cv::Size(WIDTH, HEIGHT) );

	
	
	bool first = true;
	
	cv::Mat container( HEIGHT * 2, WIDTH * 2, CV_8UC3, cv::Scalar(0, 0, 0) ); 
	
	struct timespec t_start, t_end;
	
	// Grab and retrieve image from camera
	for( ;; ) {
		
		clock_gettime( CLOCK_REALTIME, &t_start );
		
		cam.set( CV_CAP_PROP_WHITE_BALANCE_RED_V, -1 );
		cam.set( CV_CAP_PROP_WHITE_BALANCE_BLUE_U, -1 );

		// Get current image from camera
		cam.grab();
		cam.retrieve( frame );
    

    
		// Mask image
		cv::Mat mask = frame( cv::Rect(0, par.M_MID_high, WIDTH, par.M_MID_low) );    //Error when inserting "par.TopBorder" instead of "80"
		mask.setTo( cv::Scalar(0, 0, 0) );
		
		
		
		//cv::Point A(par.M_SIDE_low, par.M_MID_high);
		//cv::Point B(WIDTH, par.M_MID_high);
		//cv::Point C(WIDTH, 0);
		
		/** Create some points */
		cv::Point right_top_points[1][3];
		//right_points[0][0] = cv::Point(WIDTH-par.M_SIDE_low, par.M_MID_high);
		right_top_points[0][0] = cv::Point(WIDTH, par.M_MID_high);
		right_top_points[0][1] = cv::Point(WIDTH, 0);
		right_top_points[0][2] = cv::Point(WIDTH-par.M_SIDE_high, 0);
		const cv::Point* ppt[1] = { right_top_points[0] };
		int npt[] = { 3 };
		cv::fillPoly(frame, ppt, npt, 1,cv::Scalar(0, 0, 0), 8);
		
		cv::Point right_low_points[1][3];
		right_low_points[0][0] = cv::Point(WIDTH-par.M_SIDE_low, par.M_MID_high);
		right_low_points[0][1] = cv::Point(WIDTH, par.M_MID_high);
		right_low_points[0][2] = cv::Point(WIDTH, 0);
		//right_low_points[0][3] = cv::Point(WIDTH-par.M_SIDE_high, 0);
		const cv::Point* ppt_[1] = { right_low_points[0] };
		int npt_[] = { 3 };
		cv::fillPoly(frame, ppt_, npt_, 1,cv::Scalar(0, 0, 0), 8);
		
		
		cv::Point left_top_points[1][3];
		//left_points[0][0] = cv::Point(par.M_SIDE_low, par.M_MID_high);
		left_top_points[0][0] = cv::Point(0, par.M_MID_high);
		left_top_points[0][1] = cv::Point(0, 0);
		left_top_points[0][2] = cv::Point(par.M_SIDE_high, 0);
		const cv::Point* ppt_L[1] = { left_top_points[0] };
		int npt_L[] = { 3 };
		cv::fillPoly(frame, ppt_L, npt_L, 1,cv::Scalar(0, 0, 0), 8);
		
		
		cv::Point left_low_points[1][3];
		left_low_points[0][0] = cv::Point(par.M_SIDE_low, par.M_MID_high);
		left_low_points[0][1] = cv::Point(0, par.M_MID_high);
		left_low_points[0][2] = cv::Point(0, 0);
		//left_low_points[0][3] = cv::Point(par.M_SIDE_high, 0);
		const cv::Point* ppt_L_[1] = { left_low_points[0] };
		int npt_L_[] = { 3 };
		cv::fillPoly(frame, ppt_L_, npt_L_, 1,cv::Scalar(0, 0, 0), 8);
		
		
		
		
		cv::Point mid( frame.cols / 2, frame.rows );

		if( first ) {
			printf( "[*] Image size: %d %d\n", frame.cols, frame.rows );
			first = false;
			continue;
		}
    
    
    goal_blue.M_MID_high = par.M_MID_high;
	goal_yellow.M_MID_high = par.M_MID_high;
	ball.M_MID_high = par.M_MID_high;
	
	goal_blue.M_MID_low = par.M_MID_low;
	goal_yellow.M_MID_low = par.M_MID_low;
	ball.M_MID_low = par.M_MID_low;
	
	goal_blue.M_SIDE_high = par.M_SIDE_high;
	goal_yellow.M_SIDE_high = par.M_SIDE_high;
	ball.M_SIDE_high = par.M_SIDE_high;
	
	goal_blue.M_SIDE_low = par.M_SIDE_low;
	goal_yellow.M_SIDE_low = par.M_SIDE_low;
	ball.M_SIDE_low = par.M_SIDE_low;
    
    
    isGoal_yellow = (GoalBall==1)?true:false;
    isBall = (GoalBall==2)?true:false;	
		if( isBall )
    {
      memcpy( &par, &ball, sizeof( calPar_t ) );
  
    }
    else if( isGoal_yellow )
    {
      memcpy( &par, &goal_yellow, sizeof( calPar_t ) );
    }
    else
    {
      memcpy( &par, &goal_blue, sizeof( calPar_t ) );
    }
    
    //setTrackbarPos
    cv::setTrackbarPos( "H_MIN", "Slider", par.H_MIN);
    cv::setTrackbarPos( "H_MAX", "Slider", par.H_MAX);
    cv::setTrackbarPos( "S_MIN", "Slider", par.S_MIN);
    cv::setTrackbarPos( "S_MAX", "Slider", par.S_MAX);
    cv::setTrackbarPos( "V_MIN", "Slider", par.V_MIN);
    cv::setTrackbarPos( "V_MAX", "Slider", par.V_MAX);
    cv::setTrackbarPos( "M_MID_high", "Slider", par.M_MID_high);
    cv::setTrackbarPos( "M_MID_low", "Slider", par.M_MID_low);
    cv::setTrackbarPos( "M_SIDE_high", "Slider", par.M_SIDE_high);
    cv::setTrackbarPos( "M_SIDE_low", "Slider", par.M_SIDE_low);
    //cv::setTrackbarPos( "THOLD", "Slider", par.THOLD);
    //cv::setTrackbarPos( "TCENTER", "Slider", par.TCENTER);
    
		//cv::GaussianBlur( frame, frame, cv::Size(13, 13), 2, 2 );

		// Convert image from BGR to HSV
		cv::cvtColor( frame, hsv, cv::COLOR_RGB2HSV );
		/* cv::cvtColor( frame, gray, cv::COLOR_BGR2GRAY ); */
		
		
		// Filter pixel for specific values in given range
		cv::inRange( hsv, cv::Scalar( par.H_MIN, par.S_MIN, par.V_MIN ), cv::Scalar( par.H_MAX, par.S_MAX, par.V_MAX ), filtered );
		/* cv::Mat maskFilter = filtered.clone(); 
		
		gray.copyTo( gray, maskFilter ); 
		
		cv::Canny( gray, canny, THOLD, THOLD*3, 3 ); */
		
		// Found areas
		std::vector<Area> areas;

		// Search every 4th pixel 
		for( int y = 0; y < filtered.rows; y+=4 ) {
		   	for( int x = 0; x < filtered.cols; x+=4 ) {

				// Read value
				uchar value = filtered.at<uchar>( y, x );

                // Pixel is not white
                if( value != 255 ) continue;

				// New area
                Area a( cv::Point( x, y ) );

				// Queue for searching pixel
				std::queue<cv::Point> queue;
				queue.push( cv::Point( x, y ) );

				// Flood fill using a queue
				bool bEmpty = false;
				while( !bEmpty ) {
					cv::Point p = queue.front();
					if( p.x > 0 && filtered.at<uchar>( p.y, p.x - 1 ) == 255 ) {
						a.addPixel( cv::Point( p.x - 1, p.y ) );
						filtered.at<uchar>( p.y, p.x - 1 ) = 254;
						queue.push( cv::Point( p.x - 1, p.y ) );
					}
					if( p.y > 0 && filtered.at<uchar>( p.y - 1, p.x ) == 255 ) {
						a.addPixel( cv::Point( p.x, p.y - 1 ) );
						filtered.at<uchar>( p.y - 1, p.x ) = 254;
						queue.push( cv::Point( p.x, p.y - 1 ) );
					}
					if( p.x < filtered.cols - 1 && filtered.at<uchar>( p.y, p.x + 1 ) == 255 ) {
						a.addPixel( cv::Point( p.x + 1, p.y ) );
						filtered.at<uchar>( p.y, p.x + 1) = 254;
						queue.push( cv::Point( p.x + 1, p.y ) );
					}
					if( p.y < filtered.rows - 1 && filtered.at<uchar>( p.y + 1, p.x ) == 255 ) {
						a.addPixel( cv::Point( p.x, p.y + 1 ) );
						filtered.at<uchar>( p.y + 1, p.x ) = 254;
						queue.push( cv::Point( p.x, p.y + 1) );
					}

					queue.pop();
					bEmpty = queue.empty();
				}

				// Area found
				areas.push_back( a );
            }
		}
		

		Area bigArea( cv::Point(0,0) );

		// Search biggest area
		for( std::vector<Area>::iterator it = areas.begin(); it != areas.end(); it++ ) {
			Area a = (Area) *it;

			if( a.getPixelCount() > bigArea.getPixelCount() ) bigArea = a;
		}

		
		float Width = (float) bigArea.getWidth();
		float Height = (float) bigArea.getHeight();		

		float prop1 = Width / Height;
		float prop2 = Height / Width;
		
		// Draw rectangle around biggest area
		if( bigArea.getPixelCount() > 15 && prop1 < 5.0 && prop2 < 2.5 )  // check proportions of the area //or out of "proportion border": bounding box around ball not possible 
		{
			cv::Point obj = bigArea.getStart();
			obj.x += Width / 2;
			obj.y += Height / 2;
				
			float diffX = obj.x - mid.x;
			float diffY = mid.y - obj.y;
			
			bigArea.draw( &frame, cv::Scalar( 0, 0, 255 ), cv::Scalar( 0, 255, 0 ) );			
			cv::line( frame, obj, mid, cv::Scalar( 255, 100, 100 ) );

			float horizontal = 0, vertical = 0;
			horizontal = ((float) (obj.x - mid.x) / ((float) WIDTH / 2.0f)) * 31.0f + 31.0f;
			vertical = ((float) (mid.y - obj.y) / (float) HEIGHT) * 50.0f;



			std::string text;
			std::stringstream out;
			out << horizontal << " " << vertical;
			text = out.str();
			
			
			cv::putText( frame, text, cv::Point(mid.x, 50), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 0, 255) );

		} else {
			cv::putText( frame, "Ball not found", cv::Point(mid.x, 50), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(0,0,255) );
		}
		
		cv::cvtColor( filtered, filtered, cv::COLOR_GRAY2BGR );
		
		
		frame.copyTo( container(cv::Rect(0, 0, WIDTH, HEIGHT)) );
		filtered.copyTo( container(cv::Rect(WIDTH, 0, WIDTH, HEIGHT)) );
		cv::imshow( "Images", container );
		
		if( cv::waitKey( 2 ) == 27 ) break;
    
		if( isBall )
    {
      memcpy( &ball, &par, sizeof( calPar_t ) );
  
    }
    else if ( isGoal_yellow )
    {
      memcpy( &goal_yellow, &par, sizeof( calPar_t ) );
    }
    else
    {
      memcpy( &goal_blue, &par, sizeof( calPar_t ) );
    }
    
		clock_gettime( CLOCK_REALTIME, &t_end );
		
		unsigned long ss = t_start.tv_sec * 1000;
		unsigned long es = t_end.tv_sec * 1000;
		
		ss += t_start.tv_nsec / 1.0e6;
		es += t_end.tv_nsec / 1.0e6;
		
		unsigned long d = es - ss;
		
		//vidOut << frame;
		printf( "Frames: %d\n", 1000 / d );
	}
	
	
	// Write calibration data out
  std::ofstream fileOut;
	fileOut.open("/home/pi/soccer/calibrateBall.txt");
	fileOut << ball.H_MIN << "\n";
	fileOut << ball.H_MAX << "\n";
	fileOut << ball.S_MIN << "\n";
	fileOut << ball.S_MAX << "\n";
	fileOut << ball.V_MIN << "\n";
	fileOut << ball.V_MAX << "\n";
	fileOut << ball.M_MID_high << "\n";
	fileOut << ball.M_MID_low << "\n";
	fileOut << ball.M_SIDE_high << "\n";
	fileOut << ball.M_SIDE_low;
	fileOut.close();
  
  // Write calibration data out
	fileOut.open("/home/pi/soccer/calibrateGoal_blue.txt");
	fileOut << goal_blue.H_MIN << "\n";
	fileOut << goal_blue.H_MAX << "\n";
	fileOut << goal_blue.S_MIN << "\n";
	fileOut << goal_blue.S_MAX << "\n";
	fileOut << goal_blue.V_MIN << "\n";
	fileOut << goal_blue.V_MAX << "\n";
	fileOut << ball.M_MID_high << "\n";
	fileOut << ball.M_MID_low << "\n";
	fileOut << ball.M_SIDE_high << "\n";
	fileOut << ball.M_SIDE_low;
	fileOut.close();
  
  // Write calibration data out
	fileOut.open("/home/pi/soccer/calibrateGoal_yellow.txt");
	fileOut << goal_yellow.H_MIN << "\n";
	fileOut << goal_yellow.H_MAX << "\n";
	fileOut << goal_yellow.S_MIN << "\n";
	fileOut << goal_yellow.S_MAX << "\n";
	fileOut << goal_yellow.V_MIN << "\n";
	fileOut << goal_yellow.V_MAX << "\n";
	fileOut << ball.M_MID_high << "\n";
	fileOut << ball.M_MID_low << "\n";
	fileOut << ball.M_SIDE_high << "\n";
	fileOut << ball.M_SIDE_low;
	fileOut.close();
  

	printf( "[*] Release\n" );
	cam.release();
	printf( "[*] Finished!\n" );

	return 0;
}


bool loadCalibration(bool isBall, bool isGoal_yellow, calPar_t *par) {
  
  std::ifstream fileIn;
  
	if ( isBall )
  {
    printf( "[*] Open calibrationBall file\n" );
    fileIn.open("/home/pi/soccer/calibrateBall.txt"); 
    if( !fileIn.is_open() ) 
    {
      printf( "[*] Error: Failed to open calibrationBall file\n" );
      return false;
    }
  }	
  else if (isGoal_yellow)
  {
    printf( "[*] Open calibrationGoal_yellow file\n" );
    fileIn.open( "/home/pi/soccer/calibrateGoal_yellow.txt" );
    if( !fileIn.is_open() ) 
    {
      printf( "[*] Error: Failed to open calibrationGoal_yellow file\n" );
      return false;
    }
  }
  else
  {
    printf( "[*] Open calibrationGoal_blue file\n" );
    fileIn.open( "/home/pi/soccer/calibrateGoal_blue.txt" );
    if( !fileIn.is_open() ) 
    {
      printf( "[*] Error: Failed to open calibrationGoal_blue file\n" );
      return false;
    }
  }
	std::string line = "EMPTY";
	size_t val;
	for( int i = 0; i < 10; i++ ) {
		if( !std::getline( fileIn, line ) ) {
			printf( "[*] Error: Calibration file wrong format\n" );
			return false;
		} 
			
		val = std::stoi( line.c_str(), &val );
		switch( i ) {
			case 0:
				par->H_MIN = val;
				printf( "H_MIN: %d\n", par->H_MIN );
				break;
			case 1:
				par->H_MAX = val;
				printf( "H_MAX: %d\n", par->H_MAX );
				break;
			case 2:
				par->S_MIN = val;
				printf( "S_MIN: %d\n", par->S_MIN );
				break;
			case 3:
				par->S_MAX = val;
				printf( "S_MAX: %d\n", par->S_MAX );
				break;
			case 4:
				par->V_MIN = val;
				printf( "V_MIN: %d\n", par->V_MIN );
				break;
			case 5:
				par->V_MAX = val;
				printf( "V_MAX: %d\n", par->V_MAX );
				break;
			case 6:
				par->M_MID_high = val;
				printf( "M_MID_high: %d\n", par->M_MID_high );
				break;
			case 7:
				par->M_MID_low = val;
				printf( "M_MID_low: %d\n", par->M_MID_low );
				break;
			case 8:
				par->M_SIDE_high = val;
				printf( "M_SIDE_high: %d\n", par->M_SIDE_high );
				break;
			case 9:
				par->M_SIDE_low = val;
				printf( "M_SIDE_low: %d\n", par->M_SIDE_low );
				break;
		}
	}
	
	fileIn.close();
	
	return true;
}
