
boolean manual_brightness = false;
int manual_brightness_val = 128;

void adjust_brightness() {
  if (manual_brightness) {
    apply_brightness(manual_brightness_val);
  } else {
    apply_brightness(get_light_intensity());
  }
}

int get_light_intensity() {
  int value = analogRead(PORT_LIGHT_SENSOR);
  int scaledValue = (double) (value - FULL_AMBIENT_LIGHT) / NO_AMBIENT_LIGHT * 255.0;
  if (scaledValue > 255) {
    scaledValue = 255;
  }
  mySerial.print(value);mySerial.write(";");
  return (255 - scaledValue);
}

int get_brightness_value() {
 return manual_brightness_val;
}

void set_brightness_value(int b) {
 manual_brightness_val = b;
}

void apply_brightness(int b) {
  analogWrite(PORT_STATUS_LED, b);
}

void set_manual_brightness(boolean b) {
  manual_brightness = b;
}

boolean get_manual_brightness() {
  return manual_brightness;
}
