
#include "buzzer.h"

const uint8_t BUZZER = 26;

int notes[] =
    {
        NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
        NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
        NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
        NOTE_A4, NOTE_G4, NOTE_A4, 0,

        NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
        NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
        NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
        NOTE_A4, NOTE_G4, NOTE_A4, 0,

        NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
        NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
        NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
        NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

        NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
        NOTE_D5, NOTE_E5, NOTE_A4, 0,
        NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
        NOTE_C5, NOTE_A4, NOTE_B4, 0,

        NOTE_A4, NOTE_A4,

        NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
        NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
        NOTE_A4, NOTE_G4, NOTE_A4, 0,

        NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
        NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
        NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
        NOTE_A4, NOTE_G4, NOTE_A4, 0,

        NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
        NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
        NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
        NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

        NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
        NOTE_D5, NOTE_E5, NOTE_A4, 0,
        NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
        NOTE_C5, NOTE_A4, NOTE_B4, 0,

        NOTE_E5, 0, 0, NOTE_F5, 0, 0,
        NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
        NOTE_D5, 0, 0, NOTE_C5, 0, 0,
        NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

        NOTE_E5, 0, 0, NOTE_F5, 0, 0,
        NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
        NOTE_D5, 0, 0, NOTE_C5, 0, 0,
        NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4

};

int duration[] =
    {
        125, 125, 250, 125, 125,
        125, 125, 250, 125, 125,
        125, 125, 250, 125, 125,
        125, 125, 375, 125,

        125, 125, 250, 125, 125,
        125, 125, 250, 125, 125,
        125, 125, 250, 125, 125,
        125, 125, 375, 125,

        125, 125, 250, 125, 125,
        125, 125, 250, 125, 125,
        125, 125, 250, 125, 125,
        125, 125, 125, 250, 125,

        125, 125, 250, 125, 125,
        250, 125, 250, 125,
        125, 125, 250, 125, 125,
        125, 125, 375, 375,

        250, 125,

        125, 125, 250, 125, 125,
        125, 125, 250, 125, 125,
        125, 125, 375, 125,

        125, 125, 250, 125, 125,
        125, 125, 250, 125, 125,
        125, 125, 250, 125, 125,
        125, 125, 375, 125,

        125, 125, 250, 125, 125,
        125, 125, 250, 125, 125,
        125, 125, 250, 125, 125,
        125, 125, 125, 250, 125,

        125, 125, 250, 125, 125,
        250, 125, 250, 125,
        125, 125, 250, 125, 125,
        125, 125, 375, 375,

        250, 125, 375, 250, 125, 375,
        125, 125, 125, 125, 125, 125, 125, 125, 375,
        250, 125, 375, 250, 125, 375,
        125, 125, 125, 125, 125, 500,

        250, 125, 375, 250, 125, 375,
        125, 125, 125, 125, 125, 125, 125, 125, 375,
        250, 125, 375, 250, 125, 375,
        125, 125, 125, 125, 125, 500

};

void setupBuzzer()
{
    pinMode(BUZZER, OUTPUT);
    digitalWrite(BUZZER, LOW);
}

void buzz(long frequency, long length)
{

    long delayValue = 1000000 / frequency / 2; // Berechnung des Verzögerungswertes zwischen den Übergängen
    long numCycles = frequency * length / 1000; // Berechnung der Anzahl der Zyklen für das richtige Timing

    for (long i = 0; i < numCycles; i++)
    { // for the calculated length of time...

        digitalWrite(BUZZER, LOW);     // BUZZER an
        delayMicroseconds(delayValue); // warten auf den berechneten Verzögerungswert
        digitalWrite(BUZZER, HIGH);    // BUZZER aus
        delayMicroseconds(delayValue); // warten auf den berechneten Verzögerungswert
    }
}

void playTones()
{
    int size = sizeof(notes) / sizeof(int);
    Serial.println(String("Going to play ") + size + " notes");

    for (int thisNote = 0; thisNote < size; thisNote++)
    {
        int noteDuration = duration[thisNote];

        if (notes[thisNote] > 0)
            buzz(notes[thisNote], noteDuration);

        int pauseBetweenNotes = noteDuration * 0.5;
        delay(pauseBetweenNotes);
    }
    digitalWrite(BUZZER, HIGH);
}