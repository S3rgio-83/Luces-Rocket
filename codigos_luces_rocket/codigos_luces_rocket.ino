#include <Adafruit_NeoPixel.h>

#define PIN            6   // El pin al que están conectados los Neopixels
#define NUMPIXELS      7   // Número de Neopixels en tu tabla redonda

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Colores predefinidos
uint32_t red = strip.Color(255, 0, 0);
uint32_t orange = strip.Color(255, 165, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t whiteBlue = strip.Color(200, 200, 255);

unsigned long startTime = 0;
int transitionDuration = 5000; // Duración de la transición de color en milisegundos
int randomRedLED = 0;

void setup() {
  Serial.begin(9600); // Inicializa la comunicación serial para depuración
  strip.begin();
  strip.show();  // Inicializa todos los píxeles a 'apagado'
  randomSeed(analogRead(0)); // Inicializa la semilla aleatoria
  startTime = millis();  // Inicializa el temporizador
  randomRedLED = random(NUMPIXELS); // Inicializa la selección aleatoria del LED rojo
}

void loop() {
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - startTime;

  if (elapsedTime >= transitionDuration) {
    // Realizar transición de color de naranja a azul y de rojo a blanco
    Serial.println("Transición iniciada.");
    for (int i = 0; i < NUMPIXELS; i++) {
      int r = map(elapsedTime, transitionDuration, 0, (orange >> 16) & 0xFF, (blue >> 16) & 0xFF);
      int g = map(elapsedTime, transitionDuration, 0, (orange >> 8) & 0xFF, (blue >> 8) & 0xFF);
      int b = map(elapsedTime, transitionDuration, 0, orange & 0xFF, blue & 0xFF);
      strip.setPixelColor(i, strip.Color(r, g, b));
    }
    randomRedLED = random(NUMPIXELS); // Selección aleatoria del LED rojo
    strip.setPixelColor(randomRedLED, whiteBlue); // Luz roja aleatoria
    strip.show();
  } else {
    // Efecto de variación de intensidad de las luces naranjas y luz roja aleatoria
    Serial.println("Efecto de naranja y luz roja aleatoria.");
    for (int i = 0; i < NUMPIXELS; i++) {
      int brightness = random(30, 255);  // Rango de intensidad de luz naranja
      strip.setPixelColor(i, strip.Color(brightness, brightness / 2, 0));  // Color naranja
    }
    randomRedLED = random(NUMPIXELS); // Selección aleatoria del LED rojo
    strip.setPixelColor(randomRedLED, red); // Luz roja aleatoria
    strip.show();
  }
}
