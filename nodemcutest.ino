#include "painlessMesh.h"

#define MESH_PREFIX "mertdemirelmesh"
#define MESH_PASSWORD "12345678"
#define MESH_PORT 5555

Scheduler userScheduler;
painlessMesh mesh;

// Gelen mesajlar için geri çağırma fonksiyonu
void receivedCallback(uint32_t from, String &msg) {
    Serial.printf("Mesh'ten mesaj alındı!\n");
    Serial.printf("Gönderen Node ID: %u\n", from);
    Serial.printf("Mesaj: %s\n", msg.c_str());
}

// Yeni bağlantılar için geri çağırma fonksiyonu
void newConnectionCallback(uint32_t nodeId) {
    Serial.printf("Yeni bağlantı: Node ID %u\n", nodeId);
}

// Bağlantı değişikliklerini izlemek için geri çağırma
void changedConnectionCallback() {
    Serial.println("Bağlantılar değişti.");
}

// Zaman ayarlandığında çağrılır
void nodeTimeAdjustedCallback(int32_t offset) {
    Serial.printf("Zaman ayarlandı. Offset = %d\n", offset);
}

void setup() {
    Serial.begin(115200);  // Seri iletişim başlatılır
    Serial.println("Mesh Test Başlatılıyor...");

    // Mesh ağı başlatılır
    mesh.setDebugMsgTypes(ERROR | STARTUP | CONNECTION); // Hata ayıklama mesajlarını aktif et
    mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
    mesh.onReceive(&receivedCallback);
    mesh.onNewConnection(&newConnectionCallback);
    mesh.onChangedConnections(&changedConnectionCallback);
    mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

    Serial.println("Mesh ağı başlatıldı. Mesaj bekleniyor...");
}

void loop() {
    mesh.update(); // Mesh ağını güncelle
}
