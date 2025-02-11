#include <M5StickCPlus.h>
#include <Wire.h>
#include "porthub.h"

#define X_OFFSET 10
#define Y_OFFSET 9

PortHub porthub;
uint8_t HUB_ADDR[6] = {HUB1_ADDR, HUB2_ADDR, HUB3_ADDR,
                       HUB4_ADDR, HUB5_ADDR, HUB6_ADDR};

void setup() {
    M5.begin(true, false, true);
    M5.Lcd.setRotation(3);
    porthub.begin();
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
}

void loop() {
    M5.Lcd.fillScreen(BLACK);
    for (int i = 0; i < 6; i++) {
        M5.Lcd.setCursor(8 * X_OFFSET, (i * 2) * Y_OFFSET);
        // if (i == 0 || i == 3 || i == 4 || i == 5){
        if (i == 0 || i == 1 || i == 2){
          M5.Lcd.printf("%d:%d, %d", i + 1, porthub.hub_d_read_value_A(HUB_ADDR[i]), porthub.hub_d_read_value_B(HUB_ADDR[i])); 
        }
        if (i == 3){
          porthub.hub_d_wire_value_A(HUB_ADDR[i], 1); //write value high
          porthub.hub_d_wire_value_B(HUB_ADDR[i], 1); //write value high
          M5.Lcd.printf("%d:%d, %d", i + 1, porthub.hub_d_read_value_A(HUB_ADDR[i]), porthub.hub_d_read_value_B(HUB_ADDR[i])); 
        }
        else {
          M5.Lcd.printf("%d:%d", i + 1, porthub.hub_a_read_value(HUB_ADDR[i]));
        }
    }

    for (int i = 0; i < 6; i++) {
        porthub.hub_wire_setBrightness(HUB_ADDR[i], 1);
        porthub.hub_wire_fill_color(HUB_ADDR[i], 0, 15, 250, 250, 250);
    }
    delay(100);
}
