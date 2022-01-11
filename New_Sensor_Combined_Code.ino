#include<Servo.h>
#include<LiquidCrystal.h>
#include<dht.h>
dht DHT;
#define DHT11_PIN A0
LiquidCrystal lcd = LiquidCrystal(5,6,7,8,9,10);
int Rain_In = A1;
int Motion_input_sensor_1 =  A2;
int Motion_input_sensor_2  = A3;
int Soil_moisture_pin = A5;
int Gas_sensor_pin = A4;
int Rain_Digital_In = 2; 
int Buzz_Pin = 3;
int YELLOW = 12;
int Vibr_Pin = 4;
int RED = 13;
Servo rubo;
int motion_1 = 0;
int motion_2 = 0;

void setup() 
{
 Serial.begin(9600);
 lcd.begin(16,2);
 //pinMode(Rain_In,INPUT);
 pinMode(Motion_input_sensor_1,INPUT);
 pinMode(Motion_input_sensor_2,INPUT);
 pinMode(Soil_moisture_pin,INPUT);
 pinMode(Gas_sensor_pin,INPUT);
 pinMode(Rain_Digital_In,INPUT);
 pinMode(Buzz_Pin,OUTPUT); //for vibration sensor
 pinMode(YELLOW,OUTPUT);
 pinMode(Vibr_Pin,INPUT);
 pinMode(RED, OUTPUT);
 rubo.attach(11);
 digitalWrite(Buzz_Pin,LOW);
 digitalWrite(YELLOW,LOW);
 digitalWrite(RED,LOW);
}

void loop()
{
  Temp_and_Humid_Sensor();
  Vibration_Sensor();
  PIR_Sensor();
  Gas_Sensor_Module();
  Soil_Moisture_Sensor();
  Servo_Control();
  Rain_Sensor();
}

void Gas_Sensor_Module()
{
  int Gas_In = analogRead(Gas_sensor_pin);
  Serial.print("Gas_Val = ");
  Serial.println(Gas_In);
  if (Gas_In > 600)
  {
    digitalWrite(RED,HIGH);
  }
  else
  {
    digitalWrite(RED,LOW);
  }
  delay(100);
}

void Servo_Control()
{
 rubo.write(0);
 delay(1000);
 rubo.write(45);
 delay(1000);
 rubo.write(0);
 delay(1000);
}

void PIR_Sensor()
{
 motion_1 = digitalRead(Motion_input_sensor_1);
 motion_2 = digitalRead(Motion_input_sensor_2);
 Serial.print("Motion_1 = ");
 Serial.println(motion_1);
 Serial.print("Motion_2 = ");
 Serial.println(motion_2);
 if(motion_1 == 1 || motion_2 == 1)
 {
  digitalWrite(YELLOW,HIGH);
  delay(10); 
  digitalWrite(YELLOW,LOW);
  delay(10);
  }
 else
 {
  digitalWrite(YELLOW,LOW);
 }
 delay(100);
}

void Vibration_Sensor()
{
  long measurement = pulseIn(Vibr_Pin, HIGH);
  delay(10);
  Serial.print("Measurement = ");
  Serial.println(measurement);
  if (measurement > 1000)
  {
    digitalWrite(Buzz_Pin, HIGH);
  }
  else
  {
    digitalWrite(Buzz_Pin, LOW);
  }
 delay(10);
}

void Temp_and_Humid_Sensor()
{
  int chk = DHT.read11(DHT11_PIN); 
  lcd.setCursor(0,0);
  lcd.print("Temp = ");
  lcd.print(DHT.temperature);  
  lcd.print(" ");
  lcd.print((char)223);
  lcd.println("C  ");
  lcd.setCursor(0,1);
  lcd.print("Humidity =");
  lcd.print(DHT.humidity);
  lcd.print("%");
  delay(100);
}

/*void Soil_Moisture_Sensor()
{
// Soil Moisture Sensor
  int soil_moisture_val = analogRead(Soil_moisture_pin);
  soil_moisture_val = map(soil_moisture_val,1023,0,0,100);
  Serial.print("Moisture = ");
  Serial.print(soil_moisture_val);
  Serial.print("%");
  delay(1000);
}

void Rain_Sensor()
{
  // Rain Sensor
  int Rain_Val = analogRead(Rain_In);
  bool blsRaining = !(digitalRead(Rain_Digital_In));
  if(blsRaining)
  {
  blsRaining = "YES";
  //digitalWrite(buzz,HIGH);
  //delay(1000);
  }
  else 
  {
  blsRaining = "NO";
  }
  Serial.print("Raining?:");
  Serial.print(blsRaining);
  Serial.print(", Moisture Level:");
  Serial.println(Rain_Val);
  delay(100);
}*/
