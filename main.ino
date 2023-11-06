#include <Servo.h>

Servo servoMotor;
int AteaPosizioa = 90;
int DenboraProzesua = 2000;
int DenboraIxteko = 3000;
int UltraSoinuSentsorePina = 7;

int LedUrdina = 8;
int LedGorria = 12;
int LedBerdea = 13;

bool EzinDaItxi = false;

long UltraSoinuSentsoreDistantzia(int triggerPina, int echoPina) {
  pinMode(triggerPina, OUTPUT);
  digitalWrite(triggerPina, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPina, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPina, LOW);
  pinMode(echoPina, INPUT);
  return pulseIn(echoPina, HIGH);
}

void setup() {
  servoMotor.attach(9);
  pinMode(LedUrdina, OUTPUT);
  pinMode(LedGorria, OUTPUT);
  pinMode(LedBerdea, OUTPUT);
  Serial.begin(9600);
  digitalWrite(LedGorria, HIGH);
}

void AteaIreki() {
  Serial.println("Atea Irekitzen");
  AteaPosizioa = 0;
  servoMotor.write(AteaPosizioa);
  digitalWrite(LedGorria, LOW);
  digitalWrite(LedBerdea, HIGH);

  if (servoMotor.read() == 0) {
    /* Serial.println("Atea Irekita");
    Serial.print("Atearen Posizioa: ");
    Serial.println(AteaPosizioa); */
    delay(DenboraIxteko);
    AteaItxi();
  }
}


void AteaItxi() {
  int DistantziaAnalogikoa = UltraSoinuSentsoreDistantzia(UltraSoinuSentsorePina, UltraSoinuSentsorePina);
  float DistantziaCm = 0.01723 * DistantziaAnalogikoa;

  if (DistantziaCm < 100.0) { // CM tan (100cm)
    Serial.println("Kotxea metro bat baño gertuago dago. Ezin da atea Itxi. 3 Segundu barru berriz saiatzen...");
    EzinDaItxi = true;
    ledurdina();
    delay(3000);
    AteaItxi();
  } else {
    EzinDaItxi = false;
    Serial.println("Atea Ixten");
    AteaPosizioa = 90;
    servoMotor.write(AteaPosizioa);
    digitalWrite(LedGorria, HIGH);
    digitalWrite(LedBerdea, LOW);  

    if (servoMotor.read() == 90) {
      /* Serial.println("Atea Itxita");
      Serial.print("Atearen Posizioa: ");
      Serial.println(AteaPosizioa); */
    }
  }
}

void ledurdina() {
  while (EzinDaItxi) {
  digitalWrite(LedUrdina, HIGH);
  delay(250);
  digitalWrite(LedUrdina, LOW);
  delay(250);
  }
}

void loop() {
  String Kodigoak[] = {"Kaixo", "Oteitza"};
  String esk;

  Serial.println("Idatzi Zure Kodigoa: ");
  while (Serial.available() == 0) {
    // Itxaron kodea sartzeko
  }

  esk = Serial.readString(); // Erabiltzaileak Sartutako Kodea

  bool KodeaExistitzenDa = false;

  for (String Kodigoa : Kodigoak) {
    if (esk.equalsIgnoreCase(Kodigoa)) {
      AteaIreki();
      KodeaExistitzenDa = true;
      break;
    }
  }

  if (!KodeaExistitzenDa) {
    Serial.println("Kode hau ez da existitzen.");
  }
}
