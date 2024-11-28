#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "SoftPWM.h"
RF24 radio(9, 10); const uint64_t address = 0x1A2B3C4D5ELL;
int period = 120;
unsigned long time_now = 0;
int receivedData[3] ={512,512,1};
int ch1_value = 0;
int ch2_value = 0;
int ch3_value = 0;
void reset_the_Data() {
 receivedData[0] = 512; receivedData[1] = 512;
 receivedData[2] = 1;
 SoftPWMSet(2, 0); SoftPWMSet(3, 0);
 SoftPWMSet(4, 0); SoftPWMSet(5, 0);
 }
void forwardmode(){
 if((receivedData[0] !=0) && (receivedData[1] !=0)){
 if(receivedData[0] > 530 && (receivedData[1] > 470 && receivedData[1] < 530)){
 int motor = map(receivedData[0],512,1024,50,255);
 SoftPWMSet(2, 0); SoftPWMSet(3, motor);
 SoftPWMSet(4, motor); SoftPWMSet(5, 0);
 Serial.print("fordward:");
 Serial.print(receivedData[0]);
 Serial.print(",");
 Serial.print(receivedData[1]);
 Serial.print("PWM:");
 Serial.print(motor);
 Serial.print("KICK:");
 Serial.println(receivedData[2]);
 }
 else if(receivedData[0] > 530 && (receivedData[1] < 470)){
 int motor = map(receivedData[0],512,1024,50,255);
 int turn = map(receivedData[1], 512, 0, 0, motor);
 SoftPWMSet(2, 0); SoftPWMSet(3, motor-turn);
 SoftPWMSet(4, motor); SoftPWMSet(5, 0);
 Serial.print("turn-left:");
 Serial.print(receivedData[0]);
 Serial.print(",");
 Serial.print(receivedData[1]);
 Serial.print("PWM:");
 Serial.print(motor-turn);
 Serial.print("KICK:");
 Serial.println(receivedData[2]);
 }
 else if(receivedData[0] > 530 && (receivedData[1] > 530)){
 int motor = map(receivedData[0],512,1024,50,255);
 int turn = map(receivedData[1], 512, 1024, 0, motor);
 SoftPWMSet(2, 0); SoftPWMSet(3, motor);
 SoftPWMSet(4, motor-turn); SoftPWMSet(5, 0);
 Serial.print("turn-right:");
 Serial.print(receivedData[0]);
 Serial.print(",");
 Serial.print(receivedData[1]);
 Serial.print("PWM:");
 Serial.print(motor-turn);
 Serial.print("KICK:");
 Serial.println(receivedData[2]);
 }
 }
}
void reversemode(){
 if((receivedData[0] !=512) && (receivedData[1] !=512)){
 if(receivedData[0] <= 470 && (receivedData[1] > 470 && receivedData[1] < 530)){
 int motor = map(receivedData[0],512,0,50,255);
 SoftPWMSet(3, 0); SoftPWMSet(2, motor);
 SoftPWMSet(5, motor); SoftPWMSet(4, 0);
 Serial.print("reverse:");
 Serial.print(receivedData[0]);
 Serial.print(",");
 Serial.print(receivedData[1]);
 Serial.print("PWM:");
 Serial.print(motor);
 Serial.print("KICK:");
 Serial.println(receivedData[2]);
 }
 }
}
void idlemode(){
 if((receivedData[0] !=512) && (receivedData[1] !=512)){
 if(receivedData[0] > 470 && receivedData[0] < 530 && receivedData[1] > 470 && receivedData[1] < 530 ){
 SoftPWMSet(2, 0); SoftPWMSet(3, 0);
 SoftPWMSet(4, 0); SoftPWMSet(5, 0);
 Serial.print("idlemode:");
 Serial.print(receivedData[0]);
 Serial.print(",");
 Serial.print(receivedData[1]);
 Serial.print("PWM:");
 Serial.print(0);
 Serial.print(",");
 Serial.print(0);
 Serial.print("KICK:");
 Serial.println(receivedData[2]);
 } }
}
void clockwiserotationmode(){
 if((receivedData[0] !=512) && (receivedData[1] !=512)){
 if(receivedData[1] >= 530 && (receivedData[0] > 470 && receivedData[0] < 530)){
 int motor = map(receivedData[1],512,1024,0,120);
 SoftPWMSet(2, 0); SoftPWMSet(3, motor);
 SoftPWMSet(4, 0); SoftPWMSet(5, motor);
 Serial.print("clockwise:");
 Serial.print(receivedData[0]);
 Serial.print(",");
 Serial.print(receivedData[1]);
 Serial.print("PWM:");
 Serial.print(motor);
 Serial.print("KICK:");
 Serial.println(receivedData[2]);
 }
 }
}
void anticlockwiserotationmode(){
 if((receivedData[0] !=512) && (receivedData[1] !=512)){
 if(receivedData[1] <= 470 && (receivedData[0] > 470 && receivedData[0] < 530)){
 int motor = map(receivedData[1],512,0,0,120);
 SoftPWMSet(2, motor); SoftPWMSet(3, 0);
 SoftPWMSet(4, motor); SoftPWMSet(5, 0);
 Serial.print("anticlockwise:");
 Serial.print(receivedData[0]);
 Serial.print(",");
 Serial.print(receivedData[1]);
 Serial.print("PWM:");
 Serial.print(motor);
 Serial.print("KICK:");
 Serial.println(receivedData[2]);
 }
 }
}
void shoot(){
 if((receivedData[0] !=512) && (receivedData[1] !=512)){
 if(receivedData[2] == 0){
 digitalWrite(8,HIGH);
 }
 else{
 digitalWrite(8,LOW);
 } } }
void disableshoot(){
 }
void setup()
{
 Serial.begin(9600);
 SoftPWMBegin();
 pinMode(8,OUTPUT);
 reset_the_Data();
 radio.begin();
 radio.setAutoAck(false);
 radio.setChannel(80);
 radio.setPALevel(RF24_PA_LOW);
 radio.setDataRate(RF24_250KBPS); radio.openReadingPipe(1,address);
 radio.startListening();
}
unsigned long lastRecvTime = 0;
void receive_the_data()
{
 while ( radio.available() ) {
 radio.read(&receivedData, sizeof(receivedData));
 lastRecvTime = millis(); }
}
void loop()
{
 receive_the_data();
 unsigned long now = millis();
 if ( now - lastRecvTime > 1000 ) {
 reset_the_Data();
 } forwardmode();
 reversemode();
 idlemode();
 clockwiserotationmode();
 anticlockwiserotationmode();
 shoot();
 if(millis() >= time_now + period){
 time_now += period;
 }
}
