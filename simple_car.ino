#include <Servo.h>
#define motora1 8
#define motora2 9
#define motorb1 10
#define motorb2 11
#define trig 2
#define echo 3
int time1=0;
char key;
bool ultraActive=0;
unsigned long long int timer1=0,timer2=0,timer3=0,timer4=0;
unsigned int position1=90,fowrwardDistance=100,leftDistance=100,rightDistance=100;
int count=0;
Servo myServo;
void setup() {
  Serial.begin(9600);

  pinMode(motora1,OUTPUT);
  pinMode(motora2,OUTPUT);
  pinMode(motorb1,OUTPUT);
  pinMode(motorb2,OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  myServo.attach(4);
  myServo.write(90);
  stop1();
  timer1=millis();
  timer2=millis();
  timer3=millis();
  timer4=millis();

}

void loop() {
  if(Serial.available())
  {
    key=Serial.read();
  }
  if(key=='M')
  {
    ultraActive=1;
  }
  if(key=='O')
  {
    ultraActive=0;
  }
  if(ultraActive==0)
{
    if(key=='A')
  {

  forward();

  }
  else if(key=='B')
  right();
  else if(key=='C')
  left();
  else if(key=='D')
  {
  back();

}
else{
  stop1();
}
  
}
else if(ultraActive==1){
  
if(millis()-timer1>=1100){
   myServo.write(90);
  timer1=millis();
  position1=90;
  
}
if(millis()-timer2>=2100){
   myServo.write(180);
  timer2=millis();
  position1=180;
  
}
if(millis()-timer3>=3100){
   myServo.write(90);
  timer3=millis();
  position1=90;
  
}
if(millis()-timer4>=4100){
   myServo.write(0);
  timer4=millis();
  position1=0;
  
}
else{}
if(position1==90)
{
  delay(100);
  fowrwardDistance=distance();
}
if(position1==180)
{
  delay(100);
  rightDistance=distance();
}
if(position1==0)
{
  delay(100);
  leftDistance=distance();
}
if(fowrwardDistance<=30)
  {
    count++;
   if(key=='A')
  {
    stop1();
  }
  else if(key=='B')
  right();
  else if(key=='C')
  left();
  else if(key=='D')
  {
  back();

}
else{
  stop1();
}
  }
  else if(rightDistance<=30)
  {
    count++;
   if(key=='A')
  {
    forward();
  }
  else if(key=='C')
  left();
  else if(key=='D')
  {
  back();

}
else{
  stop1();
}
  }
    else if(leftDistance<=30)
  {
    count++;
   if(key=='A')
  {
    forward();
  }
  else if(key=='B')
  right();
  else if(key=='D')
  {
  back();

}
else{
  stop1();
}
  }
if(count==0){
     if(key=='A')
  {
    forward();
  }
  else if(key=='B')
  right();
  else if(key=='C')
  left();
  else if(key=='D')
  {
  back();

}
else{
  stop1();
}
  }
  
}
 count=0;
 Serial.print("Fowrward");
  Serial.println(fowrwardDistance);
  Serial.print("right");
  Serial.println(rightDistance);
  Serial.print("left");
  Serial.println(leftDistance);
  Serial.print("****************************");
}
void forward(){
digitalWrite(motora1,HIGH);
digitalWrite(motora2,LOW);
digitalWrite(motorb1,HIGH);
digitalWrite(motorb2,LOW);

  }
void back(){
digitalWrite(motora1,LOW);
digitalWrite(motora2,HIGH);
digitalWrite(motorb1,LOW);
digitalWrite(motorb2,HIGH);

  }
void right(){
digitalWrite(motora1,LOW);
digitalWrite(motora2,HIGH);
digitalWrite(motorb1,HIGH);
digitalWrite(motorb2,LOW);

  }
void left(){
digitalWrite(motora1,HIGH);
digitalWrite(motora2,LOW);
digitalWrite(motorb1,LOW);
digitalWrite(motorb2,HIGH);

  }
void stop1(){
digitalWrite(motora1,LOW);
digitalWrite(motora2,LOW);
digitalWrite(motorb1,LOW);
digitalWrite(motorb2,LOW);

  }

  double distance()
  {
    double distance=0;
    digitalWrite(trig,LOW);
    delayMicroseconds(5);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    time1=pulseIn(echo,HIGH);
    distance=time1*(0.0343/2);
    return distance;
    
    

    
  }
