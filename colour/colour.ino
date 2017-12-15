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

int redu=0,greenu=0,blueu=0;
int redf=0,greenf=0,bluef=0;
int colourDis;

void setup() {
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

  Serial.begin(9600);

}

void loop() {

  colourSD();
  Serial.print(" ");
  colourSF();
  Serial.print(" ");
  colDis();
  Serial.println(" ");
  
  
}

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
}
