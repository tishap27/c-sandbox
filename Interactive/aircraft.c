#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PI 3.14159265359

// Structure to hold aircraft component information
typedef struct {
    SDL_Rect bounds;
    char* name;
    char* description;
    int color_r, color_g, color_b;
} AircraftComponent;

// Global variables
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
float propeller_angle = 0.0f;

// Aircraft components
AircraftComponent components[15];
int num_components = 0;
int hovered_component = -1;

// Function prototypes
int init_SDL();
void close_SDL();
void draw_aircraft();
void draw_propeller(int x, int y, float angle);
void draw_tooltip(int x, int y, char* text);
void handle_mouse_motion(int mouse_x, int mouse_y);
int point_in_rect(int x, int y, SDL_Rect rect);
void add_component(int x, int y, int w, int h, char* name, char* desc, int r, int g, int b);

int main(int argc, char* args[]) {
    if (!init_SDL()) {
        printf("Failed to initialize SDL!\n");
        return -1;
    }

    // Initialize aircraft components
    // Fuselage
    add_component(200, 280, 300, 40, "Fuselage", 
                  "Main body housing passengers and cargo", 200, 200, 200);
    
    // Left Wing
    add_component(120, 320, 200, 15, "Left Wing", 
                  "Generates lift for flight", 180, 180, 180);
    
    // Right Wing
    add_component(380, 320, 200, 15, "Right Wing", 
                  "Generates lift for flight", 180, 180, 180);
    
    // Left Engine
    add_component(180, 340, 50, 25, "Left Engine", 
                  "Radial piston engine with propeller", 160, 160, 160);
    
    // Right Engine
    add_component(470, 340, 50, 25, "Right Engine", 
                  "Radial piston engine with propeller", 160, 160, 160);
    
    // Cockpit
    add_component(180, 260, 60, 40, "Cockpit", 
                  "Pilot compartment with flight controls", 176, 196, 222);
    
    // Vertical Stabilizer
    add_component(480, 220, 40, 60, "Vertical Stabilizer", 
                  "Provides directional stability", 176, 176, 176);
    
    // Horizontal Stabilizer
    add_component(460, 300, 80, 12, "Horizontal Stabilizer", 
                  "Controls pitch and provides stability", 176, 176, 176);
    
    // Nose
    add_component(160, 290, 40, 20, "Nose", 
                  "Streamlined front section", 169, 169, 169);

    SDL_Event e;
    int quit = 0;
    Uint32 last_time = SDL_GetTicks();

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            else if (e.type == SDL_MOUSEMOTION) {
                handle_mouse_motion(e.motion.x, e.motion.y);
            }
        }

        // Update propeller animation
        Uint32 current_time = SDL_GetTicks();
        float delta_time = (current_time - last_time) / 1000.0f;
        propeller_angle += delta_time * 720.0f; // 720 degrees per second
        if (propeller_angle > 360.0f) propeller_angle -= 360.0f;
        last_time = current_time;

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Sky blue
        SDL_RenderClear(renderer);

        // Draw aircraft
        draw_aircraft();

        // Draw tooltip if hovering over component
        if (hovered_component >= 0) {
            int mouse_x, mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            draw_tooltip(mouse_x + 15, mouse_y - 10, components[hovered_component].description);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS
    }

    close_SDL();
    return 0;
}

int init_SDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    window = SDL_CreateWindow("Interactive Aircraft Diagram", 
                             SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                             SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return 0;
    }

    // Load font (you may need to adjust the path)
    font = TTF_OpenFont("arial.ttf", 16);
    if (font == NULL) {
        // Try alternative font paths
        font = TTF_OpenFont("/System/Library/Fonts/Arial.ttf", 16);
        if (font == NULL) {
            font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 16);
            if (font == NULL) {
                printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
                return 0;
            }
        }
    }

    return 1;
}

