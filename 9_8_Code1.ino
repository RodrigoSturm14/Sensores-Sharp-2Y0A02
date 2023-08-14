#define PIN_SENSOR A0

const long referenceMv = 3300;

//interpolación de la distancia a intervalos de 180mV
const int TABLE_ENTRIES = 12;
const int INTERVAL = 180;
static int distance[TABLE_ENTRIES] = { 150, 140, 130, 100, 60, 50, 40, 35, 30, 25, 20, 15 };

int getCentimeter(int mV) {
  if (mV > INTERVAL * TABLE_ENTRIES - 1) return distance[TABLE_ENTRIES - 1];
  else {
    int index = mV / INTERVAL;
    float frac = (mV % 250) / (float)INTERVAL;
    return distance[index] - ((distance[index] - distance[index + 1]) * frac);
  }
}

int getDistance(int sensorPin) {
  int val = analogRead(sensorPin);
  int mV = (val * referenceMv) / 4096;  //4096
  int cm = getCentimeter(mV);
  return cm;
}

void setup() {
  Serial.begin(9600);
  pinMode(PIN_SENSOR, INPUT);
}

void loop() {
  
  //mostrar valores por pantalla
  Serial.println(getDistance(PIN_SENSOR));
  delay(1000);
}
