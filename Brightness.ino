
boolean auto_brightness = true;
int manual_brightness = 128;

void adjust_brightness() {
  if (auto_brightness) {
    set_brightness(get_light_intensity()); 
  } else {
    set_brightness(manual_brightness);
  }
}

int get_light_intensity() {
  // int value = analogRead(PORT_LIGHT_SENSOR);
  // int scaledValue = (double) (value - FULL_AMBIENT_LIGHT) / NO_AMBIENT_LIGHT * 255.0;
  // if (scaledValue > 255) {
  //   scaledValue = 255;
  //}
  
  //return scaledValue;
  return 128; 
}

void set_brightness(int b) {
  
}
