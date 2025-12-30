#pragma once
#include "TienIchChung.h"

struct CauHinh {
	string size;
	int giaCongThem = 0;
};

CauHinh docCauHinh(string thongTin) {
	istringstream phanTach(thongTin);
	CauHinh c;
	string boNhoDem;
	getline(phanTach, c.size, '|');
	getline(phanTach, boNhoDem); c.giaCongThem = stoi(boNhoDem);
	return c;
}

bool docFileCauHinh(string tenFile, CauHinh danhSach[], int& thuTu) {
	ifstream docFile(tenFile, ios::in);
	if (!docFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	string boNhoDem;
	thuTu = 0;
	while (getline(docFile, boNhoDem)) {
		if (boNhoDem.length() > 5) {
			danhSach[thuTu] = docCauHinh(boNhoDem);
			if (danhSach[thuTu].giaCongThem != 0) thuTu++;
		}
	}
	docFile.close();
	return true;
}

bool ghiFileCauHinh(string tenFile, CauHinh danhSach[], int& thuTu) {
	ofstream ghiFile(tenFile, ios::out);
	if (!ghiFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	for (int i = 0; i < thuTu; i++) {
		ghiFile << danhSach[i].size << "|"
			<< danhSach[i].giaCongThem << endl;
	}
	ghiFile.close();
	return true;
}

void xoaDongCauHinh(CauHinh danhSach[], int& thuTu, int i) {
	for (int j = i; j < thuTu - 1; j++) {
		danhSach[j] = danhSach[j + 1];
	}
	thuTu--;
}

void capNhatCauHinh(CauHinh& mon) {
	string boNhoDem;

	cout << format("Tên mới (cũ: {}): ", mon.size);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.size = boNhoDem;

	cout << format("Giá mới (cũ: {}): ", mon.giaCongThem);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.giaCongThem = stoi(boNhoDem);
}

void inCauHinh(CauHinh danhSach[], int& thuTu) {
	veDuong(37);
	cout << format("| {:<15} | {:<15} |", "SIZE", "GIÁ CỘNG THÊM") << endl;
	veDuong(37);
	for (int i = 0; i < thuTu; i++) {
		cout << format("| {:<15} | {:<15} |", danhSach[i].size, danhSach[i].giaCongThem) << endl;
	}
	veDuong(37);
	cout << endl;
}

void nhapCauHinhMoi(CauHinh& moi) {
	cout << format("{:<25}: ", "Nhập tên size");
	getline(cin, moi.size);

	cout << format("{:<25}: ", "Nhập giá cộng thêm");
	string boNhoDem;
	getline(cin, boNhoDem); moi.giaCongThem = stoi(boNhoDem);
}

void themSize(string fileCauHinh) {
	veTieuDe("THÊM SIZE MỚI");

	CauHinh danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileCauHinh(fileCauHinh, danhSach, thuTu)) {
		cout << "* CẤU HÌNH HIỆN TẠI *" << endl;
		inCauHinh(danhSach, thuTu);
	}

	ofstream themSize(fileCauHinh, ios::app);
	if (!themSize.is_open()) {
		cout << "LỖI: Không thể mở file '" << fileCauHinh << "'!" << endl;
		return;
	}
	CauHinh moi;
	nhapCauHinhMoi(moi);
	if (xacNhan()) {
		themSize << moi.size << "|" << moi.giaCongThem << endl;
		cout << "\n--> [THÀNH CÔNG] Đã thêm size vào hệ thống! *_*" << endl;
	}
	else {
		cout << "\n--> [THẤT BẠI] Đã hủy thao tác thêm size mới! *_*" << endl;
	}
	themSize.close();
}

void xoaSize(string fileCauHinh) {
	veTieuDe("XÓA SIZE");

	CauHinh danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileCauHinh(fileCauHinh, danhSach, thuTu)) {
		cout << "* CẤU HÌNH HIỆN TẠI *" << endl;
		inCauHinh(danhSach, thuTu);
	}

	cout << "Nhập size muốn xóa: ";
	string sizeXoa;
	getline(cin, sizeXoa);

	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].size == sizeXoa) {
			cout << format("\nĐang xóa size: [{}]\n", danhSach[i].size);
			timThay = true;
			if (xacNhan()) {
				xoaDongCauHinh(danhSach, thuTu, i);
				ghiFileCauHinh(fileCauHinh, danhSach, thuTu);
				cout << "\n--> [THÀNH CÔNG] Đã xóa size! *_*" << endl;
			}
			else {
				cout << "\n--> [THẤT BẠI] Đã hủy thao tác xóa size! *_*" << endl;
			}
			return;
		}
	}

	if (!timThay) {
		cout << "\n--> [CẢNH BÁO] Không tìm thấy size: " << sizeXoa << endl;
	}
}

void suaCauHinh(string fileCauHinh) {
	veTieuDe("CHỈNH SỬA THÔNG TIN");

	CauHinh danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileCauHinh(fileCauHinh, danhSach, thuTu)) {
		cout << "* CẤU HÌNH HIỆN TẠI *" << endl;
		inCauHinh(danhSach, thuTu);
	}

	cout << "Nhập size muốn sửa: ";
	string sizeSua;
	getline(cin, sizeSua);

	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].size == sizeSua) {
			timThay = true;
			cout << format("\nĐang sửa size: {}\n", danhSach[i].size);
			cout << "(Bấm Enter nếu muốn giữ nguyên giá trị cũ)\n\n";
			if (xacNhan()) {
				capNhatCauHinh(danhSach[i]);
				ghiFileCauHinh(fileCauHinh, danhSach, thuTu);
				cout << "\n--> [THÀNH CÔNG] Đã cập nhật thông tin! *_*" << endl;
			}
			else {
				cout << "\n--> [THẤT BẠI] Đã hủy thao tác cập nhật thông tin! *_*" << endl;
			}
			return;
		}
	}

	if (!timThay) {
		cout << "\n--> [CẢNH BÁO] Không tìm thấy size!" << endl;
	}
}

void cauHinhOrder() {
	while (true) {
		system("cls");
		veTieuDe("[IV] CẤU HÌNH ORDER");
		cout << format("{:<60}", "[1] Thêm") << endl;
		cout << format("{:<60}", "[2] Xóa") << endl;
		cout << format("{:<60}", "[3] Chỉnh sửa") << endl;
		cout << format("{:<60}", "[0] Quay lại") << endl;
		veDuong(60);
		cout << " [*] CHỌN: ";

		string boNhoDem;
		getline(cin, boNhoDem);
		int luaChon = 0;
		if (boNhoDem != "") luaChon = stoi(boNhoDem);
		if (luaChon == 0) break;

		system("cls");
		if (luaChon == 1) themSize("CauHinhOrder.txt");
		else if (luaChon == 2) xoaSize("CauHinhOrder.txt");
		else if (luaChon == 3) suaCauHinh("CauHinhOrder.txt");
		else cout << "\n--> Lựa chọn không hợp lệ!" << endl;

		dungManHinh();
	}
}