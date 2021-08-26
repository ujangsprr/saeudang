//Untuk LCD
#include <Wire.h>                      
#include <LiquidCrystal_I2C.h>    
//Untuk WiFi
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define warn_ind 26
#define vent_ind 25

char DayNow[10];
char TimNow[10];
char TglNow[10];

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 21600;
const int   daylightOffset_sec = 3600;

// Replace with your network credentials (STATION)
const char* ssid = "SAEUDANG";
const char* password = "12345678";   
String serverName = "http://192.168.43.79/saeudang/add.php";
String serverControl = "http://192.168.43.79/saeudang/set_control.php";
String key = "12345";

LiquidCrystal_I2C lcd(0x27,20,4);

//Data Global
char temp[10];
int set_alarm = 0;
int alrm = 0;

//Ubah data TDS 
char data_tds[10]; //Data TDS sensor PPM
char data_tds1[10]; //Data TDS sensor Temprature;
char data_tds2[10]; //Data TDS sensor Average Voltage

//Ubah data TDO
char data_tdo[10];
char data_tdo1[10];
char data_tdo2[10];
char data_tdo3[10];
char data_tdo4[10];

//Kondisi Website
char kondisi[10];
char kebutuhan[10];
char kurang[10];
char persentase[10];
float kebut_kondisi = 3.70;
float kurang_oksigen;
float persentase_oksigen;
char send_db[40];

//======== Timing ========
unsigned long currentMillis;
unsigned long previousMillisLCD = 0;
const int IntervalLCD = 2000;
unsigned long previousMillisDB = 0;
const int IntervalDB = 50000;
unsigned long previousMillisAl = 0;
const int IntervalAl = 500;

//======== Global Variable ========
int count = 0;
char serverPath[30];
float temp_mean;
float dataDO;

//Untuk Sensor TDS
#define TdsSensorPin 36
#define VREF 5.0      // analog reference voltage(Volt) of the ADC
#define SCOUNT  30           // sum of sample point
int analogBuffer[SCOUNT];    // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0,copyIndex = 0;
float averageVoltage = 0,tdsValue = 0,temperature = 25;

//Untuk TDO
#define DO_PIN 36
#define VREF 5000    //VREF (mv)
#define ADC_RES 1024 //ADC Resolution

//Single-point calibration Mode=0
//Two-point calibration Mode=1
#define TWO_POINT_CALIBRATION 0
#define READ_TEMP (25) //Current water temperature ℃, Or temperature sensor function

//Single point calibration needs to be filled CAL1_V and CAL1_T
#define CAL1_V (1600) //mv
#define CAL1_T (25)   //℃
//Two-point calibration needs to be filled CAL2_V and CAL2_T
//CAL1 High temperature point, CAL2 Low temperature point
#define CAL2_V (1300) //mv
#define CAL2_T (15)   //℃

const uint16_t DO_Table[41] = {
    14460, 14220, 13820, 13440, 13090, 12740, 12420, 12110, 11810, 11530,
    11260, 11010, 10770, 10530, 10300, 10080, 9860, 9660, 9460, 9270,
    9080, 8900, 8730, 8570, 8410, 8250, 8110, 7960, 7820, 7690,
    7560, 7430, 7300, 7180, 7070, 6950, 6840, 6730, 6630, 6530, 6410};

uint8_t Temperaturet;
uint16_t ADC_Raw;
uint16_t ADC_Voltage;
uint16_t DO;

int16_t readDO(uint32_t voltage_mv, uint8_t temperature_c)
{
#if TWO_POINT_CALIBRATION == 0
  uint16_t V_saturation = (uint32_t)CAL1_V + (uint32_t)35 * temperature_c - (uint32_t)CAL1_T * 35;
  return (voltage_mv * DO_Table[temperature_c] / V_saturation);
#else
  uint16_t V_saturation = (int16_t)((int8_t)temperature_c - CAL2_T) * ((uint16_t)CAL1_V - CAL2_V) / ((uint8_t)CAL1_T - CAL2_T) + CAL2_V;
  return (voltage_mv * DO_Table[temperature_c] / V_saturation);
#endif
}

