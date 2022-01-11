int time1,time2,time3;
int distance1, distance2, distance3;
int soil_moisture_pin = A0;
int base_moisture = 300;
void setup() 
{
  pinMode(2,OUTPUT);  // Left Ultra 2 Trig
  pinMode(4,INPUT);   // Left Ultra 4 Echo
  pinMode(5,OUTPUT);  // Motor Side 1 PWM (Left Motors)
  pinMode(6,OUTPUT);  // Motor Side 1 PWM (Left Motors)
  pinMode(9,OUTPUT);  // Motor Side 2 PWM (Right Motors)
  pinMode(10,OUTPUT); // Motor Side 2 PWM (Right Motors)
  pinMode(7,OUTPUT);  // Center Ultra 7 Trig
  pinMode(8,INPUT);   // Center Ultra 8 Echo
  pinMode(12,OUTPUT); // Right Ultra 12 Trig
  pinMode(13,INPUT);  // Right Ultra 13 Echo
  pinMode(3,OUTPUT);  // Soil Moisture Motor
  pinMode(11,OUTPUT); //  Soil Moisture Motor
  pinMode(soil_moisture_pin,INPUT);
  Serial.begin(9600);
}
void loop()
{
  digitalWrite (2,LOW);
  delayMicroseconds(2);
  digitalWrite (2,HIGH);
  delayMicroseconds(10);
  digitalWrite(2,LOW);
  time1 = pulseIn (4, HIGH);
  distance1 = (time1 * 0.034) / 2;
  Serial.print (" Distance1= ");              
  Serial.println (distance1);
  
  digitalWrite (7,LOW);
  delayMicroseconds(2);
  digitalWrite (7,HIGH);
  delayMicroseconds(10);
  digitalWrite(7,LOW);
  time2= pulseIn (8, HIGH);
  distance2 = (time2 * 0.034) / 2;
  Serial.print (" Distance2= ");              
  Serial.println (distance2);  
   
  digitalWrite (12,LOW);
  delayMicroseconds(2);
  digitalWrite (12,HIGH);
  delayMicroseconds(10);
  digitalWrite(12,LOW);
  time3 = pulseIn (13, HIGH);
  distance3 = (time3 * 0.034) / 2;
  Serial.print (" Distance3= ");              
  Serial.println (distance3);  
   
  if ((distance1 <= 80) && (distance2 <= 80) && (distance3 <= 80))
   {
  analogWrite(5,255); 
  analogWrite(6,0);
  analogWrite(9,255);
  analogWrite(10,0);
  Serial.println("GO BACK");
   }
  else if ((distance1 <= 80) && (distance2 <= 80))
   {
  analogWrite(5,0);
  analogWrite(6,255);
  analogWrite(9,0);
  analogWrite(10,10);
  Serial.println("RIGHT TURN");
   }
   else if ((distance2 <= 80) && (distance3 <= 80))
   {
  analogWrite(5,0);
  analogWrite(6,10);
  analogWrite(9,0);
  analogWrite(10,255);
  Serial.println("LEFT TURN");
   }  
  else if (distance1 <= 80)  
  {
  analogWrite(5,0);
  analogWrite(6,255);
  analogWrite(9,0);
  analogWrite(10,10);
  Serial.println("RIGHT TURN");
   }
   else if (distance2 <= 80)
   {
  analogWrite(5,255);
  analogWrite(6,0);
  analogWrite(9,255);
  analogWrite(10,0);
  Serial.println("GO BACK");
   }
   else if (distance3 <= 80)
   {
  analogWrite(5,0);
  analogWrite(6,10);
  analogWrite(9,0);
  analogWrite(10,255);
  Serial.println("LEFT TURN");
   }
   else 
   {
  analogWrite(5,0);
  analogWrite(6,255);
  analogWrite(9,0);
  analogWrite(10,255);
  Serial.println("ALL HIGH FORWARDS");
   }
SM_Motor();
SM_Sensor();
}

void SM_Motor()
{
 digitalWrite(11,0);
 digitalWrite(3,255);
 delay(80);
 digitalWrite(11,0);
 digitalWrite(3,0);
 delay(5000);
 digitalWrite(11,255);
 digitalWrite(3,0);
 delay(100);
 digitalWrite(11,0);
 digitalWrite(3,0);
 delay(5000); 
}

void SM_Sensor()
{
 int soil_moisture_val = analogRead(soil_moisture_pin);
 Serial.print("Moisture = ");
 Serial.print(soil_moisture_val);
 soil_moisture_val = map(soil_moisture_val,1023,0,0,100);
 Serial.print(", Moisture = ");
 Serial.print(soil_moisture_val);
 Serial.println("%");
 if (soil_moisture_val > base_moisture)
 {
  Serial.print("Good Amount of Moisture");
 }
 else if (soil_moisture_val < 50)
 {
  Serial.print("Very Less Amount of Moisture");
 }
 else
 {
  Serial.print("Normal Amount of Moisture");
 }
 delay(1000);
}

