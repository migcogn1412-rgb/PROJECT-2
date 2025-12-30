#pragma once
#include "TienIchChung.h"

struct DoAn {
	string ten, loai, ma;
	int giaGoc = 0;
};

DoAn docDoAn(string thongTin) {
	istringstream phanTach(thongTin);
	DoAn d;
	string boNhoDem;
	getline(phanTach, d.ten, '|');
	getline(phanTach, boNhoDem, '|'); d.giaGoc = stoi(boNhoDem);
	getline(phanTach, d.loai, '|');
	getline(phanTach, d.ma);
	return d;
}

bool docFileDoAn(string tenFile, DoAn danhSach[], int& thuTu) {
	ifstream docFile(tenFile, ios::in);
	if (!docFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	string boNhoDem;
	thuTu = 0;
	while (getline(docFile, boNhoDem)) {
		if (boNhoDem.length() > 5) {
			danhSach[thuTu] = docDoAn(boNhoDem);
			if (danhSach[thuTu].ma != "") thuTu++;
		}
	}
	docFile.close();
	return true;
}

bool ghiFileDoAn(string tenFile, DoAn danhSach[], int& thuTu) {
	ofstream ghiFile(tenFile, ios::out);
	if (!ghiFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	for (int i = 0; i < thuTu; i++) {
		ghiFile << danhSach[i].ten << "|" << danhSach[i].giaGoc << "|"
			<< danhSach[i].loai << "|" << danhSach[i].ma << endl;
	}
	ghiFile.close();
	return true;
}

void xoaDongDoAn(DoAn danhSach[], int& thuTu, int i) {
	for (int j = i; j < thuTu - 1; j++) {
		danhSach[j] = danhSach[j + 1];
	}
	thuTu--;
}

void capNhatDoAn(DoAn& mon) {
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

	cout << format("Loại mới (cũ: {}): ", mon.loai);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.loai = boNhoDem;
}

void inMenuDoAn(DoAn danhSach[], int& thuTu) {
	veDuong(73);
	cout << format("| {:<10} | {:<30} | {:<10} | {:<10} |", "MÃ", "TÊN ĐỒ ĂN", "GIÁ", "LOẠI") << endl;
	veDuong(73);
	for (int i = 0; i < thuTu; i++) {
		cout << format("| {:<10} | {:<30} | {:<10} | {:<10} |", danhSach[i].ma, danhSach[i].ten, danhSach[i].giaGoc, danhSach[i].loai) << endl;
	}
	veDuong(73);
	cout << endl;
}

void nhapDoAnMoi(DoAn& moi) {
	cout << format("{:<25}: ", "Nhập mã đồ ăn");
	getline(cin, moi.ma);

	cout << format("{:<25}: ", "Nhập tên món");
	getline(cin, moi.ten);

	cout << format("{:<25}: ", "Nhập giá gốc");
	string boNhoDem;
	getline(cin, boNhoDem); moi.giaGoc = stoi(boNhoDem);

	cout << format("{:<25}: ", "Nhập loại đồ ăn");
	getline(cin, moi.loai);
}

void themDoAn(string fileDoAn) {
	veTieuDe("THÊM ĐỒ ĂN MỚI");

	DoAn danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileDoAn(fileDoAn, danhSach, thuTu)) {
		cout << "* MENU ĐỒ ĂN HIỆN TẠI *" << endl;
		inMenuDoAn(danhSach, thuTu);
	}

	ofstream themDoAn(fileDoAn, ios::app);
	if (!themDoAn.is_open()) {
		cout << "LỖI: Không thể mở file '" << fileDoAn << "'!" << endl;
		return;
	}
	DoAn moi;
	nhapDoAnMoi(moi);
	if (xacNhan()) {
		themDoAn << moi.ten << "|" << moi.giaGoc << "|" << moi.loai << "|" << moi.ma << endl;
		cout << "\n--> [THÀNH CÔNG] Đã thêm đồ ăn vào hệ thống! *_*" << endl;
	}
	else {
		cout << "\n--> [THẤT BẠI] Đã hủy thao tác thêm đồ ăn mới! *_*" << endl;
	}
	themDoAn.close();
}

void xoaDoAn(string fileDoAn) {
	veTieuDe("XÓA ĐỒ ĂN");

	DoAn danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileDoAn(fileDoAn, danhSach, thuTu)) {
		cout << "* MENU ĐỒ ĂN HIỆN TẠI *" << endl;
		inMenuDoAn(danhSach, thuTu);
	}

	cout << "Nhập *MÃ* đồ ăn muốn xóa: ";
	string maXoa;
	getline(cin, maXoa);

	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma == maXoa) {
			timThay = true;
			cout << format("\nĐang xóa món: [{}] - {}\n", danhSach[i].ma, danhSach[i].ten);
			if (xacNhan()) {
				xoaDongDoAn(danhSach, thuTu, i);
				ghiFileDoAn(fileDoAn, danhSach, thuTu);
				cout << "--> [THÀNH CÔNG] Đã xóa đồ ăn! *_*" << endl;
			}
			else {
				cout << "\n--> [THẤT BẠI] Đã hủy thao tác xóa đồ ăn! *_*" << endl;
			}
			return;
		}
	}

	if (!timThay) {
		cout << "\n--> [CẢNH BÁO] Không tìm thấy mã đồ ăn: " << maXoa << endl;
	}
}

