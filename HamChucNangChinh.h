#pragma once
#include "MenuChiTiet.h"

void quanLiCoSoDuLieu() {
	while (true) {
		system("cls");
		veTieuDe("[I] QUẢN LÍ CƠ SỞ DỮ LIỆU");
		cout << format("{:<60}", "[1] Quản lí đồ uống") << endl;
		cout << format("{:<60}", "[2] Quản lí đồ ăn") << endl;
		cout << format("{:<60}", "[3] Quản lí topping") << endl;
		cout << format("{:<60}", "[4] Cấu hình order") << endl;
		cout << format("{:<60}", "[5] Menu chi tiết") << endl;
		cout << format("{:<60}", "[0] Quay lại màn hình chính") << endl;
		veDuong(60);
		cout << " [*] CHỌN: ";

		string boNhoDem;
		getline(cin, boNhoDem);
		int luaChon = 0;
		if (boNhoDem != "") luaChon = stoi(boNhoDem);
		if (luaChon == 0) break;

		system("cls");
		if (luaChon == 1) quanLiDoUong();
		else if (luaChon == 2) quanLiDoAn();
		else if (luaChon == 3) quanLiTopping();
		else if (luaChon == 4) cauHinhOrder();
		else if (luaChon == 5) menuChiTiet();
		else cout << "\n--> Lựa chọn không hợp lệ!" << endl;

		dungManHinh();
	}
}

void quanLiDuLieuPhatSinh() {
	while (true) {
		system("cls");
		veTieuDe("[II] QUẢN LÍ DỮ LIỆU PHÁT SINH");
		cout << format("{:<60}", "[1] Quản lí bán hàng và order") << endl;
		cout << format("{:<60}", "[2] Quản lí kho") << endl;
		cout << format("{:<60}", "[3] Tra cứu dữ liệu giao dịch") << endl;
		cout << format("{:<60}", "[0] Quay lại màn hình chính") << endl;
		veDuong(60);
		cout << " [*] CHỌN: ";

		string boNhoDem;
		getline(cin, boNhoDem);
		int luaChon = 0;
		if (boNhoDem != "") luaChon = stoi(boNhoDem);
		if (luaChon == 0) break;

		system("cls");
		if (luaChon == 1) quanLiBanHangVaOrder();
		else if (luaChon == 2) quanLiKho();
		else if (luaChon == 3) traCuuGiaoDich();
		else cout << "\n--> Lựa chọn không hợp lệ!" << endl;

		dungManHinh();
	}
}

void baoCaoThongKe() {
	while (true) {
		system("cls");
		veTieuDe("[III] BÁO CÁO THỐNG KÊ");
		cout << format("{:<60}", "[1] Thống kê bán hàng") << endl;
		cout << format("{:<60}", "[2] Thống kê món bán chạy") << endl;
		cout << format("{:<60}", "[0] Quay lại màn hình chính") << endl;
		veDuong(60);
		cout << " [*] CHỌN: ";

		string boNhoDem;
		getline(cin, boNhoDem);
		int luaChon = 0;
		if (boNhoDem != "") luaChon = stoi(boNhoDem);
		if (luaChon == 0) break;

		system("cls");
		if (luaChon == 1) thongKeBanHang();
		else if (luaChon == 2) thongKeMonBanChay();
		else cout << "\n--> Lựa chọn không hợp lệ!" << endl;

		dungManHinh();
	}
}