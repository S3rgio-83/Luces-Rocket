#include <Adafruit_NeoPixel.h>

#define PIN            6   // El pin al que están conectados los Neopixels
#define NUMPIXELS      7   // Número de Neopixels en tu tabla redonda

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Colores predefinidos
uint32_t Rojo = strip.Color(255, 10, 0);
uint32_t RojoClaro = strip.Color(244, 67, 54);
uint32_t Naranja = strip.Color(230, 136, 44);
uint32_t Azul = strip.Color(0, 0, 255);
uint32_t Blanco = strip.Color(230, 230, 255);
uint32_t Verde = strip.Color(180, 130, 130);
uint32_t Amarillo = strip.Color(244, 208, 63);
uint32_t AmarilloClaro = strip.Color(249, 231, 159);

unsigned long startTime = 0;
int effectDuration = 3000; // Duración de cada efecto en milisegundos
int randomRojoLED = 0;
int randomBlancoLED = 0;
unsigned long elapsedTime = 0;

// Enumeración para los efectos
enum Effect { NARANJA, VERDE_ROJO, AZUL_BLANCO  };
Effect currentEffect = NARANJA;

void setup() {
  Serial.begin(9600); // Inicializa la comunicación serial para depuración
  strip.begin();
  strip.show();  // Inicializa todos los píxeles a 'apagado'
  randomSeed(analogRead(0)); // Inicializa la semilla aleatoria
  startTime = millis();  // Inicializa el temporizador
}

void NaranjaRojoEffect() {
  Serial.println("Efecto de naranja y luz roja aleatoria.");
  for (int i = 0; i < NUMPIXELS; i++) {
    int brightness = random(30, 255);  // Rango de intensidad de luz naranja
    strip.setPixelColor(i, strip.Color(brightness, brightness / 2, 0));  // Color naranja
  }
  randomRojoLED = random(NUMPIXELS); // Selección aleatoria del LED rojo
  strip.setPixelColor(randomRojoLED, Rojo); // Luz roja aleatoria
  strip.show();
}

void AzulBlancoEffect() {
  Serial.println("Efecto de todas azules y una blanca aleatoria.");
  for (int i = 0; i < NUMPIXELS; i++) {
    if (random(2) == 0) {
      strip.setPixelColor(i, Azul); // Color azul
    } else {
      strip.setPixelColor(i, Blanco); // Color blanco
    }
  }
  randomBlancoLED = random(NUMPIXELS); // Selección aleatoria del LED blanco
  strip.setPixelColor(randomBlancoLED, Blanco); // Luz blanca aleatoria
  strip.show();
}

void VerdeRojoEffect() {
  Serial.println("Efecto de todas luces verdes con una roja aleatoria.");
  for (int i = 0; i < NUMPIXELS; i++) {
    if (random(2) == 0) {
      strip.setPixelColor(i, Rojo);
    } else {
      strip.setPixelColor(i, Verde);
    }
  }
  randomBlancoLED = random(NUMPIXELS); // Selección aleatoria del LED blanco
  strip.setPixelColor(randomBlancoLED, Blanco); // Luz blanca aleatoria
  strip.show();
}

void loop() {
  unsigned long currentTime = millis();
  elapsedTime = currentTime - startTime;

  // Control de duración del efecto
  if (elapsedTime >= effectDuration) {
    // Cambia al siguiente efecto
    if (currentEffect == NARANJA) {
      currentEffect = VERDE_ROJO;
    } else if (currentEffect == VERDE_ROJO) {
      currentEffect = AZUL_BLANCO;  // Agrega nuevos efectos según sea necesario
    } else if (currentEffect == AZUL_BLANCO) {
      currentEffect = NARANJA;  // Regresar al primer efecto
    }
    startTime = currentTime;
  }

  // Ejecuta el efecto actual
  if (currentEffect == NARANJA) {
    NaranjaRojoEffect();
  } else if (currentEffect == AZUL_BLANCO) {
    AzulBlancoEffect();
  } else if (currentEffect == VERDE_ROJO) {
    VerdeRojoEffect();
  }
}