void suaDoAn(string fileDoAn) {
	veTieuDe("CHỈNH SỬA THÔNG TIN");

	DoAn danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileDoAn(fileDoAn, danhSach, thuTu)) {
		cout << "* MENU ĐỒ ĂN HIỆN TẠI *" << endl;
		inMenuDoAn(danhSach, thuTu);
	}

	cout << "Nhập *MÃ* đồ ăn muốn sửa: ";
	string maSua;
	getline(cin, maSua);

	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma == maSua) {
			timThay = true;
			cout << format("\nĐang sửa món: {}\n", danhSach[i].ten);
			cout << "(Bấm Enter nếu muốn giữ nguyên giá trị cũ)\n\n";
			if (xacNhan()) {
				capNhatDoAn(danhSach[i]);
				ghiFileDoAn(fileDoAn, danhSach, thuTu);
				cout << "\n--> [THÀNH CÔNG] Đã cập nhật thông tin! *_*" << endl;
			}
			else {
				cout << "\n--> [THẤT BẠI] Đã hủy thao tác cập nhật thông tin! *_*" << endl;
			}
			return;
		}
	}

	if (!timThay) {
		cout << "\n--> [CẢNH BÁO] Không tìm thấy mã đồ ăn!" << endl;
	}
}

void timKiemDoAn(string fileDoAn) {
	veTieuDe("TÌM KIẾM ĐỒ ĂN");

	DoAn danhSach[TOI_DA];
	int thuTu = 0;
	if (!docFileDoAn(fileDoAn, danhSach, thuTu)) return;

	cout << "Nhập *MÃ* hoặc *TỪ KHÓA*: ";
	string doTimKiem;
	getline(cin, doTimKiem);

	cout << endl;
	veDuong(73);
	cout << format("| {:<10} | {:<30} | {:<10} | {:<10} |", "MÃ", "TÊN ĐỒ ĂN", "GIÁ", "LOẠI") << endl;
	veDuong(73);
	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma.find(doTimKiem) != string::npos || danhSach[i].ten.find(doTimKiem) != string::npos) {
			cout << format("| {:<10} | {:<30} | {:<10} | {:<10} |", danhSach[i].ma, danhSach[i].ten, danhSach[i].giaGoc, danhSach[i].loai) << endl;
			timThay = true;
		}
	}
	veDuong(73);
	if (!timThay) {
		cout << "\n--> Không tìm thấy kết quả nào phù hợp với: " << doTimKiem << endl;
	}
}

void quanLiDoAn() {
	while (true) {
		system("cls");
		veTieuDe("[II] QUẢN LÍ ĐỒ ĂN");
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
		if (luaChon == 1) themDoAn("DoAn.txt");
		else if (luaChon == 2) xoaDoAn("DoAn.txt");
		else if (luaChon == 3) suaDoAn("DoAn.txt");
		else if (luaChon == 4) timKiemDoAn("DoAn.txt");
		else cout << "\n--> Lựa chọn không hợp lệ!" << endl;

		dungManHinh();
	}
}