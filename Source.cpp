#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<opencv2\highgui\highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>
#include<opencv\cv.h>
#include<stdio.h>
#include <string>
#include<Windows.h>
#include<time.h>
#include <Wininet.h>
#pragma comment(lib, "wininet.lib")
using namespace std;
using namespace cv;


double minval, maxval;

Mat hwnd2mat(HWND hwnd) {

	HDC hwindowDC, hwindowCompatibleDC;

	int height, width, srcheight, srcwidth;
	HBITMAP hbwindow;
	Mat src;
	BITMAPINFOHEADER  bi;

	hwindowDC = GetDC(hwnd);
	hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
	SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

	RECT windowsize;    // get the height and width of the screen
	GetClientRect(hwnd, &windowsize);

	srcheight = windowsize.bottom;
	srcwidth = windowsize.right;
	height = windowsize.bottom;  //change this to whatever size you want to resize to
	width = windowsize.right;

	src.create(height, width, CV_8UC4);

	// create a bitmap
	hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
	bi.biSize = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
	bi.biWidth = width;
	bi.biHeight = -height;  //this is the line that makes it draw upside down or not
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	// use the previously created device context with the bitmap
	SelectObject(hwindowCompatibleDC, hbwindow);
	// copy from the window device context to the bitmap device context
	StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, srcwidth, srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
	GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow

																									   // avoid memory leak
	DeleteObject(hbwindow); DeleteDC(hwindowCompatibleDC); ReleaseDC(hwnd, hwindowDC);

	return src;
}


