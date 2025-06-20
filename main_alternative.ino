#include <driver/can.h>
#include <driver/gpio.h>

// CAN Configuration
#define CAN_TX_PIN GPIO_NUM_21
#define CAN_RX_PIN GPIO_NUM_22
#define CAN_SPEED CAN_SPEED_500KBPS

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 CAN Bus Sniffer Starting...");
  
  // Configure CAN
  can_config_t can_config = CAN_DEFAULT_CONFIG();
  can_config.tx_pin_id = CAN_TX_PIN;
  can_config.rx_pin_id = CAN_RX_PIN;
  can_config.mode = CAN_MODE_NORMAL;
  can_config.rx_queue_len = 10;
  
  // Install CAN driver
  if (can_driver_install(&can_config) == ESP_OK) {
    Serial.println("CAN driver installed successfully");
  } else {
    Serial.println("CAN driver installation failed");
    return;
  }
  
  // Start CAN driver
  if (can_start() == ESP_OK) {
    Serial.println("CAN driver started successfully");
  } else {
    Serial.println("CAN driver start failed");
    return;
  }
  
  Serial.println("Waiting for CAN messages...");
  Serial.println("Format: ID: 0xXXX Data: XX XX XX XX XX XX XX XX");
  Serial.println("----------------------------------------");
}

void loop() {
  can_message_t message;
  
  // Check for received CAN messages
  if (can_receive(&message, pdMS_TO_TICKS(100)) == ESP_OK) {
    // Print message ID
    Serial.print("ID: 0x");
    if (message.identifier < 0x100) Serial.print("0");
    if (message.identifier < 0x10) Serial.print("0");
    Serial.print(message.identifier, HEX);
    
    // Print data bytes
    Serial.print(" Data: ");
    for (int i = 0; i < message.data_length_code; i++) {
      if (message.data[i] < 0x10) Serial.print("0");
      Serial.print(message.data[i], HEX);
      Serial.print(" ");
    }
    
    // Fill remaining spaces if message is shorter than 8 bytes
    for (int i = message.data_length_code; i < 8; i++) {
      Serial.print("   ");
    }
    
    // Print additional info
    Serial.print(" | DLC: ");
    Serial.print(message.data_length_code);
    Serial.print(" | RTR: ");
    Serial.print(message.rtr ? "Yes" : "No");
    Serial.print(" | EXT: ");
    Serial.print(message.extd ? "Yes" : "No");
    
    Serial.println();
  }
  
  // Small delay to prevent watchdog issues
  delay(1);
} 