#include <Wire.h>
#include <Adafruit_MPL3115A2.h>
#include <LiquidCrystal.h> // LCD kütüphanesi

// MMA7361L pinleri
const int xPin = A0; // X ekseni
const int yPin = A1; // Y ekseni
const int zPin = A2; // Z ekseni

// MPL3115A2 sensörü
Adafruit_MPL3115A2 mpl = Adafruit_MPL3115A2();

// LCD pin tanımları
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  Serial.begin(9600); // NodeMCU ile iletişim için seri port
  Wire.begin();

  // MPL3115A2 başlatma
  if (!mpl.begin()) {
    Serial.println("MPL3115A2 sensörü bulunamadı!");
    while (1); // Sonsuz döngü
  }

  // LCD başlatma
  lcd.begin(16, 2); // 16x2 LCD
  lcd.print("Veriler Hazir...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // MMA7361L verilerini oku
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);
  int zValue = analogRead(zPin);

  // MPL3115A2 verilerini oku
  float pressure = mpl.getPressure();  // Basınç (Pa)
  float temperatureF = mpl.getTemperature(); // Sıcaklık (Fahrenheit olarak okunduğunu varsayıyoruz)
  float temperatureC = (temperatureF - 32) * 5.0 / 9.0; // Sıcaklık (Celsius)

  // NodeMCU'ya verileri gönder
  Serial.print("MMA7361L:");
  Serial.print(xValue);
  Serial.print(",");
  Serial.print(yValue);
  Serial.print(",");
  Serial.print(zValue);
  Serial.print("|MPL3115A2:");
  Serial.print(pressure);
  Serial.print(",");
  Serial.print(temperatureC); // Celsius olarak gönder
  Serial.println();

  // LCD'de göster
  lcd.setCursor(0, 0); // İlk satıra yaz
  lcd.print("X:");
  lcd.print(xValue);
  lcd.print(" Y:");
  lcd.print(yValue);

  lcd.setCursor(0, 1); // İkinci satıra yaz
  lcd.print("P:");
  lcd.print(pressure, 1); // Basınç (Pa)
  lcd.print(" T:");
  lcd.print(temperatureC, 1); // Sıcaklık (Celsius)

  delay(1000); // 1 saniye bekle
}

