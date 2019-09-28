#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library
 //motor module pins
const int channel_a_enable  = 6;
const int leftwheel_input_1 = 4;
const int leftwheel_input_2 = 7;
const int channel_b_enable  = 5;
const int rightwheel_input_3 = 3;
const int rightwheel_input_4 = 2;

 //Ultrasonic sensor pins
#define TRIG 9
#define ECHO 10

#define maximum_distance 100
boolean goesForward = false;
int distance = 100;
int reverse_distance = 0;

  

NewPing sonar(TRIG, ECHO, maximum_distance); //sensor function
//Servo servo_motor; //our servo name

boolean fire = false;
//connect PUMP to Digital Pin 8
//#define pump 8
//Connect IR sensore TO Digital Pin 9
//#define f_sensore 9

void setup(){
  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);    //GND for ultrasonic
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);    //5V for ultrasonic
  
  pinMode( channel_a_enable, OUTPUT );  // Channel A enable
  pinMode( leftwheel_input_1, OUTPUT ); // Channel A input 1
  pinMode( leftwheel_input_2, OUTPUT ); // Channel A input 2
  
  pinMode( channel_b_enable, OUTPUT );  // Channel B enable
  pinMode( rightwheel_input_3, OUTPUT ); // Channel B input 3
  pinMode( rightwheel_input_4, OUTPUT ); // Channel B input 4
  
  //servo_motor.attach(10); //our servo pin

  //servo_motor.write(115);
  delay(2000);
  distance = readPing();
  reverse_distance = (100 - (maximum_distance - distance));
  
//  delay(100);
//  distance = readPing();
//  delay(100);
//  distance = readPing();
//  delay(100);
//  distance = readPing();
//  delay(100);
}

void loop(){
 Serial.begin( 9600 );
 int fire = digitalRead(TRIG);
 if(fire==HIGH)
 {
   digitalWrite(ECHO,HIGH);
   fire = true;
   moveStop();
  }
  else if (fire==LOW){
    digitalWrite(ECHO,LOW);
    fire = false;
  }

  delay(50);
  
  if (distance <= 20 && (distance == (100 - (maximum_distance - distance)))){
    moveStop();
    delay(1000); 
    Serial.print("ALERT! BLOCKAGE PINPOINTED: "); Serial.print(distance); Serial.println(" CM AWAY ");
    delay(1200);
    if((100 - (maximum_distance - distance)) == distance);
    {
      Serial.print("ALERT! PIPEBOT MOVING BACK: "); Serial.print((100 - (maximum_distance - distance))); Serial.println(" CM AWAY FROM BLOCKAGE");
        moveBackward();
        delay(500);
        moveStop();

        
    
//      if(distance > 20)
//        {
//          
//          moveForward();
//          delay(1000);
//          moveStop();
//        }
    }
  }
    else {
//    distanceRight = lookRight();
//    delay(300);
//    distanceLeft = lookLeft();
//    delay(300);
  
//    if (distanceRight >= distanceLeft){
//      turnRight();
//      moveStop();
//    }
//    else{
//      turnLeft();
//      moveStop();
//    }
//  }
//  else{
  
  moveForward(); 
  Serial.print("ALERT! BLOCKAGE NOT LOCATED: "); Serial.print(distance); Serial.println(" CM");
//  
 }
    distance = readPing();
}

//int lookRight(){  
//  servo_motor.write(50);
//  delay(500);
//  int distance = readPing();
//  delay(100);
//  servo_motor.write(115);
//  return distance;
//}
//
//int lookLeft(){
//  servo_motor.write(170);
//  delay(500);
//  int distance = readPing();
//  delay(100);
//  servo_motor.write(115);
//  return distance;
//  delay(100);
//}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=100;
  }
  return cm;
}

void moveStop(){
  
  digitalWrite( leftwheel_input_1, LOW);
  digitalWrite( leftwheel_input_2, LOW);
  digitalWrite( channel_a_enable, LOW);

  digitalWrite( rightwheel_input_3, LOW);
  digitalWrite( rightwheel_input_4, LOW);
  digitalWrite( channel_b_enable, LOW);
}

void moveForward(){

  if(!goesForward){

    goesForward=true;
    
  digitalWrite( leftwheel_input_1, HIGH);
  digitalWrite( rightwheel_input_3, LOW);
  digitalWrite( channel_a_enable, HIGH);

  digitalWrite( leftwheel_input_2, LOW);
  digitalWrite( rightwheel_input_4, HIGH);
  digitalWrite( channel_b_enable, HIGH); 
  }
}

void moveBackward(){

  
  goesForward=false;
  
  digitalWrite( leftwheel_input_1, LOW);
  digitalWrite( rightwheel_input_3, HIGH);
  digitalWrite( channel_a_enable, HIGH);

  digitalWrite( leftwheel_input_2, HIGH);
  digitalWrite( rightwheel_input_4, LOW);
  digitalWrite( channel_b_enable, HIGH); 
  
}


