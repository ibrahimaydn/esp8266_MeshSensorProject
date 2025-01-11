/*#include <SoftwareSerial.h>

// Arduino ile iletişim için yazılım tabanlı seri port
SoftwareSerial mySerial(D5, D6); // RX, TX

void setup() {
  Serial.begin(115200);       // NodeMCU'nun kendi seri portu
  mySerial.begin(9600);       // Arduino ile iletişim için seri port
  Serial.println("NodeMCU hazır!");
}

void loop() {
  // Arduino'dan gelen veriyi okuma
  if (mySerial.available()) {
    String receivedData = mySerial.readStringUntil('\n'); // Mesajı sonuna kadar oku
    Serial.print("Arduino'dan gelen: ");
    Serial.println(receivedData);
  }
}
*/

///////////////////////////////////////////////////////////////////////////////////////



/*

#include <SoftwareSerial.h>

// Arduino ile iletişim için yazılım tabanlı seri port
SoftwareSerial mySerial(D5, D6); // RX, TX

void setup() {
  Serial.begin(115200);       // NodeMCU'nun kendi seri portu
  mySerial.begin(9600);       // Arduino ile iletişim için seri port
  Serial.println("NodeMCU hazır!");
}

void loop() {
  // Arduino'dan gelen veriyi okuma
  if (mySerial.available()) {
    String data = mySerial.readStringUntil('\n'); // Gelen veriyi oku
    Serial.print("Gelen veri: ");
    Serial.println(data);

    // Veriyi ayırarak işleyebilirsiniz
    int mmaStart = data.indexOf("MMA7361L:");
    int mplStart = data.indexOf("|MPL3115A2:");

    if (mmaStart != -1 && mplStart != -1) {
      String mmaData = data.substring(mmaStart + 9, mplStart);
      String mplData = data.substring(mplStart + 11);

      Serial.println("MMA7361L verileri:");
      Serial.println(mmaData);

      Serial.println("MPL3115A2 verileri:");
      Serial.println(mplData);
    }
  }
}




*/








///////////////////////////////////////////////////////////

/*

#include "painlessMesh.h"
#include <SoftwareSerial.h>

#define MESH_PREFIX "mertdemirelmesh"
#define MESH_PASSWORD "12345678"
#define MESH_PORT 5555

// Arduino ile iletişim için yazılım tabanlı seri port
SoftwareSerial mySerial(D5, D6); // RX, TX

Scheduler userScheduler;
painlessMesh mesh;

// Mesaj gönderme fonksiyonunun prototipi
void sendMessage();

// Belirli aralıklarla mesaj gönderme görevi
Task taskSendMessage(TASK_SECOND * 1, TASK_FOREVER, &sendMessage);

void sendMessage() {
    if (mySerial.available()) {
        String data = mySerial.readStringUntil('\n'); // Arduino'dan gelen veriyi oku

        // Gelen veriyi işleyin
        int mmaStart = data.indexOf("MMA7361L:");
        int mplStart = data.indexOf("|MPL3115A2:");

        if (mmaStart != -1 && mplStart != -1) {
            String mmaData = data.substring(mmaStart + 9, mplStart);
            String mplData = data.substring(mplStart + 11);

            // Mesh mesajı oluştur
            String msg = "Node " + String(mesh.getNodeId()) + " - ";
            msg += "MMA7361L: " + mmaData + ", MPL3115A2: " + mplData;

            // Mesajı mesh ağına gönder
            mesh.sendBroadcast(msg);
            Serial.println("Gönderilen mesaj: " + msg);
        }
    }
    taskSendMessage.setInterval(random(TASK_SECOND * 1, TASK_SECOND * 5)); // Gönderim aralığını rastgele değiştir
}

// Gelen mesajlar için geri çağırma fonksiyonu
void receivedCallback(uint32_t from, String &msg) {
    Serial.printf("Received from %u msg=%s\n", from, msg.c_str());
}

void newConnectionCallback(uint32_t nodeId) {
    Serial.printf("New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
    Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
    Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}

void setup() {
    Serial.begin(115200);
    mySerial.begin(9600); // Arduino ile iletişim için seri port

    mesh.setDebugMsgTypes(ERROR | STARTUP);
    mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
    mesh.onReceive(&receivedCallback);
    mesh.onNewConnection(&newConnectionCallback);
    mesh.onChangedConnections(&changedConnectionCallback);
    mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

    userScheduler.addTask(taskSendMessage);
    taskSendMessage.enable();
}

void loop() {
    mesh.update();
}*/


/////////////////////////////////////////////////////////////////

/*
#include <painlessMesh.h>
#include <SoftwareSerial.h>

// Mesh ayarları
#define MESH_PREFIX "mertdemirelmesh"
#define MESH_PASSWORD "12345678"
#define MESH_PORT 5555

Scheduler userScheduler;
painlessMesh mesh;

// SoftwareSerial ile Arduino bağlantısı
SoftwareSerial mySerial(D5, D6); // RX, TX

// Sensör Kimliği
String sensorID = " sensor02";

void sendToMesh(String data);

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
  // Seri haberleşme ayarları
  Serial.begin(115200);      // NodeMCU'nun kendi seri portu
  mySerial.begin(9600);      // Arduino ile iletişim için yazılım tabanlı seri port
  Serial.println("NodeMCU hazır!");

  // Mesh ağı ayarları
  mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
}

void loop() {
  // Mesh güncellemesi
  mesh.update();

  // Arduino'dan gelen veriyi oku ve işleme al
  if (mySerial.available()) {
    String data = mySerial.readStringUntil('\n'); // Gelen veriyi oku
    Serial.print("Arduino'dan gelen veri: ");
    Serial.println(data);

    // Veriyi ayır ve mesh ağına gönder
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
      float tempCelsius = mplData.substring(pressureIndex + 1).toFloat(); // Direkt Celsius olarak al

      // Mesh ağına gönderilecek veri formatı
     //String meshData =" basınç:" + pressure+  sensorID ;

 String meshData = "x:" + x + " y:" + y + " z:" + z +
                      " basınç:" + pressure +
                        " sıcaklık(C):" + String(tempCelsius, 2) + sensorID;
     
      sendToMesh(meshData);
    }
  }
}

// Mesh ağına veri gönderme
void sendToMesh(String data) {
  mesh.sendBroadcast(data);
  Serial.println("Mesh ağına veri gönderildi:\n" + data);
}
*/


////////////////////////////////////////////////////

#include <painlessMesh.h>
#include <SoftwareSerial.h>

// Mesh ayarları
#define MESH_PREFIX "mertdemirelmesh"
#define MESH_PASSWORD "12345678"
#define MESH_PORT 5555

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
