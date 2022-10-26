#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

const int trigPin = 5;
const int LM35_pin = 15;
const int PIN_TO_SENSOR = 16;
const int ledPin = 21;
const int echoPin = 18;
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

int ADC_VALUE = 0;
int pinStateCurrent = LOW;  // current state of pin
int pinStatePrevious = LOW;  // previous state of pin
int LEDs[] = {27,26,25,33,32,2,13};     // for ESP32 microcontroller
int zero[] = {0, 1, 1, 1, 1, 1, 1};     // cero
int one[] = {0, 0, 0, 0, 1, 1, 0};      // uno
int two[] = {1, 0, 1, 1, 0, 1, 1};      // dos
int three[] = {1, 0, 0, 1, 1, 1, 1};    // tres
int four[] = {1, 1, 0, 0, 1, 1, 0};     // cuatro 
int five[] = {1, 1, 0, 1, 1, 0, 1};     // cinco
int six[] = {1, 1, 1, 1, 1, 0, 1};      // seis
int seven[] = {1, 0, 0, 0, 1, 1, 1};    // siete
int eight[] = {1, 1, 1, 1, 1, 1, 1};    // ocho
int nine[] = {1, 1, 0, 1, 1, 1, 1};     // nueve
int ten[] = {1, 1, 1, 0, 1, 1, 1};      // diez, A
int eleven[] = {1, 1, 1, 1, 1, 0, 0};   // once, b
int twelve[] = {0, 1, 1, 1, 0, 0, 1};   // doce, C
int thirteen[] = {1, 0, 1, 1, 1, 1, 0}; // trece, d
int fourteen[] = {1, 1, 1, 1, 0, 0, 1}; // catorce, E
int fifteen[] = {1, 1, 1, 0, 0, 0, 1};  // quince, F
float c_value = 0;
float distanceCm;
float distanceInch;
long duration;
unsigned char contador = 0;

void setup() {
    Serial.begin(115200);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(PIN_TO_SENSOR, INPUT);
    ledcSetup(ledChannel, freq, resolution);
    ledcAttachPin(ledPin, ledChannel);
    for (int i = 0; i<7; i++) pinMode(LEDs[i], OUTPUT);
}

void loop() {
    fun_LM35();
    fun_Ojitos();
    fun_PIR();
    fun_Display();
    fun_LED();
}

void fun_LM35() {
    ADC_VALUE = analogRead(LM35_pin);
    delay(1000);
    c_value = (((float)ADC_VALUE * 5000)/4095.0)/10.0;
    Serial.print("LM35: ");
    Serial.print(c_value);
    Serial.println("°C");
    delay(1000);
}

void fun_Ojitos() {
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
  
    // Calculate the distance
    distanceCm = duration * SOUND_SPEED/2;
  
    // Convert to inches
    distanceInch = distanceCm * CM_TO_INCH;
  
    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);
    Serial.print("Distance (inch): ");
    Serial.println(distanceInch);
    delay(1000);
}

void fun_PIR() {
  pinStatePrevious = pinStateCurrent;                           // store old state
  pinStateCurrent = digitalRead(PIN_TO_SENSOR);                 // read new state

  if (pinStatePrevious == LOW && pinStateCurrent == HIGH)       // pin state change: LOW -> HIGH
    Serial.println("Motion detected!");
  else if (pinStatePrevious == HIGH && pinStateCurrent == LOW)  // pin state change: HIGH -> LOW
    Serial.println("Motion stopped!");
}

void fun_Display() {
    segment_display(contador);
    delay(1000);
    if(contador < 15) contador++;
    else contador = 0;
}


void fun_LED() {
  // increase the LED brightness
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);
    delay(15);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);
    delay(15);
  }
}

void segment_display(unsigned char valor) {
    switch(valor) {
        case 0:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], zero[i]);
                    break;
        case 1:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], one[i]);
                    break;
        case 2:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], two[i]);
                    break;
        case 3:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], three[i]);
                    break;
        case 4:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], four[i]);
                    break;
        case 5:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], five[i]);
                    break;
        case 6:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], six[i]);
                    break;
        case 7:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], seven[i]);
                    break;
        case 8:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], eight[i]);
                    break;
        case 9:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], nine[i]);
                    break;
        case 10:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], ten[i]);
                    break;
        case 11:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], eleven[i]);
                    break;
        case 12:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], twelve[i]);
                    break;
        case 13:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], thirteen[i]);
                    break;
        case 14:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], fourteen[i]);
                    break;
        case 15:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], fifteen[i]);
                    break; 
        default:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], zero[i]);
                    break;          
    }
}
