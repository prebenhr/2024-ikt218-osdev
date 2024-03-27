#include <song.h>
extern "C"
{
#include <memory.h>
#include <libc/stdint.h>
#include <terminal.h>

    int kernel_main();
}

// Existing global operator new overloads
void *operator new(size_t size)
{
    return malloc(size);
}

void *operator new[](size_t size)
{
    return malloc(size);
}

// Existing global operator delete overloads
void operator delete(void *ptr) noexcept
{
    free(ptr);
}

void operator delete[](void *ptr) noexcept
{
    free(ptr);
}

// Add sized-deallocation functions
void operator delete(void *ptr, size_t size) noexcept
{
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}

void operator delete[](void *ptr, size_t size) noexcept
{
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}

int kernel_main()
{

    printf("We are now in CPP kernel.\n");
    // Allocate some memory using the kernel memory manager
    // THIS IS PART OF THE ASSIGNMENT
    void *some_memory = malloc(12345);
    void *memory2 = malloc(54321);
    void *memory3 = malloc(13331);
    char *memory4 = new char[1000]();

    Song *songs[] = {
        new Song({music_1, sizeof(music_1) / sizeof(Note)})};
    uint32_t n_songs = sizeof(songs) / sizeof(Song *);

    SongPlayer *player = create_song_player();

    while (true)
    {
        for (uint32_t i = 0; i < n_songs; i++)
        {
            printf("Playing Song...\n");
            player->play_song(songs[i]);
            printf("Finished playing the song.\n");
        }
    };

    // More code....
    while (true)
        ;
}