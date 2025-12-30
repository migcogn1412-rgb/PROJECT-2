#pragma once
#include "TienIchChung.h"

struct Topping {
	string ten, ma;
	int giaGoc = 0;
};

Topping docTopping(string thongTin) {
	istringstream phanTach(thongTin);
	Topping t;
	string boNhoDem;
	getline(phanTach, t.ten, '|');
	getline(phanTach, boNhoDem, '|'); t.giaGoc = stoi(boNhoDem);
	getline(phanTach, t.ma);
	return t;
}

bool docFileTopping(string tenFile, Topping danhSach[], int& thuTu) {
	ifstream docFile(tenFile, ios::in);
	if (!docFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	string boNhoDem;
	thuTu = 0;
	while (getline(docFile, boNhoDem)) {
		if (boNhoDem.length() > 5) {
			danhSach[thuTu] = docTopping(boNhoDem);
			if (danhSach[thuTu].ma != "") thuTu++;
		}
	}
	docFile.close();
	return true;
}

bool ghiFileTopping(string tenFile, Topping danhSach[], int& thuTu) {
	ofstream ghiFile(tenFile, ios::out);
	if (!ghiFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	for (int i = 0; i < thuTu; i++) {
		ghiFile << danhSach[i].ten << "|"
			<< danhSach[i].giaGoc << "|"
			<< danhSach[i].ma << endl;
	}
	ghiFile.close();
	return true;
}

void xoaDongTopping(Topping danhSach[], int& thuTu, int i) {
	for (int j = i; j < thuTu - 1; j++) {
		danhSach[j] = danhSach[j + 1];
	}
	thuTu--;
}

void capNhatTopping(Topping& mon) {
	string boNhoDem;

	cout << format("Mã mới (cũ: {}): ", mon.ma);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.ma = boNhoDem;

	cout << format("Tên mới (cũ: {}): ", mon.ten);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.ten = boNhoDem;

	cout << format("Giá mới (cũ: {}): ", mon.giaGoc);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.giaGoc = stoi(boNhoDem);
}

void inMenuTopping(Topping danhSach[], int& thuTu) {
	veDuong(60);
	cout << format("| {:<10} | {:<30} | {:<10} |", "MÃ", "TÊN ĐỒ UỐNG", "GIÁ") << endl;
	veDuong(60);
	for (int i = 0; i < thuTu; i++) {
		cout << format("| {:<10} | {:<30} | {:<10} |", danhSach[i].ma, danhSach[i].ten, danhSach[i].giaGoc) << endl;
	}
	veDuong(60);
	cout << endl;
}

void nhapToppingMoi(Topping& moi) {
	cout << format("{:<25}: ", "Nhập mã topping");
	getline(cin, moi.ma);

	cout << format("{:<25}: ", "Nhập tên món");
	getline(cin, moi.ten);

	cout << format("{:<25}: ", "Nhập giá gốc");
	string boNhoDem;
	getline(cin, boNhoDem); moi.giaGoc = stoi(boNhoDem);
}

void themTopping(string fileTopping) {
	veTieuDe("THÊM TOPPING MỚI");

	Topping danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileTopping(fileTopping, danhSach, thuTu)) {
		cout << "* MENU TOPPING HIỆN TẠI *" << endl;
		inMenuTopping(danhSach, thuTu);
	}

	ofstream themTopping(fileTopping, ios::app);
	if (!themTopping.is_open()) {
		cout << "LỖI: Không thể mở file '" << fileTopping << "'!" << endl;
		return;
	}
	Topping moi;
	nhapToppingMoi(moi);
	if (xacNhan()) {
		themTopping << moi.ten << "|" << moi.giaGoc << "|" << moi.ma << endl;
		cout << "\n--> [THÀNH CÔNG] Đã thêm topping vào hệ thống! *_*" << endl;
	}
	else {
		cout << "\n--> [THẤT BẠI] Đã hủy thao tác thêm topping mới! *_*" << endl;
	}
	themTopping.close();
}

void xoaTopping(string fileTopping) {
	veTieuDe("XÓA TOPPING");

	Topping danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileTopping(fileTopping, danhSach, thuTu)) {
		cout << "* MENU TOPPING HIỆN TẠI *" << endl;
		inMenuTopping(danhSach, thuTu);
	}

	cout << "Nhập *MÃ* đồ topping muốn xóa: ";
	string maXoa;
	getline(cin, maXoa);

	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma == maXoa) {
			timThay = true;
			cout << format("\nĐang xóa món: [{}] - {}\n", danhSach[i].ma, danhSach[i].ten);
			if (xacNhan()) {
				xoaDongTopping(danhSach, thuTu, i);
				ghiFileTopping(fileTopping, danhSach, thuTu);
				cout << "--> [THÀNH CÔNG] Đã xóa topping! *_*" << endl;
			}
			else {
				cout << "\n--> [THẤT BẠI] Đã hủy thao tác xóa topping! *_*" << endl;
			}
			return;
		}
	}

	if (!timThay) {
		cout << "\n--> [CẢNH BÁO] Không tìm thấy mã topping: " << maXoa << endl;
	}
}

