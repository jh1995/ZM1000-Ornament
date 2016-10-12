
// ********* BEGIN USER CONFIG AREA **********

#define NR_CONTROL_PINS 4
#define NR_SYMBOLS 6

#define INTER_SYMBOL_TIME 0
#define SYMBOL_ON_TIME 30000

int controlPins[NR_CONTROL_PINS] = {7,9,10,6}; //LSB first

byte symbol[NR_SYMBOLS][NR_CONTROL_PINS] = {
  {0,0,0,0}, // tilde
  {0,0,1,0}, // +
  {0,1,1,0}, // -
  {1,0,0,0}, // Z
  {1,1,0,0}, // Y
  {1,0,1,0}  // X
};

void setup(){

  for(int i=0; i < NR_CONTROL_PINS; i++) {
    pinMode( controlPins[i], OUTPUT );
  }

  randomSeed( analogRead(0) );

  dePoison(10, 50);
  
  //allOFF();
  
} // END SETUP


void dePoison(int rounds, int dpdelay) {
  
  allOFF();
  
  for(int k=0; k<rounds; k=k+1){
    for (int j=0; j<NR_SYMBOLS; j=j+1) {  // this for loop goes through all symbols
      for(int i=0;i<NR_CONTROL_PINS; i++){ // this for loop outputs the symbol
        digitalWrite(controlPins[i], symbol[j][i]);
      }
      delay(dpdelay);
    }
  }
  
  //allOFF();
  
}


// send an invalid combination to the BCD decoder
// so that all lines go high and nothing is shown
// better replaced with a TBD anodeOFF() function
// that needs a HW mod as well
void allOFF(){
  for(int i=0;i<NR_CONTROL_PINS; i++){
    digitalWrite(controlPins[i],1);
  }
}


void loop(){

  static int mode = 1;  // modes; 0 = fade in, 1 = keep, 2 = fade out, 3 = off
  static unsigned int sym;

  switch (mode) {
    case 0:
//      for (int fadein=100; fadein>0; fadein=fadein-10) {
//        analogWrite(controlPins[3], fadein);
//        delay(10);
//      }
//      analogWrite(controlPins[3], 0);
      mode = 1;
      break;
    case 1:
      for(int ii=0;ii<3; ii++){ // this for loop outputs the symbol
        digitalWrite(controlPins[ii], symbol[sym][ii]);
      }
      delay(SYMBOL_ON_TIME);
      mode = 2;
      break;
    case 2:
//      for (int fadeout=100; fadeout<256; fadeout=fadeout+10) {
//        analogWrite(controlPins[3], fadeout);
//        delay(10);
//      }
//      analogWrite(controlPins[3], 255);
      mode = 3;
      break;
    case 3:
      
      
      mode = random(1, 10); // dirty reuse of a variable
      sym = random(50,300); // dirty reuse of a variable, 2nd time
      dePoison(mode, sym); // do a light show before next digit

      sym = random(0, NR_SYMBOLS);
      delay(INTER_SYMBOL_TIME);
      
      mode = 0; // go into fade-in
      break;
  }

  allOFF();

}





