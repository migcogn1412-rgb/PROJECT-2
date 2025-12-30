#pragma once
#include "TienIchChung.h"
#include "QuanLiDoUong.h"
#include "QuanLiDoAn.h"
#include "QuanLiTopping.h"
#include "CauHinhOrder.h"

const int TOI_DA = 100;

void menuChiTiet() {
	DoUong du[TOI_DA];
	DoAn da[TOI_DA];
	Topping t[TOI_DA];
	CauHinh ch[TOI_DA];
	int soLuongDU = 0, soLuongDA = 0, soLuongT = 0, soLuongCH = 0;

	docFileDoUong("DoUong.txt", du, soLuongDU);
	docFileDoAn("DoAn.txt", da, soLuongDA);
	docFileTopping("Topping.txt", t, soLuongT);
	docFileCauHinh("CauHinhOrder.txt", ch, soLuongCH);

	veTieuDe("MENU QUÁN CÀ PHÊ");
	cout << "\n=== ĐỒ UỐNG ===\n";
	if (soLuongDU == 0) cout << "Chưa có dữ liệu\n";
	else inMenuDoUong(du, soLuongDU);

	cout << "\n=== ĐỒ ĂN ===\n";
	if (soLuongDA == 0) cout << "Chưa có dữ liệu\n";
	else inMenuDoAn(da, soLuongDA);

	cout << "\n=== TOPPING ===\n";
	if (soLuongT == 0) cout << "Chưa có dữ liệu\n";
	else inMenuTopping(t, soLuongT);

	cout << "\n=== SIZE ===\n";
	if (soLuongCH == 0) cout << "Chưa có dữ liệu\n";
	else inCauHinh(ch, soLuongCH);
	cout << endl;
}

