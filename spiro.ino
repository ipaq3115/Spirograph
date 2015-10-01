
#include <PiWatch.h>
#include <SdFat.h>
#include <myUtils.h>

PiWatch watch;

void setup() {

    // Serial.begin(0);
    // while(!Serial);
    // delay(200);

    watch.init();
    
    watch.setColor(GREEN);
    
    watch.setBrightness(100);

}

int cx = 110;
int cy = 110;

int circle0 = 0;
int circle1 = 0;

int lastX = -1,lastY = -1;

int color = 0;

void loop() {

    int tmpX, tmpY;

    orbitPoint(cx, cy, circle0, 80, tmpX, tmpY);
    
    Serial.printf("tmpX %d tmpY %d ", tmpX, tmpY);
    
    circle0++;
    if(circle0 == 360) circle0 = 0;
    
    int tmpXa, tmpYa;
    
    tmpXa = tmpX;
    tmpYa = tmpY;
    
    orbitPoint(tmpXa, tmpYa, circle1, 20, tmpX, tmpY);
    
    Serial.printf("tmpXa %d tmpYa %d %d %d\r\n", tmpX, tmpY, tmpXa - tmpX, tmpYa - tmpY);
    
    circle1 += 13;
    if(circle1 >= 360) circle1 = 0;
    
    if(lastX != -1) watch.drawLine(lastX, lastY, tmpX, tmpY);
    
    lastX = tmpX;
    lastY = tmpY;
    
    watch.setColor(color+=3);
    
    delay(1);

    if(analogRead(PIN::POWER_BUTTON) > 127) watch.powerDown();
    
}


void orbitPoint(int x, int y, int angle, int radius, int &returnX, int &returnY) {

	angle -= 180;

	int xoffset = sin(degreestoradians(angle)) * radius;
	int yoffset = cos(degreestoradians(angle)) * radius;
	
	returnX = xoffset + x;
	returnY = yoffset + y;
	

}

float degreestoradians(float degreesToConvert){
  
  float pi = 3.14159265,divide = 180.0;
  
  return degreesToConvert * pi / divide;

}

float radianstodegrees(float radiansToConvert){
  
  float pi = 3.14159265, divide = 180.0;
  
  return radiansToConvert * (divide / pi);

}
