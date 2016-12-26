
#include <Entropy.h>

// ********* BEGIN USER CONFIG AREA **********

#define NR_CONTROL_PINS 4
#define NR_SYMBOLS 6

#define INTER_SYMBOL_TIME 0
#define SYMBOL_ON_TIME 15000
#define OFF_TIME 25000

int controlPins[NR_CONTROL_PINS] = {7,10,9,6}; // DCBA // MSB first

byte symbol[NR_SYMBOLS][NR_CONTROL_PINS] = {
  {0,0,0,0}, // tilde
  {0,0,0,1}, // +
  {0,0,1,1}, // -
  {0,1,0,0}, // Z
  {0,1,1,0}, // Y
  {0,1,0,1}  // X
};

void setup(){

  uint32_t seed_value;
  Entropy.initialize();
  seed_value = Entropy.random();
  randomSeed(seed_value);

  for(int i=0; i < NR_CONTROL_PINS; i++) {
    pinMode( controlPins[i], OUTPUT );
  }

  dePoison(7, 50, 0);
  
  //allOFF();
  
} // END SETUP


void dePoison(int rounds, int dpdelay, int dir) {
  
  allOFF();
  
  for(int k=0; k<rounds; k=k+1){
    if (dir == 0) {
      for (int j=0; j<NR_SYMBOLS; j=j+1) {  // this for loop goes through all symbols
        for(int i=0;i<NR_CONTROL_PINS; i++){ // this for loop outputs the symbol
          digitalWrite(controlPins[i], symbol[j][i]);
        }
        delay(dpdelay);
      }
    } else {
      for (int j=NR_SYMBOLS; j>0; j=j-1) {  // this for loop goes through all symbols
        for(int i=0;i<NR_CONTROL_PINS; i++){ // this for loop outputs the symbol
          digitalWrite(controlPins[i], symbol[j-1][i]);
        }
        delay(dpdelay);
      }
      
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

  int dir;
  static int mode = 1;  // modes; 0 = fade in, 1 = keep, 2 = fade out, 3 = off
  static unsigned int sym;

  switch (mode) {
    case 0:
//      for (int fadein=200; fadein>0; fadein=fadein-1) {
//        analogWrite(controlPins[0], fadein);
//        delay(10);
//      }
//      analogWrite(controlPins[0], 0);
      mode = 1;
      break;
    case 1:
      for(int ii=0;ii<NR_CONTROL_PINS; ii++){ // this for loop outputs the symbol
        digitalWrite(controlPins[ii], symbol[sym][ii]);
      }
      delay(SYMBOL_ON_TIME);
      mode = 2;
      break;
    case 2:
//      for (int fadeout=50; fadeout<256; fadeout=fadeout+1) {
//        analogWrite(controlPins[0], fadeout);
//        delay(10);
//      }
//      analogWrite(controlPins[0], 255);
      mode = 3;
      break;
    case 3:
      
      
      mode = random(1, 10); // dirty reuse of a variable
      sym = random(20,300); // dirty reuse of a variable, 2nd time
      dir = random(0,2); // looping direction
      dePoison(mode, sym, dir); // do a light show before next digit

      // taking a break from time to time
      if (sym > 200) {
        allOFF();
        delay(OFF_TIME);
        dePoison(mode, sym, 0);
      }
      sym = random(0, NR_SYMBOLS);
      delay(INTER_SYMBOL_TIME);
      
      mode = 0; // go into fade-in
      break;
  }

  allOFF();

}


