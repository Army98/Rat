#include <iostream>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <Windows.h>
#include <lmcons.h>


// https://learn.microsoft.com/en-us/windows/win32/api/securitybaseapi/nf-securitybaseapi-checktokenmembership?redirectedfrom=MSDN
BOOL IsUserAdmin(VOID)
{
    BOOL b;
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    PSID AdministratorsGroup;
    b = AllocateAndInitializeSid(
        &NtAuthority,
        2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0,
        &AdministratorsGroup );

    if(b)
    {
        if (!CheckTokenMembership( NULL, AdministratorsGroup, &b))
        {
             b = FALSE;
        }
        FreeSid(AdministratorsGroup);
    }

    return(b);
}

void windows_presistence(char* filePath) {
    // first: get current user name running thread
    TCHAR user[UNLEN+1];
    DWORD userLen = UNLEN+1;
    GetUserName((TCHAR*)user, &userLen);
    //if(std::rename(filePath, ""))

    bool s = IsUserAdmin();
    if (s > 0) {
        system("DATE");
    }
    
}

int main(int argc, char** argv) {

    windows_presistence(argv[0]); // pass current file name to windows_presistence function
}
