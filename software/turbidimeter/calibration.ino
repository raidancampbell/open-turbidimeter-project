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

void calibrate() {
  float y[9]; // raw readings
  float x[9] = {0.0, 5, 10, 25, 30, 35, 40, 45, 50}; // CYA
  float m[8]; // slopes (readings/CYA).

//  displayForInterval(0, "ready",50000);
  Serial.println("Starting calibration.");

//  displayForInterval(x[0], "data",10000);

//  Serial.print("Insert ");
//  Serial.print(x[0]);
//  Serial.println(" CYA calibration sample.");
//  waitForKeypress();
//  y[0] = rawValue(5);


  for(int i = 0; i < 9; i++) {
    displayForInterval(x[i], "data",10000);
    Serial.print("Insert ");
    Serial.print(x[i]);
    Serial.println(" CYA calibration sample.");
    waitForKeypress();
    y[i] = rawValue(100);
    Serial.print("raw value observed: ");
    Serial.println(y[i]);
  }

//  slope "at" a point is the slope of the line until the next point.
//  last point has no slope, or can be assumed to have the same slope as the previous.
  for(int i = 0; i < 8; i++) {
    m[i] = (y[i+1] - y[i]) / (x[i+1] - x[i]);
  }

/* Now we have 8 linear equations in point-slope form:
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
  // Serial.print("config.y0: ");
  // Serial.println(config.y0);
  config.m0 = 1 / m[0];
  // Serial.print("config.m0: ");
  // Serial.println(config.m0);
  config.b0 = x[0] - config.m0 * y[0];
  // Serial.print("config.b0: ");
  // Serial.println(config.b0);
  config.y1 = y[1];
  // Serial.print("config.y1: ");
  // Serial.println(config.y1);
  config.m1 = 1 / m[1];
  // Serial.print("config.m1: ");
  // Serial.println(config.m1);
  config.b1 = x[1] - y[1] / m[1];
  // Serial.print("config.b1: ");
  // Serial.println(config.b1);
  config.y2 = y[2];
  // Serial.print("config.y2: ");
  // Serial.println(config.y2);
  config.m2 = 1 / m[2];
  // Serial.print("config.m2: ");
  // Serial.println(config.m2);
  config.b2 = x[2] - y[3] / m[2];
  // Serial.print("config.b2: ");
  // Serial.println(config.b2);
  config.y3 = y[3];
  // Serial.print("config.y3: ");
  // Serial.println(config.y3);
  config.m3 = 1 / m[3];
  // Serial.print("config.m3: ");
  // Serial.println(config.m3);
  config.b3 = x[3] - y[3] / m[3];
  // Serial.print("config.b3: ");
  // Serial.println(config.b3);
  config.y4 = y[4];
  // Serial.print("config.y4: ");
  // Serial.println(config.y4);
  config.m4 = 1 / m[4];
  // Serial.print("config.m4: ");
  // Serial.println(config.m4);
  config.b4 = x[4] - y[4] / m[4];
  // Serial.print("config.b4: ");
  // Serial.println(config.b4);
    config.y5 = y[5];
  // Serial.print("config.y5: ");
  // Serial.println(config.y5);
  config.m5 = 1 / m[5];
  // Serial.print("config.m5: ");
  // Serial.println(config.m5);
  config.b5 = x[5] - y[5] / m[5];
  // Serial.print("config.b5: ");
  // Serial.println(config.b5);
    config.y5 = y[5];
  // Serial.print("config.y5: ");
  // Serial.println(config.y5);
  config.m5 = 1 / m[5];
  // Serial.print("config.m5: ");
  // Serial.println(config.m5);
  config.b5 = x[5] - y[5] / m[5];
  // Serial.print("config.b5: ");
  // Serial.println(config.b5);
    config.y6 = y[6];
  // Serial.print("config.y6: ");
  // Serial.println(config.y6);
  config.m6 = 1 / m[6];
  // Serial.print("config.m6: ");
  // Serial.println(config.m6);
  config.b6 = x[6] - y[6] / m[6];
  // Serial.print("config.b6: ");
  // Serial.println(config.b6);
    config.y7 = y[7];
  // Serial.print("config.y7: ");
  // Serial.println(config.y7);
  config.m7 = 1 / m[7];
  // Serial.print("config.m7: ");
  // Serial.println(config.m7);
  config.b7 = x[7] - y[7] / m[7];
  // Serial.print("config.b7: ");
  // Serial.println(config.b7);
    config.y8 = y[8];
  // Serial.print("config.y8: ");
  // Serial.println(config.y8);
  config.m8 = 1 / m[8];
  // Serial.print("config.m8: ");
  // Serial.println(config.m8);
  config.b8 = x[8] - y[8] / m[8];
  // Serial.print("config.b8: ");
  // Serial.println(config.b8);
  EEPROM_writeAnything(0, config);

  Serial.println("Calibration complete.");
  displayForInterval(0, "ready",50000);
}
