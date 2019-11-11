#include <Ethernet.h>

#include <dht11.h>
#define DHT11PIN 4
#define led1 13
#define led2 12
#define led3 11

dht11 DHT11;
int motorPin = 9;
int buzzer = 8;


void setup() {
  
  Serial.begin(9600);
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(motorPin, OUTPUT);
 

}

void loop() 
{

  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  int sensorValue1 = analogRead(A1);
  int sensorValue2 = analogRead(A2);
  

  // getting the voltage values
  int v1 = sensorValue * (5.0 / 1023.0)*100;
  int val1 = map(temp,140 , 165, 0, 100);

  int v2 = sensorValue1 * (5.0 / 1023.0)*100;
  int val2 = map(temp,140 , 165, 0, 100);

  int v3 = sensorValue2 * (5.0 / 1023.0)*100;
  int val3 = map(temp,140 , 165, 0, 100);
   


//displaying the remperature
  int chk = DHT11.read(DHT11PIN);
  int temp =(int)DHT11.humidity;
  temp = map(temp,38 , 65, 23, 35);
  
  
  
 //logic for passive balancing

 if((v1-v2)>10){
  digitalWrite(led1, HIGH);
     delay(100);
     digitalWrite(led1, LOW);
     delay(10);
  
 }
 else if((v2-v1)>10){
  //turn on led 2
  digitalWrite(led2, HIGH);
     delay(10);
     digitalWrite(led2, LOW);
     delay(10);
  
 }

  if((v2-v3)>20){
  //trun on the led 2
  digitalWrite(led2, HIGH);
     delay(10);
     digitalWrite(led2, LOW);
     delay(10);
  
 }
 else if((v3-v2)>20){
  //turn on led 3
  digitalWrite(led3, HIGH);
     delay(10);
     digitalWrite(led3, LOW);
     delay(10);
  
 }
 


//Logic for controlling the motor if the heat is more
  if(temp>=33){
    
     digitalWrite(motorPin, HIGH);
     delay(25); 
  
  
  }
  
  else{
    
    digitalWrite(motorPin, LOW);
    
  }

if(temp>=38){
      tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(25);        // ...
  noTone(buzzer);     // Stop sound...
  delay(25);        // ...
  
 
  
  }


  Serial.print("Temperature (C): ");
  Serial.println(temp);


  Serial.print("SOC 1 = ");
  Serial.println(val1);
  
  Serial.print("SOC 2 = ");
  Serial.println(val2);
  
  //Serial.print("SOC 3 = ");
  Serial.println(val3);
    delay(500);

 
}
