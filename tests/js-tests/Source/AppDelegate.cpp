/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2019-present Axmol Engine contributors (see AUTHORS.md).

 https://axmol.dev/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "AppDelegate.h"

#include "axmol/platform/FileUtils.h"
#include "js-bindings/manual/JSEngine.h"

#include "Inspector/Inspector.h"
#include "ImGui/ImGuiPresenter.h"

#include "backward.hpp"

using namespace ax;

namespace
{

//backward::SignalHandling sh;

class RestartableJSEngine : public JSEngine
{
public:
    /**
     * Handle kRestartGame event.
     *
     * We do this because there currently no event dispatched for when we restart() the director
     * and ApplicationDelegate::applicationDidFinishLaunching() is not called on restart() so
     * we literally cannot do anything without this callback after a director restart.
     */
    int sendEvent(const ScriptEvent& evt) override
    {
        if (evt.type == ax::kRestartGame)
        {
            // Remove the current script engine
            ScriptEngineManager::getInstance()->removeScriptEngine();

            // The instant of this class just got deleted by the call to removeScriptEngine()
            //
            // So now we in a really weird state where "this" value
            // in this method is invalid and using it will be a use after free

            // Re-initialize
            AppDelegate* delegate = reinterpret_cast<AppDelegate*>(Application::getInstance());
            delegate->start();
            return 0;
        }

        return JSEngine::sendEvent(evt);
    }
};

}  // namespace

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}

void AppDelegate::initGfxContextAttrs()
{
    ContextAttrs gfxContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    setContextAttrs(gfxContextAttrs);
}

void AppDelegate::start()
{
    JSEngine* jsEngine = new RestartableJSEngine();
    jsEngine->init();

    ScriptEngineManager::getInstance()->setScriptEngine(jsEngine);

    FileUtils::getInstance()->addSearchPath("src");
    FileUtils::getInstance()->addSearchPath("res");
    jsEngine->executeScriptFile("axmol/init.js");

    extension::ImGuiPresenter::destroyInstance();
    extension::Inspector::destroyInstance();
    extension::Inspector::getInstance()->setAutoAddToScenes(true);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    ax::setLogFmtFlag(ax::LogFmtFlag::Colored);
    start();

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
}
