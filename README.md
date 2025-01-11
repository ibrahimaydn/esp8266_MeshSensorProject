# esp8266_MeshSensorProject
# ESP8266 Mesh Ağ ve UART Haberleşme Projesi

Bu proje, **ESP8266** (NodeMCU) ve **Arduino** arasında **UART haberleşmesi** gerçekleştiren ve bu verileri bir **mesh ağı** üzerinden ileten bir sistemdir. Proje, sensör verilerini toplamak, işlemek ve mesh ağdaki diğer düğümlere iletmek için tasarlanmıştır.

## Proje Özellikleri
1. **UART Haberleşme**:
   - ESP8266, Arduino'dan gelen sensör verilerini alır.
   - UART protokolü kullanılarak Arduino ile ESP8266 arasında iletişim sağlanır.
   - Sensör verileri ayrıştırılır ve JSON formatına dönüştürülür.

2. **Mesh Ağ**:
   - ESP8266 cihazları arasında bir **painlessMesh** ağı kurulur.
   - Mesh ağı, verileri düğümler arasında paylaşır.
   - Merkezi bir yönlendiriciye ihtiyaç duymadan düğümler arası iletişim sağlanır.

3. **Sensör Verileri**:
   - **MMA7361L** ivme ölçer sensörü verileri (x, y, z ekseni).
   - **MPL3115A2** barometre ve sıcaklık sensörü verileri (basınç ve sıcaklık).

---

## Donanım Gereksinimleri
- **ESP8266 (NodeMCU)**
- **Arduino Uno veya Mega**
- **MMA7361L** ivme ölçer sensörü
- **MPL3115A2** barometre ve sıcaklık sensörü
- Bağlantı kabloları

---

## Yazılım Gereksinimleri
Projenin çalışması için aşağıdaki Arduino kütüphanelerini yüklemeniz gerekmektedir:
- [painlessMesh](https://github.com/gmag11/painlessMesh)
- SoftwareSerial (Arduino IDE'de yerleşik)

---

## Bağlantılar
### Arduino ile ESP8266 Bağlantısı
| Arduino Pin | ESP8266 Pin |
|-------------|-------------|
| TX          | D5          |
| RX          | D6          |
| GND         | GND         |

### Sensör Bağlantıları
#### MMA7361L
- VCC: 3.3V
- GND: GND
- X, Y, Z: Analog giriş pinleri (Arduino)

#### MPL3115A2
- VCC: 3.3V
- GND: GND
- SDA, SCL: Arduino I2C pinleri

---

## Kod Açıklaması
### UART Haberleşmesi (Arduino Kodu)
Arduino, sensörlerden gelen verileri toplar ve UART üzerinden ESP8266'ya iletir. 
