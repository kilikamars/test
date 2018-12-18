#include"test_func.h"
#include"GSA.h"
#include <iostream>
#include <sstream>
#include <string>
#include<stdlib.h>
#include <cmath>
#include <Windows.h>
#include "resource.h"



BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE
	hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int ret = DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),
		NULL, (DLGPROC)DlgProc);
	return ret;
}


HWND hCombo1; 
TCHAR str_Him[] = { "Schaffer" };
TCHAR str_Simp1[] = { "Weierstrass" };
TCHAR str_Simp2[] = { "Rastrigin" };
TCHAR str_Simp3[] = { "Rosenbrock" };
TCHAR str_Simp4[] = { "Ackley" };
TCHAR str_Simp5[] = { "Schwefel" };


HWND hCombo2;
TCHAR str_min[] = { "min" };
TCHAR str_max[] = { "max" };

HWND hCombo3;
TCHAR str_res1[] = { "Restrict_Schwefel" };
TCHAR str_res2[] = { "Restrict_Ackley" };
TCHAR str_res3[] = { "Restrict_Schaffer" };
TCHAR str_res4[] = { "Restrict_Rosenbrock" };
TCHAR str_res5[] = { "Restrict_Rastrigin" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam,
	LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{

		hCombo1 = GetDlgItem(hwnd, IDC_FUNC);
		SendMessage(hCombo1, CB_ADDSTRING, 0, (LPARAM)str_Him);
		SendMessage(hCombo1, CB_ADDSTRING, 0, (LPARAM)str_Simp1);
		SendMessage(hCombo1, CB_ADDSTRING, 0, (LPARAM)str_Simp2);
		SendMessage(hCombo1, CB_ADDSTRING, 0, (LPARAM)str_Simp3);
		SendMessage(hCombo1, CB_ADDSTRING, 0, (LPARAM)str_Simp4);
		SendMessage(hCombo1, CB_ADDSTRING, 0, (LPARAM)str_Simp5);

		hCombo2 = GetDlgItem(hwnd, IDC_EXS);
		SendMessage(hCombo2, CB_ADDSTRING, 0, (LPARAM)str_max);
		SendMessage(hCombo2, CB_ADDSTRING, 0, (LPARAM)str_min);

		hCombo3 = GetDlgItem(hwnd, IDC_REST);
		SendMessage(hCombo3, CB_ADDSTRING, 0, (LPARAM)str_res1);
		SendMessage(hCombo3, CB_ADDSTRING, 0, (LPARAM)str_res2);
		SendMessage(hCombo3, CB_ADDSTRING, 0, (LPARAM)str_res3);
		SendMessage(hCombo3, CB_ADDSTRING, 0, (LPARAM)str_res4);
		SendMessage(hCombo3, CB_ADDSTRING, 0, (LPARAM)str_res5);
		return FALSE;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_OK:
		{

			TCHAR SN[10];
			int n;

			//Fichiers de sortie secondaires IDC_EDIT1
			GetDlgItemText(hwnd, IDC_N, SN, 8);
			int N = atoi(SN);
			GetDlgItemText(hwnd, IDC_IT, SN, 8);
			int it = atoi(SN);
			GetDlgItemText(hwnd, IDC_G, SN, 8);
			double G = atof(SN);
			n = SendMessage(hCombo2, CB_GETCURSEL, 0, 0L);
			bool mode = n == 0 ? true : false;
			n = SendMessage(hCombo1, CB_GETCURSEL, 0, 0L);
			double(*func)(vector<double>,int);
			func = nullptr;
			switch (n)
			{
			case 0:
				func = weierstrass;
				break;
			case 1:
				func = rastrigin;
				break;
			case 2:
				func = schaffer;
				break;
			case 3:
				func = rosenbrock;
				break;
			case 4:
				func = ackley;
				break;
			case 5:
				func = schwefel;
				break;
			//default:
				//break;
			}
			bool(*restrict) (vector<double>,int);
			restrict = nullptr;
			n = SendMessage(hCombo3, CB_GETCURSEL, 0, 0L);
			switch (n)
			{
			case 0:
			{
				restrict = restrictAckley;
				break;
			}
			case 1:
			{
				restrict = restrictSchwefel;
				break;
			}
			case 2:
			{
				restrict = restrictSchaffer;
				break;
			}
			case 3:
			{
				restrict = restrictRosenbrock;
				break;
			}
			case 4:
			{
				restrict = restrictRastrigin;
				break;
			}
			}
			if (!func || !restrict || !G || !N || !it || n < 0)
			{
				MessageBox(NULL, (LPCTSTR)"OUT! Circonférence permanente infinie", "Error",
					MB_OK | MB_ICONWARNING);
				return FALSE;
			}
			SetDlgItemText(hwnd, IDC_RX, "");
			SetDlgItemText(hwnd, IDC_RY, "");
			SetDlgItemText(hwnd, IDC_RFUNC, "");
			SetDlgItemText(hwnd, IDC_TIME, "");
			double start = GetTickCount();
			vector<double> max = GSA::GSA(func, 2, restrict, G, N, it, mode);
			double end = GetTickCount();
			double time = end - start;
			double best = func(max,2);
			std::ostringstream out;
			out << std::fixed << max[0];

			char R[30];
			strcpy_s(R, out.str().c_str());
			SetDlgItemText(hwnd, IDC_RX, R);
			out.str("");


			out << std::fixed << max[1];
			strcpy_s(R, out.str().c_str());
			SetDlgItemText(hwnd, IDC_RY, R);

			out.str("");

			out << std::fixed << best;
			strcpy_s(R, out.str().c_str());
			SetDlgItemText(hwnd, IDC_RFUNC, R);

			out.str("");

			out << std::fixed << time;
			strcpy_s(R, out.str().c_str());
			SetDlgItemText(hwnd, IDC_TIME, R);

			return FALSE;
		}
		case IDC_N:
			SetDlgItemText(hwnd, IDC_RX, "");
			SetDlgItemText(hwnd, IDC_RY, "");
			SetDlgItemText(hwnd, IDC_RFUNC, "");
			SetDlgItemText(hwnd, IDC_TIME, "");
			return FALSE;
		case IDC_G:
			SetDlgItemText(hwnd, IDC_RX, "");
			SetDlgItemText(hwnd, IDC_RY, "");
			SetDlgItemText(hwnd, IDC_RFUNC, "");
			SetDlgItemText(hwnd, IDC_TIME, "");
			return FALSE;
		case IDC_IT:
			SetDlgItemText(hwnd, IDC_RX, "");
			SetDlgItemText(hwnd, IDC_RY, "");
			SetDlgItemText(hwnd, IDC_RFUNC, "");
			SetDlgItemText(hwnd, IDC_TIME, "");
			return FALSE;
		case IDC_EXS:
			SetDlgItemText(hwnd, IDC_RX, "");
			SetDlgItemText(hwnd, IDC_RY, "");
			SetDlgItemText(hwnd, IDC_RFUNC, "");
			SetDlgItemText(hwnd, IDC_TIME, "");
			return FALSE;
		case IDC_FUNC:
			SetDlgItemText(hwnd, IDC_RX, "");
			SetDlgItemText(hwnd, IDC_RY, "");
			SetDlgItemText(hwnd, IDC_RFUNC, "");
			SetDlgItemText(hwnd, IDC_TIME, "");
			return FALSE;
		case IDC_REST:
		{
			int n = SendMessage(hCombo3, CB_GETCURSEL, 0, 0L);
			switch (n)
			{
			case 0:
			{
				SetDlgItemText(hwnd, IDC_VREST, "- 500 <= x <= 500");
				break;
			}
			case 1:
			{
				SetDlgItemText(hwnd, IDC_VREST, "- 32768 <= x <= 32768");
				break;
			}
			case 2:
			{
				SetDlgItemText(hwnd, IDC_VREST, "- 100 <= x <= 100");
				break;
			}
			case 3:
			{
				SetDlgItemText(hwnd, IDC_VREST, "- 5 <= x <= 10");
				break;
			}
			case 4:
			{
				SetDlgItemText(hwnd, IDC_VREST, "- 5.12 <= x <= 5.12");
				break;
			}
			}
			return FALSE; 
		}
		case IDC_VREST:
			return FALSE;
		case IDC_RFUNC:
			return FALSE;
		case IDC_RX:
			return FALSE;
		case IDC_RY:
			return FALSE;
		case IDC_TIME:
			return FALSE;
		}
	}
	case WM_CLOSE:
	{
		EndDialog(hwnd, 0);
		return FALSE;
	}
	}
	return FALSE;
}