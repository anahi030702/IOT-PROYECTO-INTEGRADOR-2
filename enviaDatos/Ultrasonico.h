//----Sensores A-B----
const int triggerA1 = 2;
const int echoA1 = 3;
const int triggerA2 = 4;
const int echoA2 = 5;
//----Sensores B-A----
const int triggerB2 = 6;
const int echoB2 = 7;
const int triggerB1 = 8;
const int echoB1 = 9;

// Umbral de detección (5 cm) y límite de velocidad (2 km/h)
const int umbralDeteccion = 5;
const float limiteVelocidad = 2.5; // Límite de velocidad en km/h

// Variables para detección y cronómetro
bool detectadoA1 = false;
bool detectadoA2 = false;
bool detectadoB1 = false;
bool detectadoB2 = false;
bool enCursoA = false;  // Marca de cronómetro activo para A a B
bool enCursoB = false;  // Marca de cronómetro activo para B a A
unsigned long tiempoInicioA = 0;
unsigned long tiempoInicioB = 0;

void setup() {
  Serial.begin(9600);

  // Configuración de pines de los sensores ultrasónicos
  pinMode(triggerA1, OUTPUT);
  pinMode(echoA1, INPUT);
  pinMode(triggerA2, OUTPUT);
  pinMode(echoA2, INPUT);

  pinMode(triggerB2, OUTPUT);
  pinMode(echoB2, INPUT);
  pinMode(triggerB1, OUTPUT);
  pinMode(echoB1, INPUT);
}

void loop() {
  // Verificar detección rápida en ambos sentidos
  verificarDeteccion(triggerA1, echoA1, "A1");
  verificarDeteccion(triggerA2, echoA2, "A2");
  verificarDeteccion(triggerB2, echoB2, "B2");
  verificarDeteccion(triggerB1, echoB1, "B1");
}

void verificarDeteccion(int triggerPin, int echoPin, String evento) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long duracion = pulseIn(echoPin, HIGH);
  float distancia = duracion * 0.034 / 2;

  // Manejo de cronómetro y detección en el sentido A (de A1 a A2)
  if (evento == "A1" && distancia <= umbralDeteccion && !enCursoA && !detectadoA1) {
    Serial.println("Cronómetro iniciado en A1");
    tiempoInicioA = millis();  // Guardamos el tiempo de inicio
    enCursoA = true;
    detectadoA1 = true;
  } else if (evento == "A2" && distancia <= umbralDeteccion && enCursoA && !detectadoA2) {
    unsigned long tiempoFinalA = millis();  // Tiempo cuando se detiene en A2
    float tiempoA = (tiempoFinalA - tiempoInicioA) / 1000.0;  // Convertir a segundos
    float velocidadA = calcularVelocidad(tiempoA);  // Calcular velocidad

    Serial.print("Cronómetro detenido en A2. Tiempo: ");
    Serial.print(tiempoA);
    Serial.print(" segundos. Velocidad: ");
    Serial.print(velocidadA);
    Serial.println(" km/h");

    // Advertencia por exceso de velocidad
    if (velocidadA > limiteVelocidad) {
      Serial.println("¡Advertencia! Velocidad excedida en sentido A-B.");
    }

    enCursoA = false;
    detectadoA2 = true;
  }

  // Manejo de cronómetro y detección en el sentido B (de B1 a B2)
  if (evento == "B1" && distancia <= umbralDeteccion && !enCursoB && !detectadoB1) {
    Serial.println("Cronómetro iniciado en B1");
    tiempoInicioB = millis();  // Guardamos el tiempo de inicio
    enCursoB = true;
    detectadoB1 = true;
  } else if (evento == "B2" && distancia <= umbralDeteccion && enCursoB && !detectadoB2) {
    unsigned long tiempoFinalB = millis();  // Tiempo cuando se detiene en B2
    float tiempoB = (tiempoFinalB - tiempoInicioB) / 1000.0;  // Convertir a segundos
    float velocidadB = calcularVelocidad(tiempoB);  // Calcular velocidad

    Serial.print("Cronómetro detenido en B2. Tiempo: ");
    Serial.print(tiempoB);
    Serial.print(" segundos. Velocidad: ");
    Serial.print(velocidadB);
    Serial.println(" km/h");

    // Advertencia por exceso de velocidad
    if (velocidadB > limiteVelocidad) {
      Serial.println("¡Advertencia! Velocidad excedida en sentido B-A.");
    }

    enCursoB = false;
    detectadoB2 = true;
  }

  // Resetear detección cuando el objeto ya no está dentro del rango
  if (distancia > umbralDeteccion) {
    if (evento == "A1") detectadoA1 = false;
    if (evento == "A2") detectadoA2 = false;
    if (evento == "B1") detectadoB1 = false;
    if (evento == "B2") detectadoB2 = false;
  }
}

float calcularVelocidad(float tiempo) {
  float distancia = 0.25;  // Distancia entre los sensores (en metros)
  float velocidad = (distancia / tiempo) * 3.6;  // Convertir de m/s a km/h
  return velocidad;
}
