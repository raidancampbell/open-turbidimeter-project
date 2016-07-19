/*--------------------------------Calibration--------------------------------*/

void waitForKeypress() {
  Serial.println("Press any key to continue...");
  while (true) {
    if (Serial.available() > 0) {
      Serial.read();  // don't forget to remove the character from the buffer
      return;
    }
  }
}

void calibrate(){
  float y[10]; // raw readings
  float x[10] = {0.0, 0.2, 0.5, 10, 30, 100, 300, 500, 1200}; // NTU
  float m[5]; // slopes (readings/NTU)

//  displayForInterval(0, "ready",50000);
  Serial.println("Starting calibration.");

//  displayForInterval(x[0], "data",10000);

  Serial.print("Insert ");
  Serial.print(x[0]);
  Serial.println(" NTU calibration sample.");
  waitForKeypress();
  y[0] = rawValue(5);


  for(int i = 1; i < 9; i=i+2){
    displayForInterval(x[i], "data",10000);
    Serial.print("Insert ");
    Serial.print(x[i]);
    Serial.println(" NTU calibration sample.");
    waitForKeypress();
    y[i] = rawValue(5);
  }

  m[0] = (y[1] - y[0]) / (x[1] - x[0]);

  for(int i = 2; i < 8; i=i+2){
    y[i] = m[i/2-1]*(x[i]-x[i-1]) + y[i-1];
    m[i/2] = (y[i] - y[i-1]) / (x[i] - x[i-1]);
  }

/* Now we have 5 linear equations in point-slope form:
     (y-y0) = m(x-x0),
   where y is the raw reading and x is the NTU value.
   Since normally we want to find NTU from the readings, rearrange:
     x = (1/m)(y-y0) + x0
   in slope-intercept form:
     x = (1/m)y + (x0-y0/m)
    To make calculation simple later, we want 
      ntu_value = raw_value * m + b
    Define a new m = 1/m
    Then b = x0 - m*y0
    These are values we will to save in the config.
*/

  config.last_calibration_timestamp = 1468949330; // no RTC, no way of doing this in code
  config.y0 = y[0];
  Serial.print("config.y0: ");
  Serial.println(config.y0);
  config.m0 = 1 / m[0];
  Serial.print("config.m0: ");
  Serial.println(config.m0);
  config.b0 = x[0] - y[0] / m[0];
  Serial.print("config.b0: ");
  Serial.println(config.b0);
  config.y1 = y[2];
  Serial.print("config.y1: ");
  Serial.println(config.y1);
  config.m1 = 1 / m[1];
  Serial.print("config.m1: ");
  Serial.println(config.m1);
  config.b1 = x[2] - y[2] / m[1];
  Serial.print("config.b1: ");
  Serial.println(config.b1);
  config.y2 = y[4];
  Serial.print("config.y2: ");
  Serial.println(config.y2);
  config.m2 = 1 / m[2];
  Serial.print("config.m2: ");
  Serial.println(config.m2);
  config.b2 = x[4] - y[4] / m[2];
  Serial.print("config.b2: ");
  Serial.println(config.b2);
  config.y3 = y[6];
  Serial.print("config.y3: ");
  Serial.println(config.y3);
  config.m3 = 1 / m[3];
  Serial.print("config.m3: ");
  Serial.println(config.m3);
  config.b3 = x[6] - y[6] / m[3];
  Serial.print("config.b3: ");
  Serial.println(config.b3);
  config.y4 = y[8];
  Serial.print("config.y4: ");
  Serial.println(config.y4);
  config.m4 = 1 / m[4];
  Serial.print("config.m4: ");
  Serial.println(config.m4);
  config.b4 = x[8] - y[8] / m[4];
  Serial.print("config.b4: ");
  Serial.println(config.b4);

  EEPROM_writeAnything(0, config);

  Serial.println("Calibration complete.");
  displayForInterval(0, "ready",50000);
}
