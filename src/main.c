#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

typedef struct
{
    int x, y;
    int x_speed, y_speed;
    int size;
} block;

typedef struct 
{
    block *arr;
    unsigned int used;
    unsigned int max;
} array_list;


// Functions for Array List
int get_size(array_list list)
{
    return sizeof(list.arr) / sizeof(list.arr[0]);
}

void al_append(array_list list, block item)
{
    if (list.used == list.max)
    {
        // Reallocate more memory - make array list bigger
        size_t current_size = sizeof(list);
        size_t new_size = current_size + sizeof(block);
        list.arr = realloc(list.arr, new_size);
        list.max = (int) new_size;
    }
    
    // Add item at the end of list
    for (int i = 0; i < get_size(list); i++)
    {
        if (list.arr[i].size == 0)
        {
            list.arr[i] = item;
            list.used++;
            return;
        }
    }

    printf("Array Length: %lu\n", get_size(list));
}

void print_list(array_list list)
{
    for (int i = 0; i < sizeof(list); i++)
    {
        block b = list.arr[i];
        printf("{ %d, %d, %d, %d, %d }, ", b.x, b.y, b.x_speed, b.y_speed, b.size);
    }
    printf("\n");
}
//

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int init(void)
{   
    // init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Failed to initialize SDL.\n");
        return -1;
    }
    
    // create window
    window = SDL_CreateWindow(
        "gun",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );
    if (!window)
    {
        fprintf(stderr, "Failed to create window.\n");
        return -1;
    }
    
    // create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        fprintf(stderr, "Failed to create renderer.\n");
        return -1;
    }

    return 0;
}

void draw(array_list blocks)
{
    SDL_SetRenderDrawColor(renderer, 255, 127, 80, 255);
    SDL_RenderClear(renderer); // Clear render context with color
    
    // Start drawing
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // while
    for (int i = 0; i < get_size(blocks); i++)
    {
        block b = blocks.arr[i];
        if (b.size != 0)
        {
            SDL_Rect rect = { b.x, b.y, b.size, b.size };
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_RenderPresent(renderer); // Essentially swap front and back buffers
}

void die(void)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    fprintf(stderr, "Program exited.\n");
}

void spawn_block(array_list blocks, int x, int y)
{
    block b = { x, y, 1, 1, 2 };
    al_append(blocks, b);
    print_list(blocks);
}

int main(void)
{
    if (init() != 0)
    {
        die();
        return -1;
    }

    array_list blocks;
    blocks.arr = calloc(4, sizeof(block) * 4);
    printf("size of array: %lu\n", sizeof(*blocks.arr) / sizeof(blocks.arr[0]));
    print_list(blocks);
    blocks.max = 4;
    blocks.used = 0;

    if (blocks.arr == NULL)
    {
        die();
        return -1;
    }

    bool running = true;

    while (running)
    {
        // process_input()
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_q)
                    running = false;
                else if (event.key.keysym.sym == SDLK_w)
                {
                    int x, y;
                    SDL_GetGlobalMouseState(&x, &y);
                    printf("spawn block at %i, %i\n", x, y);
                    spawn_block(blocks, x, y);
                }
                break;
        }
        //

        //update();
        draw(blocks);
    }
    
    free(blocks.arr);
    die();

    return 0;
}
