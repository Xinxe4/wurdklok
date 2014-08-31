//Reading temperature from MCP9808 I2C temperature sensor and remembering min/max temperatures.

int temp = 0;
int temp_min = 0;
int temp_max = 0;
boolean temp_init = false;

void read_temperature() {
  temp = tempsensor.readTempC_int();
  
  // Set min-max temperatures
  if (temp > temp_max) { 
    temp_max = temp;
  } else if (temp < temp_min) {
    temp_min = temp;
  }
  
  // Initialize min-max temperatures once
  if (!temp_init) {
    temp_min = temp;
    temp_max = temp;
  }
  
  temp_init = true;
}

int get_temperature() {
  return temp;
}

int get_temperature_min() {
  return temp_min;
}

int get_temperature_max() {
  return temp_max;
}

void get_temperature_char(char * tc) {
  int ti = get_temperature();
  itoa(ti, tc, 10);
}

