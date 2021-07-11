#include <Adafruit_NeoPixel.h>
#include <iarduino_RTC.h>
  
iarduino_RTC watch(RTC_DS1307);  // Объявляем объект watch для модуля на базе чипа DS1307

Adafruit_NeoPixel Hour1 (16, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel Hour3 (48, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel HS1 (16, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel Layer2 (32, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel Layer3 (32, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel Layer4 (64, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel Layer (64, 9, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel Min1 (16, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel Min3 (48, 9, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel Sec1 (16, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel Sec3 (48, 9, NEO_GRB + NEO_KHZ800);

uint32_t myTimer1=0, myTimer2=0, myTimer3=0, previousTime=0;
int ser=0, k=3;
int Hou = 0;    // start time
int Min = 0;
int Sec = 0;
#define VOL 255

void setup() {

for(int i=0; i<64; i++) { Layer.setPixelColor(i, 0, 0, 0); }
for(int i=0; i<64; i++) { HS1.setPixelColor(i, 200, 200, 200); }
for(int i=0; i<5; i++) {
      Hour1.setPixelColor(i, 250, 0, 0);
     Hour3.setPixelColor(i+32, 250, 0, 0);
    }
      for(int i=13; i<16; i++){HS1.setPixelColor(i, 150, 150, 250);}
    for(int i=5; i<13; i++) {
      Min1.setPixelColor(i, 0, 250, 0);
      Min3.setPixelColor(i+32, 0, 250, 0);
    }  
    for(int i=13; i<16; i++)  {
      Sec1.setPixelColor(i, 0, 0, 250);
     Sec3.setPixelColor(i+32, 0, 0, 250); 
    }
    for(int i=17; i<31; i++) {  Layer2.setPixelColor(i, 150, 150, 0); }
      for(int i=17; i<27; i++) {  Layer3.setPixelColor(i, 150, 150, 0); } 
    
Layer.begin();
Layer.show(); 
Layer2.begin();
Layer2.show(); 
Layer3.begin();
Layer3.show();
Layer4.begin();
Layer4.show(); 
  
Hour1.begin();
Hour1.show(); 
Hour3.begin();
Hour3.show(); 
HS1.begin();
HS1.show();

Min1.begin();
Min1.show(); 
Min3.begin();
Min3.show(); 
 
Sec1.begin();
Sec1.show(); 
Sec3.begin();
Sec3.show(); 

 Serial.begin(9600);
watch.begin();
}

void loop() {

         watch.gettime();
        Sec = watch.seconds;
        Min = watch.minutes;
        Hou = watch.hours;
        
if (digitalRead(A0)==HIGH) {
  delay(5000);
while(true)
  {

if (millis() >= (previousTime)) 
  {
     previousTime = previousTime + 1000;
     Sec ++;
     if (Sec == 60)
     {
        Sec = 0;
        Min ++;
     }
     if (Min == 60)
     {
        Min = 0;
        Hou ++;
     }
     if (Hou == 12)
     {
        Hou = 0;
     }   
      }   
     int n=0;
while(digitalRead(A0)==LOW){ }
if(Serial.available()){ 
   int ser = Serial.read(); 
    if(ser=='L'){k=1;}
    if(ser=='R'){k=2;} // change for speed
    if(ser=='C'){k=3;}
     }
while(n<60){


   if(k==1){ PrintLayer(n);}
    if(k==2){ rainbowCycle(3);} // change for speed
    if(k==3){ PrintClock1(n);}
       n++;
delayMicroseconds(700); 
    }
   }
  }
}



          //-------функции--------------


void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<16; i++) {
      Layer4.setPixelColor(i, c);
       Layer4.setPixelColor(i+16, c);
        Layer4.setPixelColor(i+32, c);
         Layer4.setPixelColor(i+48, c);
      Layer4.show();
      delay(wait);
  }
}
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  for(j=0; j<(VOL+1)*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< 16; i++) {
      Layer4.setPixelColor(i, Wheel(((i * (VOL+1) / Layer4.numPixels()) + j) & VOL));
       Layer4.setPixelColor(i+16, Wheel(((i * (VOL+1) / Layer4.numPixels()) + j) & VOL));
        Layer4.setPixelColor(i+32, Wheel(((i * (VOL+1) / Layer4.numPixels()) + j) & VOL));
         Layer4.setPixelColor(i+48, Wheel(((i * (VOL+1) / Layer4.numPixels()) + j) & VOL));

    }
    Layer4.show();
    delay(wait);
  }
}
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < (VOL/3)) {
   return Layer4.Color(WheelPos * 3, VOL - WheelPos * 3, 0);
  } else if(WheelPos < (VOL*2/3)) {
   WheelPos -= (VOL/3);
   return Layer4.Color(VOL - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= (VOL*2/3);
   return Layer4.Color(0, WheelPos * 3, VOL - WheelPos * 3);
  }
}


void PrintLayer(int n )
{
  if(n%2==1){
      Layer2.show();
  delayMicroseconds(600);
  Layer.show();
  }
    if(n%2==0){
      Layer3.show();
  delayMicroseconds(600);
  Layer.show();
  }
}

void PrintClock1(int n )
{
  if(n == Hou*5 && n==Sec){
  HS1.show();
  delayMicroseconds(400); 
  Layer.show(); 
}
  if(n == Hou*5 && n==Min){
  HS1.show();
  delayMicroseconds(400); 
  Layer.show(); 
}  

  if(n == Min && n==Sec){
  HS1.show();
  delayMicroseconds(400);
  Layer.show();

}   

if(n == Hou*5){
  Hour1.show();
  delayMicroseconds(600);
  Layer.show();
}

 if(n == Min)  {
   Min1.show(); 
   delayMicroseconds(400); 
   Layer.show();
  }
   
   if(n == Sec){
    Sec1.show(); 
    delayMicroseconds(500);
    Layer.show();
   }
      
   if(n!=Sec || n!=Min || n!=Hou*5){
    delayMicroseconds(600);
   }    
}
