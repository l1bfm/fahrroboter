//Das Hauptprogramm

//Pins
const int LDR_links = A0;
const int LDR_rechts = A1;
const int motor [2] = {5, 7};
const int pushbutton = 4;

//LDR-Kalibrierung
int Schwarz = 1023;
int Weiss = 0;

void setup() {
	//Motorpins als Output deklarieren
	for(int i=0; i<=1; i++) {
		pinMode(motor[i], OUTPUT);
		pinMode(motor[i]+1, OUTPUT);
	}
	pinMode(pushbutton, INPUT)
	Serial.begin(9600);
	kalibrierung()
}

void loop() {
	//LDR-Werte auslesen
	int LDR_Werte [2] = ldr_read();
	//Linienfolger ausführen
	linien_drive(LDR_Werte);
}

int ldr_read() {
	//Array der Werte einlesen und dann returnen
	int Werte [2] = { analog.Read(LDR_links), analog.Read(LDR_rechts) };
	return Werte;
}

void linien_drive(LDR_Werte) {
	int fahr_werte [2];
	int fahr_werte_diff [2];
	int vorwaerts = 1;
	// Map
	for(int i=0; i<=1; i++) {
		fahr_werte[i] = map(LDR_Werte[i], Weiss, Schwarz, 510, 0) - 255;
		fahr_werte_diff[i] = 255 - fahr_werte[i]
	}
	// Maximierung der Geschwindigkeit
	sort(fahr_werte_diff, fahr_werte_diff + 5);
	for(int i=0; i<=1; i++) {
		fahr_werte[i] += fahr_werte_diff[0];
		// gemapptes zu zwei-pin-Daten
		if(fahr_werte[i] < 0) {
			fahr_werte[i] *= -1;
			vorwaerts = 0;
		}
		// Für jede Seite Motor ansteuern
		analogWrite(motor[i], 0);
		analogWrite(motor[i]+1, 0);
		analogWrite(motor[i]+vorwaerts, fahr_werte[i]);
	}

}

void kalibrierung() {
	// Während der Knopf nicht gedrückt ist
	while(digitalRead(pushbutton) == 0) {
		// LDR lesen
		int LDR_Werte [2] = ldr_read();
		// Werte ausgeben
		Serial.print(LDR_Werte[0]);
		Serial.print("\t");
		serial.print(LDR_Werte[1]);
		serial.println();
