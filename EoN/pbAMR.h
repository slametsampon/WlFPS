/*
  pbAMR.h - Library for Push Button Auto, Manual, Reset
  Priority :
    1. Reset
    2. Manual
    3. Auto
  By : Sam March 01, 2021
*/

#ifndef pbAMR_h
#define pbAMR_h

const int PB_READY = 0;
const int PB_AUTO = 1;
const int PB_MANUAL = 2;
const int PB_MANUAL_ON = 3;
const int PB_RESET = 4;
//const unsigned long DEBOUNCE_PB = 150;//milli second

#include "Arduino.h"
#include "src\switchExt\switchExt.h"

    class PbAMR{
        public:
            PbAMR(SwitchExt*, SwitchExt*, SwitchExt*);
            int getCmd(unsigned long);
            String status();
            void info();
        private:
            SwitchExt *_pbAuto, *_pbManual, *_pbReset;
            int    _prevCmd;
            bool  _isInfo;//one shoot info
    };

#endif
