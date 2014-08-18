
int datapin  = 10; // DI
int latchpin = 11; // LI
int enablepin = 12; // EI
int clockpin = 13; // CI

/*
int datapin  = 11; // DI
int latchpin = 9; // LI
int enablepin = 10; // EI
int clockpin = 13; // CI
*/

unsigned long SB_CommandPacket;
int SB_CommandMode;
int SB_BlueCommand;
int SB_RedCommand;
int SB_GreenCommand;
int numColors = 255;
int counter = 0;
int animationDelay = 30; // number milliseconds before RGB LED changes to next color
String txtMsg = "";  
char s;


// 0 = off
// 1 = white
// 2 = red
// 3 = green
// 4 = blue
// 5 = purple
// 6 = red+green
// 7 = stained glass
// 8 = plaid
// 9 = flw stain glass

int colormode = 9;
int numshifts = 200;
int changed = 1;

void setup() {  
   pinMode(datapin, OUTPUT);
   pinMode(latchpin, OUTPUT);
   pinMode(enablepin, OUTPUT);
   pinMode(clockpin, OUTPUT);

   digitalWrite(latchpin, LOW);
   digitalWrite(enablepin, LOW);
   
   Serial.begin(9600);

 
   for(int l=0; l<numshifts; l++) {  
     SB_CommandMode = B00; // Write to current control registers
     SB_RedCommand = 0; // Full current 127
     SB_GreenCommand = 0; // Full current
     SB_BlueCommand = 0; // Full current
     SB_SendPacket();
   }      
   for(int l=0; l<numshifts; l++) {  
     SB_CommandMode = B01; // Write to current control registers
     SB_RedCommand = 127; // Full current 127
     SB_GreenCommand = 127; // Full current
     SB_BlueCommand = 127; // Full current
     SB_SendPacket();
   }   
}



