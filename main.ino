/*
EIN SIMPLES PROGRAMM FÜR EIN AUTONOMES VEHIKEL
(c) 2020 by Florentin Möhle <florentin.moehle@t-online.de>
Lizensiert unter der GNU GPL v3
*/

// Anschlüsse definieren

// Motoren
const int motor_left_plus = 0;
const int motor_left_minus = 0;
const int motor_right_plus = 0;
const int motor_right_minus = 0;

// LDRs
const int ldr_led = 0;
const char ldr_left = A0;
const char ldr_right = A0;

// UI
const int exit_button = 0;
const int on_led = 0;

// Globale Variablen

// Motoren

// LDRs
int white = 1023;
int black = 0;
float grey = (white + black) / 2;


// Setup
void setup() {
  // Pin Modes

  // Motoren
  pinMode(motor_left_plus, OUTPUT);
  pinMode(motor_left_minus, OUTPUT);
  pinMode(motor_right_plus, OUTPUT);
  pinMode(motor_right_minus, OUTPUT);

  // LDRs
  pinMode(ldr_led, OUTPUT);

  // UI
  pinMode(exit_button, INPUT);
  pinMode(on_led, OUTPUT);
}

// Kalibrierung der Sensoren
void calibrate() {
  // Kalibrierung beider Optokoppler erfolgt jetzt
  delay(5000);
  // Muss noch implementiert werden
}


// Sensoren

std::unordered_map all_sensors_read() {
  // Alle Sensoren werden ausgelesen und in einem Array zurückgegeben
   std::unordered_map <char, int> ldr_wert = ldr_read();
   std::unordered_map <char, int> output = {
     {"ldr_left", ldr_wert["left"]}, {"ldr_right", ldr_wert["right"]},
     {"uss_dist", 0}
   }
  return 0;
}

void ldr_read() {
  // Die beiden LDRs werden ausgelesen und ihr Wert zurückgegeben
  int ldr_left_wert = analogRead(ldr_left);
  int ldr_right_wert = analogRead(ldr_right);
  array output[2] = {ldr_left_wert, ldr_right_wert
  return output;
}


// Motoren

void motoren_speed(int left=0, int right=0) {
  // Die beiden Motoren werden über eine Geschwindigkeit angesteuert

  //links
  if(left>=0){
    analogWrite(motor_left_plus, left);
  }
  else if(left<0){
    analogWrite(motor_left_minus, left);
  }

  // rechts
  if(right>=0){
    analogWrite(motor_right_plus, left);
  }
  else if(right<0){
    analogWrite(motor_right_minus, left);
  }

}


// Verarbeitung

// Mapping
void ldr_map_motor_speed(int left_in=0, int right_in=0) {
  // Mappt die Werte des LDRs auf die Werte für den Motor
  // Links
  int left_out = map(left_in, black, white, 0, 510);
  left_out -= 255;
  // Rechts
  int right_out = map(right_in, black, white, 0, 510);
  right_out -= 255;
  array output[2] = {left_out, right_out}
   return output;
}

void mainloop() {
  sensor_data = all_sensors_read()
  map_data = ldr_map_motor_speed(sensor_data["ldr_left"], data["ldr_right"])
  motoren_speed(left=map_data["left"], right=map_data["right"]);
}

// UI

bool check_exit() {
  if(digitalRead(exit_button) == true) {
    return true;
  }
  return false;
}

void standby() {
  // Gefahrenwarn-LED ausschalten
  digitalWrite(on_led, 0);
  // Warteschleife
  while(true) {
    if(check_exit() == true) {
      break;
    }
  }
  // Gefahrenwarn-LED einschalten
  digitalWrite(on_led, 1);
}

void loop() {
  mainloop();
  if(check_exit() == true) {
    standby();
  }
}
