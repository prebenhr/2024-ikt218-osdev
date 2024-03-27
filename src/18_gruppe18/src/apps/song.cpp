/*
void enable_speaker() {
    // Pseudocode for enable_speaker:
    // 1. Read the current state from the PC speaker control port.
    // 2. The control register bits are usually defined as follows:
    //    - Bit 0 (Speaker gate): Controls whether the speaker is on or off.
    //    - Bit 1 (Speaker data): Determines if data is being sent to the speaker.
    // 3. Set both Bit 0 and Bit 1 to enable the speaker.
    //    - Use bitwise OR operation to set these bits without altering others.
}

void disable_speaker() {
    // Pseudocode for disable_speaker:
    // 1. Read the current state from the PC speaker control port.
    // 2. Clear both Bit 0 and Bit 1 to disable the speaker.
    //    - Use bitwise AND with the complement of 3 (0b11) to clear these bits.
}

void play_sound(uint32_t frequency) {
    // Pseudocode for play_sound:
    // 1. Check if the frequency is 0. If so, exit the function as this indicates no sound.
    // 2. Calculate the divisor for setting the PIT (Programmable Interval Timer) frequency.
    //    - The PIT frequency is a base value, typically 1.193182 MHz.
    //    - The divisor is PIT frequency divided by the desired sound frequency.
    // 3. Configure the PIT to the desired frequency:
    //    - Send control word to PIT control port to set binary counting, mode 3, and access mode (low/high byte).
    //    - Split the calculated divisor into low and high bytes.
    //    - Send the low byte followed by the high byte to the PIT channel 2 port.
    // 4. Enable the speaker (by setting the appropriate bits) to start sound generation.
}

void stop_sound() {
    // Pseudocode for stop_sound:
    // 1. Read the current state from the PC speaker control port.
    // 2. Clear the bit that enables speaker data to stop the sound.
    //    - Use bitwise AND with the complement of the bit responsible for enabling the speaker data.
}

void play_song_impl(Song *song) {
    // Pseudocode for play_song_impl:
    // 1. Enable the speaker before starting the song.
    // 2. Loop through each note in the song's notes array:
    //    a. For each note, display its details such as frequency and duration.
    //    b. Call play_sound with the note's frequency.
    //    c. Delay execution for the duration of the note (this can be implemented with a sleep function).
    //    d. Call stop_sound to end the note.
    // 3. Disable the speaker after all notes have been played.
}

void play_song(Song *song) {
    // Pseudocode for play_song:
    // 1. Call play_song_impl with the given song.
    //    - This function handles the entire process of playing each note in the song.
} */

extern "C"
{

#include <pit.h>
#include <io.h>
#include <libc/stdint.h>
#include <terminal.h>
}
#include <song.h>

void enable_speaker()
{
    // Read the current state of the PC speaker control register
    uint8_t speaker_state = inb(PC_SPEAKER_PORT);

    /*
    Bit 0: Speaker gate
            0: Speaker disabled
            1: Speaker enabled
    Bit 1: Speaker data
            0: Data is not passed to the speaker
            1: Data is passed to the speaker
    */
    // Check if bits 0 and 1 are not set (0 means that the speaker is disabled)
    if (speaker_state != (speaker_state | 3))
    {
        // If bits 0 and 1 are not set, enable the speaker by setting bits 0 and 1 to 1
        outb(PC_SPEAKER_PORT, speaker_state | 3);
    }
}

void disable_speaker()
{
    // Turn off the PC speaker
    uint8_t speaker_state = inb(PC_SPEAKER_PORT);
    outb(PC_SPEAKER_PORT, speaker_state & 0xFC);
}

void nosound()
{
}

void play_sound(uint32_t frequency)
{
    if (frequency == 0)
        return;

    uint16_t divisor = PIT_BASE_FREQUENCY / frequency;
    if (divisor % 2 != 0)
    {
        divisor -= 1;
    }

    outb(PIT_CMD_PORT, 0xB6);
    outb(PIT_CHANNEL2_PORT, divisor & 0xFF);
    outb(PIT_CHANNEL2_PORT, (divisor >> 8) & 0xFF);

    enable_speaker();

    // Pseudocode for play_sound:
    // 1. Check if the frequency is 0. If so, exit the function as this indicates no sound.
    // 2. Calculate the divisor for setting the PIT (Programmable Interval Timer) frequency.
    //    - The PIT frequency is a base value, typically 1.193182 MHz.
    //    - The divisor is PIT frequency divided by the desired sound frequency.
    // 3. Configure the PIT to the desired frequency:
    //    - Send control word to PIT control port to set binary counting, mode 3, and access mode (low/high byte).
    //    - Split the calculated divisor into low and high bytes.
    //    - Send the low byte followed by the high byte to the PIT channel 2 port.
    // 4. Enable the speaker (by setting the appropriate bits) to start sound generation.
}

void play_song_impl(Song *song)
{

    for (uint32_t i = 0; i < song->length; i++)
    {
        Note *note = &song->notes[i];
        printf("Note: %d, Freq=%d, Sleep=%d\n", i, note->frequency, note->duration);
        play_sound(note->frequency);
        sleep_interrupt(note->duration);
        disable_speaker();
    }
}

void play_song(Song *song)
{
    play_song_impl(song);
}

/* void play_sound(uint32_t frequency)
{
    if (frequency == 0)
    {
        return;
    }

    auto divisor = (uint16_t)(PIT_BASE_FREQUENCY / frequency);

    // Set up the PIT
    outb(PIT_CMD_PORT, 0b10110110);
    outb(PIT_CHANNEL2_PORT, (uint8_t)(divisor & 0xFF));
    outb(PIT_CHANNEL2_PORT, (uint8_t)(divisor >> 8));
}
 */
SongPlayer *create_song_player()
{
    auto *player = new SongPlayer();
    player->play_song = play_song_impl;
    return player;
}