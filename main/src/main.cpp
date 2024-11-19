#include <Arduino.h>
#include <KeyboardioHID.h>
#include <Wire.h>

// Right

const int colCount = 6;
const int rowCount = 6;

const int colPins[colCount] = { 9, 8, 7, 6, 5, 4 };
const int rowPins[rowCount] = { 10, 16, 14, 15, 18, 19 };

// Local keys

bool keyPressed[colCount * rowCount] = {0};

// Remote keys (I2C)
bool remoteKeyActive[colCount * rowCount] = {0};
bool remoteKeyPressed[colCount * rowCount] = {0};


int localMapLayer1[colCount * rowCount] = {0};
int localMapLayer2[colCount * rowCount] = {0};
int localMapLayer3[colCount * rowCount] = {0};

int remoteMapLayer1[colCount * rowCount] = {0};
int remoteMapLayer2[colCount * rowCount] = {0};
int remoteMapLayer3[colCount * rowCount] = {0};


int layer = 1;

int localFnKey = 35;
int remoteFnKey = 31;

bool localFnPressed = false;
bool remoteFnPressed = false;

void remoteKeysUpdate(int state) {
    int i = 0;
    while(Wire.available()) {
        remoteKeyActive[i++] = Wire.read();
    }
}

void setup()
{
    Serial.begin(9600);

    // Right
    localMapLayer1[5] = HID_KEYBOARD_6_AND_CARAT;
    localMapLayer1[4] = HID_KEYBOARD_7_AND_AMPERSAND;
    localMapLayer1[3] = HID_KEYBOARD_8_AND_ASTERISK;
    localMapLayer1[2] = HID_KEYBOARD_9_AND_LEFT_PAREN;
    localMapLayer1[1] = HID_KEYBOARD_0_AND_RIGHT_PAREN;
    localMapLayer1[0] = HID_KEYBOARD_DELETE;

    localMapLayer1[11] = HID_KEYBOARD_Y_AND_Y;
    localMapLayer1[10] = HID_KEYBOARD_U_AND_U;
    localMapLayer1[9] = HID_KEYBOARD_I_AND_I;
    localMapLayer1[8] = HID_KEYBOARD_O_AND_O;
    localMapLayer1[7] = HID_KEYBOARD_P_AND_P;
    localMapLayer1[6] = HID_KEYBOARD_BACKSLASH_AND_PIPE;

    localMapLayer1[17] = HID_KEYBOARD_H_AND_H;
    localMapLayer1[16] = HID_KEYBOARD_J_AND_J;
    localMapLayer1[15] = HID_KEYBOARD_K_AND_K;
    localMapLayer1[14] = HID_KEYBOARD_L_AND_L;
    localMapLayer1[13] = HID_KEYBOARD_SEMICOLON_AND_COLON;
    localMapLayer1[12] = HID_KEYBOARD_QUOTE_AND_DOUBLEQUOTE;

    localMapLayer1[23] = HID_KEYBOARD_N_AND_N;
    localMapLayer1[22] = HID_KEYBOARD_M_AND_M;
    localMapLayer1[21] = HID_KEYBOARD_COMMA_AND_LESS_THAN;
    localMapLayer1[20] = HID_KEYBOARD_PERIOD_AND_GREATER_THAN;
    localMapLayer1[19] = HID_KEYBOARD_SLASH_AND_QUESTION_MARK;
    localMapLayer1[18] = HID_KEYBOARD_RIGHT_SHIFT;

    localMapLayer1[24] = HID_KEYBOARD_EQUALS_AND_PLUS;

    localMapLayer1[27] = HID_KEYBOARD_LEFT_BRACKET_AND_LEFT_CURLY_BRACE;
    localMapLayer1[26] = HID_KEYBOARD_RIGHT_BRACKET_AND_RIGHT_CURLY_BRACE;

    localMapLayer1[28] = HID_KEYBOARD_ENTER;
    localMapLayer1[29] = HID_KEYBOARD_RIGHT_ALT;

    localMapLayer1[32] = HID_KEYBOARD_PAGE_DOWN;
    localMapLayer1[33] = HID_KEYBOARD_RIGHT_GUI;
    localMapLayer1[34] = HID_KEYBOARD_PAGE_UP;

    // Layer 2 and 3 default
    for (int i = 0; i < rowCount * colCount; i++) {
        localMapLayer2[i] = localMapLayer1[i];
        localMapLayer3[i] = localMapLayer1[i];
    } 

    localMapLayer2[5] = HID_KEYBOARD_F6;
    localMapLayer2[4] = HID_KEYBOARD_F7;
    localMapLayer2[3] = HID_KEYBOARD_F8;
    localMapLayer2[2] = HID_KEYBOARD_F9;
    localMapLayer2[1] = HID_KEYBOARD_F10;
    localMapLayer2[0] = HID_KEYBOARD_F11;
    localMapLayer2[6] = HID_KEYBOARD_F12;

    localMapLayer3[0] = HID_KEYBOARD_DELETE_FORWARD;

    localMapLayer3[7] = HID_KEYBOARD_PRINTSCREEN;

    localMapLayer3[17] = HID_KEYBOARD_LEFT_ARROW;
    localMapLayer3[16] = HID_KEYBOARD_DOWN_ARROW;
    localMapLayer3[15] = HID_KEYBOARD_UP_ARROW;
    localMapLayer3[14] = HID_KEYBOARD_RIGHT_ARROW;

    // Left

    remoteMapLayer1[0] = HID_KEYBOARD_ESCAPE;
    remoteMapLayer1[1] = HID_KEYBOARD_1_AND_EXCLAMATION_POINT;
    remoteMapLayer1[2] = HID_KEYBOARD_2_AND_AT;
    remoteMapLayer1[3] = HID_KEYBOARD_3_AND_POUND;
    remoteMapLayer1[4] = HID_KEYBOARD_4_AND_DOLLAR;
    remoteMapLayer1[5] = HID_KEYBOARD_5_AND_PERCENT;

    remoteMapLayer1[6] = HID_KEYBOARD_TAB;
    remoteMapLayer1[7] = HID_KEYBOARD_Q_AND_Q;
    remoteMapLayer1[8] = HID_KEYBOARD_W_AND_W;
    remoteMapLayer1[9] = HID_KEYBOARD_E_AND_E;
    remoteMapLayer1[10] = HID_KEYBOARD_R_AND_R;
    remoteMapLayer1[11] = HID_KEYBOARD_T_AND_T;

    remoteMapLayer1[12] = HID_KEYBOARD_CAPS_LOCK;
    remoteMapLayer1[13] = HID_KEYBOARD_A_AND_A;
    remoteMapLayer1[14] = HID_KEYBOARD_S_AND_S;
    remoteMapLayer1[15] = HID_KEYBOARD_D_AND_D;
    remoteMapLayer1[16] = HID_KEYBOARD_F_AND_F;
    remoteMapLayer1[17] = HID_KEYBOARD_G_AND_G;

    remoteMapLayer1[18] = HID_KEYBOARD_LEFT_SHIFT;
    remoteMapLayer1[19] = HID_KEYBOARD_Z_AND_Z;
    remoteMapLayer1[20] = HID_KEYBOARD_X_AND_X;
    remoteMapLayer1[21] = HID_KEYBOARD_C_AND_C;
    remoteMapLayer1[22] = HID_KEYBOARD_V_AND_V;
    remoteMapLayer1[23] = HID_KEYBOARD_B_AND_B;

    remoteMapLayer1[24] = HID_KEYBOARD_EQUALS_AND_PLUS;
    remoteMapLayer1[25] = HID_KEYBOARD_MINUS_AND_UNDERSCORE;

    remoteMapLayer1[26] = HID_KEYBOARD_SPACEBAR;
    remoteMapLayer1[27] = HID_KEYBOARD_LEFT_CONTROL;


    remoteMapLayer1[28] = HID_KEYBOARD_END;
    remoteMapLayer1[30] = HID_KEYBOARD_HOME;
    remoteMapLayer1[29] = HID_KEYBOARD_LEFT_GUI;


    // Alt keymapping when FN is pressed
    for (int i = 0; i < rowCount * colCount; i++) {
        remoteMapLayer2[i] = remoteMapLayer1[i];
        remoteMapLayer3[i] = remoteMapLayer1[i];
    } 

    remoteMapLayer2[0] = HID_KEYBOARD_GRAVE_ACCENT_AND_TILDE;
    remoteMapLayer2[1] = HID_KEYBOARD_F1;
    remoteMapLayer2[2] = HID_KEYBOARD_F2;
    remoteMapLayer2[3] = HID_KEYBOARD_F3;
    remoteMapLayer2[4] = HID_KEYBOARD_F4;
    remoteMapLayer2[5] = HID_KEYBOARD_F5;

    remoteMapLayer2[15] = HID_KEYBOARD_DELETE_FORWARD;



    for (int i = 0; i < colCount; i++) {
        pinMode(colPins[i], INPUT_PULLUP);
    }
    for (int i = 0; i < rowCount; i++) {
        pinMode(rowPins[i], OUTPUT);
        digitalWrite(rowPins[i], HIGH);
    }

    Keyboard.begin();
    Wire.begin(9);
    Wire.onReceive(remoteKeysUpdate);
}

