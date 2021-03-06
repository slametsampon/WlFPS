/*
  pbAMR.h - Library for P/B Auto, Manual, Reset
  By : Sam March 01, 2021
*/

/* Dependencies */
#include "pbAMR.h"

PbAMR::PbAMR(SwitchExt *pbAuto, SwitchExt *pbManual, SwitchExt *pbReset): _pbAuto(pbAuto), _pbManual(pbManual), _pbReset(pbReset){}

int PbAMR::getCmd(unsigned long debounceTime){
    int cmd;
    if (_pbReset->isStatus(debounceTime)){
      if (_prevCmd == PB_RESET) cmd = PB_READY;//highest priority
      else if (_prevCmd == PB_READY) cmd = PB_READY;//highest priority
      else cmd = PB_RESET;//highest priority
      if(_prevCmd != cmd) _isInfo = false;
      _prevCmd = cmd;
    }
    else {
        if((_pbAuto->isStatus(debounceTime) && (_prevCmd != PB_MANUAL_ON))){
            cmd = PB_AUTO;//lower priority
            if(_prevCmd != cmd) _isInfo = false;
            _prevCmd = cmd;
        }
        if(_pbManual->isStatus(debounceTime)){
          if (_prevCmd == PB_MANUAL) cmd = PB_MANUAL_ON;//higher priority
          else if (_prevCmd == PB_MANUAL_ON) cmd = PB_MANUAL_ON;//higher priority
          else cmd = PB_MANUAL;//higher priority

          if(_prevCmd != cmd) _isInfo = false;
          _prevCmd = cmd;
        }
        else cmd = _prevCmd;
    }
    return cmd;
}

String PbAMR::status(){
    String str = "NO_PB";
    switch (_prevCmd)
    {
    case PB_AUTO:
        str = "PB : Auto";
        break;
    
    case PB_MANUAL:
        str = "PB : Manual";
        break;
    
    case PB_MANUAL_ON:
        str = "PB : Manual ON";
        break;
    
    case PB_READY:
        str = "PB : Ready";
        break;
    
    case PB_RESET:
        str = "PB : Reset";
        break;
    
    default:
        break;
    }
    return str;
}

void PbAMR::info(){
    String str;
    str = String("_pbAuto \n");//with new line
    str = String(str + _pbAuto->info());
    Serial.println(str);

    str = String("_pbManual \n");//with new line
    str = String(str + _pbManual->info());
    Serial.println(str);
    
    str = String("_pbReset \n");//with new line
    str = String(str + _pbReset->info());
    Serial.println(str);
    
}