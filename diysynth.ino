//These are the external libraries that your code uses
#include <Mozzi.h>
#include <Oscil.h>
#include <ADSR.h>
#include <tables/saw512_int8.h>
#include <tables/square_analogue512_int8.h>
#include <mozzi_midi.h>
#include <MIDI.h>

//This code sets up your MIDI output
MIDI_CREATE_DEFAULT_INSTANCE();
#define midi_channel 1 //This is the MIDI channel that your board will send messages on
#define midi_velocity 127 //This is the default velocity of your MIDI messages (127 is the max)

//This code sets up your synthesizer. As you can see, we're currently using 2 saw wave oscillators.
//To change the type of wave from saw to square, comment out the 2 lines below and remove the slashes from the 2 lines beneath them.
Oscil <SAW512_NUM_CELLS, MOZZI_AUDIO_RATE> aOsc1(SAW512_DATA);
Oscil <SAW512_NUM_CELLS, MOZZI_AUDIO_RATE> aOsc2(SAW512_DATA);
//Oscil <SQUARE_ANALOGUE512_NUM_CELLS, MOZZI_AUDIO_RATE> aOsc1(SQUARE_ANALOGUE512_DATA);
//Oscil <SQUARE_ANALOGUE512_NUM_CELLS, MOZZI_AUDIO_RATE> aOsc2(SQUARE_ANALOGUE512_DATA);

//This code sets up the envelope.
ADSR <MOZZI_CONTROL_RATE, MOZZI_AUDIO_RATE> envelope;
unsigned int attack_ms = 0; //You can change this value at any time. Maybe even with a potentiometer?
unsigned int release_ms = 1000; //You can change this value at any time. Maybe even with a potentiometer?
int current_note = 0; //This keeps track of what note is currently playing.
float pitch_bend = 0; //We will use this to bend the pitch of one of both of the oscillators.

//These variables keep track of your input pins
long last_debounce = 0;
uint8_t debounce_delay_ms = 10;
uint8_t input_pins[] = {2, 3, 4, 5, 6, 7, 8, 10, 11, 12};
uint8_t analog_pins[] = {A3,A2,A1,A0};
bool input_states[] = {0,0,0,0,0,0,0,0,0,0};

#define led_pin 13

//This is the setup code. It runs once when your synth powers up/
void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  startMozzi(64);
  aOsc1.setFreq(100);
  aOsc2.setFreq(100);
  envelope.setADLevels(255, 255);

  
  //This code sets the attack and release times. You can use this line of code at any point to change these values.
  envelope.setTimes(attack_ms, 0, 10000, release_ms);

  //This sets up all of the input pins.
  for (uint8_t i = 0; i < 11; i++)
  {
    pinMode(input_pins[i], INPUT_PULLUP);
  }
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
}

//This is your main loop. It runs 64 times per second.
void updateControl() {
  check_inputs(); 
  check_analog_inputs();
  envelope.update();
}

//This function checks all of your input pins. If one is connected to ground, it runs the input_on function.
void check_inputs()
{
  for (uint8_t i = 0; i < 10; i++)
  {
    if ((!digitalRead(input_pins[i]) != input_states[i]) && (millis() > last_debounce + debounce_delay_ms))
    {
      last_debounce = millis();
      input_states[i] = !input_states[i];
      if (input_states[i])
      {
        input_on(i);
      }
      else
      {
        input_off(i);
      }
    }
  }
}

