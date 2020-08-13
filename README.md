<p align="center">
<img src="doc/OLIB_LOGO.png" align="center" width="360" height="150"/> 
 </p>

# OLib
Just a collection of libraries i have created, olib, own libraray...
# OREG
This is a library for managing registry keys in windows.
You can Create/Write, Read and check if it exists.

``` C++

#include <oreg.h>

int main() {
  /*
  AVAILABLE TYPES:
  OREG_STRING
  OREG_INT
  OREG_BOOL
  */
  olib::oreg_key<olib::oreg::OREG_STRING> reg(olib::oreg::keys::CURRENT_USER, 
                                                  "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\run\\ArduinoMixer");
  reg.set_value("C:\\Program Files\\ArduinoMixer\\ArduinoMixer.exe");
  if(!olib::oreg::write(&reg)) {
    printf("NOPE!\n");
    return 0;
  }
  if(olib::oreg::read(&reg)) {
    // the return type of value is based on the template parameter given above!
    printf("Value: %s\n", reg.value().c_str());
  }
}
```
