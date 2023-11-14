#include <Servo.h>

Servo servoMotor;

int AteaPosizioa = 90;
int DenboraIxteko = 10000;

int UltraSoinuSentsorePinaTrigger = 5;
int UltraSoinuSentsorePinaEcho = 6;

int LedUrdina = 8;
int LedGorria = 12;
int LedBerdea = 13;

int Soinua = 3;

float DistantziaCm;

void setup() {
  servoMotor.attach(9);
  pinMode(LedUrdina, OUTPUT);
  pinMode(LedGorria, OUTPUT);
  pinMode(LedBerdea, OUTPUT);
  Serial.begin(9600);
  digitalWrite(LedGorria, HIGH);
  pinMode(UltraSoinuSentsorePinaTrigger, OUTPUT);
  pinMode(UltraSoinuSentsorePinaEcho, INPUT);
  digitalWrite(UltraSoinuSentsorePinaTrigger, LOW);
}

long UltraSoinuSentsoreDistantzia(int triggerPina, int echoPina) {
  digitalWrite(triggerPina, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPina, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPina, LOW);
  return pulseIn(echoPina, HIGH);
}

void AteaIreki() {
  noTone(Soinua);
  Serial.println("Atea Irekitzen");
  AteaPosizioa = 0;
  servoMotor.write(AteaPosizioa);
  digitalWrite(LedGorria, LOW);
  digitalWrite(LedBerdea, HIGH);

  while (servoMotor.read() == 0) {
    delay(DenboraIxteko);
    digitalWrite(LedBerdea, LOW);
    AteaItxi();
  }
}

void AteaItxi() {
  noTone(Soinua);
  DistantziaCm = UltraSoinuSentsoreDistantzia(UltraSoinuSentsorePinaTrigger, UltraSoinuSentsorePinaEcho) / 59;

  if (DistantziaCm < 100.0) {
    Serial.println("Kotxea metro bat baño gertuago dago. Ezin da atea Itxi.");

    while (DistantziaCm < 100.0) {
      digitalWrite(LedUrdina, HIGH);
      tone(Soinua, 440);
      delay(250);
      noTone(Soinua);
      DistantziaCm = UltraSoinuSentsoreDistantzia(UltraSoinuSentsorePinaTrigger, UltraSoinuSentsorePinaEcho) / 59;
      digitalWrite(LedUrdina, LOW);
      delay(250);
      DistantziaCm = UltraSoinuSentsoreDistantzia(UltraSoinuSentsorePinaTrigger, UltraSoinuSentsorePinaEcho) / 59;
    }

    digitalWrite(LedUrdina, LOW);
  }

  Serial.println("Atea Ixten");
  AteaPosizioa = 90;
  servoMotor.write(AteaPosizioa);
  digitalWrite(LedGorria, HIGH);
  digitalWrite(LedBerdea, LOW);
  if (servoMotor.read() == 90) {
    digitalWrite(LedGorria, LOW);
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

  if (esk.equalsIgnoreCase("itxi")) {
    AteaItxi();
    KodeaExistitzenDa = true;
  } else if (esk.equalsIgnoreCase("ireki")) {
    AteaIreki();
    KodeaExistitzenDa = true;
  }

  if (!KodeaExistitzenDa) {
    Serial.println("Kode hau ez da existitzen.");
  }
}
