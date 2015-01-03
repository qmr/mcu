const int pingPin = P1_4;
const int pingReceive = P1_5;

void setup() {
  
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
}

void blink_int(long i, int led)
{
  while(i > 0){
    if(i < 1)
      return;
    digitalWrite(led, HIGH);
    delay(50);
    digitalWrite(led, LOW);
    delay(450);
    i--;
  }
  delay(500);
}

// blinkenlights to signal beginning of loop
void reset()
{
  int interval = 25;
  for(int i = 1; i < 3 ; i++){
    digitalWrite(RED_LED, HIGH);
    delay(interval);
    digitalWrite(RED_LED, LOW);
    delay(interval);
    digitalWrite(GREEN_LED, HIGH);
    delay(interval);
    digitalWrite(GREEN_LED, LOW);
  }
  delay(500);
}
  
long microsecondsToInches(long microseconds)
{
  // 73.746 microseconds per inch 
  // add compile time option for altitude and temp?
  return microseconds / 74 / 2;
}

void loop()
{
  reset();
  long duration, inches, inchesMeasured, feetMeasured, i;
  long feet = 0;
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingReceive, INPUT);
  duration = pulseIn(pingReceive, HIGH);

  inches = microsecondsToInches(duration);
  
  while(inches >= 12){
    feet++;
    inches -= 12;
  }
  
  Serial.print(feet);
  Serial.print(" feet ");
  Serial.print(inches);
  Serial.print(" inches");
  Serial.println();
  blink_int(feet, RED_LED);
  delay(500);
  blink_int(inches, GREEN_LED);
  
}
