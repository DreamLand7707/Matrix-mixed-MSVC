#include <Windows.h>
#include <tchar.h>

int main(void)
{
    HGLOBAL hG = GlobalAlloc(GPTR, 1024);
    wchar_t *p = (wchar_t *)GlobalLock(hG);
    wchar_t ph[30] = L"复制到的信息（UNICODE形式）";
    for (int i = 0; i < wcslen(ph); i++)
    {
        p[i] = ph[i];
    }
    GlobalUnlock(hG);
    HWND hwnd = NULL;
    OpenClipboard(hwnd);
    EmptyClipboard();
    SetClipboardData(CF_UNICODETEXT, hG);
    CloseClipboard();
    GlobalFree(hG);
    return 0;
}