#include <iostream>
#include <windows.h>
#include <lm.h>

#include <napi.h>

ULONG isTokenAdmin(HANDLE hToken, PBOOL pbIsAdmin)
{
    ULONG cbSid = MAX_SID_SIZE;
    PSID pSid = alloca(cbSid);
    return CreateWellKnownSid(::WinBuiltinAdministratorsSid, 0, pSid, &cbSid) &&
        CheckTokenMembership(hToken, pSid, pbIsAdmin) ? NOERROR : GetLastError();
}

ULONG isUserAnAdminEx(PBOOL pbIsAdmin, PBOOL pbNeedElevate)
{
    ULONG dwError = NOERROR;

    HANDLE hToken;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_DUPLICATE, &hToken))
    {
        ULONG cb;
        union {
            TOKEN_ELEVATION_TYPE tet;
            TOKEN_LINKED_TOKEN tlt;
        };

        if (GetTokenInformation(hToken, ::TokenElevationType, &tet, sizeof(tet), &cb))
        {
            switch (tet)
            {
            case TokenElevationTypeLimited:
                *pbNeedElevate = TRUE;
                if (GetTokenInformation(hToken, ::TokenLinkedToken, &tlt, sizeof(tlt), &cb))
                {
                    dwError = IsTokenAdmin(tlt.LinkedToken, pbIsAdmin);
                    CloseHandle(tlt.LinkedToken);
                }
                else
                {
                    dwError = GetLastError();
                }
                break;
            case TokenElevationTypeFull:
            case TokenElevationTypeDefault:
                *pbNeedElevate = FALSE;
                // only because CheckTokenMembership want an impersonation token.
                // really most query can be and must be done direct with this token
                if (DuplicateToken(hToken, ::SecurityIdentification, &tlt.LinkedToken))
                {
                    dwError = IsTokenAdmin(tlt.LinkedToken, pbIsAdmin);
                    CloseHandle(tlt.LinkedToken);
                }
                else
                {
                    GetLastError();
                }
                break;
            default:
                dwError = ERROR_GEN_FAILURE;
            }
        }
        else
        {
            dwError = GetLastError();
        }

        CloseHandle(hToken);
    }

    return dwError;
}

Napi::Value currentUserIsAdmin(const Napi::CallbackInfo &info){
    BOOL isAdmin;
    BOOL needElevate;
    ULONG error = IsUserAnAdminEx(&isAdmin, &needElevate);
		return Napi::Value::From(info.Env(), isAdmin);
}



Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(Napi::String::New(env, "currentUserIsAdmin"), Napi::Function::New(env, currentUserIsAdmin));
  return exports;
}
#if NODE_MAJOR_VERSION >= 10
NAN_MODULE_WORKER_ENABLED(currentUserIsAdminModule, Init)
#else
NODE_API_MODULE(currentUserIsAdminModule, Init);
#endif