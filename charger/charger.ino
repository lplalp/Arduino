#include "esp_adc_cal.h"
#include "driver/adc.h"

#define sense1 30
#define sense2 31
#define Sense_Resistor 1.0

int gate_voltage_raw = 0;

uint32_t readADC_Cal(int ADC_Raw){
  esp_adc_cal_characteristics_t adc_chars;
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
  return esp_adc_cal_raw_to_voltage(ADC_Raw, &adc_chars);
}

int strobe_voltage(uint8_t pin){
  return readADC_Cal(analogRead(pin));
}

double current_sense(uint8_t pin1, uint8_t pin2, double Rs){
  double strobe1[10], strobe2[10];
  double avg1 = 0, avg2 = 0;
  for(int i=0; i<10; i++){
    strobe1[i] = strobe_voltage(pin1);
    strobe2[i] = strobe_voltage(pin2);
  }
  for(int i=0; i<10; i++){
    avg1 += strobe1[i];
    avg2 += strobe2[i];
  }
  avg1 /= 10;
  avg2 /= 10;
  return unsigned (avg1 - avg2) / Rs;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");

  
}

void loop() {
  

}

