
#include "keypad_4_4.h"
#ifdef KEYPAD_4_4_ELEMENT_ENABLED


const Uint8 ROWS = 4; //four rows
const Uint8 COLS = 4; //four columns

//define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','A','B'},
  {'C','D','E','F'}
};

/* Initialize the 4 * 4 keyboard.
   StartPinForRow The row pin is 4 width. that means that 4 pins are needed from the start pin.
   StartPinForColumn The column pin is 4 width, that means that 4 pins are needed from the start pin. For example start with pin 0.
   VarElementNameInDomiq The element name in domiq base. For example start with 4.
*/
void KEYPAD_4_4_ELEMENT::initiate(Uint8 StartPinForRow, Uint8 StartPinForColumn, const String &VarElementNameInDomiq)
{
    Uint8 rowPins[ROWS] = {(Uint8)(StartPinForRow + 3u), (Uint8)(StartPinForRow + 2u), (Uint8)(StartPinForRow + 1u), StartPinForRow}; //connect to the row pinouts of the keypad
    Uint8 colPins[COLS] = {(Uint8)(StartPinForColumn + 3u), (Uint8)(StartPinForColumn + 2u), (Uint8)(StartPinForColumn + 1u), StartPinForColumn}; //connect to the column pinouts of the keypad
    
    Pad.initialize(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

    CONNECTED_ELEMENT_BASE::initiate(StartPinForRow, VarNameInDomiq);

}


void KEYPAD_4_4_ELEMENT::background_routine(void)
{
    char key = Pad.getKey();
    String keyValue = String(key);

    CONNECTED_ELEMENT_BASE::set_new_data_sampled(keyValue);
}


#endif // KEYPAD_4_4_ELEMENT_ENABLED