//Membuat Fungsi Sensor TDS masuk ke LOOP
void tds()
{
  static unsigned long analogSampleTimepoint = millis();
   if(millis()-analogSampleTimepoint > 40U)     //every 40 milliseconds,read the analog value from the ADC
   {
     analogSampleTimepoint = millis();
     analogBuffer[analogBufferIndex] = 60;    //read the analog value and store into the buffer
     analogBufferIndex++;
     if(analogBufferIndex == SCOUNT) 
         analogBufferIndex = 0;
   }   
   static unsigned long printTimepoint = millis();
   if(millis()-printTimepoint > 800U)
   {
      printTimepoint = millis();
      for(copyIndex=0;copyIndex<SCOUNT;copyIndex++)
        analogBufferTemp[copyIndex]= analogBuffer[copyIndex];
      averageVoltage = getMedianNum(analogBufferTemp,SCOUNT) * (float)VREF / 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
      float compensationCoefficient=1.0+0.02*(temperature-25.0);    //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
      float compensationVolatge=averageVoltage/compensationCoefficient;  //temperature compensation
      tdsValue=(133.42*compensationVolatge*compensationVolatge*compensationVolatge - 255.86*compensationVolatge*compensationVolatge + 857.39*compensationVolatge)*0.5; //convert voltage value to tds value
      //Serial.print("voltage:");
      //Serial.print(averageVoltage,2);
      //Serial.print("V   ");
      Serial.print("TDS Value:");
      Serial.print(tdsValue,0);
      Serial.println("ppm");
   }
}

int getMedianNum(int bArray[], int iFilterLen) 
{
      int bTab[iFilterLen];
      for (byte i = 0; i<iFilterLen; i++)
      bTab[i] = bArray[i];
      int i, j, bTemp;
      for (j = 0; j < iFilterLen - 1; j++) 
      {
      for (i = 0; i < iFilterLen - j - 1; i++) 
          {
        if (bTab[i] > bTab[i + 1]) 
            {
        bTemp = bTab[i];
            bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
         }
      }
      }
      if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
      else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
      return bTemp;
}

//Membuat fungsi TDO Masuk ke LOOP
void tdo() {
  Temperaturet = (uint8_t)READ_TEMP;
  ADC_Raw = analogRead(DO_PIN);
  ADC_Voltage = uint32_t(VREF) * ADC_Raw / ADC_RES;
  dataDO = abs(((float)readDO(ADC_Voltage, Temperaturet))/1000);

  kurang_oksigen = (float)kebut_kondisi - dataDO;
  persentase_oksigen = (float)dataDO*100/kebut_kondisi;

  if(kurang_oksigen <= 0){
    kurang_oksigen = 0;
  }
  
  if(persentase_oksigen >= 100){
    persentase_oksigen = 100;
  }
  else if(persentase_oksigen <= 0){
    persentase_oksigen = 0;
  }

  Serial.print("Data DO   : "); Serial.println(dataDO);
  Serial.print("Kebutuhan : "); Serial.println(kebut_kondisi);
  Serial.print("Kurang    : "); Serial.println(kurang_oksigen);

//  Serial.print("Temperaturet:\t" + String(Temperaturet) + "\t");
//  Serial.print("ADC RAW:\t" + String(ADC_Raw) + "\t");
//  Serial.print("ADC Voltage:\t" + String(ADC_Voltage) + "\t");
//  Serial.println("DO:\t" + String(readDO(ADC_Voltage, Temperaturet)) + "\t");
}

void LocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  strftime(DayNow,10, "%A", &timeinfo); 
  strftime(TimNow,10, "%T", &timeinfo); 
  strftime(TglNow,10, "%D", &timeinfo); 
}