void suaTopping(string fileTopping) {
	veTieuDe("CHỈNH SỬA THÔNG TIN");

	Topping danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileTopping(fileTopping, danhSach, thuTu)) {
		cout << "* MENU TOPPING HIỆN TẠI *" << endl;
		inMenuTopping(danhSach, thuTu);
	}

	cout << "Nhập *MÃ* topping muốn sửa: ";
	string maSua;
	getline(cin, maSua);

	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma == maSua) {
			timThay = true;
			cout << format("\nĐang sửa món: {}\n", danhSach[i].ten);
			cout << "(Bấm Enter nếu muốn giữ nguyên giá trị cũ)\n\n";
			if (xacNhan()) {
				capNhatTopping(danhSach[i]);
				ghiFileTopping(fileTopping, danhSach, thuTu);
				cout << "\n--> [THÀNH CÔNG] Đã cập nhật thông tin! *_*" << endl;
				break;
			}
			else {
				cout << "\n--> [THẤT BẠI] Đã hủy thao tác cập nhật thông tin! *_*" << endl;
				break;
			}
		}
	}

	if (!timThay) {
		cout << "\n--> [CẢNH BÁO] Không tìm thấy mã topping!" << endl;
	}
}

void timKiemTopping(string fileTopping) {
	veTieuDe("TÌM KIẾM TOPPING");

	Topping danhSach[TOI_DA];
	int thuTu = 0;
	if (!docFileTopping(fileTopping, danhSach, thuTu)) return;

	cout << "Nhập *MÃ* hoặc *TỪ KHÓA*: ";
	string doTimKiem;
	getline(cin, doTimKiem);

	cout << endl;
	veDuong(60);
	cout << format("| {:<10} | {:<30} | {:<10} |", "MÃ", "TÊN TOPPING", "GIÁ") << endl;
	veDuong(60);
	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma.find(doTimKiem) != string::npos || danhSach[i].ten.find(doTimKiem) != string::npos) {
			cout << format("| {:<10} | {:<30} | {:<10} |", danhSach[i].ma, danhSach[i].ten, danhSach[i].giaGoc) << endl;
			timThay = true;
		}
	}
	veDuong(60);
	if (!timThay) {
		cout << "\n--> Không tìm thấy kết quả nào phù hợp với: " << doTimKiem << endl;
	}
}

void quanLiTopping() {
	while (true) {
		system("cls");
		veTieuDe("[III] QUẢN LÍ TOPPING");
		cout << format("{:<60}", "[1] Thêm") << endl;
		cout << format("{:<60}", "[2] Xóa") << endl;
		cout << format("{:<60}", "[3] Chỉnh sửa") << endl;
		cout << format("{:<60}", "[4] Tìm kiếm") << endl;
		cout << format("{:<60}", "[0] Quay lại") << endl;
		veDuong(60);
		cout << " [*] CHỌN: ";

		string boNhoDem;
		getline(cin, boNhoDem);
		int luaChon = 0;
		if (boNhoDem != "") luaChon = stoi(boNhoDem);
		if (luaChon == 0) break;

		system("cls");
		if (luaChon == 1) themTopping("Topping.txt");
		else if (luaChon == 2) xoaTopping("Topping.txt");
		else if (luaChon == 3) suaTopping("Topping.txt");
		else if (luaChon == 4) timKiemTopping("Topping.txt");
		else cout << "\n--> Lựa chọn không hợp lệ!" << endl;

		dungManHinh();
	}
}