void Ctrl_W() {
	keybd_event(VK_CONTROL, 0x11, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event('W', 0x91, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event('W', 0x91, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0x11, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

void Ctrl_C(){
	keybd_event(VK_CONTROL, 0x11, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event('C', 0x43, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event('C', 0x43, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0x11, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

void Ctrl_V(){
	keybd_event(VK_CONTROL, 0x11, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event('V', 0x56, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event('V', 0x56, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0x11, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

void Enter() {
	keybd_event(VK_RETURN, 0x0d, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event(VK_RETURN, 0x0d, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

void Ctrl_shift_tab() {
	keybd_event(VK_CONTROL, 0x11, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event(VK_SHIFT, 0x10, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event(VK_TAB, 0x09, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event(VK_TAB, 0x09, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	keybd_event(VK_SHIFT, 0x10, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0x11, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

void Ctrl_tab() {
	keybd_event(VK_CONTROL, 0x11, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event(VK_TAB, 0x09, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event(VK_TAB, 0x09, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0x11, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

void Ctrl_tab_x2() {
	keybd_event(VK_CONTROL, 0x11, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event(VK_TAB, 0x09, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event(VK_TAB, 0x09, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	Sleep(500);
	keybd_event(VK_TAB, 0x09, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event(VK_TAB, 0x09, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0x11, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

void Alt_tab() {
	keybd_event(VK_MENU, 0x12, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event(VK_TAB, 0x09, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event(VK_TAB, 0x09, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x12, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}


void Larrow_alt() {
	keybd_event(VK_MENU, 0x12, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event(VK_LEFT, 0x25, KEYEVENTF_EXTENDEDKEY | 0, 0);
	Sleep(100);
	keybd_event(VK_LEFT, 0x25, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x12, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

void L() {
	keybd_event('L', 0xa6, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event('L', 0xa6, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

void J() {
	keybd_event('J', 0xa4, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event('J', 0xa4, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}
void Page_Down_key() {
	keybd_event(VK_NEXT, 0x22, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event(VK_NEXT, 0x22, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}
void Esc() {
	keybd_event(VK_ESCAPE, 0x1b, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event(VK_ESCAPE, 0x1b, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}


void page_down() {
	int px;
	px = rand() % 25 + 5;
	for (int i = 0; i < px; i++) {
		mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -25, 0);
		Sleep(rand() % 60 + 20);
	}
}

void page_up() {
	int px;
	px = rand() % 25 + 5;
	for (int i = 0; i < px; i++) {
		mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 25, 0);
		Sleep(rand() % 60 + 20);
	}
}

void page_down(int x) {
	for (int i = 0; i < x; i += 5) {
		mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_WHEEL, 0, 0, -5, 0);
		Sleep(rand() % 30 + 10);
	}
}

void page_up(int x) {
	for (int i = 0; i < x; i += 5) {
		mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_WHEEL, 0, 0, 5, 0);
		Sleep(rand() % 30 + 10);
	}
}

void Tap_down() {
	keybd_event(VK_DOWN, 0x28, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event(VK_DOWN, 0x28, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

void click() {
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); // íàæàëè
	Sleep(100);
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0); //îòïóñòèëè
}

void move(int x, int y) {
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, x, y, 0, 0);
}

int get_curs_x(){
	POINT p;
	GetCursorPos(&p);
	return p.x;
}

int get_curs_y(){
	POINT p;
	GetCursorPos(&p);
	return p.y;
}



int main()
{
	setlocale(0, "");
	srand(time(NULL));
	int ans;
	char answer;
	do{
		cout << "       MENU" << endl;
		cout << "1. Like posts" << endl;
		cout << "2. Invite friends to the group" << endl;
		cout << "3. Like only one post by all bots" << endl;
		cout << "4. Check сursor position" << endl;
		cout << "5. Go to the link by all bots" << endl;
		cout << "6. Add friends" << endl;
		cout << "7. Exit" << endl;
		cin >> ans;
		switch (ans) {
		case 1: {
		int N;
		double bots, x, y, x_s, y_s, like_x, like_y, wid, hei, t, width, height, spawn_x, spawn_y, err=0;
		srand(time(NULL));
		t = rand() % 200 + 100;
		x = get_curs_x();
		y = get_curs_y();
		move(66000, 66000);
		wid = get_curs_x();
		hei = get_curs_y();
		move(-66000, -66000);
		x = (65535 * ((x / wid) * 100)) / 100;
		y = (65535 * ((y / hei) * 100)) / 100;
		move(x, y);

		cout << "Enter the number of bots" << endl;
		cin >> bots;
		double *posts = new double[bots];
		cout << "Enter the number of likes for every bot" << endl;
		for (int i = 0; i < bots; i++) {
			cout << "Bot #" << i + 1 << ": ";
			cin >> posts[i];
		}
		cout << "Move the cursor to a point free of elements on the page and press Enter" << endl;
		system("pause>null");
		spawn_x = get_curs_x();
		spawn_y = get_curs_y();
		spawn_x = (65535 * ((spawn_x / wid) * 100)) / 100;
		spawn_y = (65535 * ((spawn_y / hei) * 100)) / 100;
		cout << "Complete" << endl;
		cout << "Move the cursor to the left border to check the frame, and press Enter" << endl;
		system("pause>null");
		x_s = get_curs_x();
		cout << "Complete" << endl;
		cout << "Move the cursor to the right border to check the frame, and press Enter" << endl;
		system("pause>null");
		x = get_curs_x();
		cout << "Complete" << endl;
		cout << "Move the cursor to the top border to check the frame, and press Enter" << endl;
		system("pause>null");
		y = get_curs_y();
		cout << "Complete" << endl;
		cout << "Move the cursor to the bottom border to check the frame, and press Enter" << endl;
		system("pause>null");
		y_s = get_curs_y();
		cout << "Complete" << endl;

		cout << "Close tab after likes?" << endl;
		cout << "1. Yes" << endl;
		cout << "0. No" << endl;
		cin >> N;


		string shablon_im = "like.bmp";
		char ish_sh[100];
		strcpy(ish_sh, shablon_im.c_str());
		IplImage* templ = 0;
		templ = cvLoadImage(ish_sh, 1);

		string ishod_im = "screen.bmp";
		char ish_is[100];
		strcpy(ish_is, ishod_im.c_str());

		HWND hDesktopWnd;
		Mat scr;
		IplImage* image = 0;
		IplImage *res, *res1;
		CvPoint minloc, maxloc, minloc1, maxloc1;

		Sleep(5000);

		cout << "Open browser!" << endl;


		for (int i = 0; i < bots; i++) {
			for (int j = 0; j < posts[i]; j++) {
				do {
					hDesktopWnd = GetDesktopWindow();


					scr = hwnd2mat(hDesktopWnd);
					imwrite("screen.bmp", scr);



					image = cvLoadImage(ish_is, 1);



					width = templ->width;
					height = templ->height;
					res = cvCreateImage(cvSize((image->width - templ->width + 1), (image->height - templ->height + 1)), IPL_DEPTH_32F, 1);
					cvMatchTemplate(image, templ, res, CV_TM_SQDIFF);
					cvMinMaxLoc(res, &minval, &maxval, &minloc, &maxloc, 0);

					move(spawn_x, spawn_y);
					if (minloc.x < x && minloc.x>x_s) {
						if (minloc.y > y && minloc.y < y_s) {
							like_x = (65535 * (((minloc.x + 10) / wid) * 100)) / 100;
							like_y = (65535 * (((minloc.y + 10) / hei) * 100)) / 100;
							move(like_x, like_y);
							//Sleep(2 * t);
							click();
							//Sleep(2 * t);
							move(spawn_x, spawn_y);
							click();
							Page_Down_key();
							cvReleaseImage(&image);
							cvReleaseImage(&res);
							Sleep(2 * t);
							err = 0;
						}
						else {
							Page_Down_key();
							click();
							Esc();
							Sleep(5 * t);
							cvReleaseImage(&image);
							cvReleaseImage(&res);
							err = 1;
						}
					}
					else {
						Page_Down_key();
						click();
						Esc();
						Sleep(5 * t);
						cvReleaseImage(&image);
						cvReleaseImage(&res);
						err = 1;
					}
				} while (err == 1);
			}
			if (N != 0) { Ctrl_W(); }
			if (N == 0) { Ctrl_tab(); }
			Sleep(1500);
		}
		break;
	}
		case 2: {
		int size, frnd, ver;

		cout << "Enter the number of bots" << endl;
		cin >> size;
		int *arr = new int[size];
		cout << "Enter the number of friends" << endl;
		cin >> frnd;

		cout << "Enter count of friends for start(for every tab different):" << endl;

		for (int i = 0; i < size; i++) {
			cout << "Tab #" << i + 1 << " ";
			cin >> arr[i];
		}

		cout << "Open browser!" << endl;
		Sleep(10000);

		for (int i = 0; i < size; i++) {

			Sleep(4000);

			if (arr[i] > 0) {
				for (int j = 0; j < arr[i]; j++) {
					page_down(70);
				}
			}
			else {}

			for (int j = 0; j < frnd; j++) {
				Sleep(rand() % 1000 + 256);
				click();
				Sleep(rand() % 1000 + 256);
				page_down(70);
				ver = rand() % 5;
				if (ver == 3) { page_down(70); }
			}
			Sleep(4000);
			Ctrl_tab_x2();

		}
		delete[] arr;
		break;
	}
		case 3: {
		int N;
		char NN;
		double bot, x_url, y_url, wid, hei, t, width, height, like_x, like_y, x_s, y_s, fails = 0;
		bool f = false;

		double x, y;
		x = get_curs_x();
		y = get_curs_y();
		move(66000, 66000);
		wid = get_curs_x();
		hei = get_curs_y();
		move(-66000, -66000);
		x = (65535 * ((x / wid) * 100)) / 100;
		y = (65535 * ((y / hei) * 100)) / 100;
		move(x, y);

		cout << "Enter the number of bots" << endl;
		cin >> bot;

		cout << "Move the cursor to the adress line and press Enter" << endl;
		system("pause>null");
		x_url = get_curs_x();
		y_url = get_curs_y();
		cout << "Complete" << endl;

		cout << "Enter the count of sec of pause for load a page" << endl;
		cin >> t;

		x_url = (65535 * ((x_url / wid) * 100)) / 100;
		y_url = (65535 * ((y_url / hei) * 100)) / 100;


		cout << "Move the cursor to the left border to check the frame, and press Enter" << endl;
		system("pause>null");
		x_s = get_curs_x();
		cout << "Complete" << endl;
		cout << "Move the cursor to the right border to check the frame, and press Enter" << endl;
		system("pause>null");
		x = get_curs_x();
		cout << "Complete" << endl;
		cout << "Move the cursor to the top border to check the frame, and press Enter" << endl;
		system("pause>null");
		y = get_curs_y();
		cout << "Complete" << endl;
		cout << "Move the cursor to the bottom border to check the frame, and press Enter" << endl;
		system("pause>null");
		y_s = get_curs_y();
		cout << "Complete" << endl;

		cout << "Close tabs after like?" << endl;
		cout << "1. Yes" << endl;
		cout << "0. No" << endl;
		cin >> N;

		string shablon_im = "like.bmp";
		char ish_sh[100];
		strcpy(ish_sh, shablon_im.c_str());
		IplImage* templ = 0;
		templ = cvLoadImage(ish_sh, 1);

		string ishod_im = "screen.bmp";
		char ish_is[100];
		strcpy(ish_is, ishod_im.c_str());

		HWND hDesktopWnd;
		Mat scr;
		IplImage* image = 0;
		IplImage *res, *res1;
		CvPoint minloc, maxloc, minloc1, maxloc1;

	n:
		cout << "Open browser!" << endl;

		Sleep(10000);

		move(-66000, -66000);


		for (int i = 0; i < bot; i++) {
			move(x_url, y_url);
			//Sleep(450);
			click();
			//Sleep(450);
			Ctrl_V();
			//Sleep(450);
			Enter();
			//Sleep(450);
			move(-x_url, -y_url);
			Sleep(t * 1000);
			for (int m = 0; m <= 2; m++) {
				hDesktopWnd = GetDesktopWindow();


				scr = hwnd2mat(hDesktopWnd);
				imwrite("screen.bmp", scr);



				image = cvLoadImage(ish_is, 1);



				width = templ->width;
				height = templ->height;
				res = cvCreateImage(cvSize((image->width - templ->width + 1), (image->height - templ->height + 1)), IPL_DEPTH_32F, 1);
				cvMatchTemplate(image, templ, res, CV_TM_SQDIFF);
				cvMinMaxLoc(res, &minval, &maxval, &minloc, &maxloc, 0);

				if (minloc.x < x && minloc.x>x_s) {
					if (minloc.y > y && minloc.y < y_s) {
						like_x = (65535 * (((minloc.x + 10) / wid) * 100)) / 100;
						like_y = (65535 * (((minloc.y + 10) / hei) * 100)) / 100;
						move(like_x, like_y);
						//Sleep(400);
						click();
						//Sleep(1000);
						cvReleaseImage(&image);
						cvReleaseImage(&res);
						f = false;
						m = 3;
					}
					else {
						Page_Down_key();
						Sleep(500);
						f = true;
						cvReleaseImage(&image);
						cvReleaseImage(&res);
					}
				}
				else {
					Page_Down_key();
					Sleep(500);
					f = true;
					cvReleaseImage(&image);
					cvReleaseImage(&res);
				}
			}
			if (f == true) { fails++; }
			if (N != 0) { Ctrl_W(); }
			if (N == 0) { Ctrl_tab(); }
			Sleep(1000);
		}
		cout << "Fails:" << fails << endl;
		break;
	}
		case 4: {
		double x = get_curs_x(), y = get_curs_y();
		cout << "X=" << x << endl;
		cout << "y=" << y << endl;
		break;
	}
		case 5: {
		double bot, x_url, y_url, wid, hei, t;

		double x, y;
		x = get_curs_x();
		y = get_curs_y();
		move(66000, 66000);
		wid = get_curs_x();
		hei = get_curs_y();
		move(-66000, -66000);
		x = (65535 * ((x / wid) * 100)) / 100;
		y = (65535 * ((y / hei) * 100)) / 100;
		move(x, y);

		cout << "Enter the number of bots" << endl;
		cin >> bot;

		cout << "Move the cursor to the adress line and press Enter" << endl;
		system("pause>null");
		x_url = get_curs_x();
		y_url = get_curs_y();
		cout << "Complete" << endl;

		cout << "Enter the count of sec of pause between tabs" << endl;
		cin >> t;

		x_url = (65535 * ((x_url / wid) * 100)) / 100;
		y_url = (65535 * ((y_url / hei) * 100)) / 100;


		cout << "Open browser!" << endl;

		Sleep(10000);

		move(-66000, -66000);

		for (int i = 0; i < bot; i++) {
			move(x_url, y_url);
			Sleep(450);
			click();
			Sleep(450);
			Ctrl_V();
			Sleep(450);
			Enter();
			Sleep(450);
			Ctrl_tab();
			Sleep(100);
			move(-x_url, -y_url);
			Sleep(t * 1000);
		}
		break;
	}
		case 6: {
			double bots, x, y, x_s, y_s, like_x, like_y, wid, hei, t, width, height, spawn_x, spawn_y, err = 0;
		srand(time(NULL));
		t = rand() % 200 + 100;
		x = get_curs_x();
		y = get_curs_y();
		move(66000, 66000);
		wid = get_curs_x();
		hei = get_curs_y();
		move(-66000, -66000);
		x = (65535 * ((x / wid) * 100)) / 100;
		y = (65535 * ((y / hei) * 100)) / 100;
		move(x, y);

		cout << "Enter the number of bots" << endl;
		cin >> bots;
		double *friends = new double[bots];
		cout << "Enter the number of friends for each bot" << endl;
		for (int i = 0; i < bots; i++) {
			cout << "Bot ¹" << i + 1 << ": ";
			cin >> friends[i];
		}
		cout << "Move the cursor to a point free of elements on the page and press Enter" << endl;
		system("pause>null");
		spawn_x = get_curs_x();
		spawn_y = get_curs_y();
		spawn_x = (65535 * ((spawn_x / wid) * 100)) / 100;
		spawn_y = (65535 * ((spawn_y / hei) * 100)) / 100;
		cout << "Comlete" << endl;
		cout << "Move the cursor to the left border to check the frame, and press Enter" << endl;
		system("pause>null");
		x_s = get_curs_x();
		cout << "Complete" << endl;
		cout << "Move the cursor to the right border to check the frame, and press Enter" << endl;
		system("pause>null");
		x = get_curs_x();
		cout << "Complete" << endl;
		cout << "Move the cursor to the top border to check the frame, and press Enter" << endl;
		system("pause>null");
		y = get_curs_y();
		cout << "Complete" << endl;
		cout << "Move the cursor to the bottom border to check the frame, and press Enter" << endl;
		system("pause>null");
		y_s = get_curs_y();
		cout << "Complete" << endl;

		cout << "Open browser!" << endl;

		string shablon_im = "friend.bmp";
		char ish_sh[100];
		strcpy(ish_sh, shablon_im.c_str());
		IplImage* templ = 0;
		templ = cvLoadImage(ish_sh, 1);

		string ishod_im = "screen.bmp";
		char ish_is[100];
		strcpy(ish_is, ishod_im.c_str());

		HWND hDesktopWnd;
		Mat scr;
		IplImage* image = 0;
		IplImage *res, *res1;
		CvPoint minloc, maxloc, minloc1, maxloc1;
		Sleep(5000);
		for (int i = 0; i < bots; i++) {
			for (int j = 0; j < friends[i]; j++) {
				do {
					hDesktopWnd = GetDesktopWindow();


					scr = hwnd2mat(hDesktopWnd);
					imwrite("screen.bmp", scr);



					image = cvLoadImage(ish_is, 1);



					width = templ->width;
					height = templ->height;
					res = cvCreateImage(cvSize((image->width - templ->width + 1), (image->height - templ->height + 1)), IPL_DEPTH_32F, 1);
					cvMatchTemplate(image, templ, res, CV_TM_SQDIFF);
					cvMinMaxLoc(res, &minval, &maxval, &minloc, &maxloc, 0);

					move(spawn_x, spawn_y);
					if (minloc.x < x && minloc.x>x_s) {
						if (minloc.y > y && minloc.y < y_s) {
							like_x = (65535 * (((minloc.x + 15) / wid) * 100)) / 100;
							like_y = (65535 * (((minloc.y + 15) / hei) * 100)) / 100;
							move(like_x, like_y);
							Sleep(2 * t);
							click();
							Sleep(2 * t);
							move(spawn_x, spawn_y);
							click();
							cvReleaseImage(&image);
							cvReleaseImage(&res);
							Sleep(4 * t);
							err = 0;
						}
						else {
							Page_Down_key();
							click();
							Esc();
							Sleep(10 * t);
							cvReleaseImage(&image);
							cvReleaseImage(&res);
							err = 1;
						}
					}
					else {
						Page_Down_key();
						click();
						Esc();
						Sleep(10 * t);
						cvReleaseImage(&image);
						cvReleaseImage(&res);
						err = 1;
					}
				} while (err = 1);
			}
			Ctrl_W();
			Sleep(1500);
		}
		break;
	}
		case 7: {
		return 0;
		}
		default: {}
		}
	}while (true);
}
