

#include <iostream>
#include <string>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


using namespace std;


#ifndef COMMON FUNCTION_H_INCLUDED
#define COMMON FUNCTION_H_INCLUDED

//  Kiểm tra xem cây vợt có ra ngoài màn hình hay không.


bool CheckoutLimited(int x, int y) {
	if (y >= 520 || y <= 0) {
		return false;
	}
	return true;
}

// Hàm trên dựa vào mối liên hệ giữa tọa độ bóng và tọa độ cây gậy để xác định 4 loại va chạm , với mỗi loại va chạm thì hướng nảy sẽ khác.
// Loại va chạm: Chia cây vợt thành 4 ô nảy vào mỗi ô thì tốc độ quả bóng sẽ khác nhau

int Crash(float x1, float y1, float x2, float y2) {
	if ((x2 < x1 + 20 && x2 >= x1) || (x2 + 20 > x1 && x1 > 200)) {
		if (y2 > y1 && y2 <= y1 + 20) {
			return 1;
		}
		else if (y2 > y1 + 20 && y2 <= y1 + 40) {
			return 2;
		}
		else if (y2 > y1 + 40 && y2 <= y1 + 60) {
			return 3;
		}
		else if (y2 > y1 + 60 && y2 < y1 + 80) {
			return 4;
		}
	}
	return 5;
}


// Hàm step có mục đích dùng để thêm dấu vào tốc độ nhận vào a,b để tạo ra hướng chuyển động mới của bóng.


bool Step(float& step1, float& step2, float a, float b, float x, float y) {
	if (step1 < 0 && step2 < 0 && y <= 0) {
		step1 = -a;
		step2 = b;
		return true;
	}

	else if (step1 < 0 && step2 < 0) {
		step1 = a;
		step2 = -b;
		return true;
	}

	if (step1 > 0 && step2 < 0 && y <= 0) {
		step1 = a;
		step2 = b;
		return true;
	}

	else if (step1 > 0 && step2 < 0) {
		step1 = -a;
		step2 = -b;
		return true;
	}

	if (step1 < 0 && step2 > 0 && y + 20 >= 600) {
		step1 = -a;
		step2 = -b;
		return true;
	}

	else if (step1 < 0 && step2 > 0) {
		step1 = a;
		step2 = b;
		return true;
	}

	if (step1 > 0 && step2 > 0 && y + 20 >= 600) {
		step1 = a;
		step2 = -b;
		return true;
	}

	else if (step1 > 0 && step2 > 0) {
		step1 = -a;
		step2 = b;
		return true;
	}

}

// Hàm rederer text

void rendertext(SDL_Renderer* renderer, string Text, int _x, int _y) {
	TTF_Font* font = TTF_OpenFont("font.ttf", 24);
	SDL_Color White = { 255, 255, 255 , 255 };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, Text.c_str(), White);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);
	SDL_Rect Message_rect;
	Message_rect.x = _x;
	Message_rect.y = _y;
	Message_rect.w = 20;
	Message_rect.h = 50;
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
}

#endif




