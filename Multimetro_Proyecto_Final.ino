#include <SoftwareSerial.h>

const int Medicion1 =7;         
const int Medicion2 =6;         
int Valuable;               
float Voltaje;              
float Sensibilidad = 0.185;
const int pinAnalogico = A0;    
const float resistenciaConocida = 1000.0; 

SoftwareSerial BLUEE(7,6);

unsigned long tiempoAnterior =0;
const unsigned long intervaloMedicion =1000; 

void setup() {
  pinMode(Medicion1, OUTPUT); 
  pinMode(Medicion2, OUTPUT);  
  Serial.begin(9600);    
  BLUEE.begin(9600);
}

char recep;
void loop() {
  if (BLUEE.available()) {
    recep = BLUEE.read();
    Serial.println(recep);

    if (recep == 'A') {
      medirVoltaje();
    }
    else if (recep == 'B') {
      medirResistencia();
    }
    else if (recep == 'C') {
      medirCorriente();
    }
  }

  unsigned long tiempoActual = millis();
  if (tiempoActual - tiempoAnterior >= intervaloMedicion) {
    tiempoAnterior = tiempoActual;

  }
}
void medirResistencia() {
  digitalWrite(Medicion1, LOW);
  digitalWrite(Medicion2, LOW);
  int valorAnalogico = analogRead(pinAnalogico);
  //Voltaje
  float tensionMedida = (float)valorAnalogico * (5.0 / 1023.0);
  //corriente
  float corriente = tensionMedida / resistenciaConocida;
  //recistencia 
  float resistenciaDesconocida = tensionMedida / corriente;

  Serial.print("Resistencia: ");
  Serial.println(resistenciaDesconocida);
  BLUEE.print(resistenciaDesconocida);
  BLUEE.print(";");
}

void medirCorriente() {
  float Corriente=calculo(500);
      Serial.print("Corriente: ");
      Serial.println(Corriente,3);
      BLUEE.print(Corriente,3);
      BLUEE.print(";");
}

void medirVoltaje() {
  digitalWrite(Medicion1, HIGH);
  digitalWrite(Medicion2, HIGH);
  Valuable = analogRead(A1);              
  Voltaje = map(Valuable, 0, 1023, 0, 250) / 10.0;  
  Serial.print("Voltaje: ");
  Serial.println(Voltaje);         
  BLUEE.print(Voltaje);
  BLUEE.print(";");
}

float calculo(int numeroMuestral)
{
float LeerSenso = 0;
float inten = 0;
for(int i=0;i<numeroMuestral;i++)
{
  LeerSenso= analogRead(A2) * (5.0 / 1023.0);
  inten=inten+(LeerSenso-2.5)/Sensibilidad;
}
inten=inten/numeroMuestral;
return(inten);
}
