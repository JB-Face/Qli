#include "SDL.h"
#undef main

#include "imgui.h"
#include "imgui_sdl.h"

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("SDL2 ImGui Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    ImGui::CreateContext();
    ImGuiSDL::Initialize(renderer, 800, 600);

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET,500, 500);
    {
        SDL_SetRenderTarget(renderer, texture);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
            // 设置渲染器颜色（蓝）
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        // 设置长方形的坐标以及宽高
        SDL_Rect rect;
        rect.x = 20;
        rect.y = 20;
        rect.w = 24;
        rect.h = 80;
        // 绘制长方形
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
        SDL_SetRenderTarget(renderer, nullptr);
    }

    bool run = true;
    while (run)
    {
        ImGuiIO& io = ImGui::GetIO();

        int wheel = 0;

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) run = false;
            else if (e.type == SDL_WINDOWEVENT)
            {
                if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    io.DisplaySize.x = static_cast<float>(e.window.data1);
                    io.DisplaySize.y = static_cast<float>(e.window.data2);
                }
            }
            else if (e.type == SDL_MOUSEWHEEL)
            {
                wheel = e.wheel.y;
            }
        }

        int mouseX, mouseY;
        const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

        // Setup low-level inputs (e.g. on Win32, GetKeyboardState(), or write to those fields from your Windows message loop handlers, etc.)

        io.DeltaTime = 1.0f / 60.0f;
        io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
        io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
        io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
        io.MouseWheel = static_cast<float>(wheel);

        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        ImGui::Begin("Image");
        ImGui::Image(texture, ImVec2(500, 500));
        ImGui::End();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        // 设置渲染器颜色（蓝）
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        // 设置长方形的坐标以及宽高
        SDL_Rect rect;
        rect.x = 20;
        rect.y = 20;
        rect.w = 240;
        rect.h = 800;
        // 绘制长方形
        SDL_RenderFillRect(renderer, &rect);

        //SDL_RenderClear(renderer);

        ImGui::Render();
        ImGuiSDL::Render(ImGui::GetDrawData());

        SDL_RenderPresent(renderer);
    }

    ImGuiSDL::Deinitialize();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    ImGui::DestroyContext();

    return 0;
}
