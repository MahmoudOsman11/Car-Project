#include <Servo.h>
#define motora1 8
#define motora2 9
#define motorb1 10
#define motorb2 11
#define trig 2
#define echo 3
#define Self_Driving_Distance 30
Servo myServo;
int time1=0;
char key;
bool ultraActive=0,Self_Avoid=0;
unsigned long long int timer1=0,timer2=0,timer3=0,timer4=0;
unsigned int position1=90,fowrwardDistance=100,leftDistance=100,rightDistance=100; 
unsigned int rightDistance_Self=100,leftDistance_Self=100,maxd=0,fowrward_Self=0;
int count=0;
unsigned int count3=0;

///function declerations

void forward();
void back();
void right();
void left();
void stop1();
unsigned int distance();
void Self_Drive(unsigned int *count3,unsigned int *rightDistance,unsigned int *leftDistance,unsigned int *maxd,unsigned int *fowrward);
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
  if(key=='M')  //Press M via Bluetooth to active radar
  {
    ultraActive=1;
    Self_Avoid=0;
  }
  if(key=='O')     //Press M via Bluetooth to disable radar
  {
    ultraActive=0;
    Self_Avoid=0;
  }
  if(key=='S'){   //Press S via Bluetooth to active Self avoiding collision
    ultraActive=1;
    Self_Avoid=1;
    
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
if(ultraActive==1 &&Self_Avoid ==0){
  ///radar movement (90 ->> 180 ->>90 ->> 0) 
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
///Store the distance in all directions
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
///Take action to disable direction that will make collide
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
  ///If the road is clear so move anywhere without limits
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
 if(Self_Avoid==1){
  count++;
  Self_Drive(&count3,&rightDistance_Self,&leftDistance_Self,&maxd,&fowrward_Self);
    
  }

 count=0;

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

  unsigned int distance()
  {
   unsigned int  distance=0;
    digitalWrite(trig,LOW);
    delayMicroseconds(5);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    time1=pulseIn(echo,HIGH);
    distance=time1*(0.0343/2);
    return distance;
    
    
  }
  void Self_Drive(unsigned int *count3,unsigned int *rightDistance,unsigned int *leftDistance,unsigned int *maxd,unsigned int *fowrward){
    
    myServo.write(90);
    delay(100);
    *fowrward=distance();
    if(*fowrward>=Self_Driving_Distance){
      forward();
      *count3=0;
      
    }
    else {
    {
      if(*count3==0){
      stop1();
      myServo.write(160);
      delay(500);
      *leftDistance=distance();
      myServo.write(40);
      delay(500);
      *rightDistance=distance();
       if(*rightDistance>=Self_Driving_Distance || *leftDistance >=Self_Driving_Distance)
    {
      if(max(*rightDistance,*leftDistance)==*rightDistance)
      {
        *maxd=*rightDistance;
      }
      else if(max(*rightDistance,*leftDistance)==*leftDistance)
      {
        *maxd=*leftDistance;
      }
      else{
        stop1();
    }
    
  }
  *count3=1;
    }
    
    if(*maxd==*rightDistance &&*fowrward<Self_Driving_Distance){
      right();
    }
    else if(* maxd==*leftDistance&&*fowrward<Self_Driving_Distance){
      left();
    }
    else{
      stop1();
    }
  }
  }
  }
