#include <SPI.h>
#include <Pixy.h>
// This is the main Pixy object 
Pixy pixy;
double angleToTarget_x;
double angleToTarget_y;
double distanceToTarget;
double FOV_X = 75; //horizontal FOV in degrees
double FOV_Y = 47; //vertical FOV in degrees
double RESOLUTION_WIDTH = 320; //in pixels, 320 x 200
double RESOLUTION_HEIGHT = 200; //in pixels
double PIXEL_TO_IN = 20; //scale from height in pixels to height in inches
double CAMERA_HEIGHT = 1.5; //inches
double TARGET_HEIGHT = 2.125; //inches 


void setup()
{
  Serial.begin(9600);
  Serial.print("Starting...\n");

  pixy.init();
}

void loop()
{ 
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32]; 
  
  // grab blocks!
  blocks = pixy.getBlocks();
  
  
  // If there are detect blocks, print them!
  if (blocks)
  {
    i++;
    
    // do this (print) every 50 frames because printing every
    // frame would bog down the Arduino
    if (i%50==0)
    {
        angleToTarget_x = getHorizontalAngleOffset(pixy.blocks[0].x);
        angleToTarget_y = getVerticalAngleOffset(pixy.blocks[0].y);
        distanceToTarget = getDistance(getVerticalAngleOffset(pixy.blocks[0].y));
        
        Serial.println(angleToTarget_y);
    }

  
  }  
}

double getHorizontalAngleOffset(double x){
  return (x*FOV_X/RESOLUTION_WIDTH) - 37.5;
}

double getVerticalAngleOffset(double y) {
  return -((y*FOV_Y/RESOLUTION_HEIGHT) - 23.5);
}

double getDistance(double deg){
  return (TARGET_HEIGHT-CAMERA_HEIGHT)/tan(degreesToRadians((getVerticalAngleOffset(deg))));
}

double degreesToRadians(double deg){
  return deg * 0.0174533;
}


