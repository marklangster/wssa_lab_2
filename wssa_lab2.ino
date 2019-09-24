
#include <FreeRTOS_ARM.h> 
#define BLUE      8
#define GREEN     7   
#define RED       6


String strBlink = "r";

/*
  Midi Parser Callback functions
*/

//typedef struct notes{
//  uint8_t note;
//  uint8_t velocity;
//  uint8_t status;
//}notes;
//
//
//  uint32_t _bpm = 120;           //default values
//  uint16_t _ticksPerNote = 96;  // default values
//
//void onError(int errorCode){
//  SerialUSB.print("Error received: ");
//  SerialUSB.println(errorCode);
//}
// 
//void onReady(){
//  SerialUSB.println("Device ready");  
//  SerialUSB.print("Device IP: ");
//  //SerialUSB.println(IPAddress(PowerDueWiFi.getDeviceIP()));  
//  xTaskCreate(TcpMIDIStream, "tcp",configMINIMAL_STACK_SIZE, NULL, 1, NULL);
//}
//
//
//void midi_handleEvent(uint64_t delayTicks, uint8_t status, uint8_t note, uint8_t velocity){
////  if (status == STATUS_NOTE_ON && velocity > 0){
////    SerialUSB.println(freq[note]);
////    Codec.playTone(freq[note]);
////  }else{
////       Codec.stopTone();
////    }
//
////    
////    uint32_t waitTimeMS =  TRACK_TIMER_PERIOD_MS(_ticksPerNote, _bpm) * delayTicks;
////    delay(waitTimeMS);
////    if (status == STATUS_NOTE_ON && velocity > 0){
////    Codec.playTone(freq[note]);
////    }else{
////    Codec.stopTone();
////    }
//
//  notes newNote;
//  newNote.note = note;
//  newNote.velocity = velocity;
//  newNote.status = status;
//  vTaskDelay(pdMS_TO_TICKS(TRACK_TIMER_PERIOD_MS(_ticksPerNote, _bpm)* delayTicks));
//  xQueueSend(xQueue, &newNote, 5000); 
//}

//void midi_volumeChanged(uint8_t volume){
//  WMSynth.setMasterVolume(volume);
//}
//
//void midi_trackStart(void){
//  
//}
//
//void midi_tackEnd(void){
//  
//}
//
//void midi_setTicksPerNote(uint16_t ticksPerNote){
//  
// 
//    _ticksPerNote = ticksPerNote;
// 
//}
//
//void midi_setBPM(uint32_t bpm){
//  
//    _bpm = bpm;
//  
//}
void setup() {
  SerialUSB.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  xTaskCreate(serialBlink, "serialBlink", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  xTaskCreate(timeBlink, "timeBlink", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

//  xTaskCreate(queueRead, "queueRead",configMINIMAL_STACK_SIZE, NULL, 1, NULL);
//  xTaskCreate(serialRead, "serialRead",configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  vTaskStartScheduler();
  while(1);
}

void loop() {
//  if (SerialUSB.available()){
//    parser->feed(SerialUSB.read());
//  }
}

//void TcpMIDIStream (void *arg) {
//  MidiParser parser = MidiParser(&midiCallbacks);
//  uint8_t buf[BUFSIZE];
//  struct sockaddr_in serverAddr;
//  int socklen;
//  memset(&serverAddr, 0, sizeof(serverAddr));
//
//  serverAddr.sin_len = sizeof(serverAddr);
//  serverAddr.sin_family = AF_INET;
//  serverAddr.sin_port = htons(SERVER_PORT);
//  inet_pton(AF_INET, SERVER_ADDR, &(serverAddr.sin_addr));
//
//  int s = lwip_socket (AF_INET, SOCK_STREAM, 0);
//  if (lwip_connect(s, (struct sockaddr *)&serverAddr, sizeof(serverAddr))) {
//    SerialUSB.println("Failed to connect to server");
//    assert(false);
//  }
//  //register with the server
//  lwip_write(s, ANDREW_ID, strlen(ANDREW_ID));
//
//  SerialUSB.println("Connected and waiting for events!");
//
//  //listen for incoming events
//  while (1) {
//    memset(&buf, 0, BUFSIZE);
//    int n = lwip_read(s, buf, BUFSIZE);
//    for (int i = 0; i < n; i++){
//      parser1->feed(buf[i]);
//    }
//  }
//
//  //close socket after everything is done
//  lwip_close(s);
//}
//
//void queueRead (void *arg){
//  while (1){
//    notes newNote;
//    xQueueReceive(xQueue, &(newNote), 5000);
//  
//      if (newNote.status == STATUS_NOTE_ON && newNote.velocity > 0){
//        WMSynth.playToneN(newNote.note,newNote.velocity,0);
//      } else{
//        WMSynth.stopToneN(newNote.note);
//      }
//  }
//}

void timeBlink (void *arg){
  while(1){
    int pin;
    if (strBlink == "r"){
      pin = RED;
    }
    else if (strBlink == "b"){
      pin = BLUE;
    }
    else {
      pin = GREEN;
    }
    digitalWrite(pin, HIGH);
    delay(200);
    digitalWrite(pin, LOW);
    delay(200);
  }
}

void serialBlink (void *arg){
  while(1){
    if (SerialUSB.available()){
      String re = SerialUSB.readString();
      if (re == "b" || re == "r" || re == "g"){
        strBlink = re;
      }
    }
  }
}
//
//void serialRead (void *arg){
//  while(1){
//    if (SerialUSB.available()){
//      uint8_t re = SerialUSB.read();
//      parser2->feed(re);
//    }
//  }
//}