void loop() {
 while (Serial.available() > 0) {
  s=(char)Serial.read();
  if (s == '\n') {
    if(txtMsg=="0") {  colormode=0;  }
    if(txtMsg=="1") {  colormode=1;  }
    if(txtMsg=="2") {  colormode=2;  }
    if(txtMsg=="3") {  colormode=3;  }
    if(txtMsg=="4") {  colormode=4;  }
    if(txtMsg=="5") {  colormode=5;  }
    if(txtMsg=="6") {  colormode=6;  }
    if(txtMsg=="7") {  colormode=7;  }
    if(txtMsg=="8") {  colormode=8;  }
    if(txtMsg=="9") {  colormode=9;  }
    txtMsg = "";
    changed = 1;
   } else {  
    txtMsg +=s; 
   }
 }  
  
 if(changed == 1) {
  switch(colormode) {
   case 0:
     for(int l=0; l<numshifts; l++) {  
       SB_CommandMode = B00; // Write to PWM control registers
       SB_RedCommand = 0; // Maximum red
       SB_GreenCommand = 0; // Minimum green
       SB_BlueCommand = 0; // Minimum blue
       SB_SendPacket();
     }
     break;
   case 1:
     for(int l=0; l<numshifts; l++) {  
       SB_CommandMode = B00; // Write to PWM control registers
       SB_RedCommand = 1023; // Maximum red
       SB_GreenCommand = 1023; // Minimum green
       SB_BlueCommand = 512; // Minimum blue
       SB_SendPacket();
     }
     break;
   case 2:
     for(int l=0; l<numshifts; l++) {  
       SB_CommandMode = B00; // Write to PWM control registers
       SB_RedCommand = 1023; // Maximum red
       SB_GreenCommand = 0; // Minimum green
       SB_BlueCommand = 0; // Minimum blue
       SB_SendPacket();
     }
     break;
   case 3:
     for(int l=0; l<numshifts; l++) {  
       SB_CommandMode = B00; // Write to PWM control registers
       SB_RedCommand = 0; // Maximum red
       SB_GreenCommand = 1023; // Minimum green
       SB_BlueCommand = 0; // Minimum blue
       SB_SendPacket();
     }
     break;     
   case 4:
     for(int l=0; l<numshifts; l++) {  
       SB_CommandMode = B00; // Write to PWM control registers
       SB_RedCommand = 0; // Maximum red
       SB_GreenCommand = 0; // Minimum green
       SB_BlueCommand = 1023; // Minimum blue
       SB_SendPacket();
     }
     break;
   case 5:
     for(int l=0; l<numshifts; l++) {  
       SB_CommandMode = B00; // Write to PWM control registers
       SB_RedCommand = 1023; // Maximum red
       SB_GreenCommand = 0; // Minimum green
       SB_BlueCommand = 1023; // Minimum blue
       SB_SendPacket();
     }
     break;    
   case 6:
     for(int l=0; l<(numshifts/2); l++) {  
       SB_CommandMode = B00; // Write to PWM control registers
       SB_RedCommand = 0; // Maximum red
       SB_GreenCommand = 1023; // Minimum green
       SB_BlueCommand = 0; // Minimum blue
       SB_SendPacket();   
   
       SB_CommandMode = B00; // Write to PWM control registers
       SB_RedCommand = 1023; // Maximum red
       SB_GreenCommand = 0; // Minimum green
       SB_BlueCommand = 0; // Minimum blue
       SB_SendPacket();         
     }
     break;    
   case 7:
     for(int l=0; l<(numshifts/2); l++) {  
       SB_CommandMode = B00; // Write to PWM control registers
       SB_RedCommand = 0; // Maximum red
       SB_GreenCommand = 1023; // Minimum green
       SB_BlueCommand = 0; // Minimum blue
       SB_SendPacket();   
   
       SB_CommandMode = B00; // Write to PWM control registers
       SB_RedCommand = 1023; // Maximum red
       SB_GreenCommand = 0; // Minimum green
       SB_BlueCommand = 0; // Minimum blue
       SB_SendPacket();   
   
       SB_CommandMode = B00; // Write to PWM control registers
       SB_RedCommand = 0; // Maximum red
       SB_GreenCommand = 0; // Minimum green
       SB_BlueCommand = 1023; // Minimum blue
       SB_SendPacket();     
     }
     break;       
   case 8:
     for(int l=0; l<(numshifts/2); l++) {  
       SB_CommandMode = B00; // Write to PWM control registers
       SB_RedCommand = 0; // Maximum red
       SB_GreenCommand = 1023; // Minimum green
       SB_BlueCommand = 0; // Minimum blue
       SB_SendPacket();   
   
       SB_CommandMode = B00; // Write to PWM control registers
       SB_RedCommand = 1023; // Maximum red
       SB_GreenCommand = 0; // Minimum green
       SB_BlueCommand = 0; // Minimum blue
       SB_SendPacket();   
   
       SB_CommandMode = B00; // Write to PWM control registers
       SB_RedCommand = 1023; // Maximum red
       SB_GreenCommand = 1023; // Minimum green
       SB_BlueCommand = 0; // Minimum blue
       SB_SendPacket();     
     }
     break;    
   case 9:
     for(int l=0; l<(numshifts/4); l++) {  
       SB_CommandMode = B00; // Write to PWM control registers
       SB_RedCommand = 1023; // Maximum red
       SB_GreenCommand = 1023; // Minimum green
       SB_BlueCommand = 512; // Minimum blue
       SB_SendPacket();   
       
       SB_CommandMode = B00; // Write to PWM control registers
       SB_RedCommand = 1023; // Maximum red
       SB_GreenCommand = 0; // Minimum green
       SB_BlueCommand = 0; // Minimum blue
       SB_SendPacket();   
   
       SB_CommandMode = B00; // Write to PWM control registers
       SB_RedCommand = 1023; // Maximum red
       SB_GreenCommand = 1023; // Minimum green
       SB_BlueCommand = 512; // Minimum blue
       SB_SendPacket();   
   
       SB_CommandMode = B00; // Write to PWM control registers
       SB_RedCommand = 0; // Maximum red
       SB_GreenCommand = 0; // Minimum green
       SB_BlueCommand = 1023; // Minimum blue
       SB_SendPacket();   
   
       SB_CommandMode = B00; // Write to PWM control registers
       SB_RedCommand = 920; // Maximum red
       SB_GreenCommand = 920; // Minimum green
       SB_BlueCommand = 0; // Minimum blue
       SB_SendPacket();   
     
       SB_CommandMode = B00; // Write to PWM control registers
       SB_RedCommand = 1023; // Maximum red
       SB_GreenCommand = 1023; // Minimum green
       SB_BlueCommand = 512; // Minimum blue
       SB_SendPacket();     
     }
     break;      
  }
  changed = 0;
 } // end changed
 delay(animationDelay);
} 

