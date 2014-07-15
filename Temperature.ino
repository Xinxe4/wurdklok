float temp = 0.0;
float temp_min = 0.0;
float temp_max = 0.0;
boolean temp_init = false;

void read_temperature() {
  temp = tempsensor.readTempC();
  
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

float get_temperature() {
  return temp;
}

float get_temperature_min() {
  return temp_min;
}

float get_temperature_max() {
  return temp_max;
}



