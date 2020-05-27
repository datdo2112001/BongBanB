#include <iostream>
#include <string>
#include <SDL.h>
#include <time.h>
#include <SDL_image.h>
#include "Object.h"
#include "Process.h"
#include <SDL_ttf.h>
using namespace std;

void logSDLError(ostream& os, const string& msg, bool fatal = false);
const int SCREEN_WIDTH = 800;

const int SCREEN_HEIGHT = 600;


const string WINDOW_TITLE = "PING PONG Game";

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
SDL_Texture* balltex;
SDL_Texture* player1tex;
SDL_Texture* form;
SDL_Texture* start;
SDL_Texture* endgame;
// khai báo các texture để ghép đồ họa.
int main(int argc, char* argv[])
{
    TTF_Init();                   // khởi tạo TTF.
    SDL_Window* window;
    SDL_Renderer* renderer;

    initSDL(window, renderer);
    // khởi tạo cửa sổ SDL.
    Background open;
    bool signal = false;
    while (!signal) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // tạo phông nền màu trắng cho cửa sổ.
        SDL_RenderClear(renderer);        // xóa hết hình ảnh cũ.
        open.render(renderer, start);     // in background ra màn hình.
        SDL_RenderPresent(renderer);      // in hình ảnh hiện tại.
        SDL_Event e;                      // tạo 1 biến để nhận sự kiện từ bàn phím.
        SDL_Delay(5);
        if (SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_ESCAPE: break;

            case SDLK_s: signal = true;
                break;
            default: break;
            }
        }
    }

    if (signal == true) {
        bool quit = false;
        while (quit == false) {
            srand(time(0));
            SDL_RenderClear(renderer);
            // Object về player 1 và player 2
            racquet player1(10, 200);
            racquet player2(770, 200);
            Ball bounce(300, 300, -2.15, -2.15);
            Background bg;
            int point1 = 0;
            int point2 = 0;
            // điểm số ban đầu

            while (point1 <= 5 && point2 <= 5) {
                bounce.moves();
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
                SDL_Event e;


                if (bounce.x >= -10 && bounce.x <= 400) {
                    bounce.Direction(player1.x, player1.y);
                }
                else if (bounce.x >= 400 && bounce.y <= 810) {
                    bounce.Direction(player2.x, player2.y);
                }
                // Xác định tọa độ của bóng để tính Point1 , Point2.
                if (bounce.x <= 5) {
                    point2++;
                    cout << point1 << " " << point2 << endl;
                }
                else if (bounce.x >= 797) {
                    point1++;
                    cout << point1 << " " << point2 << endl;
                }

                bg.render(renderer, form);
                bounce.render(renderer, balltex);
                player2.render(renderer, player1tex);
                player1.render(renderer, player1tex);
                rendertext(renderer, to_string(point1), 300, 20);
                rendertext(renderer, to_string(point2), 500, 20);
                SDL_RenderPresent(renderer);


                SDL_Delay(5);
                if (SDL_PollEvent(&e) == 0) continue;
                if (e.type == SDL_QUIT) break;
                if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE: break;

                    case SDLK_2: player1.down();
                        break;
                    case SDLK_1: player1.up();
                        break;

                    default: break;
                    }


                }
                if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE: break;

                    case SDLK_UP: player2.up();
                        break;
                    case SDLK_DOWN: player2.down();
                        break;
                    default: break;
                    }


                }
            }

            // khi game over thì nhập backspace để chơi lại .
            SDL_RenderClear(renderer);
            bool node = false;
            Background endtask;
            while (node != true) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderClear(renderer);
                endtask.render(renderer, endgame);
                SDL_RenderPresent(renderer);
                SDL_Event m;
                SDL_Delay(5);
                if (SDL_PollEvent(&m) == 0) continue;
                if (m.type == SDL_QUIT) {
                    quit = true;
                    break;
                }
                if (m.type == SDL_KEYDOWN) {
                    switch (m.key.keysym.sym) {
                    case SDLK_ESCAPE: break;

                    case SDLK_BACKSPACE: node = true;
                        break;
                    default: break;
                    }
                }
            }
        }




        quitSDL(window, renderer);
        TTF_Quit();
        return 0;
    }
}


void logSDLError(std::ostream& os, const std::string& msg, bool fatal) {
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}


void initSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC);
    SDL_Surface* surface1 = IMG_Load("ball.png");
    balltex = SDL_CreateTextureFromSurface(renderer, surface1);
    SDL_FreeSurface(surface1);
    SDL_Surface* surface2 = IMG_Load("Racquet.png");
    player1tex = SDL_CreateTextureFromSurface(renderer, surface2);
    SDL_FreeSurface(surface2);
    SDL_Surface* surface3 = IMG_Load("NHT.png");
    form = SDL_CreateTextureFromSurface(renderer, surface3);
    SDL_FreeSurface(surface3);
    SDL_Surface* sf = IMG_Load("Start.png");
    start = SDL_CreateTextureFromSurface(renderer, sf);
    SDL_FreeSurface(sf);
    SDL_Surface* sf2 = IMG_Load("End.png");
    endgame = SDL_CreateTextureFromSurface(renderer, sf2);
    SDL_FreeSurface(sf2);
}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if (SDL_WaitEvent(&e) != 0 &&
            (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}



//  File chuyên tạo các struct về player , ball , dùng để nhận vào tọa độ và in ra hình ảnh lên màn hình.