#define trigL 4
#define trigR 5
#define trigF 6

#define echoL 7
#define echoR 8
#define echoF 9

#define m1f 26//motor 1 forward   (N1)
#define m1b 28//motor 1 backward  (N2)
#define m2f 22//motor 2 forward   (N3)
#define m2b 24//motor 2 backward  (N4)

#define m1e 11   //motor 1 enable  (ENA)
#define m2e 10  //motor 2 enable  (ENB)

#define s0f 46
#define s1f 47
#define s2f 48
#define s3f 49
#define outf 50

#define s0u 38
#define s1u 39
#define s2u 40
#define s3u 41
#define outu 42

#define irL1 30
#define irL2 31
#define irC 32
#define irR1 34
#define irR2 33

#include<Servo.h>


Servo left;
Servo right;
Servo arm;

int x,y;
int t=50;
int time=3000;

int steps=0,disL,disR,disF;
int fullSpeedm1=250,minSpeedm1=180,fullSpeedm2=255,minSpeedm2=180;
int delayTime=500,range=25,turn=11,forwardK=30;
boolean c=0,state=1,mode=0;

int redu=0,greenu=0,blueu=0;
int redf=0,greenf=0,bluef=0;
int colourDis;

void setup() {
  pinMode(irL1,INPUT);
  pinMode(irL2,INPUT);
  pinMode(irC,INPUT);
  pinMode(irR1,INPUT);
  pinMode(irR2,INPUT);
  
  pinMode(trigL,OUTPUT);
  pinMode(trigR,OUTPUT);
  pinMode(trigF,OUTPUT);
  pinMode(echoL,INPUT);
  pinMode(echoR,INPUT);
  pinMode(echoF,INPUT);

  pinMode(m1f,OUTPUT);
  pinMode(m1b,OUTPUT);
  pinMode(m2f,OUTPUT);
  pinMode(m2b,OUTPUT);
  
  pinMode(m1e,OUTPUT);
  pinMode(m2e,OUTPUT);

  pinMode(14,INPUT);

  pinMode(s0f,OUTPUT);
  pinMode(s1f,OUTPUT);
  pinMode(s2f,OUTPUT);
  pinMode(s3f,OUTPUT);
  pinMode(outf,INPUT);

  digitalWrite(s0f,HIGH);
  digitalWrite(s1f,LOW);

  pinMode(s0u,OUTPUT);
  pinMode(s1u,OUTPUT);
  pinMode(s2u,OUTPUT);
  pinMode(s3u,OUTPUT);
  pinMode(outu,INPUT);

  digitalWrite(s0u,LOW);
  digitalWrite(s1u,HIGH);

  
  left.attach(2);
  right.attach(3);
  arm.attach(12);
  
// 90= left lanwee,  180= left aathwee
// 90= right lanwee, 0= right aathwee 

  arm.write(45);
  left.write(120);
  right.write(60);
  up();
  Serial.begin(9600);
}

void loop() {

  colDis();
  getDistance();
  
  printDistance();
  if(mode==0){
  
  forward();
  
  
  if(disL<range && disR<range){
    bal();
  }

  if(disF<6 && disL>range && disR<range){
    stp(delayTime);
    turnLeft(2,turn);
    stp(delayTime);
    forwardAndStop(forwardK);
  }
  if(disF<6 && disL<range && disR>range){
    stp(delayTime);
    turnRight(2,turn);
    stp(delayTime);
    forwardAndStop(forwardK);
  }
  if(disF<6 && disL>range && disR>range){
    stp(delayTime);
    turnLeft(2,turn);
    stp(delayTime);
    forwardAndStop(forwardK);
  }
  if(disF<6 && disL<range && disR<range){
    stp(delayTime);
    turnLeft(2,2*turn);
    stp(delayTime);
    forwardAndStop(forwardK);
  }
  
  if(disF>6 && disL>range && disR<range){
    forwardAndStop(25);
    stp(delayTime);
    turnLeft(2,turn);
    stp(delayTime);
    forwardAndStop(forwardK);
  }
  
  }
  
  if(colourDis<380){
    mode=1;
    for(int i;i<100;i++){
    if(disF>4){
      forward(200);
    }
    if(disF<3){
      backward(200);
    }
    if(disF==3){
      stp();
      //delay(100);
    }
    }
    load();
    delay(1000);
    unload();
    
  }
}

