#include <iostream>
#include "include/cef_app.h"
#include "include/cef_process_util.h"
#include "include/cef_browser.h"
#include "include/capi/cef_base_capi.h"

#include "SimpleApp.h"

int main(int c, char *a[]) {
    std::cout << "Hello, World! MainFunction" << std::endl;
    CefMainArgs mainArgs(c, a);

    CefRefPtr<SimpleApp> app(new SimpleApp);

    int exit_code = CefExecuteProcess(mainArgs, nullptr, nullptr);
    if (exit_code >= 0) {
        std::cout << "error in the CefProcess\n";
        // The sub-process has completed so return here.
        return exit_code;
    }
    std::cout << "Passes the CefProcess\n";

    CefSettings settings;
    settings.command_line_args_disabled = true;
    settings.ignore_certificate_errors = true;
    settings.no_sandbox = true;
    std::cout << "Passes the settings\n";

    CefInitialize(mainArgs, settings, app.get(), NULL);
    std::cout << "Passes the Intialized\n";

    CefRunMessageLoop();
    std::cout << "Passes the Finishes message loop\n";

    CefShutdown();
    std::cout << "Passes the Shoutdown\n";

    return 0;
}
