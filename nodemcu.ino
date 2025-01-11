#include <painlessMesh.h>
#include <SoftwareSerial.h>
// Mesh ayarları
#define MESH_PREFIX "meshName"
#define MESH_PASSWORD "meshPassword"
#define MESH_PORT meshPort

Scheduler userScheduler;
painlessMesh mesh;

SoftwareSerial mySerial(D5, D6); // RX, TX

// Sensör 
String sensorID = "4";

void sendToMesh(const String &jsonData) {
  mesh.sendBroadcast(jsonData);
  Serial.println("Mesh ağına veri gönderildi:");
  Serial.println(jsonData);
}

// Mesh callback fonksiyonları
void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Mesh'ten gelen mesaj (Node %u): %s\n", from, msg.c_str());
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("Yeni bir cihaz bağlandı: %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.println("Mesh bağlantı durumu değişti.");
}

void setup() {
  Serial.begin(115200);      // NodeMCU'nun kendi seri portu
  mySerial.begin(9600);      // Arduino ile iletişim
  Serial.println("NodeMCU hazır!");

  mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
}
void loop() {
  mesh.update();

  if (mySerial.available()) {
    String data = mySerial.readStringUntil('\n'); 
    data.trim(); // \r ve \n karakterlerini kaldır
    Serial.print("Arduino'dan gelen veri: ");
    Serial.println(data);

    int mmaStart = data.indexOf("MMA7361L:");
    int mplStart = data.indexOf("|MPL3115A2:");

    if (mmaStart != -1 && mplStart != -1) {
      String mmaData = data.substring(mmaStart + 9, mplStart);
      String mplData = data.substring(mplStart + 11);

      // MMA7361L verileri ayrıştır
      int xIndex = mmaData.indexOf(",");
      int yIndex = mmaData.indexOf(",", xIndex + 1);

      String x = mmaData.substring(0, xIndex);
      String y = mmaData.substring(xIndex + 1, yIndex);
      String z = mmaData.substring(yIndex + 1);

      // MPL3115A2 verileri ayrıştır
      int pressureIndex = mplData.indexOf(",");
      String pressure = mplData.substring(0, pressureIndex);
      String tempCelsius = mplData.substring(pressureIndex + 1);

      // JSON formatını oluştur
      String jsonData = "{\"id\":\"" + sensorID + "\",\"sensor\":[\"x : " + x + "\",\"y : " + y + "\",\"z : " + z + "\",\"basinç : " + pressure + "\",\"sicaklik : " + tempCelsius + "\"]}";

      // JSON  gönder
      sendToMesh(jsonData);
    }
  }
}
