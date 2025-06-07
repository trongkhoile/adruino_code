int soundSensor = 8;    // nối chân OUT của cảm biến âm thanh vào chân số 8 trên Arduino.
int relay = 7;          // nối chân IN của module relay vào chân số 7 trên Arduino.
bool relayState = false; // lưu trạng thái hiện tại của relay (đang tắt).

void setup() {
  pinMode(soundSensor, INPUT);       // Thiết lập chân 8 là input (đọc từ cảm biến âm thanh)
  pinMode(relay, OUTPUT);            // Thiết lập chân 7 là output (điều khiển relay)
  digitalWrite(relay, LOW);          // Ban đầu tắt relay
  Serial.begin(9600);                // Bắt đầu giao tiếp Serial để in trạng thái (debug)
}

void loop() {
  int sound = digitalRead(soundSensor); // Đọc trạng thái của cảm biến (HIGH hoặc LOW)
  
  if (sound == HIGH) {
    // Đổi trạng thái relay mỗi khi phát hiện tiếng vỗ
    relayState = !relayState;                         // Đảo trạng thái hiện tại (ON <-> OFF)
    digitalWrite(relay, relayState ? HIGH : LOW);     // Gửi tín hiệu điều khiển relay bật/tắt
    Serial.println(relayState ? "ON" : "OFF");        // In trạng thái relay ra Serial Monitor
    delay(500);                                       // Chờ 500ms để chống rung (debounce)
  }
}