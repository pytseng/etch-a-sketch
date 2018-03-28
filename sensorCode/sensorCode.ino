//#define SENSORPINA A0 // x axis
#define verticalPin A0
#define horizontalPin A1
#include <Adafruit_LSM303_U.h>
#include <Adafruit_LSM303.h>
int accelRead=0;
String vertical = "";
String horizontal = "";
String dataString = "";

unsigned long targetTime=0;
const unsigned long interval=2500; //TODO: How fast should we read
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);

void setup(){
    #ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif
  Serial.begin(115200);
  Serial.println("Accelerometer Test"); Serial.println("");

  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }

// TODO: begin the serial connection with a baudrate of 115200
}

void shakeErase()  // Use Accelerometer to clear the drawing.
{
    sensors_event_t event;
  accel.getEvent(&event);

  accelRead = event.acceleration.y;
//  Serial.print(accelRead);

  if(abs(accelRead) > 5)        
    Serial.println("rst"); //This is where the clear function will be triggered
}


void loop(){

  
	if(millis()>=targetTime){
		targetTime= millis()+interval;
//		Serial.println(analogRead(SENSORPINA));

		 //TODO: Add other sensor read outs
     //TODO: convert values into a string https://www.arduino.cc/en/Tutorial/StringConstructors
        vertical =  String(analogRead(verticalPin), DEC);
        horizontal =  String(analogRead(horizontalPin), DEC);
    
		 //TODO: combine them into a string that can be understood by server.js
        dataString = horizontal + "," + vertical;
        
		 //TODO: send the string over serial
        Serial.println(dataString);

	}
	// TODO: Detect if you want to reset the screen(shake the etch-a-sketch)
  // TODO: write the reset message(see server.js) to the serial port

  shakeErase();
  delay(100);
}
