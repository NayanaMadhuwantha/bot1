#include<Servo.h>


Servo left;
Servo right;
Servo arm;

int x,y;
int t=50;
int time=3000;

void setup() {

  left.attach(2);
  right.attach(3);
  arm.attach(4);
  
// 90= left lanwee,  180= left aathwee
// 90= right lanwee, 0= right aathwee 

arm.write(45);
left.write(120);
right.write(60);

}

void loop() {

  load();
  delay(1000);
  unload();
  delay(1000);
 
  

}

void load(){
  miss();
  delay(500);
  down();
  delay(500);
  fix();
  delay(500);
  up();
  delay(500);
}

void unload(){
  down();
  delay(500);
  miss();
  delay(500);
  up();
  delay(500);
}
void miss(){
for(x=0; x<45; x+=5){ 
  left.write(90+x);      // left aathwee 90-180, 90-135
  right.write(90-x);     // right aathwee 90-0, 90-45
  delay(t);
}
}

void fix(){
  for(x=45; x>-10; x-=5){
  left.write(90+x);      // left lanwee 180-80
  right.write(90-x);     // right lanwee 0-100
  delay(t);
}
}

void down(){
for(y=45; y<=180; y+=5){
 arm.write(y);          // up
 delay(t);
}
}

void up(){
for(y=180; y>45; y-=5){
 arm.write(y);         // down
 delay(t);
}
}