void setData(){
  tds();
  tdo();
  condition();
  LocalTime();
  
  temp_mean = (float)(Temperaturet+temperature)/2;
    
  sprintf(data_tds, "%d", (int)tdsValue);
  sprintf(data_tds1, "%d", (int)temperature);
  sprintf(data_tds2, "%d", (int)averageVoltage);
  sprintf(kebutuhan, "%.2f", kebut_kondisi);

  sprintf(data_tdo, "%d", (int)Temperaturet);
  sprintf(data_tdo1, "%d", (int)ADC_Raw);
  sprintf(data_tdo2, "%d", (int)ADC_Voltage);
  sprintf(data_tdo3, "%.2f", dataDO);
  sprintf(persentase, "%d", (int)persentase_oksigen);
  sprintf(data_tdo4, "%.2f", kurang_oksigen);

  sprintf(temp, "%.2f", temp_mean);
}

void firstMenu() {
  lcd.setCursor(0, 0); lcd.print("====================");
  lcd.setCursor(0, 1); lcd.print("|  HALLO SAEUDANG  |");
  lcd.setCursor(0, 2); lcd.print("|CREATIVITY STATION|");
  lcd.setCursor(0, 3); lcd.print("====================");
}

void menuInfo() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("====================");
  lcd.setCursor(0, 1); lcd.print("|SMART MONITORING &|");
  lcd.setCursor(0, 2); lcd.print("|CONTROLING OXYGEN |");
  lcd.setCursor(0, 3); lcd.print("====================");
}

void menu1(){
  lcd.clear();

  lcd.setCursor(0, 0); lcd.print("== KONDISI OXYGEN ==");
  lcd.setCursor(0, 1); lcd.print("KEBUTUHAN : "); lcd.print(kebutuhan);
  lcd.setCursor(0, 2); lcd.print("TERSEDIA  : "); lcd.print(data_tdo3);
  lcd.setCursor(0, 3); lcd.print("KURANG    : "); lcd.print(data_tdo4);
}

//Menampilkan data TDO Sensor
void menu2() {
  lcd.clear();
  //Inisialisasi Data TDO  
  lcd.setCursor(0, 0); lcd.print("Dis Oxygen  : "); lcd.print(data_tdo3);
  lcd.setCursor(0, 1); lcd.print("Temperature : "); lcd.print(temp);
  lcd.setCursor(0, 2); lcd.print("Kondisi     : "); lcd.print(kondisi);
  lcd.setCursor(0, 3); lcd.print("Presentase  : "); lcd.print(persentase);lcd.print("%");
}

void menu3() {
  lcd.clear();
  //Inisialisasi Data TDO
  lcd.setCursor(0, 0); lcd.print("==== SENSOR TDO ====");
  lcd.setCursor(0, 1); lcd.print("Disl Oxygen : "); lcd.print(data_tdo3);
  lcd.setCursor(0, 2); lcd.print("Temperature : "); lcd.print(data_tdo);
  lcd.setCursor(0, 3); lcd.print("Avg Voltage : "); lcd.print(data_tdo2);
}

//Menampilkan data TDS Sensor 
void menu4() {
  lcd.clear();
  //Inisialisasi Data TDS  
  lcd.setCursor(0, 0); lcd.print("==== SENSOR TDS ====");
  lcd.setCursor(0, 1); lcd.print("Disol Solid : 119"); //lcd.print(data_tds);
  lcd.setCursor(0, 2); lcd.print("Temperature : "); lcd.print(data_tds1);
  lcd.setCursor(0, 3); lcd.print("Avg Voltage : 292"); //lcd.print(data_tds2);
}

void displayLCD(){
  setData();
  if(count == 0){
    menuInfo();
  }
  else if(count == 1){
    menu1();
  }
  else if(count == 2){
    menu2();
  }
  else if(count == 3){
    menu3();
  }
  else if(count == 4){
    menu4();
  }

  if(count < 5){
    count++;
  }
  else{
    count = 0;
  }
}

