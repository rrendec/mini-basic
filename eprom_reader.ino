#define DATA_PIN_0 2
#define DATA_PIN_1 3
#define DATA_PIN_2 4
#define DATA_PIN_3 5
#define DATA_PIN_4 6
#define DATA_PIN_5 7
#define DATA_PIN_6 8
#define DATA_PIN_7 9

#define ADDRESS_PIN_0 A0
#define ADDRESS_PIN_1 A1
#define ADDRESS_PIN_2 A2
#define ADDRESS_PIN_3 A3
#define ADDRESS_PIN_4 A4
#define ADDRESS_PIN_5 A5
#define ADDRESS_PIN_6 10
#define ADDRESS_PIN_7 11
#define ADDRESS_PIN_8 12
#define ADDRESS_PIN_9 13
//#define ADDRESS_PIN_10 A4
//#define ADDRESS_PIN_11 A5

//#define OE_PIN A6

#define READ_DELAY 10 // Microseconds delay for stability

#define EPROM_SIZE 1024 // Size of the EPROM in bytes
#define RECORD_DATA_LENGTH 8 // Number of bytes in each Intel hex record

void setup() {
  // Set data pins as inputs
  pinMode(DATA_PIN_0, INPUT);
  pinMode(DATA_PIN_1, INPUT);
  pinMode(DATA_PIN_2, INPUT);
  pinMode(DATA_PIN_3, INPUT);
  pinMode(DATA_PIN_4, INPUT);
  pinMode(DATA_PIN_5, INPUT);
  pinMode(DATA_PIN_6, INPUT);
  pinMode(DATA_PIN_7, INPUT);

  // Set address pins as outputs
  pinMode(ADDRESS_PIN_0, OUTPUT);
  pinMode(ADDRESS_PIN_1, OUTPUT);
  pinMode(ADDRESS_PIN_2, OUTPUT);
  pinMode(ADDRESS_PIN_3, OUTPUT);
  pinMode(ADDRESS_PIN_4, OUTPUT);
  pinMode(ADDRESS_PIN_5, OUTPUT);
  pinMode(ADDRESS_PIN_6, OUTPUT);
  pinMode(ADDRESS_PIN_7, OUTPUT);
  pinMode(ADDRESS_PIN_8, OUTPUT);
  pinMode(ADDRESS_PIN_9, OUTPUT);
  //pinMode(ADDRESS_PIN_10, OUTPUT);
  //pinMode(ADDRESS_PIN_11, OUTPUT);

  // Set output enable pin as output
  //pinMode(OE_PIN, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  int address = 0;
  int data[RECORD_DATA_LENGTH];

  // Loop through all addresses
  while (address < EPROM_SIZE) {
    // Read data for current record and store in array
    for (int i = 0; i < RECORD_DATA_LENGTH; i++) {
      setAddress(address + i);
      data[i] = readData();
    }

    // Print Intel Hex record for current address and data
    printIntelHexRecord(address, data);

    // Increment address
    address += RECORD_DATA_LENGTH;
  }

  // End of data marker
  Serial.println(":00000001FF");

  // End of program
  while (1);
}

void setAddress(int address) {
  digitalWrite(ADDRESS_PIN_0, (address & 0x01) >> 0);
  digitalWrite(ADDRESS_PIN_1, (address & 0x02) >> 1);
  digitalWrite(ADDRESS_PIN_2, (address & 0x04) >> 2);
  digitalWrite(ADDRESS_PIN_3, (address & 0x08) >> 3);
  digitalWrite(ADDRESS_PIN_4, (address & 0x10) >> 4);
  digitalWrite(ADDRESS_PIN_5, (address & 0x20) >> 5);
  digitalWrite(ADDRESS_PIN_6, (address & 0x40) >> 6);
  digitalWrite(ADDRESS_PIN_7, (address & 0x80) >> 7);
  digitalWrite(ADDRESS_PIN_8, (address & 0x100) >> 8);
  digitalWrite(ADDRESS_PIN_9, (address & 0x200) >> 9);
  //digitalWrite(ADDRESS_PIN_10, (address & 0x400) >> 10);
  //digitalWrite(ADDRESS_PIN_11, (address & 0x800) >> 11);

  delayMicroseconds(READ_DELAY);
}

int readData() {
  int data = 0;

  data |= digitalRead(DATA_PIN_0) << 0;
  data |= digitalRead(DATA_PIN_1) << 1;
  data |= digitalRead(DATA_PIN_2) << 2;
  data |= digitalRead(DATA_PIN_3) << 3;
  data |= digitalRead(DATA_PIN_4) << 4;
  data |= digitalRead(DATA_PIN_5) << 5;
  data |= digitalRead(DATA_PIN_6) << 6;
  data |= digitalRead(DATA_PIN_7) << 7;

  return data;
}

void printIntelHexRecord(int startAddress, int data[]) {
  char buf[5];

  Serial.print(":"); // Start of record

  // Record length (number of data bytes)
  snprintf(buf, sizeof(buf), "%02x", RECORD_DATA_LENGTH);
  Serial.print(buf);

  // Address
  snprintf(buf, sizeof(buf), "%04x", startAddress);
  Serial.print(buf);

  // Record type (data)
  Serial.print("00");

  // Data bytes
  for (int i = 0; i < RECORD_DATA_LENGTH; i++) {
    snprintf(buf, sizeof(buf), "%02x", data[i]);
    Serial.print(buf);
  }

  // Checksum calculation
  int checksum = RECORD_DATA_LENGTH + ((startAddress >> 8) & 0xFF) + (startAddress & 0xFF);
  for (int i = 0; i < RECORD_DATA_LENGTH; i++) {
    checksum += data[i];
  }
  checksum = (~checksum) + 1; // Two's complement

  // Print checksum
  snprintf(buf, sizeof(buf), "%02x", checksum & 0xFF);
  Serial.print(buf);

  // End of record
  Serial.println();
}
