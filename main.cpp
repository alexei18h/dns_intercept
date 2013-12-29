
#include <Windows.h>
#include <CommCtrl.h>
#include "resource.h"

static HINSTANCE ghInstance = NULL;
static HWND ghDlg = NULL;
static HWND ghRunButton = NULL;
static HWND ghCancelButton = NULL;

static HWND
  ghStatusSystemEdit = NULL,
  ghStatusElevationEdit = NULL,
  ghStatusRunningEdit = NULL;

static INT_PTR CALLBACK RuleEditorDlgProc(
  HWND hDlg,
  UINT msg,
  WPARAM wParam,
  LPARAM lParam)
{
  switch (msg)
  {
  case WM_COMMAND:
    switch (LOWORD(wParam))
    {
    case IDOK:
      break;

    case IDCANCEL:
      SendMessageW(hDlg, WM_CLOSE, 0, 0);
      break;
    }
    break;

  case WM_CLOSE:
    EndDialog(hDlg, 0);
    break;
  }

  return 0;
}

static void CmdShowRuleEditor()
{
  DialogBoxParamW(
    ghInstance,
    (LPCWSTR)IDD_RULE_EDITOR_DLG,
    ghDlg,
    RuleEditorDlgProc,
    0);
}

static void CmdRun()
{
}

static void InitMainDlg(HWND hDlg)
{
  ghDlg = hDlg;

  ghStatusSystemEdit = GetDlgItem(ghDlg, IDC_STATUS_SYSTEM);
  ghStatusRunningEdit = GetDlgItem(ghDlg, IDC_STATUS_RUNNING);
  ghStatusElevationEdit = GetDlgItem(ghDlg, IDC_STATUS_ELEVATION);

  SetWindowTextW(ghStatusSystemEdit, L"Win x64");
}

static INT_PTR CALLBACK DlgProc(
  HWND hDlg,
  UINT msg,
  WPARAM wParam,
  LPARAM lParam)
{
  switch (msg)
  {
  case WM_INITDIALOG:
    InitMainDlg(hDlg);
    break;

  case WM_COMMAND:
    switch (LOWORD(wParam))
    {
    case IDC_RULES:
      CmdShowRuleEditor();
      break;

    case IDOK:
      CmdRun();
      break;

    case IDCANCEL:
      SendMessageW(hDlg, WM_CLOSE, 0, 0);
      break;
    }
    break;

  case WM_CLOSE:
    EndDialog(hDlg, 0);
    break;
  }

  return 0;
}

int APIENTRY entry()
{
  ghInstance = GetModuleHandleW(NULL);
  InitCommonControls();

  return
   DialogBoxParamW(
    ghInstance,
    (LPCWSTR)IDD_MAINDLG,
    HWND_DESKTOP,
    DlgProc,
    0);
}
