const int s0 = 2; // Pin connected to S0 of 4051
const int s1 = 3; // Pin connected to S1 of 4051
const int s2 = 4; // Pin connected to S2 of 4051

const int ledPin = 13;

int channel = 1; // midi channel

int cc[16] = { 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117};

int val[16];
int lastVal[16] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

void setup() {
  pinMode(ledPin, OUTPUT);

  // set pins to output multiplexor 4051
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);

  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
}

void loop() {

  val[0] = readPot(0, 0); // (Analog input, Mux port)
  val[1] = readPot(0, 1);
  val[2] = readPot(0, 2);
  val[3] = readPot(0, 3);
  val[4] = readPot(0, 4);
  val[5] = readPot(0, 5);
  val[6] = readPot(0, 6);
  val[7] = readPot(0, 7);
  
  val[8] = readPot(1, 0);
  val[9] = readPot(1, 1);
  val[10] = readPot(1, 2);
  val[11] = readPot(1, 3);
  val[12] = readPot(1, 4);
  val[13] = readPot(1, 5);
  val[14] = readPot(1, 6);
  val[15] = readPot(1, 7);
  
  for (int i = 0; i < 5 ; i ++){
    if (val[i] != lastVal[i]) {
      usbMIDI.sendControlChange(cc[i],val[i],channel);
      lastVal[i] = val[i];
    }
  }
}

int readPot(int input, int port){
  
  selectInput(port); // of 4051
  
  int knobVal = smoothRead(input);
  int val = knobVal/8;
  return val;
}

void selectInput(int input){
  
  // select 4051 channel 0 (of 0 to 7)
  
  digitalWrite(s0, bitRead(input, 0));
  digitalWrite(s1, bitRead(input, 1));
  digitalWrite(s2, bitRead(input, 2));

  // allow 100 us for signals to stablize because of 3.3v, 50 us  for  5v
  delayMicroseconds(100); 
}

int smoothRead(int input){

  int numReadings = 10;
  int readings[numReadings];
  int total = 0;
  int average = 0;

  for (int i = 0; i < numReadings; i++){
    readings[i] = analogRead(input);
    total= total + readings[i];
  }
  average = total / numReadings;
  return average;
}

