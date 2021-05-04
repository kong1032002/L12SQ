#include "Draw.h"

Draw::Draw()
{

    initSDL(window, renderer);
    SDL_Color fg = { 243, 156, 18 };

    P1Win = loadTexture("Assets/Menu/P1Win.png", renderer);
    P2Win = loadTexture("Assets/Menu/P2Win.png", renderer);
    Xsword = loadTexture("Assets/Menu/swordX.png", renderer);
    MainMenu = loadTexture("Assets/Menu/Menu_game.png", renderer);
    Tutorial_1 = loadTexture("Assets/Menu/HDTrang1.png", renderer);
    Tutorial_2 = loadTexture("Assets/Menu/HDTrang2.png", renderer);
    PWait = loadTexture("Assets/PlayerBG.png", renderer);
    PTurn = loadTexture("Assets/PlayerTurnBG.png", renderer);
    P1Character = loadTexture("Assets/Elementals_Fire.png", renderer);
    P2Character = loadTexture("Assets/Elementals_Ice.png", renderer);
    background = loadTexture("Assets/Menu/background.png", renderer);
    EmptyBar = loadTexture("Assets/C_Bar/EFoodBar.png", renderer);
    HPBar = loadTexture("Assets/C_Bar/HP.png", renderer);
    MPBar = loadTexture("Assets/C_Bar/MP.png", renderer);
    FoodBar = loadTexture("Assets/C_Bar/Food.png", renderer);
    Target = loadTexture("Assets/Icon/Target.png", renderer);
    TargetSelected = loadTexture("Assets/Icon/TargetSelected.png", renderer);
    Mana = loadTexture("Assets/Icon/Mana.png", renderer);
    Heart = loadTexture("Assets/Icon/Heart.png", renderer);
    Sword = loadTexture("Assets/Icon/Sword.png", renderer);
    RedSword = loadTexture("Assets/Icon/RedSword.png", renderer);
    EXPScroll = loadTexture("Assets/Icon/EXPScroll.png", renderer);
    Gold = loadTexture("Assets/Icon/Gold.png", renderer);
    Food = loadTexture("Assets/Icon/Food.png", renderer);
    filled_rect.x = 0;
    filled_rect.y = 0;
    filled_rect.w = step + 2;
    filled_rect.y = step + 2;
    playerTurn = 1;
}

Draw::~Draw()
{
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_DestroyTexture(P1Win);
    SDL_DestroyTexture(P2Win);
    SDL_DestroyTexture(PWait);
    SDL_DestroyTexture(PTurn);
    SDL_DestroyTexture(P1Character);
    SDL_DestroyTexture(P2Character);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(TargetSelected);
    SDL_DestroyTexture(Target);
    SDL_DestroyTexture(RedSword);
    SDL_DestroyTexture(Sword);
    SDL_DestroyTexture(Heart);
    SDL_DestroyTexture(Mana);
    SDL_DestroyTexture(EXPScroll);
    SDL_DestroyTexture(Gold);
    SDL_DestroyTexture(Food);
    SDL_DestroyTexture(EmptyBar);
    SDL_DestroyTexture(FoodBar);
    SDL_DestroyTexture(HPBar);
    SDL_DestroyTexture(MPBar);
    SDL_Quit();
}


int Draw::random()
{
    int temp = rand() % 14 + 2;
    return temp / 2;
}

void Draw::DropIcon()
{
    for (int j = 0;j < gplay.BFSize;j++)
        for (int i = 0;i < gplay.BFSize;i++)
            if (gplay.BF[i][j] == 0)
            {
                for (int k = i;k >= 0;k--)
                {
                    if (k == 0)
                        gplay.BF[k][j] = random();
                    else
                        swap(gplay.BF[k - 1][j], gplay.BF[k][j]);
                }
                SDL_Delay(50);
                refreshScreen(window, renderer, filled_rect);
            }
}

