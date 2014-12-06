int pin_e1 = 52;
int pin_in1_1 = 50;
int pin_in1_2 = 48;
 
int pin_e2 = 42;
int pin_in2_1 = 40;
int pin_in2_2 = 38;
 
void full_right()
{
  digitalWrite(pin_in1_1, HIGH);
  digitalWrite(pin_in1_2, LOW);
  digitalWrite(pin_in2_1, HIGH);
  digitalWrite(pin_in2_2, LOW);
}
 
void full_left()
{
  digitalWrite(pin_in1_1, LOW);
  digitalWrite(pin_in1_2, HIGH);
  digitalWrite(pin_in2_1, LOW);
  digitalWrite(pin_in2_2, HIGH);
}
 
void backward()
{
  digitalWrite(pin_in1_1, LOW);
  digitalWrite(pin_in1_2, HIGH);
  digitalWrite(pin_in2_1, HIGH);
  digitalWrite(pin_in2_2, LOW);
}
 
void forward()
{
  digitalWrite(pin_in1_1, HIGH);
  digitalWrite(pin_in1_2, LOW);
  digitalWrite(pin_in2_1, LOW);
  digitalWrite(pin_in2_2, HIGH);
}
 
void left()
{
  digitalWrite(pin_in1_1, HIGH);
  digitalWrite(pin_in1_2, LOW);
  digitalWrite(pin_in2_1, LOW);
  digitalWrite(pin_in2_2, LOW);
}
 
void right()
{
  digitalWrite(pin_in1_1, LOW);
  digitalWrite(pin_in1_2, LOW);
  digitalWrite(pin_in2_1, HIGH);
  digitalWrite(pin_in2_2, LOW);
}
 
void stall()
{
  digitalWrite(pin_in1_1, LOW);
  digitalWrite(pin_in1_2, LOW);
  digitalWrite(pin_in2_1, LOW);
  digitalWrite(pin_in2_2, LOW);
}
 
void freerun()
{
    digitalWrite(pin_e1,LOW);
    digitalWrite(pin_e2,LOW);
}
 
void setup()
{
  Serial.begin(9600);
  pinMode(pin_e1, OUTPUT);
  pinMode(pin_in1_1, OUTPUT);
  pinMode(pin_in1_2, OUTPUT);
  digitalWrite(pin_e1, HIGH);
  pinMode(pin_e2, OUTPUT);
  pinMode(pin_in2_1, OUTPUT);
  pinMode(pin_in2_2, OUTPUT);
  digitalWrite(pin_e2, HIGH);
  pinMode(22,OUTPUT);
  pinMode(24,OUTPUT);
  
}
 
void loop()
{ 
  if(Serial.read()=='w')
  forward();
  else if(Serial.read()=='s')
  backward();
  else if(Serial.read()=='a')
  left();
  else if(Serial.read()=='d')
  right();
  else
  stall();
}