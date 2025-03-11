#define TRIG 13
#define ECHO 12

int ledr = 7;
int ledg = 9;

void setup()
{
  Serial.begin(9600);
  pinMode(ledr, OUTPUT);
  pinMode(ledg, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop()
{
  long duration,distance;
  digitalWrite(TRIG,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG,LOW);
  duration = pulseIn(ECHO,HIGH);
  distance = duration/58.2;
  Serial.print("Distance:");
  Serial.print(distance);
  Serial.println(" Cm");
  if(distance>=100){
    digitalWrite(ledr,HIGH);
    digitalWrite(ledg,LOW);
  }else{
    digitalWrite(ledr,LOW);
    digitalWrite(ledg,HIGH);
  }
  delay(1000);
}