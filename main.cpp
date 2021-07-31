#include <SPI.h>
#include <SD.h>
#include <string.h>


File myFile;
long random_number;
char directory_buffer[32];
char filename_buffer[64];
char rng_buffer[16];
char individual_log_appendage[] = "/datalog.csv";


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
  if (!SD.begin(9)) 
  {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");



 
  for (int i = 0; i < 4; i++)
  {

    random_number = random(1000);
    Serial.print("random number: ");
    Serial.println(random_number);

    sprintf(rng_buffer, "%ld", random_number);
    Serial.print("strlen of rng buffer: ");
    Serial.println(strlen(rng_buffer));

    strcat(directory_buffer, rng_buffer);
    Serial.print("strlen of dir buffer: ");
    Serial.println(strlen(directory_buffer));

  }

  Serial.println(directory_buffer);
  Serial.println(filename_buffer);
  
  strcpy(filename_buffer, directory_buffer);
  strcat(filename_buffer, individual_log_appendage);

  Serial.println(directory_buffer);
  Serial.println(filename_buffer);

  if(SD.mkdir(directory_buffer)){
    Serial.println("Folder creation succesful");
  }else{
    Serial.println("Folder creation failed");
  }

  Serial.print("strlen of dir: ");
  Serial.println(strlen(directory_buffer));
  Serial.print("strlen of filename: ");
  Serial.println(strlen(filename_buffer));


  myFile = SD.open(filename_buffer, FILE_WRITE);


  Serial.println("");
  

  if (myFile) 
  {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    
    myFile.close();
    
  }else 
  {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}


void loop() {
    // nothing happens after setup
}
