
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
    digitalWrite(BUZZER, HIGH);
}

void buzz(long frequency, long length)
{

    long delayValue = 1000000 / frequency / 2; // Berechnung des Verzögerungswertes zwischen den Übergängen
    // 1 Sekunde in Mikrosekunden, geteilt durch die Frequenz und dann halbiert, da zu jedem Zyklus zwei Phasen vorhanden sind

    long numCycles = frequency * length / 1000; // Berechnung der Anzahl der Zyklen für das richtige Timing
    // Frequenz, die die wirklichen Zyklen pro Sekunde ist, multipliziert mit der Anzahl der Sekunden,um die Gesamtzahl der Zyklen zu erhalten

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

    Serial.println(size);

    for (int thisNote = 0; thisNote < size; thisNote++)
    {
        Serial.println("thisNote:" + (String)thisNote);

        int noteDuration = duration[thisNote];

        Serial.print("  buzz(" + (String)notes[thisNote] + " " + (String)noteDuration);
        if (notes[thisNote] > 0)
            buzz(notes[thisNote], noteDuration);

        // Um die Noten zu unterscheiden, wird eine Mindestzeit zwischen ihnen festgelegt.
        int pauseBetweenNotes = noteDuration * 0.5;
        Serial.print("  delay(" + (String)pauseBetweenNotes);
        delay(pauseBetweenNotes);

        Serial.println("");
    }
    digitalWrite(BUZZER, HIGH); // BUZZER aus (Low-Aktiv)
}