void close_SDL() {
    if (font != NULL) {
        TTF_CloseFont(font);
        font = NULL;
    }

    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    if (window != NULL) {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    TTF_Quit();
    SDL_Quit();
}

void draw_aircraft() {
    // Draw all components
    for (int i = 0; i < num_components; i++) {
        AircraftComponent* comp = &components[i];
        
        // Highlight if hovered
        if (i == hovered_component) {
            SDL_SetRenderDrawColor(renderer, 
                                 comp->color_r + 30, 
                                 comp->color_g + 30, 
                                 comp->color_b + 30, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 
                                 comp->color_r, 
                                 comp->color_g, 
                                 comp->color_b, 255);
        }
        
        SDL_RenderFillRect(renderer, &comp->bounds);
        
        // Draw outline
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderDrawRect(renderer, &comp->bounds);
    }

    // Draw propellers (animated)
    draw_propeller(205, 352, propeller_angle);
    draw_propeller(495, 352, propeller_angle);

    // Draw passenger windows
    SDL_SetRenderDrawColor(renderer, 65, 105, 225, 255);
    for (int i = 0; i < 8; i++) {
        SDL_Rect window_rect = {220 + i * 30, 290, 8, 8};
        SDL_RenderFillRect(renderer, &window_rect);
    }

    // Draw landing gear
    SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
    SDL_Rect gear1 = {240, 320, 6, 25};
    SDL_Rect gear2 = {440, 320, 6, 25};
    SDL_Rect nose_gear = {190, 320, 4, 20};
    SDL_RenderFillRect(renderer, &gear1);
    SDL_RenderFillRect(renderer, &gear2);
    SDL_RenderFillRect(renderer, &nose_gear);

    // Draw wheels
    SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
    SDL_Rect wheel1 = {237, 340, 12, 12};
    SDL_Rect wheel2 = {437, 340, 12, 12};
    SDL_Rect nose_wheel = {188, 335, 8, 8};
    SDL_RenderFillRect(renderer, &wheel1);
    SDL_RenderFillRect(renderer, &wheel2);
    SDL_RenderFillRect(renderer, &nose_wheel);

    // Draw title
    if (font != NULL) {
        SDL_Color textColor = {44, 82, 130, 255};
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Twin-Engine Aircraft Diagram", textColor);
        if (textSurface != NULL) {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if (textTexture != NULL) {
                SDL_Rect textRect = {SCREEN_WIDTH/2 - textSurface->w/2, 50, textSurface->w, textSurface->h};
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                SDL_DestroyTexture(textTexture);
            }
            SDL_FreeSurface(textSurface);
        }
    }
}

void draw_propeller(int x, int y, float angle) {
    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // Brown color
    
    // Draw propeller hub
    SDL_Rect hub = {x - 5, y - 5, 10, 10};
    SDL_RenderFillRect(renderer, &hub);
    
    // Draw propeller blades
    float rad = angle * PI / 180.0f;
    int blade_length = 30;
    
    for (int i = 0; i < 4; i++) {
        float blade_angle = rad + (i * PI / 2);
        int end_x = x + (int)(cos(blade_angle) * blade_length);
        int end_y = y + (int)(sin(blade_angle) * blade_length);
        
        SDL_SetRenderDrawColor(renderer, 139, 69, 19, 180);
        SDL_RenderDrawLine(renderer, x, y, end_x, end_y);
        
        // Draw blade shape
        SDL_Rect blade = {end_x - 2, end_y - 1, 4, 2};
        SDL_RenderFillRect(renderer, &blade);
    }
}

void draw_tooltip(int x, int y, char* text) {
    if (font == NULL || text == NULL) return;
    
    SDL_Color textColor = {44, 82, 130, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    if (textSurface != NULL) {
        // Draw background
        SDL_Rect bg_rect = {x, y, textSurface->w + 20, textSurface->h + 10};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 240);
        SDL_RenderFillRect(renderer, &bg_rect);
        
        // Draw border
        SDL_SetRenderDrawColor(renderer, 44, 82, 130, 255);
        SDL_RenderDrawRect(renderer, &bg_rect);
        
        // Draw text
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture != NULL) {
            SDL_Rect textRect = {x + 10, y + 5, textSurface->w, textSurface->h};
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_DestroyTexture(textTexture);
        }
        SDL_FreeSurface(textSurface);
    }
}

void handle_mouse_motion(int mouse_x, int mouse_y) {
    hovered_component = -1;
    
    for (int i = 0; i < num_components; i++) {
        if (point_in_rect(mouse_x, mouse_y, components[i].bounds)) {
            hovered_component = i;
            break;
        }
    }
}

int point_in_rect(int x, int y, SDL_Rect rect) {
    return (x >= rect.x && x < rect.x + rect.w && 
            y >= rect.y && y < rect.y + rect.h);
}

void add_component(int x, int y, int w, int h, char* name, char* desc, int r, int g, int b) {
    if (num_components < 15) {
        components[num_components].bounds.x = x;
        components[num_components].bounds.y = y;
        components[num_components].bounds.w = w;
        components[num_components].bounds.h = h;
        components[num_components].name = name;
        components[num_components].description = desc;
        components[num_components].color_r = r;
        components[num_components].color_g = g;
        components[num_components].color_b = b;
        num_components++;
    }
}