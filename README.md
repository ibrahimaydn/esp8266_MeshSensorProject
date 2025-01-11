
# ESP8266 Mesh Ağ ve UART Haberleşme Projesi

Bu proje, ESP8266 tabanlı bir mesh ağı kullanarak çeşitli sensör verilerini toplama ve bu verileri diğer cihazlarla paylaşma uygulamasıdır. Projede MMA7361L, MPL3115A2 sensörleri ve LCD ekran gibi bileşenler yer almakta ve veriler mesh ağı üzerinden iletilmektedir.

İçindekiler
Özellikler
Gereksinimler
Kurulum
Kodların Açıklaması
Proje Detayları
Katkıda Bulunanlar
Özellikler
Mesh Ağ Yapısı: painlessMesh kütüphanesi kullanılarak ESP8266 ve ESP cihazları arasında veri iletimi sağlanır.
Sensör Desteği:
MMA7361L (X, Y, Z ekseni ivme verileri)
MPL3115A2 (Basınç ve sıcaklık ölçümü)
Veri Görselleştirme:
16x2 LCD ekran kullanarak sensör verilerini görüntüleme.
JSON Formatında Veri İletimi: Mesh ağı üzerinden sensör verileri JSON formatında iletilir.
Gereksinimler
Donanım:
NodeMCU (ESP8266)
Arduino Uno
MMA7361L sensörü
MPL3115A2 sensörü
16x2 LCD ekran
Yazılım:
Arduino IDE
painlessMesh kütüphanesi
Adafruit_MPL3115A2 kütüphanesi
LiquidCrystal kütüphanesi
Kurulum
Gerekli Kütüphaneleri Yükleyin: Arduino IDE üzerinden aşağıdaki kütüphaneleri yükleyin:

painlessMesh
Adafruit_MPL3115A2
LiquidCrystal
Donanımı Bağlayın:

MMA7361L sensörünü, MPL3115A2'yi ve LCD ekranı NodeMCU veya Arduino'ya bağlayın.
Bağlantılar için sensör dokümanlarını referans alın.
Kodları Yükleyin:

arduino.ino dosyasını Arduino Uno'ya yükleyin.
nodemcu.ino ve nodemcutest.ino dosyalarını NodeMCU'ya yükleyin.
Mesh Ağını Başlatın:

NodeMCU cihazları arasında iletişim kurmak için cihazların aynı ağ adı (MESH_PREFIX) ve şifreyle (MESH_PASSWORD) çalıştığından emin olun.
Kodların Açıklaması
1. arduino.ino
Arduino, MMA7361L ve MPL3115A2 sensörlerinden verileri toplar. Veriler, LCD ekrana yazdırılır ve seri port üzerinden NodeMCU'ya gönderilir.

2. nodemcu.ino
NodeMCU, gelen seri verileri işler ve mesh ağına JSON formatında gönderir. Mesh ağı üzerinden gelen mesajlar da işlenir ve konsola yazdırılır.

3. nodemcutest.ino
Bu dosya, mesh ağı üzerinde temel iletişim testleri yapmak için kullanılır. Mesh ağına katılan cihazların bağlantı durumu izlenir ve gelen mesajlar işlenir.

Proje Detayları
Mesh Ağı: ESP8266 cihazları arasında veri paylaşımı için kullanılır.
JSON Formatı: Sensör verileri şu formatta iletilir:
json
Kodu kopyala
{
  "id": "4",
  "sensor": [
    "x : 123",
    "y : 456",
    "z : 789",
    "basinç : 101325",
    "sicaklik : 25.0"
  ]
}
Seri İletişim: Arduino ile NodeMCU arasında sensör verilerini paylaşmak için SoftwareSerial kullanılır.
