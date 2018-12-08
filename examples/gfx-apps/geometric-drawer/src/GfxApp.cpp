#include "GfxApp.h"
#include "PolygonsScreen.h"

GfxApp::GfxApp(const Color &bgColor) : GfxScreen(bgColor, 720, 1280)
{
}

GfxApp::~GfxApp()
{
}

void GfxApp::onInit()
{
}

void GfxApp::addScreens()
{
    m_screenList->addScreen(new PolygonsScreen());
    m_screenList->setScreen(0);
}

void GfxApp::onExit()
{
}