void loop()
{

    layer = 1;

    if (remoteFnPressed) {
        layer = 2;
    }

    if (localFnPressed) {
        layer = 3;
    }

	int keyIndex = 0;
    for (int row = 0; row < rowCount; row++) {
        digitalWrite(rowPins[row], LOW);
        for (int col = 0; col < colCount; col++) {
            delayMicroseconds(100);
            if (digitalRead(colPins[col]) == LOW) {
                if (!keyPressed[keyIndex]) {
                    keyPressed[keyIndex] = true;
                    switch (layer) {
                        case 1:
                            Keyboard.press(localMapLayer1[keyIndex]);
                            break;
                        case 2:
                            Keyboard.press(localMapLayer2[keyIndex]);
                            break;
                        case 3:
                            Keyboard.press(localMapLayer3[keyIndex]);
                            break;
                    }
                    Keyboard.sendReport();

                    if (keyIndex == localFnKey) {
                        localFnPressed = true;
                    }


                    Serial.print(keyIndex); 
                    Serial.println("R pressed");
                }
            } else {
                if(keyPressed[keyIndex]) {
                    keyPressed[keyIndex] = false;
                    Keyboard.release( localMapLayer1[keyIndex] );
                    Keyboard.release( localMapLayer2[keyIndex] );
                    Keyboard.release( localMapLayer3[keyIndex] );
                    Keyboard.sendReport();

                    if (keyIndex == localFnKey) {
                        localFnPressed = false;
                    }

                    Serial.print(keyIndex); 
                    Serial.println("R released");
                }
            }
            keyIndex++;
        }
        digitalWrite(rowPins[row], HIGH);
        delayMicroseconds(100);
    }


    for (int i = 0; i < colCount * rowCount; i++) {
        if (remoteKeyActive[i]) {
            if (!remoteKeyPressed[i]) {
                remoteKeyPressed[i] = true;
                switch (layer) {
                    case 1:
                        Keyboard.press(remoteMapLayer1[i]);
                        break;
                    case 2:
                        Keyboard.press(remoteMapLayer2[i]);
                        break;
                    case 3:
                        Keyboard.press(remoteMapLayer3[i]);
                        break;
                }
                Keyboard.sendReport();

                if (i == remoteFnKey) {
                    remoteFnPressed = true;
                }

                Serial.print(i);
                Serial.println("L press");
            }
        } else {
            if (remoteKeyPressed[i]) {
                remoteKeyPressed[i] = false;
                Keyboard.release( remoteMapLayer1[i] );
                Keyboard.release( remoteMapLayer2[i] );
                Keyboard.release( remoteMapLayer3[i] );
                Keyboard.sendReport();

                if (i == remoteFnKey) {
                    remoteFnPressed = false;
                }

                Serial.print(i);
                Serial.println("L release");
            }
        }
    } 

    //Serial.println(isFN);
}
