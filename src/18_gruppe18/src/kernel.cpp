#include <song.h>
extern "C"
{
#include <memory.h>
#include <libc/stdint.h>
#include <terminal.h>
#include <pit.h>
    void norgesflagg();
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

    // printf("We are now in CPP kernel.\n");
    //  Allocate some memory using the kernel memory manager
    //  THIS IS PART OF THE ASSIGNMENT
    void *some_memory = malloc(12345);
    void *memory2 = malloc(54321);
    void *memory3 = malloc(13331);
    char *memory4 = new char[1000]();

    norgesflagg();

    setColors(BLACK, GRAY);
    printf("\n");
    printf("                  Velkommen til NorgeOS - laget av Gruppe 18 \n");

    Song *songs[] = {
        new Song({anthem, sizeof(anthem) / sizeof(Note)})};
    uint32_t n_songs = sizeof(songs) / sizeof(Song *);

    SongPlayer *player = create_song_player();
    printf("\n\n                       Reis dere for Norges nasjonalsang!\n");
    while (true)
    {
        for (uint32_t i = 0; i < n_songs; i++)
        {

            player->play_song(songs[i]);
            if (i == 0)
                printf("\n                                 Takk for oss.\n");
        }
    };

    // More code....
    while (true)
        ;
}