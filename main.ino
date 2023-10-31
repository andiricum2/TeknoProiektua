#include <Servo.h>

Servo servoMotor;
int AteaPosizioa = 90;
int Denbora = 2000;

void setup() {
  servoMotor.attach(9); // Serboa 9. pinean (Analogikoa)
  Serial.begin(9600);
}

void AteaIreki() {
  Serial.println("Atea Irekitzen");
  AteaPosizioa = 0;
  servoMotor.write(AteaPosizioa);
  delay(Denbora);
  Serial.println("Atea Irekita");
  Serial.print("Atearen Posizioa: ");
  Serial.print(AteaPosizioa);
  if !KotxeaDago { 
    AteaItxi();
  }
}

void KotxeaDago() {
  //TODO 
  /*GERTUTASUN SENTSOREAK DETEKTATUTA*/
}

void AteaItxi() {
  Serial.println("Atea Ixten");
  AteaPosizioa = 90;
  servoMotor.write(AteaPosizioa);
  delay(Denbora);
  Serial.println("Atea Itxita");
  Serial.println("Atearen Posizioa: ");
  Serial.println(AteaPosizioa);
}

void loop() {
  String Kodigoak[] = {"Estanix", "Andoni"};
  String esk; //Erabiltzailea Sartutako Kodea

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