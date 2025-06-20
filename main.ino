#include <ESP32CAN.h>
#include <CAN_config.h>

// Global variables
CAN_device_t CAN_cfg;
QueueHandle_t rx_queue;

void setup() {
  Serial.begin(115200);
  Serial.println("CAN Bus Sniffer Starting...");
  
  // Configure CAN
  CAN_cfg.speed = CAN_SPEED_500KBPS;
  CAN_cfg.tx_pin_id = GPIO_NUM_21;
  CAN_cfg.rx_pin_id = GPIO_NUM_22;
  CAN_cfg.rx_queue = xQueueCreate(10, sizeof(CAN_frame_t));
  rx_queue = CAN_cfg.rx_queue;

  // Initialize CAN with configuration
  if (ESP32Can.CANInit(CAN_cfg) == CAN_OK) {
    Serial.println("CAN initialized successfully");
  } else {
    Serial.println("CAN initialization failed");
  }
  
  Serial.println("Waiting for CAN messages...");
  Serial.println("Format: ID: 0xXXX Data: XX XX XX XX XX XX XX XX");
  Serial.println("----------------------------------------");
}

void loop() {
  CAN_frame_t rx_frame;
  
  // Check for received CAN messages
  if (xQueueReceive(rx_queue, &rx_frame, 3) == pdTRUE) {
    // Print message ID
    Serial.print("ID: 0x");
    if (rx_frame.MsgID < 0x100) Serial.print("0");
    if (rx_frame.MsgID < 0x10) Serial.print("0");
    Serial.print(rx_frame.MsgID, HEX);
    
    // Print data bytes
    Serial.print(" Data: ");
    for (int i = 0; i < rx_frame.FIR.B.DLC; i++) {
      if (rx_frame.data.u8[i] < 0x10) Serial.print("0");
      Serial.print(rx_frame.data.u8[i], HEX);
      Serial.print(" ");
    }
    
    // Fill remaining spaces if message is shorter than 8 bytes
    for (int i = rx_frame.FIR.B.DLC; i < 8; i++) {
      Serial.print("   ");
    }
    
    // Print additional info
    Serial.print(" | DLC: ");
    Serial.print(rx_frame.FIR.B.DLC);
    Serial.print(" | RTR: ");
    Serial.print(rx_frame.FIR.B.RTR ? "Yes" : "No");
    
    Serial.println();
  }
  
  // Small delay to prevent watchdog issues
  delay(1);
}