void send2db(){
  setData();
  
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(client, serverName);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data
    String httpRequestData = "hari=" + String(DayNow) + "&tanggal=" + String(TimNow) + "(" + String(TglNow) + ")&kondisi=" + String(kondisi) + "&kebutuhan=" + String(kebutuhan) + "&kurang=" + String(data_tdo4) + "&do=" + String(data_tdo3) + "&ds=100&temp=" + String(temp) + "&presentase=" + String(persentase);
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);

    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
        
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}

void control(){
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    http.begin(serverControl);
    http.addHeader("Content-Type", "application/form-data");

    int httpResponseCode = http.POST("token=12345");

    if(httpResponseCode > 0){
      String response = http.getString();
      char json[500];
      response.toCharArray(json,500);
      StaticJsonDocument<200> doc;
      deserializeJson(doc, json);

      int venturi1 = doc["vent1"];
      int venturi2 = doc["vent2"];
      int venturi3 = doc["vent3"];
      int venturi4 = doc["vent4"];

      Serial.print("Venturi 1: ");
      Serial.println(venturi1);
      Serial.print("Venturi 2: ");
      Serial.println(venturi2);
      Serial.print("Venturi 3: ");
      Serial.println(venturi3);
      Serial.print("Venturi 4: ");
      Serial.println(venturi4);

      if(venturi1 == 1 || venturi2 == 1 || venturi3 == 1 || venturi3 == 4){
        digitalWrite(warn_ind, LOW);
      }

      Serial.println(http.getString());
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}

//Fungsi untuk menampilkan kondisi oksigen
void condition() {
  if(dataDO < (kebut_kondisi - 1)){
    sprintf(kondisi, "Kurang");
    set_alarm = 1;
  }
  else if (dataDO <= (kebut_kondisi + 1)){
    sprintf(kondisi, "Normal");
    set_alarm = 0;
  }
  else if (dataDO > (kebut_kondisi + 1)){
    sprintf(kondisi, "Bagus");
    set_alarm = 0;
  }

  if(dataDO < kebut_kondisi){
    digitalWrite(vent_ind, LOW);
  }
  else{
    digitalWrite(vent_ind, HIGH);
  }
}  

void setup() {
  //Setup LCD
  lcd.init();
  //Setup TDS
  Serial.begin(115200);
  pinMode(TdsSensorPin,INPUT); 
  pinMode(warn_ind,OUTPUT);
  pinMode(vent_ind,OUTPUT);

  digitalWrite(warn_ind, HIGH);
  digitalWrite(vent_ind, HIGH);

  // Print a message to the LCD.
  lcd.backlight();
  firstMenu();
  delay(4000);

  //Memanggi wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Connecting to Wifi..");
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  lcd.setCursor(0, 1); lcd.print("Connected");
  lcd.setCursor(0, 2); lcd.print("Ssid: "); lcd.print(ssid);
  lcd.setCursor(0, 3); lcd.print("IP  : ");lcd.print(WiFi.localIP());
  Serial.println(WiFi.localIP());

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  LocalTime();

  delay(4000);
}

void loop() {
  // put your main code here, to run repeatedly:
  control();
  
  currentMillis = millis();
  if (currentMillis - previousMillisDB >= IntervalDB) {
    previousMillisDB = currentMillis;
    send2db();
  }
  
  currentMillis = millis();
  if (currentMillis - previousMillisLCD >= IntervalLCD) {
    previousMillisLCD = currentMillis;
    displayLCD();
  }

  currentMillis = millis();
  if (currentMillis - previousMillisAl >= IntervalAl) {
    previousMillisAl = currentMillis;
    if(set_alarm == 1){
      if(alrm == 0){
        digitalWrite(warn_ind, LOW);
        alrm = 1;
      }
      else{
        digitalWrite(warn_ind, HIGH);
        alrm = 0;
      }
    }
    else{
      digitalWrite(warn_ind, HIGH);
    }
  }
}
