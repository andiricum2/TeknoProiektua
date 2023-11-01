#include <Servo.h>

Servo servoMotor;
int AteaPosizioa = 90;
int DenboraProzesua = 2000;
int DenboraIxteko = 1000;

int UltraSoinuSentsorePina = 7;

void setup() {
  servoMotor.attach(9);
  Serial.begin(9600);
}

void AteaIreki() {
  Serial.println("Atea Irekitzen");
  AteaPosizioa = 0;
  servoMotor.write(AteaPosizioa);
  delay(DenboraProzesua);
  Serial.println("Atea Irekita");
  Serial.print("Atearen Posizioa: ");
  Serial.println(AteaPosizioa);
  delay(DenboraIxteko);
  AteaItxi();
}

void AteaItxi() {
  int Distantzia = analogRead(UltraSoinuSentsorePina);
  Serial.println(Distantzia);
  if (Distantzia < 400) {
    Serial.println("Kotxea 1 metro baino gertuago dago. Ezin da atea Itxi. 3 Segundu barru berriz saiatzen...");
    delay(3000);
    AteaItxi();
  } else {
    Serial.println("Atea Ixten");
    AteaPosizioa = 90;
    servoMotor.write(AteaPosizioa);
    delay(DenboraProzesua);
    Serial.println("Atea Itxita");
    Serial.print("Atearen Posizioa: ");
    Serial.println(AteaPosizioa);
  }
}

void loop() {
  String Kodigoak[] = {"Estanix", "Andoni"};
  String esk; // Erabiltzailea Sartutako Kodea

  Serial.println("Idatzi Zure Kodigoa: ");
  while (Serial.available() == 0) {
  /* Loop infinito hau ez gertatzeko.
  Kode hau ez da existitzen.Idatzi Zure Kodigoa: 
  Kode hau ez da existitzen.Idatzi Zure Kodigoa: 
  ...
  */
  }

  esk = Serial.readString();

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