#include "SDL.h"
#include "imgui.h"
#include "imgui_sdl.h"
#include	<SDL_image.h>
#include <string>

void load_texture(std::string filepath);
SDL_Renderer* renderer;
SDL_Texture* mtexture;



int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("SDL2 ImGui Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    ImGui::CreateContext();
    ImGuiSDL::Initialize(renderer, 800, 600);
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
    {
        SDL_Log("Failed to initialize SDL_image: %s", SDL_GetError());
        return false;
    }
    //SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET,500, 500);

    load_texture("..\\..\\Assset\\TETRIS\\Main.png");
    SDL_Texture* texture = mtexture;
    {


        
        //// ������Ⱦ����ɫ������
        //SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

        //// ���������
        //SDL_RenderClear(renderer);

        //int textureW;
        //int textureH;
        //// ��ȡ��ͼ�Ŀ�͸�
        //SDL_QueryTexture(mtexture, nullptr, nullptr, &textureW, &textureH);

        //// ��ȡԭͼƬ��������������ȡ��
        //SDL_Rect imageRect{ 0, 0, textureW, textureH };
        //// ͼƬĿ�ĵ�
        //SDL_Rect dstRect{ 130, 50, textureW, textureH };
        //// ����ȡ�õ�ͼƬ�����������Ŀ�ĵصĳ�������
        //SDL_RenderCopy(renderer, mtexture, &imageRect, &dstRect);

        //// ����������
        //SDL_RenderPresent(renderer);






        SDL_SetRenderTarget(renderer, texture);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
            // ������Ⱦ����ɫ������
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        // ���ó����ε������Լ����
        SDL_Rect rect;
        rect.x = 20;
        rect.y = 20;
        rect.w = 24;
        rect.h = 80;
        // ���Ƴ�����
        SDL_RenderFillRect(renderer, &rect);

        //SDL_RenderPresent(renderer);
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
        // ������Ⱦ����ɫ������
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        // ���ó����ε������Լ����
        SDL_Rect rect;
        rect.x = 20;
        rect.y = 20;
        rect.w = 240;
        rect.h = 800;
        // ���Ƴ�����
        SDL_RenderFillRect(renderer, &rect);

        //SDL_RenderClear(renderer);
       
        ImGui::Render();
        ImGuiSDL::Render(ImGui::GetDrawData());

        SDL_RenderPresent(renderer);
    }

    ImGuiSDL::Deinitialize();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    ImGui::DestroyContext();

    return 0;
}

void load_texture(const std::string filepath)
{
    // ��յ�ǰ��ͼ����ֹ�ظ���ȡʱ�ڴ�й©
    if (mtexture)
    {
        SDL_DestroyTexture(mtexture);
    }
    const char* f = filepath.c_str();
    // ��ȡͼƬ��Ϊsurface��ʽ
    SDL_Surface* surf = IMG_Load(filepath.c_str());
    if (!surf)
    {
        SDL_Log("Failed to load texture file %s", filepath.c_str());
    }

    // ��surfaceת��Ϊtexture��ʽ
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    // �ͷ�surface���ڴ�
    SDL_FreeSurface(surf);
    if (!tex)
    {
        SDL_Log("Failed to convert surface to texture for %s", filepath.c_str());
    }

    mtexture = tex;
}
