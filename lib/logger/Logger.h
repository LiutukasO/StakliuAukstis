
#ifdef IN_DEBUG_MODE
    #define PRINTS(s)   { Serial.print(F(s)); }
    #define PRINT(s,v)  { Serial.print(F(s)); Serial.print(v); }
    #define PRINTX(s,v) { Serial.print(F(s)); Serial.print(F("0x")); Serial.print(v, HEX); }
    #define PRINTSLN(s)   { Serial.println(F(s)); }
    #define PRINTLN(s,v)  { Serial.print(F(s)); Serial.println(v); }
    #define PRINTXLN(s,v) { Serial.print(F(s)); Serial.print(F("0x")); Serial.println(v, HEX); }
#else
    #define PRINTS(s)
    #define PRINT(s,v)
    #define PRINTX(s,v)
    #define PRINTSLN(s)
    #define PRINTLN(s,v)
    #define PRINTXLN(s,v)
#endif