void Draw::Turtorial()
{
    SDL_Event e;
    SDL_Rect srcRect;
    int page;
    SDL_RenderClear(renderer);
    renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    renderTexture(Tutorial_1, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderPresent(renderer);
    page = 1;
    while (true)
    {
        SDL_Delay(10);
        if (SDL_WaitEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            srcRect.x = e.button.x; // Lấy hoành độ x của chuột
            srcRect.y = e.button.y; // Lấy tung độ y của chuột
            if (page == 1)
            {
                if (400 <= srcRect.x && srcRect.x <= 475 && 550 <= srcRect.y && srcRect.y <= 640) // trang tiep theo
                {
                    cout << 1 << endl;
                    SDL_RenderClear(renderer);
                    renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                    renderTexture(Tutorial_2, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                    SDL_RenderPresent(renderer);
                    page = 2;
                }
            }
            else if (page == 2)
            {
                cout << srcRect.x << " " << srcRect.y << endl;
                if (400 <= srcRect.x && srcRect.x <= 475 && 550 <= srcRect.y && srcRect.y <= 640) // tro ve menu chinh
                {
                    SDL_RenderClear(renderer);
                    renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                    renderTexture(MainMenu, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                    renderTexture(Xsword, renderer, 100, 270, 30, 30);
                    SDL_RenderPresent(renderer);
                    return;
                }
                if (0 <= srcRect.x && srcRect.x <= 95 && 550 <= srcRect.y && srcRect.y <= 640) // tro lai trang 1
                {
                    SDL_RenderClear(renderer);
                    renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                    renderTexture(Tutorial_1, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                    SDL_RenderPresent(renderer);
                    page = 1;
                }
            }
        }
    }
}

void Draw::PlayGame()
{
    SDL_Event e;
    P[1].~Player();
    P[2].~Player();
    refreshScreen(window, renderer, filled_rect);
    while (true) {
        // Đợi 10 mili giây
        SDL_Delay(10);
        if (SDL_WaitEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_ESCAPE) break;
            if (e.key.keysym.sym == SDLK_LEFT) filled_rect.x = (filled_rect.x + SCREEN_WIDTH - step) % SCREEN_WIDTH;
            if (e.key.keysym.sym == SDLK_RIGHT) filled_rect.x = (filled_rect.x + step) % SCREEN_WIDTH;
            if (e.key.keysym.sym == SDLK_DOWN) filled_rect.y = (filled_rect.y + step) % SCREEN_WIDTH;
            if (e.key.keysym.sym == SDLK_UP) filled_rect.y = (filled_rect.y + SCREEN_WIDTH - step) % SCREEN_WIDTH;
            if (e.key.keysym.sym == SDLK_SPACE)
            {
                if (Pos.saved == 0)
                {
                    Pos.saved = 1;
                    Pos.x = filled_rect.x / step;
                    Pos.y = filled_rect.y / step;
                }
                else
                {
                    Pos.saved = 0;
                    if (Pos.x == filled_rect.x / step && Pos.y == filled_rect.y / step)
                        continue;
                    gplay.Turn--;
                    swap(gplay.BF[Pos.y][Pos.x], gplay.BF[filled_rect.y / step][filled_rect.x / step]);
                    refreshScreen(window, renderer, filled_rect);
                    SDL_Delay(100);
                    gplay.Combo = 1;
                    while (gplay.CheckBF())
                    {
                        DropIcon();
                        gplay.Combo++;
                    }
                    for (int i = 1;i <= 7;i++)
                    {
                        switch (i)
                        {
                        case 3:
                            P[playerTurn].Healing(gplay.Act[i]);
                        case 4:
                            P[playerTurn].GatherFood(gplay.Act[i]);
                        case 5:
                            P[playerTurn].ManaRecovery(gplay.Act[i]);
                        case 6: case 7:
                            P[playerTurn % 2 + 1].TakeDMG(gplay.Act[i]);
                        default:
                            break;
                        }
                        gplay.Act[i] = 0;
                    }
                }
            }
            refreshScreen(window, renderer, filled_rect);
            if (P[1].HP == 0 )
            {
                cout << "EndGame" << endl;
                refreshScreen(window, renderer, filled_rect);
                renderTexture(P2Win, renderer, 0, SCREEN_HEIGHT / 2 - 50, 480, 100);
                SDL_RenderPresent(renderer);
                SDL_Delay(1000);
                return;
            }
            else if (P[2].HP == 0)
            {
                cout << "EndGame" << endl;
                refreshScreen(window, renderer, filled_rect);
                renderTexture(P1Win, renderer, 0, SCREEN_HEIGHT / 2 - 50, 480, 100);
                SDL_RenderPresent(renderer);
                SDL_Delay(1000);
                return;
            }
            if (gplay.Turn <= 0)
            {
                gplay.Turn = 1;
                playerTurn = playerTurn % 2 + 1;
            }
            cout << "P" << playerTurn << " " << gplay.Turn << endl;
        }
    }
}

bool Draw::MenuGame()
{
    SDL_Event e;
    SDL_Rect srcRect;
    srcRect.x = SCREEN_WIDTH / 2;
    srcRect.y = SCREEN_HEIGHT / 2;
    srcRect.w = 16;
    srcRect.h = 12;
    SDL_RenderClear(renderer);
    renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    renderTexture(MainMenu, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderPresent(renderer);
    while (true)
    {
        SDL_Delay(10);
        if (SDL_WaitEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
        srcRect.x = e.button.x; // Lấy hoành độ x của chuột
        srcRect.y = e.button.y; // Lấy tung độ y của chuột
        if (140 <= srcRect.x && srcRect.x <= 340)
        {
            if (270 <= srcRect.y && srcRect.y <= 300)
            {
                cout << 1;
                SDL_RenderClear(renderer);
                renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                renderTexture(MainMenu, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                renderTexture(Xsword, renderer, 100, 270, 30, 30);
                SDL_RenderPresent(renderer);
            }
            else if (340 <= srcRect.y && srcRect.y <= 370)
            {
                cout << 2;
                SDL_RenderClear(renderer);
                renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                renderTexture(MainMenu, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                renderTexture(Xsword, renderer, 100, 340, 30, 30);
                SDL_RenderPresent(renderer);
            }
            else if (410 <= srcRect.y && srcRect.y <= 440)
            {
                cout << 3;
                SDL_RenderClear(renderer);
                renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                renderTexture(MainMenu, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                renderTexture(Xsword, renderer, 100, 410, 30, 30);
                SDL_RenderPresent(renderer);
            }
        }
        if (e.type == SDL_MOUSEBUTTONDOWN)
            if (140 <= srcRect.x && srcRect.x <= 340)
                if (270 <= srcRect.y && srcRect.y <= 300) // Bat dau choi
                    return 1;
                else if (340 <= srcRect.y && srcRect.y <= 370) // Huong dan
                    Turtorial();
                else if (410 <= srcRect.y && srcRect.y <= 440) // Thoat khoi tro choi
                {
                    SDL_Quit();
                    break;
                }          
    }
    return 0;
}

void Draw::refreshScreen(SDL_Window* window, SDL_Renderer* ren, const SDL_Rect& filled_rect)
{
    SDL_RenderClear(renderer);
    renderTexture(background, ren, 0,0, SCREEN_WIDTH, SCREEN_HEIGHT);
    for (int i = 0;i < gplay.BFSize;i++)
        for (int j = 0;j < gplay.BFSize;j++)
        {
            switch (gplay.BF[i][j])
            {
            case 1:
                renderTexture(Gold, ren, j * step, i * step, step, step);
                break;
            case 2:
                renderTexture(EXPScroll, ren, j * step, i * step, step, step);
                break;
            case 3:
                renderTexture(Heart, ren, j * step, i * step, step, step);
                break;
            case 4:
                renderTexture(Food, ren, j * step, i * step, step, step);
                break;
            case 5:
                renderTexture(Mana, ren, j * step, i * step, step, step);
                break;
            case 6:
                renderTexture(Sword, ren, j * step, i * step, step, step);
                break;
            case 7:
                renderTexture(RedSword, ren, j * step, i * step, step, step);
                break;
            default:
                break;
            }
        }
    if (Pos.saved == 1)
    {
        renderTexture(TargetSelected, ren, Pos.x * step, Pos.y * step, step + 2, step + 2);
    }
    
    if (playerTurn == 1)
    {
        renderTexture(PTurn, ren, 0, step * gplay.BFSize, 70, 120);
        renderTexture(PWait, ren, SCREEN_WIDTH - 80, step * gplay.BFSize, 80, 120);
    }
    else
    {
        renderTexture(PWait, ren, 0, step * gplay.BFSize, 70, 120);
        renderTexture(PTurn, ren, SCREEN_WIDTH - 80, step * gplay.BFSize, 80, 120);
    }

    renderTexture(P1Character, ren, 0, step * gplay.BFSize, 70, 120);
    renderTexture(P1Character, ren, 0, step * gplay.BFSize, 70, 120);
    renderTexture(Target, ren, filled_rect.x - 1, filled_rect.y - 1, step + 2, step + 2);

    //P1
    renderTexture(EmptyBar, ren, 70, step * gplay.BFSize + 24, 120, 24);
    renderTexture(EmptyBar, ren, 70, step * gplay.BFSize + 48, 120, 24);
    renderTexture(EmptyBar, ren, 70, step * gplay.BFSize + 72, 120, 24);
    renderBar(HPBar, ren, 70, step * gplay.BFSize + 24, 120, 24, P[1].HP * 100 / P[1].MAXHP);
    renderBar(MPBar, ren, 70, step * gplay.BFSize + 48, 120, 24, P[1].MP * 100 / P[1].MAXMP);
    renderBar(FoodBar, ren, 70, step * gplay.BFSize + 72, 120, 24, P[1].Food * 100 / P[1].MAXFood);
    

    //P2
    renderTexture(P2Character, ren, SCREEN_WIDTH - 80, step * gplay.BFSize, 80, 120);
    renderTexture(EmptyBar, ren, SCREEN_WIDTH - 200, step * gplay.BFSize + 24, 120, 24);
    renderTexture(EmptyBar, ren, SCREEN_WIDTH - 200, step * gplay.BFSize + 48, 120, 24);
    renderTexture(EmptyBar, ren, SCREEN_WIDTH - 200, step * gplay.BFSize + 72, 120, 24);
    renderBar(HPBar, ren, SCREEN_WIDTH - 200, step * gplay.BFSize + 24, 120, 24, P[2].HP * 100 / P[2].MAXHP);
    renderBar(MPBar, ren, SCREEN_WIDTH - 200, step * gplay.BFSize + 48, 120, 24, P[2].MP * 100 / P[2].MAXMP);
    renderBar(FoodBar, ren, SCREEN_WIDTH - 200, step * gplay.BFSize + 72, 120, 24, P[2].Food * 100 / P[2].MAXFood);
    SDL_RenderPresent(ren);
}


SDL_Texture* Draw::loadTexture(const std::string& file, SDL_Renderer* ren)
{
    SDL_Texture* texture = nullptr;
    SDL_Surface* loadedImage = IMG_Load(file.c_str());
    if (loadedImage != nullptr)
    {
        texture = SDL_CreateTextureFromSurface(ren, loadedImage);
        SDL_FreeSurface(loadedImage);
        if (texture == nullptr)
            logSDLError(std::cout, "CreateTextureFromSurface");
    }
    else
        logSDLError(std::cout, "LoadBMP");
    return texture;
}

void Draw::renderBar(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h, int lengthpercent)
{
    //Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
    SDL_Rect dst, src;
    dst.x = x;
    dst.y = y;
    //Truy vẫn texture để lấy chiều rộng và cao (vào chiều rộng và cao tương ứng của hình chữ nhật đích)
    SDL_QueryTexture(tex, NULL, NULL, &src.w, &src.h);
    if (w == 0 && h == 0)
    {
        dst.w = src.w;
        dst.h = src.h;
    }
    else
    {
        dst.h = h;
        dst.w = w;
        dst.w = dst.w * lengthpercent / 100;
        src.w = src.w * lengthpercent / 100;
    }
    src.x = 0;
    src.y = 0;
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
    SDL_RenderCopy(ren, tex, &src, &dst);
}

void Draw::renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(ren, tex, NULL, &dst);
}

void Draw::logSDLError(std::ostream& os, const std::string& msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void Draw::initSDL(SDL_Window*& window, SDL_Renderer*& ren)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
    ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) logSDLError(std::cout, "CreateRenderer", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (TTF_Init() < 0) SDL_Log("%s", TTF_GetError());
}

void Draw::quitSDL(SDL_Window* window, SDL_Renderer* ren)
{
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(PWait);
    SDL_DestroyTexture(PTurn);
    SDL_DestroyTexture(P1Character);
    SDL_DestroyTexture(P2Character);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(TargetSelected);
    SDL_DestroyTexture(Target);
    SDL_DestroyTexture(RedSword);
    SDL_DestroyTexture(Sword);
    SDL_DestroyTexture(Heart);
    SDL_DestroyTexture(Mana);
    SDL_DestroyTexture(EXPScroll);
    SDL_DestroyTexture(Gold);
    SDL_DestroyTexture(Food);
    SDL_DestroyTexture(EmptyBar);
    SDL_DestroyTexture(FoodBar);
    SDL_DestroyTexture(HPBar);
    SDL_DestroyTexture(MPBar);
    SDL_Quit();
}