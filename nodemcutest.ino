#include "painlessMesh.h"

#define MESH_PREFIX "meshName"
#define MESH_PASSWORD "meshPassword"
#define MESH_PORT meshPort

Scheduler userScheduler;
painlessMesh mesh;

void receivedCallback(uint32_t from, String &msg) {
    Serial.printf("Mesh'ten mesaj alındı!\n");
    Serial.printf("Gönderen Node ID: %u\n", from);
    Serial.printf("Mesaj: %s\n", msg.c_str());
}

void newConnectionCallback(uint32_t nodeId) {
    Serial.printf("Yeni bağlantı: Node ID %u\n", nodeId);
}

void changedConnectionCallback() {
    Serial.println("Bağlantılar değişti.");
}

void nodeTimeAdjustedCallback(int32_t offset) {
    Serial.printf("Zaman ayarlandı. Offset = %d\n", offset);
}

void setup() {
    Serial.begin(115200); 
    Serial.println("Mesh Test Başlatılıyor...");

    mesh.setDebugMsgTypes(ERROR | STARTUP | CONNECTION); 
    mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
    mesh.onReceive(&receivedCallback);
    mesh.onNewConnection(&newConnectionCallback);
    mesh.onChangedConnections(&changedConnectionCallback);
    mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

    Serial.println("Mesh ağı başlatıldı. Mesaj bekleniyor...");
}

void loop() {
    mesh.update();  
}
