#include <SPI.h>
#include <SD.h>
#include <string.h>


File myFile;
long random_number;
char filename_buffer[16];
char rng_buffer[8];
char individual_log_appendage[] = ".csv";


void setup() {
  // Open serial communications and wait for port to open:
  
  randomSeed(analogRead(A0));
  Serial.begin(115200);
  while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");
  pinMode(9, OUTPUT);
  delay(1000);
  if (!SD.begin(9)) 
  {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");


  //strcat(filename_buffer, "log");
 

  for (int i = 0; i < 3; i++)
  {

    random_number = random(10,100);
    Serial.print("random number: ");
    Serial.println(random_number);

    sprintf(rng_buffer, "%ld", random_number);
    Serial.print("strlen of rng buffer: ");
    Serial.println(strlen(rng_buffer));

    strcat(filename_buffer, rng_buffer);
    Serial.print("strlen of filenamebuffer: ");
    Serial.println(strlen(filename_buffer));

  }

  strcat(filename_buffer, individual_log_appendage);

  Serial.print("Full filename: ");
  Serial.println(filename_buffer);

  Serial.print("strlen of filename: ");
  Serial.println(strlen(filename_buffer));
  delay(1000);
/*
  if(SD.mkdir(directory_buffer)){
    Serial.println("Folder creation succesful");
  }else{
    Serial.println("Folder creation failed");
  }
*/

  myFile = SD.open(filename_buffer, FILE_WRITE);
  

  if (myFile) 
  {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    
    myFile.close();
    
  }else 
  {
    // if the file didn't open, print an error:
    Serial.print("error opening ");
    Serial.println(filename_buffer);
  }
}


void loop() {
    // nothing happens after setup
}
