int n = 0;

String GPSString = "";          // A string to hold incoming data from GPS
boolean GPSComplete = false;    // Whether the string for GPS is complete

void setup() {
  // Initializing serial port #0 with a BAUD rate of 38400
  Serial.begin(38400);

  // Initializing serial port #1 with a BAUD rate of 9600 for GPS communication
  Serial1.begin(9600);

  // Reserve 200 bytes for the GPS String;
  GPSString.reserve(200);
}

void loop() {
  // Call the GPSserialEvent function to handle incoming GPS data
  GPSserialEvent();

  if (GPSComplete) {
    // Copy the GPSString to a temporary string for parsing
    String Orig = GPSString;

    // Find the first comma to extract the message header
    char ind = GPSString.indexOf(",");
    String Header = GPSString.substring(0, ind);

    // Remove the processed part from GPSString
    GPSString = GPSString.substring(ind + 1);

    // Repeat the above steps to extract Time from GPS data fields
    ind = GPSString.indexOf(",");
    String Time = GPSString.substring(0, ind);

    // Repeat the above steps to extract Latitude from GPS data fields
    GPSString = GPSString.substring(ind + 1);
    ind = GPSString.indexOf(",");
    String LAT = GPSString.substring(0, ind);

    // Repeat the above steps to extract North or South from GPS data fields
    GPSString = GPSString.substring(ind + 1);
    ind = GPSString.indexOf(",");
    String NS = GPSString.substring(0, ind);

    // Repeat the above steps to extract Longitude from GPS data fields
    GPSString = GPSString.substring(ind + 1);
    ind = GPSString.indexOf(",");
    String LON = GPSString.substring(0, ind);

    // Repeat the above steps to extract East or West from GPS data fields
    GPSString = GPSString.substring(ind + 1);
    ind = GPSString.indexOf(",");
    String EW = GPSString.substring(0, ind);

    // Check if the message header is "$GPGGA" for GPS fix information
    if (Header.equals("$GPGGA")) {
      Serial.print("\tHeader:\t");
      Serial.print(Header);
      Serial.print('\n');

      Serial.print("\tTime:\t");
      Serial.print(Time);
      Serial.print('\n');

      Serial.print("\tLatitude:\t");
      Serial.print(LAT);
      Serial.print('\n');

      Serial.print("\tN/S Indicator:\t");
      Serial.print(NS);
      Serial.print('\n');

      Serial.print("\tLongitude:\t");
      Serial.print(LON);
      Serial.print('\n');

      Serial.print("\tE/W Indicator:\t");
      Serial.print(EW);
      Serial.print('\n');
    }

    // Clear the GPSString and reset GPSComplete flag
    GPSString = "";
    GPSComplete = false;
  }
}

// Serial Event occurs whenever new data comes in the hardware serial RX.
// This routine is run between each time loop() runs, so using delay inside
// loop can delay response.

// Multiple bytes of data may be available

void GPSserialEvent() {
  while (Serial1.available()) {
    // Get the new byte
    char inChar = (char)Serial1.read();

    // Add it to the GPSString
    GPSString += inChar;

    // Check if the received character is a newline, indicating the end of a GPS message
    if (inChar == '\n') {
      GPSComplete = true;
    }
  }
}
