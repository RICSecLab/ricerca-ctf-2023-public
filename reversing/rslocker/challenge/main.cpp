#include <windows.h>
#include <intrin.h>
#include <strsafe.h>
#include "resource.h"

#define DEBUG 1

#pragma comment (linker, "/INCLUDE:_tls_used")
#pragma comment (linker, "/INCLUDE:tls_callback_func")

VOID NTAPI __stdcall _guard_check_icall(PVOID hModule, DWORD dwReason, PVOID _Reserved);

#pragma const_seg(".CRT$XLB")
EXTERN_C const PIMAGE_TLS_CALLBACK tls_callback_func = _guard_check_icall;
#pragma const_seg()

#define TIMER_ANTIDEBUG1 1
#define TIMER_ANTIDEBUG2 2
#define VAL_KEY1      0xbb40e64d
#define VAL_KEY1_FAKE 0x12b9b0a1
#define VAL_KEY2      0xa205b064
#define VAL_KEY2_FAKE 0x1033c4d6

BOOL isExceptionThrown = FALSE;
DWORD tls1, tls2;
HDESK hNewDesk, hOldDesk, hInputDesk;

CONST BYTE bMem[0x40] = {
	0x36, 0xd7, 0x8f, 0x01, 0x48, 0x9b, 0xd3, 0x3c,
	0x25, 0xa3, 0x2d, 0x0b, 0xbf, 0x76, 0x84, 0xbd,
	0x86, 0xe9, 0x52, 0x28, 0xf4, 0xaf, 0x18, 0x71,
	0xe7, 0xdd, 0x38, 0x64, 0xcd, 0xec, 0x53, 0xa8,
	0x56, 0x8c, 0x5f, 0x18, 0x65, 0x13, 0x5e, 0xe0,
	0x39, 0xd9, 0x80, 0x12, 0xcc, 0x19, 0xfd, 0xd9,
	0x7c, 0xb6, 0x8b, 0xbc, 0xb5, 0xab, 0x74, 0x3a,
	0xa3, 0x1b, 0x74, 0x9c, 0xbc, 0x3b, 0xbb, 0xb8,
};

VOID CALLBACK KickDebugger1(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime) {
	if (*(PDWORD)(__readgsqword(0x60) + 0xBC)) {
		TlsSetValue(tls1, (LPVOID)VAL_KEY1_FAKE);
	} else {
		TlsSetValue(tls1, (LPVOID)VAL_KEY1);
	}
}

VOID CALLBACK KickDebugger2(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime) {
	if (*(PBYTE)(__readgsqword(0x60) + 0x02)) {
		TlsSetValue(tls2, (LPVOID)VAL_KEY2_FAKE);
	}
	else {
		TlsSetValue(tls2, (LPVOID)VAL_KEY2);
	}
}

BOOL CheckPassword(CONST CHAR *flag) {
	BYTE cipher[0x100];
	DWORD s;
	DWORD k1, k2;
	WCHAR deskName[16] = { 0 };
	k1 = (DWORD)TlsGetValue(tls1);
	k2 = (DWORD)TlsGetValue(tls2);
	GetUserObjectInformation(GetThreadDesktop(GetCurrentThreadId()), UOI_NAME, deskName, 15, &s);

	__m128i key = _mm_set_epi32(
		_mm_crc32_u32(k1, *(UINT*)(deskName)),
		_mm_crc32_u32(k1, *(UINT*)(deskName + 2)),
		_mm_crc32_u32(k2, *(UINT*)(deskName)),
		_mm_crc32_u32(k2, *(UINT*)(deskName + 2))
	);
	for (INT i = 0; i < strlen(flag) + 1; i += 0x10) {
		__m128i p = _mm_load_si128((__m128i*)(flag + i));
		__m128i r = _mm_aesenc_si128(p, key);
		_mm_store_si128((__m128i*)(cipher + i), r);
	}

	return memcmp(cipher, bMem, 0x40) == 0;
}

BOOL CALLBACK WndProcModal(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	CHAR flag[0x100];

	switch (Msg) {
	case WM_COMMAND:
		switch (wParam) {
		case IDOK:
			memset(flag, 0, sizeof(flag));
			GetDlgItemTextA(hWnd, MAKEINTRESOURCE(IDC_EDIT1), flag, sizeof(flag));
			if (CheckPassword(flag)) {
				MessageBox(
					hWnd, L"Successfully unlocked. Thank you for paying the money.",
					L"RSLocker", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
				EndDialog(hWnd, IDOK);
			} else {
				MessageBox(
					hWnd, L"Invalid code",
					L"RSLocker", MB_OK | MB_ICONHAND | MB_TOPMOST
				);
			}
			return TRUE;

		case IDABORT:
			MessageBox(
				hWnd, L"I'll let you go this time.",
				L"RSLocker", MB_OK | MB_ICONINFORMATION | MB_TOPMOST
			);
			EndDialog(hWnd, IDOK);
			return TRUE;
		}
	}
	return FALSE;
}

VOID Cleanup(VOID) {
	TlsFree(tls2);
#if DEBUG
	SwitchDesktop(hOldDesk);
	SwitchDesktop(hInputDesk);
	SetThreadDesktop(hOldDesk);
	CloseDesktop(hNewDesk);
	CloseDesktop(hInputDesk);
#endif
	TlsFree(tls1);
	return TRUE;
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow) {
	if (IsDebuggerPresent()) {
		MessageBox(NULL, L"Do not debug this program.", L"RSLocker", MB_OK | MB_ICONHAND | MB_TOPMOST);
		ExitProcess(1);
	}
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, WndProcModal, 0);
	Cleanup();
	return 0;
}

VOID NTAPI __stdcall _guard_check_icall(PVOID hModule, DWORD dwReason, PVOID _Reserved) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		SetTimer(NULL, TIMER_ANTIDEBUG1, 100, KickDebugger1);
		tls1 = TlsAlloc();
#if DEBUG
		DWORD AccessFlag =
			STANDARD_RIGHTS_ALL | DESKTOP_CREATEWINDOW | DESKTOP_HOOKCONTROL
			| DESKTOP_READOBJECTS | DESKTOP_SWITCHDESKTOP | DESKTOP_WRITEOBJECTS;
		hOldDesk = GetThreadDesktop(GetCurrentThreadId());
		hInputDesk = OpenInputDesktop(0, FALSE, DESKTOP_SWITCHDESKTOP);
		hNewDesk = CreateDesktop(L"ねこです", NULL, NULL, 0, AccessFlag, NULL);
		if (hNewDesk == NULL) {
			MessageBox(
				NULL, L"Something went wrong. Please restart your computer.",
				L"RSLocker", MB_OK | MB_ICONHAND
			);
			ExitProcess(0);
		}
		SetThreadDesktop(hNewDesk);
		SwitchDesktop(hNewDesk);
#endif
		tls2 = TlsAlloc();
		SetTimer(NULL, TIMER_ANTIDEBUG2, 100, KickDebugger2);
	}
}
