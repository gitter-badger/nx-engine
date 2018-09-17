#include "screen-manager/GfxScreen.h"

#include "exceptions/NxEngineException.h"

GfxScreen::GfxScreen()
{
}

GfxScreen::GfxScreen(int windowHeight, int windowWidth) : m_screenHeight(windowHeight),
                                                          m_screenWidth(windowWidth)
{
}

GfxScreen::GfxScreen(const Color &color, int windowHeight, int windowWidth) : m_bgColor(color),
                                                                              m_screenHeight(windowHeight),
                                                                              m_screenWidth(windowWidth)
{
}

int GfxScreen::getScreenWidth() const
{
    return m_screenWidth;
}

int GfxScreen::getScreenHeight() const
{
    return m_screenHeight;
}

void GfxScreen::run()
{
    if (init())
    {
        while (m_running)
        {
            update();
            draw();

            SDL_RenderPresent(m_renderer);

            SDL_Color colour = m_bgColor.getColor();
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_RenderClear(m_renderer);
        }
    }
}

bool GfxScreen::init()
{
    if (!initSystems())
    {
        return false;
    }

    m_window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screenWidth, m_screenHeight, SDL_WINDOW_FULLSCREEN);
    if (!m_window)
    {
        SDL_Quit();
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, 0, SDL_RENDERER_SOFTWARE);
    if (!m_renderer)
    {
        SDL_Quit();
        return false;
    }

    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);

    m_running = true;

    onInit();
    addScreens();

    m_currentScreen = m_screenList->getCurrent();
    m_currentScreen->onEntry();
    m_currentScreen->setRunning();

    return true;
}

bool GfxScreen::initSystems()
{
    Result rc = romfsInit();
    if (rc)
    {
        // throw NxEngineException("Error initializing RomFs");
        return false;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::string errorMsg = "Couldn't initialize SDL Video: " + std::string(SDL_GetError());
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        // throw NxEngineException(errorMsg);
        return false;
    }

    return true;
}
void GfxScreen::exit()
{
    m_running = false;

    onExit();

    m_currentScreen->onExit();
    m_screenList->destroy();

    romfsExit();

    delete m_screenList;
    free(m_window);
}