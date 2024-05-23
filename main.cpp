#include "Form/loginwindow.h"
#include <QApplication>
#include <QIcon>
#include <windows.h>
#include <QMessageBox>
#include "maxcare/setupfolder.h"
bool isRunningAsAdmin() {
    BOOL fIsRunAsAdmin = FALSE;
    PSID pAdministratorsGroup = NULL;

    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    if (AllocateAndInitializeSid(
            &NtAuthority, 2,
            SECURITY_BUILTIN_DOMAIN_RID,
            DOMAIN_ALIAS_RID_ADMINS,
            0, 0, 0, 0, 0, 0,
            &pAdministratorsGroup)) {
        CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin);
        FreeSid(pAdministratorsGroup);
    }

    return fIsRunAsAdmin;
}
void runAsAdmin() {
    TCHAR szPath[MAX_PATH];
    if (GetModuleFileName(NULL, szPath, ARRAYSIZE(szPath))) {
        SHELLEXECUTEINFO sei = { sizeof(sei) };
        sei.lpVerb = L"runas";
        sei.lpFile = szPath;
        sei.hwnd = NULL;
        sei.nShow = SW_NORMAL;

        if (!ShellExecuteEx(&sei)) {
            QMessageBox::warning(nullptr, "Error", "The application needs to be run as an administrator.");
            exit(EXIT_FAILURE);
        }
    }
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow loginWindow;
    // if(!isRunningAsAdmin()){
    //     QMessageBox::information(nullptr, "Info", "Please run the application as an administrator!");
    //     runAsAdmin();
    //     return 0;
    // }
    SetupFolder::CreateBaseFolder();
    loginWindow.show();
    return a.exec();
}


