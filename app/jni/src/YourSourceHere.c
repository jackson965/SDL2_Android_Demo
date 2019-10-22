//
// Created by ecar on 2019.10.16.
//
#include <android/log.h>
#include <unistd.h>
#include "SDL.h"
#include "../sdl_ttf/SDL_ttf.h"

const int SCREEN_WIDTH = 0;
const int SCREEN_HEIGHT = 0;

//SDL demo main
int main(int argc, char* argv[]) {
    SDL_Window *window = NULL;
    SDL_Surface *surface = NULL;

    __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "%s argc:%d  argv:%s", __BASE_FILE__, argc, argv[0]);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL无法初始化 %s",SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("SDL Demo",
                              SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,//这两个是窗口的位置 x y（不在乎）
                              SCREEN_WIDTH,SCREEN_HEIGHT,//窗口的宽度和高度
                              SDL_WINDOW_SHOWN //确保在创建窗口时显示该窗口
    );

    if (window == NULL) {
        printf("创建window失败");
        return -1;
    }

    {
        SDL_Renderer  *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_RenderClear(renderer);

        char dir[PATH_MAX] = {0};
        int n = readlink("/proc/self/exe", dir, PATH_MAX);
        __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "PATH_MAX: %d\n", PATH_MAX);
        __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "readlink return: %d\n", n);
        __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "dir: %s\n", dir);


        TTF_Init();
        TTF_Font *font = TTF_OpenFont("subfont.ttf", 48);

        if(!font){
            __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "ttf open failed");
            return  - 1;
        }

        SDL_Color colorttf = {255,255,255};
        SDL_Surface *textSurf= TTF_RenderText_Blended(font, "time : 00:00:15", colorttf);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurf);



        SDL_SetRenderDrawColor(renderer, 200, 10, 10, 111);
        SDL_RenderFillRect(renderer, NULL);

        SDL_Rect rcRect = {100, 100, 100, 30};

        SDL_RenderCopy(renderer, texture, NULL, &rcRect );
        SDL_RenderPresent(renderer);

        //等待2秒
        SDL_Delay(15 * 1000);
        SDL_DestroyRenderer(renderer);

    }


//    //接下来是获取窗口的屏幕 这样才能绘制
//    surface = SDL_GetWindowSurface(window);
//
//    if (surface == NULL) {
//        printf("获取屏幕失败");
//        return -1;
//    }
//
//    int h, w;
//    SDL_GetWindowSize(window, &w, &h);
//    __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "SDL_GetWindowSize %d, %d", w, h);
//    //填充为红色
//    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xff, 0x00, 0x00));
//
//    //更新窗口操作
//    SDL_UpdateWindowSurface(window);

 //   //等待2秒
//    SDL_Delay(15 * 1000);

    //销毁资源退出
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}