// junk from prev loop
/*
  // This part takes care of displaying the
  // color changing in reverse by counting backwards if counter
  // is above the number of available colors  
  float colorNumber = counter > numColors ? counter - numColors: counter;
  
  // Play with the saturation and brightness values
  // to see what they do
  float saturation = 1; // Between 0 and 1 (0 = gray, 1 = full color)
  float brightness = .05; // Between 0 and 1 (0 = dark, 1 is full brightness)
  float hue = (colorNumber / float(numColors)) * 360; // Number between 0 and 360
  long color = HSBtoRGB(hue, saturation, brightness); 
  
  // Get the red, blue and green parts from generated color
  int red = color >> 16 & 255;
  int green = color >> 8 & 255;
  int blue = color & 255;
  
   SB_CommandMode = B00; // Write to PWM control registers
   SB_RedCommand = red*4; // Maximum red
   SB_GreenCommand = green*4; // Minimum green
   SB_BlueCommand = blue*4; // Minimum blue
   SB_SendPacket();
   
  // Counter can never be greater then 2 times the number of available colors
  // the colorNumber = line above takes care of counting backwards (nicely looping animation)
  // when counter is larger then the number of available colors
  counter = (counter + 1) % (numColors * 2);
  
  // If you uncomment this line the color changing starts from the
  // beginning when it reaches the end (animation only plays forward)
  // counter = (counter + 1) % (numColors);
*/

long HSBtoRGB(float _hue, float _sat, float _brightness) {
    float red = 0.0;
    float green = 0.0;
    float blue = 0.0;
    
    if (_sat == 0.0) {
        red = _brightness;
        green = _brightness;
        blue = _brightness;
    } else {
        if (_hue == 360.0) {
            _hue = 0;
        }

        int slice = _hue / 60.0;
        float hue_frac = (_hue / 60.0) - slice;

        float aa = _brightness * (1.0 - _sat);
        float bb = _brightness * (1.0 - _sat * hue_frac);
        float cc = _brightness * (1.0 - _sat * (1.0 - hue_frac));
        
        switch(slice) {
            case 0:
                red = _brightness;
                green = cc;
                blue = aa;
                break;
            case 1:
                red = bb;
                green = _brightness;
                blue = aa;
                break;
            case 2:
                red = aa;
                green = _brightness;
                blue = cc;
                break;
            case 3:
                red = aa;
                green = bb;
                blue = _brightness;
                break;
            case 4:
                red = cc;
                green = aa;
                blue = _brightness;
                break;
            case 5:
                red = _brightness;
                green = aa;
                blue = bb;
                break;
            default:
                red = 0.0;
                green = 0.0;
                blue = 0.0;
                break;
        }
    }

    long ired = red * 255.0;
    long igreen = green * 255.0;
    long iblue = blue * 255.0;
    
    return long((ired << 16) | (igreen << 8) | (iblue));
}

void SB_SendPacket() {
   SB_CommandPacket = SB_CommandMode & B11;
   SB_CommandPacket = (SB_CommandPacket << 10)  | (SB_BlueCommand & 1023);
   SB_CommandPacket = (SB_CommandPacket << 10)  | (SB_RedCommand & 1023);
   SB_CommandPacket = (SB_CommandPacket << 10)  | (SB_GreenCommand & 1023);

   shiftOut(datapin, clockpin, MSBFIRST, SB_CommandPacket >> 24);
   shiftOut(datapin, clockpin, MSBFIRST, SB_CommandPacket >> 16);
   shiftOut(datapin, clockpin, MSBFIRST, SB_CommandPacket >> 8);
   shiftOut(datapin, clockpin, MSBFIRST, SB_CommandPacket);

   delay(1); // adjustment may be necessary depending on chain length
   digitalWrite(latchpin,HIGH); // latch data into registers
   delay(1); // adjustment may be necessary depending on chain length
   digitalWrite(latchpin,LOW);
}
