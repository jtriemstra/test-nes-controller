 

const byte PIN_LATCH = 13;
const byte PIN_CLOCK = 12;
const byte PIN_DATA = 2; 

void setup() {
  // put your setup code here, to run once:
//  PIXEL_DDR = 0xff;    // Set all row pins to output
//  PIXEL_DDR2 = 0xff;    // Set all row pins to output
  
  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_CLOCK,  OUTPUT);
  pinMode(PIN_DATA, INPUT);
    
  Serial.begin(9600);
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  byte bytButton = readNES();
  if (bytButton == 1)
  {
    //sendRedRow(255);
    Serial.write("A");
    delay(500);
  }
  else if (bytButton == 2)
  {
    //sendBlueRow(255);
    Serial.write("B");
    delay(500);
  }
  else if (bytButton > 0)
  {
   // sendGreenRow(255);
   Serial.write("other\n");
   Serial.print(bytButton);
    delay(500);
  }
  //sendWhiteRow(255);
  else
  {
  Serial.write("nothing\n");
  delay(500);
  }
}
  
byte readNES()
{
  byte ret = 0;
  byte i;
  doLatch();
  for (i = 0; i < 8; i++) {
    ret |= (doButtonRead(i == 7) << i);
    Serial.print(ret);
  }
  return ~ret;
}

void doLatch()
{
  digitalWrite(PIN_LATCH,HIGH);
  delayMicroseconds(60);
  digitalWrite(PIN_LATCH,LOW);
}

byte doButtonRead(bool last)
{
  byte ret = digitalRead(PIN_DATA);
  if (!last)
  {
  delayMicroseconds(12);
  digitalWrite(PIN_CLOCK,HIGH);
  delayMicroseconds(12);
  digitalWrite(PIN_CLOCK,LOW);
  }
  return ret;
}

