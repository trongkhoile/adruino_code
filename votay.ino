int soundSensor = 12;    // Cảm biến âm thanh nối với chân số 12
int relay = 2;           // Module relay nối với chân số 2
bool relayState = false; // Trạng thái relay
unsigned long lastClapTime = 0; // Thời gian vỗ tay trước đó
int clapCount = 0; // Số lần vỗ tay liên tiếp

void setup() {
  pinMode(soundSensor, INPUT);    // Cảm biến âm thanh là input
  pinMode(relay, OUTPUT);         // Relay là output
  digitalWrite(relay, LOW);       // Ban đầu tắt relay
  Serial.begin(9600);             // Bắt đầu giao tiếp Serial để debug
}

void loop() {
  int sound = digitalRead(soundSensor); // Đọc trạng thái cảm biến
  unsigned long currentTime = millis();
  
  if (sound == HIGH) {
    if (clapCount==0){
      clapCount++;
    }
    else if (clapCount!=0 && currentTime - lastClapTime > 200 && currentTime - lastClapTime < 1000) { 
      clapCount++; // Tăng số lần vỗ tay
      Serial.println("Vỗ tay lần: " + String(clapCount));

      if (clapCount == 3) { // Nếu vỗ tay 3 lần liên tiếp trong < 1 giây
        relayState = !relayState; // Đổi trạng thái relay
        digitalWrite(relay, relayState ? HIGH : LOW);
        Serial.println(relayState ? "Đèn BẬT!" : "Đèn TẮT!");
        clapCount = 0; // Reset hoàn toàn sau khi bật/tắt đèn
      }
    } else {
      // Nếu khoảng cách giữa vỗ tay quá lớn (>1s), reset hoàn toàn
      clapCount = 0;
    }

    lastClapTime = currentTime; // Cập nhật thời gian vỗ tay gần nhất
    delay(50); // Tránh nhận tín hiệu nhiễu liên tục
  }
}
