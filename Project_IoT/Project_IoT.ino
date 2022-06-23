#include <NewPing.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define tankTrigPin D0
#define tankEchoPin D5
#define petTrigPin D6
#define petEchoPin D7
#define bowlTrigPin D4
#define bowlEchoPin D3
#define MAX_DISTANCE 20
#define SONAR_NUM 3

#define BLYNK_TEMPLATE_ID "TMPLsYMwwJhS"
#define BLYNK_DEVICE_NAME "auto pet feeder"
#define BLYNK_AUTH_TOKEN "DVI86zxGvx4iubDqKFqRe1LsJv0uPiiU"
#define BLYNK_PRINT Serial
BlynkTimer timer;

Servo myservo;
int val;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Nadia Layra";
char pass[] = "12345678";

NewPing sonar[SONAR_NUM] = {  
  NewPing(tankTrigPin, tankEchoPin, MAX_DISTANCE),
  NewPing(petTrigPin, petEchoPin, MAX_DISTANCE), 
  NewPing(bowlTrigPin, bowlEchoPin, MAX_DISTANCE)
};
long dur1, dur2, dur3, jarak1, jarak2, jarak3;
//Tangki
void ultra1(){
  jarak1 = sonar[0].ping_cm();
  float persen1 = jarak1*100/20;
  long y1 = (persen1*-1) + 100;
  Serial.println("jarak1 :");
  Serial.print(jarak1);
  Serial.println("cm ");
  Serial.println(y1);
  Blynk.virtualWrite(V0, y1);
}
//Hewan
void ultra2(){
  jarak2 = sonar[1].ping_cm();
  float persen2 = jarak2*100/20;
  long y2 = (persen2*-1) + 100;
  Serial.println("jarak2 :");
  Serial.print(jarak2);
  Serial.println(" cm");
  Blynk.virtualWrite(V1, y2);
}
// Mangkok
void ultra3(){
  jarak3 = sonar[2].ping_cm();
  float persen3 = jarak3*100/20;
  long y3 = (persen3*-1) + 100;
  Serial.println("jarak3 :");
  Serial.print(y3);
  Serial.println(" cm");
  Blynk.virtualWrite(V2, y3);
  //servo
  if (y3 < 30){
    myservo.write(180);
    } if (y3 > 75 && y3 < 85) {
    myservo.write(0);
    }
  }

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(tankTrigPin, OUTPUT);
  pinMode(tankEchoPin, INPUT);
  pinMode(petTrigPin, OUTPUT);
  pinMode(petEchoPin, INPUT);
  pinMode(bowlTrigPin, OUTPUT);
  pinMode(bowlEchoPin, INPUT);
  timer.setInterval(100L, ultra1);
  timer.setInterval(100L, ultra2);
  timer.setInterval(100L, ultra3);
  myservo.attach(D8);
}

void loop() {
  Blynk.run();
  timer.run();
