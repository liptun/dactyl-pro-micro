#include <Arduino.h>
#include <KeyboardioHID.h>
#include <Wire.h>

// Right

const int colCount = 6;
const int rowCount = 6;

const int colPins[colCount] = { 9, 8, 7, 6, 5, 4 };
const int rowPins[rowCount] = { 10, 16, 14, 15, 18, 19 };

// Local keys
int keyMap[colCount * rowCount] = {0};
bool keyPressed[colCount * rowCount] = {0};

// Remote keys (I2C)
bool remoteKeyActive[colCount * rowCount] = {0};
bool remoteKeyPressed[colCount * rowCount] = {0};
int remoteKeyMap[colCount * rowCount] = {0};


void remoteKeysUpdate(bool state) {
    int i = 0;
    while(Wire.available()) {
        remoteKeyActive[i++] = Wire.read();
    }
}

void setup()
{
    Serial.begin(9600);

    keyMap[0] = HID_KEYBOARD_A_AND_A;


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

	int keyIndex = 0;
    for (int row = 0; row < rowCount; row++) {
        digitalWrite(rowPins[row], LOW);
        for (int col = 0; col < colCount; col++) {
            delayMicroseconds(100);
            if (digitalRead(colPins[col]) == LOW) {
                if (!keyPressed[keyIndex]) {
                    keyPressed[keyIndex] = true;
                    Serial.print(keyIndex); 
                    Serial.println("R pressed");
                }
            } else {
                if(keyPressed[keyIndex]) {
                    keyPressed[keyIndex] = false;
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
                Serial.print(i);
                Serial.println("L press");
                //Keyboard.press(keysMap[i]);
                //Keyboard.sendReport();
            }
        } else {
            if (remoteKeyPressed[i]) {
                Serial.print(i);
                Serial.println("L release");
                remoteKeyPressed[i] = false;
                //Keyboard.release(keysMap[i]);
                //Keyboard.sendReport();
            }
        }
    } 
}

// 
// HID_SYSTEM_POWER_DOWN                   
// HID_SYSTEM_SLEEP                    
// HID_SYSTEM_WAKE_UP                  
// HID_SYSTEM_CONTEXT_MENU                 
// HID_SYSTEM_MAIN_MENU                    
// HID_SYSTEM_APP_MENU                 
// HID_SYSTEM_MENU_HELP                    
// HID_SYSTEM_MENU_EXIT                    
// HID_SYSTEM_MENU_SELECT                  
// HID_SYSTEM_MENU_RIGHT                   
// HID_SYSTEM_MENU_LEFT                    
// HID_SYSTEM_MENU_UP                  
// HID_SYSTEM_MENU_DOWN                    
// HID_SYSTEM_COLD_RESTART                 
// HID_SYSTEM_WARM_RESTART                 
// HID_D_PAD_UP                        
// HID_D_PAD_DOWN                      
// HID_D_PAD_RIGHT                     
// HID_D_PAD_LEFT                      
// HID_INDEX_TRIGGER                   
// HID_PALM_TRIGGER                    
// HID_THUMBSTICK                      
// HID_SYSTEM_FUNCTION_SHIFT               
// HID_SYSTEM_FUNCTION_SHIFT_LOCK              
// HID_SYSTEM_FUNCTION_SHIFT_LOCK_INDICATOR        
// HID_DISMISS_NOTIFICATION                
// HID_DO_NOT_DISTURB                  
// HID_SYSTEM_DOCK                     
// HID_SYSTEM_UNDOCK                   
// HID_SYSTEM_SETUP                    
// HID_SYSTEM_BREAK                    
// HID_SYSTEM_DEBUGGER_BREAK               
// HID_APPLICATION_BREAK                   
// HID_APPLICATION_DEBUGGER_BREAK              
// HID_SYSTEM_SPEAKER_MUTE                 
// HID_SYSTEM_HIBERNATE                    
// HID_SYSTEM_DISPLAY_INVERT               
// HID_SYSTEM_DISPLAY_INTERNAL             
// HID_SYSTEM_DISPLAY_EXTERNAL             
// HID_SYSTEM_DISPLAY_BOTH                 
// HID_SYSTEM_DISPLAY_DUAL                 
// HID_SYSTEM_DISPLAY_TOGGLE_INT_SLASH_EXT         
// HID_SYSTEM_DISPLAY_SWAP_PRIMARY_SLASH_SECONDARY     
// HID_SYSTEM_DISPLAY_LCD_AUTOSCALE            
// HID_KEYBOARD_NO_EVENT                   
// HID_KEYBOARD_ERROR_ROLLOVER             
// HID_KEYBOARD_POST_FAIL                  
// HID_KEYBOARD_ERROR_UNDEFINED                
// HID_KEYBOARD_A_AND_A                    
// HID_KEYBOARD_B_AND_B                    
// HID_KEYBOARD_C_AND_C                    
// HID_KEYBOARD_D_AND_D                    
// HID_KEYBOARD_E_AND_E                    
// HID_KEYBOARD_F_AND_F                    
// HID_KEYBOARD_G_AND_G                    
// HID_KEYBOARD_H_AND_H                    
// HID_KEYBOARD_I_AND_I                    
// HID_KEYBOARD_J_AND_J                    
// HID_KEYBOARD_K_AND_K                    
// HID_KEYBOARD_L_AND_L                    
// HID_KEYBOARD_M_AND_M                    
// HID_KEYBOARD_N_AND_N                    
// HID_KEYBOARD_O_AND_O                    
// HID_KEYBOARD_P_AND_P                    
// HID_KEYBOARD_Q_AND_Q                    
// HID_KEYBOARD_R_AND_R                    
// HID_KEYBOARD_S_AND_S                    
// HID_KEYBOARD_T_AND_T                    
// HID_KEYBOARD_U_AND_U                    
// HID_KEYBOARD_V_AND_V                    
// HID_KEYBOARD_W_AND_W                    
// HID_KEYBOARD_X_AND_X                    
// HID_KEYBOARD_Y_AND_Y                    
// HID_KEYBOARD_Z_AND_Z                    
// HID_KEYBOARD_1_AND_EXCLAMATION_POINT            
// HID_KEYBOARD_2_AND_AT                   
// HID_KEYBOARD_3_AND_POUND                
// HID_KEYBOARD_4_AND_DOLLAR               
// HID_KEYBOARD_5_AND_PERCENT              
// HID_KEYBOARD_6_AND_CARAT                
// HID_KEYBOARD_7_AND_AMPERSAND                
// HID_KEYBOARD_8_AND_ASTERISK             
// HID_KEYBOARD_9_AND_LEFT_PAREN               
// HID_KEYBOARD_
// HID_KEYBOARD_ENTER                  
// //HID_KEYBOARD_ENTER  HID_KEYBOARD_ENTER_SLASH_RETURN
// HID_KEYBOARD_ESCAPE                 
// HID_KEYBOARD_DELETE                 
// //HID_KEYBOARD_BACKSPACE    HID_KEYBOARD_DELETE
// HID_KEYBOARD_TAB                    
// HID_KEYBOARD_SPACEBAR                   
// HID_KEYBOARD_MINUS_AND_UNDERSCORE           
// HID_KEYBOARD_EQUALS_AND_PLUS                
// HID_KEYBOARD_LEFT_BRACKET_AND_LEFT_CURLY_BRACE      
// HID_KEYBOARD_RIGHT_BRACKET_AND_RIGHT_CURLY_BRACE    
// HID_KEYBOARD_BACKSLASH_AND_PIPE             
// HID_KEYBOARD_NON_US_POUND_AND_TILDE         
// HID_KEYBOARD_SEMICOLON_AND_COLON            
// HID_KEYBOARD_QUOTE_AND_DOUBLEQUOTE          
// HID_KEYBOARD_GRAVE_ACCENT_AND_TILDE         
// HID_KEYBOARD_COMMA_AND_LESS_THAN            
// HID_KEYBOARD_PERIOD_AND_GREATER_THAN            
// HID_KEYBOARD_SLASH_AND_QUESTION_MARK            
// HID_KEYBOARD_CAPS_LOCK                  
// HID_KEYBOARD_F1                     
// HID_KEYBOARD_F2                     
// HID_KEYBOARD_F3                     
// HID_KEYBOARD_F4                     
// HID_KEYBOARD_F5                     
// HID_KEYBOARD_F6                     
// HID_KEYBOARD_F7                     
// HID_KEYBOARD_F8                     
// HID_KEYBOARD_F9                     
// HID_KEYBOARD_F1
// HID_KEYBOARD_F11                    
// HID_KEYBOARD_F12                    
// HID_KEYBOARD_PRINTSCREEN                
// HID_KEYBOARD_SCROLL_LOCK                
// HID_KEYBOARD_PAUSE                  
// HID_KEYBOARD_INSERT                 
// HID_KEYBOARD_HOME                   
// HID_KEYBOARD_PAGE_UP                    
// HID_KEYBOARD_DELETE_FORWARD             
// HID_KEYBOARD_END                    
// HID_KEYBOARD_PAGE_DOWN                  
// HID_KEYBOARD_RIGHT_ARROW                
// HID_KEYBOARD_LEFT_ARROW                 
// HID_KEYBOARD_DOWN_ARROW                 
// HID_KEYBOARD_UP_ARROW                   
// HID_KEYPAD_NUM_LOCK_AND_CLEAR               
// HID_KEYPAD_DIVIDE                   
// HID_KEYPAD_MULTIPLY                 
// HID_KEYPAD_SUBTRACT                 
// HID_KEYPAD_ADD                      
// HID_KEYPAD_ENTER                    
// HID_KEYPAD_1_AND_END                    
// HID_KEYPAD_2_AND_DOWN_ARROW             
// HID_KEYPAD_3_AND_PAGE_DOWN              
// HID_KEYPAD_4_AND_LEFT_ARROW             
// HID_KEYPAD_5                        
// HID_KEYPAD_6_AND_RIGHT_ARROW                
// HID_KEYPAD_7_AND_HOME                   
// HID_KEYPAD_8_AND_UP_ARROW               
// HID_KEYPAD_9_AND_PAGE_UP                
// HID_KEYPAD_
// HID_KEYPAD_PERIOD_AND_DELETE                
// HID_KEYBOARD_NON_US_BACKSLASH_AND_PIPE          
// HID_KEYBOARD_APPLICATION                
// HID_KEYBOARD_POWER                  
// HID_KEYPAD_EQUALS                   
// HID_KEYBOARD_F13                    
// HID_KEYBOARD_F14                    
// HID_KEYBOARD_F15                    
// HID_KEYBOARD_F16                    
// HID_KEYBOARD_F17                    
// HID_KEYBOARD_F18                    
// HID_KEYBOARD_F19                    
// HID_KEYBOARD_F2
//