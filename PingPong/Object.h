#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <SDL_image.h>
#include "Process.h"
#include <SDL_ttf.h>


using namespace std;


#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED

// Background

struct Background {
    void render(SDL_Renderer* renderer, SDL_Texture* tex) {
        SDL_Rect filled_rect;
        filled_rect.x = 0;
        filled_rect.y = 0;
        filled_rect.w = 800;
        filled_rect.h = 600;

        SDL_RenderCopy(renderer, tex, NULL, &filled_rect);
    }
};

struct racquet {
    int x;
    int y;
    racquet(int _x, int _y) {
        x = _x;
        y = _y;
    }
    // nhận vào tọa độ cây vợt.
    void render(SDL_Renderer* renderer, SDL_Texture* tex) {
        SDL_Rect filled_rect;
        filled_rect.x = x; // tọa độ cây vợt
        filled_rect.y = y; // tọa độ cây vợt
        filled_rect.w = 20;
        filled_rect.h = 80;

        SDL_RenderCopy(renderer, tex, NULL, &filled_rect);
    }
    // hàm vẽ , xuất ra cửa sổ.
    void up() {
        y -= 20;
        if (CheckoutLimited(x, y) == false) // checkout trong common function dùng để kiểm tra xem cây vợt có đi quá màn hình hay chưa ,  nếu đi quá thì return false.
            y += 20;
    }
    void down() {
        y += 20;
        if (CheckoutLimited(x, y) == false)
            y -= 20;
    }
    // hai hàm up và down , dùng để điều khiển cây vợt.
};
struct Ball {
    int x;
    int y;
    int size = 20;
    float step1, step2;   // tốc độ theo chiều x   // tốc độ theo chiều y.

    Ball(int _x, int _y, float _step1, float _step2) {
        x = _x;
        y = _y;
        step1 = _step1;
        step2 = _step2;
    }
    void Direction(float _x, float _y) {
        int Type = Crash(_x, _y, x, y); // hàm crash dùng để xác nhận loại va chạm khi bóng va vào vợt.
        float a, b;
        a = 2.15, b = 2.15;

        if (Type == 1) {
            a = 2.4;
            b = 2.8;
            Step(step1, step2, a, b, x, y); // hàm step dùng để chuyển hướng bóng sau khi va chạm .
            // hàm step sẽ nhận vào 2 tốc độ ban đầu , nhận vào 2 chỉ số tốc độ mới là a,b.
            // tức là a,b đóng vai trò như tốc độ ,  còn step dùng để xác định step1 , step2 mới bằng cách thêm dấu + - vào.
        }
        else if (Type == 2) {
            a = 2.2;
            b = 2.5;
            Step(step1, step2, a, b, x, y);

        }
        else if (Type == 3) {
            a = 2.3;
            b = 2.3;
            Step(step1, step2, a, b, x, y);

        }
        else if (Type == 4) {
            a = 2.3;
            b = 2.6;
            Step(step1, step2, a, b, x, y);

        }
        if (y + 20 >= 600 || y <= 0) {
            a = 2.15;
            b = 2.15;
            Step(step1, step2, a, b, x, y);
        }

        if (x <= 0 || x >= 800) {
            x = 300;
            y = 300;
            step1 = 2.15;
            step2 = 2.15;
        }
        // xử lí bóng khi nó đi ra ngoài màn hình .


    }
    void render(SDL_Renderer* renderer, SDL_Texture* tex) {
        SDL_Rect filled_rect;
        filled_rect.x = x;
        filled_rect.y = y;
        filled_rect.w = size;
        filled_rect.h = size;

        SDL_RenderCopy(renderer, tex, NULL, &filled_rect);
    }
    void moves() {
        x += step1;
        y += step2;
    }
    // sau khi xác định step thì sẽ làm cho bóng chuyển động.
};
#endif