//This function 
void check_analog_inputs()
{
  //This code is currently checking the value of your first analog pin (labelled 0 on the PCB). It turns it into a value between 100 and 200. 
  //Then it converts it into a "pitch bend" value between 1 and 2. If you like, you can use this value to alter the pitch of one or both of your oscillators.
  int min_value = 100;
  int max_value = 200;
  int analog_0 = map(mozziAnalogRead(analog_pins[0]),0,1024,min_value,max_value);
  pitch_bend = (float) analog_0/100;
  //aOsc1.setFreq(current_note * pitch_bend);
  //aOsc2.setFreq(current_note * pitch_bend);

  //This code is currently checking the value of your second analog pin (labelled 1 on the PCB). It turns this into a value between 0 and 1000.
  //If you like, you can use this value to alter the release time of your envelope.
  min_value = 0;
  max_value = 1000;
  int analog_1 = map(mozziAnalogRead(analog_pins[1]),0,1024,min_value,max_value);
  release_ms = analog_1;
  //envelope.setTimes(attack_ms, 0, 10000, release_ms);

}

//This function controls what happens when one of your inputs is triggered.
void input_on(uint8_t input_number)
{
  //Any code up here will run every time an input is triggered, regardless of the number.

  digitalWrite(led_pin, HIGH); //When any input is triggered, the inbuilt LED turns on.


  //The code below looks at the number of the input that was triggered. You can do something different for each trigger.
  //Here are some commands you could try...
  //aux_note_on(NOTE); This command will play a note. Just replace the word NOTE with the MIDI note you want to play.
  //MIDI.sendNoteOn(NOTE, midi_velocity, midi_channel); This command will send a MIDI command to turn on a note. 
  switch(input_number)
  {
    case 0: 

      //what happens when input 0 is triggered?
      aux_note_on(48);
      MIDI.sendNoteOn(48, midi_velocity, midi_channel);

      break;

    case 1:

      //what happens when input 1 is triggered?
      aux_note_on(50);
      MIDI.sendNoteOn(50, midi_velocity, midi_channel);


      break;

    case 2:

      //what happens when input 2 is triggered?
      aux_note_on(52);
      MIDI.sendNoteOn(52, midi_velocity, midi_channel);


      break;
    
    case 3:

      //what happens when input 3 is triggered?
      aux_note_on(53);
      MIDI.sendNoteOn(53, midi_velocity, midi_channel);


      break;

    case 4:

      //what happens when input 4 is triggered?
      aux_note_on(55);
      MIDI.sendNoteOn(55, midi_velocity, midi_channel);


      break;
    
    case 5:

      //what happens when input 5 is triggered?
      aux_note_on(57);
      MIDI.sendNoteOn(57, midi_velocity, midi_channel);


      break;

    case 6:

      //what happens when input 6 is triggered?
      aux_note_on(59);
      MIDI.sendNoteOn(59, midi_velocity, midi_channel);


      break;
    
    case 7:

      //what happens when input 7 is triggered?
      aux_note_on(60);
      MIDI.sendNoteOn(60, midi_velocity, midi_channel);


      break;

    case 8:

      //what happens when input 8 is triggered?

      break;
    
    case 9:

      //what happens when input 9 is triggered?

      break;
  }
}

void input_off(uint8_t input_number)
{
  if (all_inputs_off()) //What happens when no inputs are triggered?
  {
    digitalWrite(led_pin, LOW); //the LED turns off.
    aux_note_off(); //the note turns off.
    MIDI.sendControlChange(123, 0, midi_channel); //send a MIDI command to turn off all notes.
  }
}

//This is the function used to check whether all inputs are off
bool all_inputs_off()
{
  for (uint8_t i = 0; i < 10; i++)
  {
    if (input_states[i])
    {
      return 0;
    }
  }
  return 1;
}

//This is the function used to turn on a synth note
void aux_note_on(int midi_note)
{
  current_note = mtof(midi_note);
  aOsc1.setFreq(current_note);
  aOsc2.setFreq(current_note);
  envelope.noteOn();
}

//This is the function used to turn off the synth note
void aux_note_off()
{
  envelope.noteOff();
}

//Don't touch this code. It controls the audio output
AudioOutput updateAudio() {
  return MonoOutput::from16Bit(
    (int) (envelope.next() * ((aOsc1.next()+aOsc2.next())/2))
    );
}

//Don't touch this code. It controls the audio output
void loop() {
  audioHook(); 
}
