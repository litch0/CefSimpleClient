//
// Created by litch0 on 11/13/20.
//
#pragma once

#include "include/cef_app.h"
#include <string>
#include "SimpleHandler.h"

#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"

// Implement application-level callbacks for the browser process.
class SimpleApp : public CefApp, public CefBrowserProcessHandler {
public:
    SimpleApp();

    // CefApp methods:
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
    OVERRIDE {
        return this;
    }

    // CefBrowserProcessHandler methods:
    virtual void OnContextInitialized() OVERRIDE;

private:
    // Include the default reference counting implementation.
IMPLEMENT_REFCOUNTING(SimpleApp);
};

class SimpleWindowDelegate : public CefWindowDelegate {
public:
    explicit SimpleWindowDelegate(CefRefPtr<CefBrowserView> browser_view)
            : browser_view_(browser_view) {}

    void OnWindowCreated(CefRefPtr<CefWindow> window) OVERRIDE {
        // Add the browser view and show the window.
        window->AddChildView(browser_view_);
        window->Show();

        // Give keyboard focus to the browser view.
        browser_view_->RequestFocus();
    }

    void OnWindowDestroyed(CefRefPtr<CefWindow> window) OVERRIDE {
        browser_view_ = nullptr;
    }

    bool CanClose(CefRefPtr<CefWindow> window) OVERRIDE {
        // Allow the window to close if the browser says it's OK.
        CefRefPtr<CefBrowser> browser = browser_view_->GetBrowser();
        if (browser)
            return browser->GetHost()->TryCloseBrowser();
        return true;
    }

    CefSize GetPreferredSize(CefRefPtr<CefView> view) OVERRIDE {
        return CefSize(800, 600);
    }

private:
    CefRefPtr<CefBrowserView> browser_view_;

IMPLEMENT_REFCOUNTING(SimpleWindowDelegate);
    DISALLOW_COPY_AND_ASSIGN(SimpleWindowDelegate);
};

class SimpleBrowserViewDelegate : public CefBrowserViewDelegate {
public:
    SimpleBrowserViewDelegate() {}

    bool OnPopupBrowserViewCreated(CefRefPtr<CefBrowserView> browser_view,
                                   CefRefPtr<CefBrowserView> popup_browser_view,
                                   bool is_devtools) OVERRIDE {
        // Create a new top-level Window for the popup. It will show itself after
        // creation.
        CefWindow::CreateTopLevelWindow(
                new SimpleWindowDelegate(popup_browser_view));

        // We created the Window.
        return true;
    }

private:
IMPLEMENT_REFCOUNTING(SimpleBrowserViewDelegate);
    DISALLOW_COPY_AND_ASSIGN(SimpleBrowserViewDelegate);
};

SimpleApp::SimpleApp() {}

void SimpleApp::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();

    CefRefPtr<CefCommandLine> command_line =
            CefCommandLine::GetGlobalCommandLine();

    const bool enable_chrome_runtime = true;

    const bool use_views = false;


    // SimpleHandler implements browser-level callbacks.
    CefRefPtr<SimpleHandler> handler(new SimpleHandler(use_views));

    // Specify CEF browser settings here.
    CefBrowserSettings browser_settings;

    std::string url;

    // Check if a "--url=" value was provided via the command-line. If so, use
    // that instead of the default URL.
    url = command_line->GetSwitchValue("url");
    if (url.empty())
        url = "http://www.google.com";

    if (use_views) {
        // Create the BrowserView.
        std::cout << "using browser view";
        CefRefPtr<CefBrowserView> browser_view = CefBrowserView::CreateBrowserView( handler, url, browser_settings, nullptr, nullptr,new SimpleBrowserViewDelegate());



        // Create the Window. It will show itself after creation.
        CefWindow::CreateTopLevelWindow(new SimpleWindowDelegate(browser_view));
    } else {
        // Information used when creating the native window.
        CefWindowInfo window_info;

        // Create the first browser window.
        CefBrowserHost::CreateBrowser(window_info, handler, url, browser_settings,
                                      nullptr, nullptr);
    }
}