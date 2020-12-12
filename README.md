KSSR22_Blynk - program na wykrywanie hałasu
KSSR22_Rec - program do tworzenia nagrań
KSSR22 - schemat w Fritzing
UWAGI:
1. przy programie do nagrywania zamiast programu do wykrywania hałasu brązowy kabel od guzika trzeba wpiąc w pin cyfrowy 2 zamiast niebieskiego i zielonego i vice versa
2. Edit pcmConfig.h
    a: On Uno or non-mega boards, #define buffSize 128. May need to increase.
    b: Uncomment #define ENABLE_RECORDING and #define BLOCK_COUNT 10000UL
3. zaimportowac czytnik kart SD, mikrofon MAX9814 i modul ESP do fritzing
    linki skąd to wziąłem: https://github.com/ydonnelly/ESP8266_fritzing/blob/master/ESP8266-01%20WiFi%20Module.fzpz
                           https://github.com/robertoostenveld/fritzing/blob/master/SD%20Card%20Module.fzpz
                           https://github.com/adafruit/Fritzing-Library/blob/master/parts/Adafruit%20MAX9814%20Electret%20Microphone%20Amplifier.fzpz
