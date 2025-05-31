#include <Adafruit_CircuitPlayground.h> 
#include <AsyncDelay.h>

AsyncDelay delay_1s; //Async delay declaration for delay_1s variable

int count = -1; //initialize timer count at 0
int switchState = false;
int i = 1010; //initialize delay time at 1010 milliseconds
int randomNum;
int A_four = 440; //Source: https://canvas.oregonstate.edu/courses/2012549/pages/melodies-loops-arrays?module_item_id=25399344
float x;
float scaledX; //float value for map x values from CPX accelerometer
float midi[127]; //Source: https://canvas.oregonstate.edu/courses/2012549/pages/melodies-loops-arrays?module_item_id=25399344

const byte interruptPin = 7;
volatile bool intSwitch = false;

void toggle() {
  intSwitch = true;
}

void generateMIDI(){ //Source: https://canvas.oregonstate.edu/courses/2012549/pages/melodies-loops-arrays?module_item_id=25399344
  for (int x =  0; x < 127; ++x)
  {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
    Serial.println(midi[x]);
  }
}

void setup() {
 CircuitPlayground.begin();
 CircuitPlayground.slideSwitch();
 pinMode(7, INPUT_PULLUP);
 pinMode(A0, OUTPUT);
 analogWrite(A0, 100); //Sets volume of CPX sound box, code referenced from studio
 attachInterrupt(digitalPinToInterrupt(interruptPin), toggle, CHANGE); //Source: https://canvas.oregonstate.edu/courses/2012549/pages/interrupts-are-polite?module_item_id=25399332
 Serial.begin(9600);
 while (!Serial);
 delay_1s.start(i, AsyncDelay::MILLIS); //Source: https://canvas.oregonstate.edu/courses/2012549/pages/interrupts-are-polite?module_item_id=25399332
 CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G); //Source: https://canvas.oregonstate.edu/courses/2012549/pages/intro-to-sound-sensor-accelerometer?module_item_id=25399383
 generateMIDI(); //Source: https://canvas.oregonstate.edu/courses/2012549/pages/melodies-loops-arrays?module_item_id=25399344
}


void loop() {
  if(count >1){ //sets largest count value to 2
    delay(5);
    count = 1;
  }

  if(i<30){ //sets lowest i delay value to 30 milliseconds
    i=30;
  }

  if (switchState == true) { //if switch is true, reset count to 0, reset delay to 1010 milliseconds, clear all pixels

    count = -1;
    i=1010;
    CircuitPlayground.clearPixels();
    intSwitch = false;
  }

  if (delay_1s.isExpired()) { //after every expiration of delay, check these parameters
    delay(5);
    delay_1s.start(i, AsyncDelay::MILLIS); //Source: https://canvas.oregonstate.edu/courses/2012549/pages/interrupts-are-polite?module_item_id=25399332
    i-=10; //decrease i delay by 10 milliseconds
    count++; //increase count by 1
    Serial.print(count);
    Serial.print(", ");
    Serial.print(i);

    int randomPixel = rand() %10; //Source: https://www.w3schools.com/cpp/cpp_howto_random_number.asp
    CircuitPlayground.setPixelColor(randomPixel, 0, 0, 255);
    Serial.print(", ");
    Serial.print(randomPixel);
    
    if(randomPixel < 6){ 
      delay(700);
      x = CircuitPlayground.motionX(); //Source: https://canvas.oregonstate.edu/courses/2012549/pages/intro-to-sound-sensor-accelerometer?module_item_id=25399383
      scaledX = map(x, -10, 10, -90, 90); //rescale CPX accelerometer values to -90 to 90 degrees
      Serial.print(", ");
      Serial.println(scaledX);
      if(scaledX >0){
        count = 0;
        Serial.println("countZero");
        CircuitPlayground.clearPixels();
      }
    } else {
      delay(700);
      x = CircuitPlayground.motionX(); // Source: https://canvas.oregonstate.edu/courses/2012549/pages/intro-to-sound-sensor-accelerometer?module_item_id=25399383
      scaledX = map(x, -10, 10, -90, 90); //rescale CPX accelerometer values to -90 to 90 degrees
      Serial.print(", ");
      Serial.println(scaledX);
      if(scaledX < 0){
        count = 0;
        Serial.println("countZero");
        CircuitPlayground.clearPixels();
      }
    switchState = digitalRead(7); //read if switch is reset
    delay_1s.repeat(); //repeat delay
    }

   if (count == 2){ 
      delay(5);
      x=0.00;
      CircuitPlayground.setPixelColor(0, 255, 0, 0);
      CircuitPlayground.setPixelColor(1, 255, 0, 0);
      CircuitPlayground.setPixelColor(2, 255, 0, 0);
      CircuitPlayground.setPixelColor(3, 255, 0, 0);
      CircuitPlayground.setPixelColor(4, 255, 0, 0);
      CircuitPlayground.setPixelColor(5, 255, 0, 0);
      CircuitPlayground.setPixelColor(6, 255, 0, 0);
      CircuitPlayground.setPixelColor(7, 255, 0, 0);
      CircuitPlayground.setPixelColor(8, 255, 0, 0);
      CircuitPlayground.setPixelColor(9, 255, 0, 0); 
      count = 1; //set count equal to 2
      CircuitPlayground.playTone(midi[60], 100); 
    }
  }
}
