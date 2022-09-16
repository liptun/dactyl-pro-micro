#include <Arduino.h>
#include <Wire.h>

// LEFT

const int colCount = 6;
const int rowCount = 6;

const int colPins[colCount] = { 9, 8, 7, 6, 5, 4 };
const int rowPins[rowCount] = { 10, 16, 14, 15, 18, 19 };

int keyMap[colCount * rowCount] = {0};
bool keyPressed[colCount * rowCount] = {0};



void setup()
{
    Serial.begin(9600);

    for (int i = 0; i < colCount; i++) {
        pinMode(colPins[i], INPUT_PULLUP);
    }
    for (int i = 0; i < rowCount; i++) {
        pinMode(rowPins[i], OUTPUT);
        digitalWrite(rowPins[i], HIGH);
    }

    Wire.begin();
}

void loop()
{

	int keyIndex = 0;
    for (int row = 0; row < rowCount; row++) {
        digitalWrite(rowPins[row], LOW);
        for (int col = 0; col < colCount; col++) {
            delayMicroseconds(100);
            if (digitalRead(colPins[col]) == LOW) {
                if (!keyPressed[keyIndex]) {
                    keyPressed[keyIndex] = true;
                    Serial.print(keyIndex); 
                    Serial.println(" pressed");
                }
            } else {
                if(keyPressed[keyIndex]) {
                    keyPressed[keyIndex] = false;
                    Serial.print(keyIndex); 
                    Serial.println(" released");
                }
            }
            keyIndex++;
        }
        digitalWrite(rowPins[row], HIGH);
        delayMicroseconds(100);
    }

    Wire.beginTransmission(9);
    for (int i = 0; i < colCount * rowCount; i++) {
        Wire.write(keyPressed[i]);
    }
    Wire.endTransmission();

}