void lineFollow(){
  if(!digitalRead(irL1) && digitalRead(irL2) && digitalRead(irR2) && !digitalRead(irR1)){
    forward();
  }
  if(!digitalRead(irL1) && !digitalRead(irL2) && digitalRead(irR2) && !digitalRead(irR1)){
    turnLeft(3);
  }
  if(!digitalRead(irL1) && digitalRead(irL2) && !digitalRead(irR2) && !digitalRead(irR1)){
    turnRight(3);
  }
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

void bal(){
  if(disL>disR){
      turnLeft(3);
    }
    else if(disL<disR){
      turnRight(3);
     }
    else if(disL==disR){
      forward();
    }
}

void printDistance(){
  Serial.print(disL);
  Serial.print(" ");
  Serial.print(disF);
  Serial.print(" ");
  Serial.println(disR);
}
////////////////////////////////////
/////Count steps from encorder/////
////////////////////////////////////
int getSteps(){

  if(digitalRead(14)==HIGH && c==0){
    steps=steps+1;
    c=1;
  }
  else if(digitalRead(14)==LOW && c==1){
    steps=steps+1;
    c=0;
  }
  //Serial.println(steps);
  return steps;
}

void getDistance(){
  digitalWrite(trigL,LOW);
  delayMicroseconds(2);
  digitalWrite(trigL,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigL,LOW);

  float t=pulseIn(echoL,HIGH);
  disL =t/29/2.0;

  if(disL>=60){
    disL=60;
  }

  digitalWrite(trigR,LOW);
  delayMicroseconds(2);
  digitalWrite(trigR,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigR,LOW);

  t=pulseIn(echoR,HIGH);
  disR =t/29/2.0;
  if(disR>=60){
    disR=60;
  }

  digitalWrite(trigF,LOW);
  delayMicroseconds(2);
  digitalWrite(trigF,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigF,LOW);

  t=pulseIn(echoF,HIGH);
  disF =t/29/2.0;
  if(disF>=60){
    disF=60;
  }
  
}
////////////////////////////////////
///////forward and backward/////////
////////////////////////////////////
void forward(){
  digitalWrite(m2f,HIGH);
  digitalWrite(m1f,HIGH);
  digitalWrite(m1b,LOW);
  digitalWrite(m2b,LOW);
  analogWrite(m1e,fullSpeedm1);
  analogWrite(m2e,fullSpeedm2);
}

void forward(int x){
  digitalWrite(m2f,HIGH);
  digitalWrite(m1f,HIGH);
  digitalWrite(m1b,LOW);
  digitalWrite(m2b,LOW);
  analogWrite(m1e,x);
  analogWrite(m2e,x);
}

void backward(){
  digitalWrite(m2f,LOW);
  digitalWrite(m1f,LOW);
  digitalWrite(m1b,HIGH);
  digitalWrite(m2b,HIGH);
  analogWrite(m1e,fullSpeedm1);
  analogWrite(m2e,fullSpeedm2);
}
void backward(int x){
  digitalWrite(m2f,LOW);
  digitalWrite(m1f,LOW);
  digitalWrite(m1b,HIGH);
  digitalWrite(m2b,HIGH);
  analogWrite(m1e,x);
  analogWrite(m2e,x);
}
////////////////////////////////////turnLeft(3);
void turnLeft(int x){
  if(x==2){
    digitalWrite(m2f,HIGH);
    digitalWrite(m1f,LOW);
    digitalWrite(m1b,HIGH);
    digitalWrite(m2b,LOW);
    analogWrite(m1e,fullSpeedm1);
    analogWrite(m2e,fullSpeedm2);
  }
  else if(x==1){
    digitalWrite(m2f,HIGH);
    digitalWrite(m1f,LOW);
    digitalWrite(m1b,LOW);
    digitalWrite(m2b,LOW);
    analogWrite(m1e,fullSpeedm1);
    analogWrite(m2e,fullSpeedm2);
  }
  else if(x==3){
    digitalWrite(m2f,HIGH);
    digitalWrite(m1f,HIGH);
    digitalWrite(m1b,LOW);
    digitalWrite(m2b,LOW);
    analogWrite(m1e,fullSpeedm1);
    analogWrite(m2e,minSpeedm2);
  }
}

void turnRight(int x){
  if(x==2){
    digitalWrite(m2f,LOW);
    digitalWrite(m1f,HIGH);
    digitalWrite(m1b,LOW);
    digitalWrite(m2b,HIGH);
    analogWrite(m1e,fullSpeedm1);
    analogWrite(m2e,fullSpeedm2);
  }
  else if(x==1){
    digitalWrite(m2f,LOW);
    digitalWrite(m1f,HIGH);
    digitalWrite(m1b,LOW);
    digitalWrite(m2b,LOW);
    analogWrite(m1e,fullSpeedm1);
    analogWrite(m2e,fullSpeedm2);
  }
  else if(x==3){
    digitalWrite(m2f,HIGH);
    digitalWrite(m1f,HIGH);
    digitalWrite(m1b,LOW);
    digitalWrite(m2b,LOW);
    analogWrite(m2e,fullSpeedm2);
    analogWrite(m1e,minSpeedm1);
  }
  
}
////////////////////////////////////turnLeft(2,20);
void turnLeft(int x,int y){
    steps=0;
    state=1;
    if(state==1){
    while(steps<=y){
      getSteps();

    if(x==2){
      digitalWrite(m2f,HIGH);
      digitalWrite(m1f,LOW);
      digitalWrite(m1b,HIGH);
      digitalWrite(m2b,LOW);
      analogWrite(m1e,fullSpeedm1);
      analogWrite(m2e,minSpeedm2);
    }
    else if(x==1){
      digitalWrite(m2f,HIGH);
      digitalWrite(m1f,LOW);
      digitalWrite(m1b,LOW);
      digitalWrite(m2b,LOW);
      analogWrite(m1e,fullSpeedm1);
      analogWrite(m2e,minSpeedm2);
    }
    }
    }
    if(steps>=y){
      stp();
      state=0;
    }
}

void turnRight(int x,int y){
    steps=0;
    state=1;
    if(state==1){
    while(steps<=y){
      getSteps();
    if(x==2){
    digitalWrite(m2f,LOW);
    digitalWrite(m1f,HIGH);
    digitalWrite(m1b,LOW);
    digitalWrite(m2b,HIGH);
    analogWrite(m1e,fullSpeedm1);
      analogWrite(m2e,minSpeedm2);
    }
    else if(x==1){
    digitalWrite(m2f,LOW);
    digitalWrite(m1f,HIGH);
    digitalWrite(m1b,LOW);
    digitalWrite(m2b,LOW);
    analogWrite(m1e,fullSpeedm1);
    analogWrite(m2e,minSpeedm2);
    }
    }
    }
    if(steps>=y){
      stp();
      state=0;
    }
}

void forwardAndStop(int y){
    steps=0;
    state=1;
    if(state==1){
    while(steps<=y){
    getSteps();
    digitalWrite(m2f,HIGH);
    digitalWrite(m1f,HIGH);
    digitalWrite(m1b,LOW);
    digitalWrite(m2b,LOW);
    analogWrite(m1e,fullSpeedm1);
    analogWrite(m2e,fullSpeedm2);
    }
    }
    if(steps>=y){
      stp();
      state=0;
    }
}
////////////////////////////////////
void stp(){
  digitalWrite(m2f,LOW);
  digitalWrite(m1f,LOW);
  digitalWrite(m1b,LOW);
  digitalWrite(m2b,LOW);
}

void stp(int x){
  digitalWrite(m2f,LOW);
  digitalWrite(m1f,LOW);
  digitalWrite(m1b,LOW);
  digitalWrite(m2b,LOW);
  delay(x);
}
////////////////////////////////////

int colourSD(){
  digitalWrite(s2u,LOW);
  digitalWrite(s3u,LOW);

  redu=pulseIn(outu,LOW);
  redu=map(redu,350,220,0,255);
  if(redu<=0){
    redu=0;
  }
  if(redu>=255){
    redu=255;
  }
  /*Serial.print("Red u= ");
  Serial.print(redu);
  Serial.print("  ");*/

  //delay(100);
  
  digitalWrite(s2u,HIGH);
  digitalWrite(s3u,HIGH);

  greenu=pulseIn(outu,LOW);
  greenu=map(greenu,350,220,0,255);
  if(greenu<=0){
    greenu=0;
  }
  if(greenu>=255){
    greenu=255;
  }
  /*Serial.print("Green u= ");
  Serial.print(greenu);
  Serial.print("  ");*/
  
  digitalWrite(s2u,LOW);
  digitalWrite(s3u,HIGH);
  
  blueu=pulseIn(outu,LOW);
  blueu=map(blueu,350,170,0,255);
  if(blueu<=0){
    blueu=0;
  }
  if(blueu>=255){
    blueu=255;
  }
  /*Serial.print("Blue u= ");
  Serial.print(blueu);
  Serial.print("  ");*/

  if(redu>greenu && redu>blueu){
    Serial.print("  Red u");
  }
  if(greenu>redu && greenu>blueu){
    Serial.print("  Green u");
  }
  if(blueu>redu && blueu>greenu){
    Serial.print("  Blue u");
  }
  if(blueu==0 && redu==0 && greenu==0){
    Serial.print("  white u");
  }
}

void colourSF(){
  digitalWrite(s2f,LOW);
  digitalWrite(s3f,LOW);

  redf=pulseIn(outf,LOW);
  redf=map(redf,350,25,0,255);
  if(redf<=0){
    redf=0;
  }
  if(redf>=255){
    redf=255;
  }
  /*Serial.print("Red f= ");
  Serial.print(redf);
  Serial.print("  ");*/

  //delay(100);
  
  digitalWrite(s2f,HIGH);
  digitalWrite(s3f,HIGH);

  greenf=pulseIn(outf,LOW);
  greenf=map(greenf,400,120,0,255);
  if(greenf<=0){
    greenf=0;
  }
  if(greenf>=255){
    greenf=255;
  }
  /*Serial.print("Green f= ");
  Serial.print(greenf);
  Serial.print("  ");*/

  //delay(100);

  digitalWrite(s2f,LOW);
  digitalWrite(s3f,HIGH);

  bluef=pulseIn(outf,LOW);
  
  bluef=map(bluef,300,25,0,255);
  if(bluef<=0){
    bluef=0;
  }
  if(bluef>=255){
    bluef=255;
  }
  /*Serial.print("Blue f= ");
  Serial.print(bluef);
  Serial.print("  ");*/

  if(redf>greenf && redf>bluef){
    Serial.print("  Red f");
  }
  if(greenf>redf && greenf>bluef){
    Serial.print("  Green f");
  }
  if(bluef>redf && bluef>greenf){
    Serial.print("  Blue f");
  }
  if(bluef==0 && redf==0 && greenf==0){
    Serial.print("  white f");
  }
  
}

void colDis(){
  digitalWrite(s2f,LOW);
  digitalWrite(s3f,HIGH);

  bluef=pulseIn(outf,LOW);
  colourDis=bluef;
  Serial.print(colourDis);
  Serial.print("  ");
}
