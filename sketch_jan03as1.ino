#include <Servo.h>
Servo servo;
Servo servo_top;
int lightLevel0;
int lightLevel1;
int lightLevel2;
int lightLevel3;
int side03,side12,side23,side01;
int current_angle,desired_angle, current_angle_top, desired_angle_top;
int total_light;
int absl01,absl12,absl03,absl23;
void setup() {
  // put your setup code here, to run once:
    servo.attach(9);
    servo_top.attach(10);
    //pinMode(11,OUTPUT);
    Serial.begin(9600);
    servo.write(0);
    servo_top.write(180); 
}
void loop() {
  // put your main code here, to run repeatedly:
    lightLevel0 = analogRead(0);
    lightLevel0 = map(lightLevel0, 0, 1023, 0, 255);
    lightLevel0 = constrain(lightLevel0, 0, 255);
    //Serial.println(lightLevel0);
    
    lightLevel1 = analogRead(1);
    lightLevel1 = map(lightLevel1, 0, 1023, 0, 255);
    lightLevel1 = constrain(lightLevel1, 0, 255);
    //Serial.println(lightLevel1);
    
    lightLevel2 = analogRead(2);
    lightLevel2 = map(lightLevel2, 0, 1023, 0, 255);
    lightLevel2 = constrain(lightLevel2, 0, 255);
    //Serial.println(lightLevel2);
    
    lightLevel3 = analogRead(3);
    lightLevel3 = map(lightLevel3, 0, 1023, 0, 255);
    lightLevel3 = constrain(lightLevel3, 0, 255);
    //Serial.println(lightLevel3);
    //Serial.println();


    side03 = lightLevel0 + lightLevel3;
    side12 = lightLevel1 + lightLevel2;
    side23 = lightLevel2 + lightLevel3;
    side01 = lightLevel0 + lightLevel1;
    total_light = lightLevel0 + lightLevel1 + lightLevel2 + lightLevel3;

    absl03 = abs(side03 - side12);   //difference between 2 hortizontal sides - bigger sides
    absl12 = abs(side23 - side01);   // difference between 2 vertical sides - smaller sides
    Serial.println(absl12);
    Serial.println(absl03);
    Serial.println(total_light);
    Serial.println ("**");
    
    //First find out if there is difference in the light received by the two long sides 12 and 03
    //There is a measure called abs03 that gives that
    
    if (absl03 >10 && total_light > 75) {     //if there is difference in light received by two horizontal sides, then first find out which side is receiving more light
      
      if(side03 - side12 > 10) {               //if side03 receives more light than side12, then side03-side12 should be greater than 10
        current_angle_top = servo_top.read();  // read the current angle
        if (current_angle_top < 180) {         //if angle is less than 180, that means the side is not completely vertical, addd 5 degrees i.e. make it more vertical and see if the difference reduces
          desired_angle_top = current_angle_top + 5; //adding 5 degress
          servo_top.write(desired_angle_top); delay(500);  //writing the new angle to the servo 
        }   
      }
      if(side12 - side03 > 10) {
        current_angle_top = servo_top.read();
        if (current_angle_top >= 93) {         //if it is not completely flat
          desired_angle_top = current_angle_top - 5;   //reduce 5 degrees and make it flatter
          servo_top.write(desired_angle_top); delay(500);
        }
   
        else
        {
          current_angle = servo.read();
          if (current_angle < 180) {
            while (current_angle < 180){
             servo.write(current_angle + 5);delay(500);
              current_angle = servo.read(); 
            } 
          }
        }
      }
    
    }                                          // end of if statement checking difference in light received by 2 horizontal sides 

    if ((absl12 > 10) && (total_light > 75)) {  //checking the difference in light between two shorter sides which are 10 and 23
      if(side01 - side23 > 10) {
       current_angle = servo.read();
        if (current_angle > 2 ) {
          servo.write(current_angle - 2); delay(500);
        }
      } 
      if(side23 - side01 > 10) {  
        current_angle = servo.read();
        if (current_angle < 178) {
          servo.write(current_angle + 2); delay(500);
        } 
      }
    }                                         //end of if statement checking difference in light received by 2 vertical sides. 
  
  if(total_light < 75) {                      //if statement to check if it is dark and time to move the solar panel to face east for the morning sun
    current_angle = servo.read();
    while (current_angle > 0){
      servo.write(current_angle - 5);delay(500);
      current_angle = servo.read();
    } 
    current_angle_top = servo_top.read(); {
      while (current_angle_top < 180) {
        servo_top.write(current_angle_top + 5);delay(500);
        current_angle_top = servo_top.read();
      } 
    }
  }
    
}   // end of the void loop
