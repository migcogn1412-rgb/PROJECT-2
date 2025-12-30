#pragma once
#include "TienIchChung.h"

struct DoUong {
	string ten, loai, ma;
	int giaGoc = 0;
};

DoUong docDoUong(string thongTin) {
	istringstream phanTach(thongTin);
	DoUong d;
	string boNhoDem;
	getline(phanTach, d.ten, '|');
	getline(phanTach, boNhoDem, '|'); d.giaGoc = stoi(boNhoDem);
	getline(phanTach, d.loai, '|');
	getline(phanTach, d.ma);
	return d;
}

bool docFileDoUong(string tenFile, DoUong danhSach[], int& thuTu) {
	ifstream docFile(tenFile, ios::in);
	if (!docFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	string boNhoDem;
	thuTu = 0;
	while (getline(docFile, boNhoDem)) {
		if (boNhoDem.length() > 5) {
			danhSach[thuTu] = docDoUong(boNhoDem);
			if (danhSach[thuTu].ma != "") thuTu++;
		}
	}
	docFile.close();
	return true;
}

bool ghiFileDoUong(string tenFile, DoUong danhSach[], int& thuTu) {
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

void xoaDongDoUong(DoUong danhSach[], int& thuTu, int i) {
	for (int j = i; j < thuTu - 1; j++) {
		danhSach[j] = danhSach[j + 1];
	}
	thuTu--;
}

void capNhatDoUong(DoUong& mon) {
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

void inMenuDoUong(DoUong danhSach[], int& thuTu) {
	veDuong(73);
	cout << format("| {:<10} | {:<30} | {:<10} | {:<10} |", "MÃ", "TÊN ĐỒ UỐNG", "GIÁ", "LOẠI") << endl;
	veDuong(73);
	for (int i = 0; i < thuTu; i++) {
		cout << format("| {:<10} | {:<30} | {:<10} | {:<10} |", danhSach[i].ma, danhSach[i].ten, danhSach[i].giaGoc, danhSach[i].loai) << endl;
	}
	veDuong(73);
	cout << endl;
}

void nhapDoUongMoi(DoUong& moi) {
	cout << format("{:<25}: ", "Nhập mã đồ uống");
	getline(cin, moi.ma);

	cout << format("{:<25}: ", "Nhập tên đồ uống");
	getline(cin, moi.ten);

	cout << format("{:<25}: ", "Nhập giá gốc");
	string boNhoDem;
	getline(cin, boNhoDem); moi.giaGoc = stoi(boNhoDem);

	cout << format("{:<25}: ", "Nhập loại đồ uống");
	getline(cin, moi.loai);
}

void themDoUong(string fileDoUong) {
	veTieuDe("THÊM ĐỒ UỐNG MỚI");

	DoUong danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileDoUong(fileDoUong, danhSach, thuTu)) {
		cout << "* MENU ĐỒ UỐNG HIỆN TẠI *" << endl;
		inMenuDoUong(danhSach, thuTu);
	}

	ofstream themDoUong(fileDoUong, ios::app);
	if (!themDoUong.is_open()) {
		cout << "LỖI: Không thể mở file '" << fileDoUong << "'!" << endl;
		return;
	}
	DoUong moi;
	nhapDoUongMoi(moi);
	if (xacNhan()) {
		themDoUong << moi.ten << "|" << moi.giaGoc << "|" << moi.loai << "|" << moi.ma << endl;
		cout << "\n--> [THÀNH CÔNG] Đã thêm đồ uống vào hệ thống! *_*" << endl;
	}
	else {
		cout << "\n--> [THẤT BẠI] Đã hủy thao tác thêm đồ uống mới! *_*" << endl;
	}
	themDoUong.close();
}

void xoaDoUong(string fileDoUong) {
	veTieuDe("XÓA ĐỒ UỐNG");

	DoUong danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileDoUong(fileDoUong, danhSach, thuTu)) {
		cout << "* MENU ĐỒ UỐNG HIỆN TẠI *" << endl;
		inMenuDoUong(danhSach, thuTu);
	}

	cout << "Nhập *MÃ* đồ uống muốn xóa: ";
	string maXoa;
	getline(cin, maXoa);

	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma == maXoa) {
			timThay = true;
			cout << format("\nĐang xóa món: [{}] - {}\n", danhSach[i].ma, danhSach[i].ten) << endl;
			if (xacNhan()) {
				xoaDongDoUong(danhSach, thuTu, i);
				ghiFileDoUong(fileDoUong, danhSach, thuTu);
				cout << "\n--> [THÀNH CÔNG] Đã xóa đồ uống! *_*" << endl;
			}
			else {
				cout << "\n--> [THẤT BẠI] Đã hủy thao tác xóa đồ uống! *_*" << endl;
			}
			return;
		}
	}

	if (!timThay) {
		cout << "\n--> [CẢNH BÁO] Không tìm thấy mã đồ uống: " << maXoa << endl;
	}
}

void suaDoUong(string fileDoUong) {
	veTieuDe("CHỈNH SỬA THÔNG TIN");

	DoUong danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileDoUong(fileDoUong, danhSach, thuTu)) {
		cout << "* MENU ĐỒ UỐNG HIỆN TẠI *" << endl;
		inMenuDoUong(danhSach, thuTu);
	}

	cout << "Nhập *MÃ* đồ uống muốn sửa: ";
	string maSua;
	getline(cin, maSua);

	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma == maSua) {
			timThay = true;
			cout << format("\nĐang sửa món: {}\n", danhSach[i].ten);
			cout << "(Bấm Enter nếu muốn giữ nguyên giá trị cũ)\n\n";
			if (xacNhan()) {
				capNhatDoUong(danhSach[i]);
				ghiFileDoUong(fileDoUong, danhSach, thuTu);
				cout << "\n--> [THÀNH CÔNG] Đã cập nhật thông tin! *_*" << endl;
			}
			else {
				cout << "\n--> [THẤT BẠI] Đã hủy thao tác cập nhật thông tin! *_*" << endl;
			}
			return;
		}
	}

	if (!timThay) {
		cout << "\n--> [CẢNH BÁO] Không tìm thấy mã đồ uống!" << endl;
	}
}

void timKiemDoUong(string fileDoUong) {
	veTieuDe("TÌM KIẾM ĐỒ UỐNG");

	DoUong danhSach[TOI_DA];
	int thuTu = 0;
	if (!docFileDoUong(fileDoUong, danhSach, thuTu)) return;

	cout << "Nhập *MÃ* hoặc *TỪ KHÓA*: ";
	string doTimKiem;
	getline(cin, doTimKiem);

	cout << endl;
	veDuong(73);
	cout << format("| {:<10} | {:<30} | {:<10} | {:<10} |", "MÃ", "TÊN ĐỒ UỐNG", "GIÁ", "LOẠI") << endl;
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

void quanLiDoUong() {
	while (true) {
		system("cls");
		veTieuDe("[I] QUẢN LÍ ĐỒ UỐNG");
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
		if (luaChon == 1) themDoUong("DoUong.txt");
		else if (luaChon == 2) xoaDoUong("DoUong.txt");
		else if (luaChon == 3) suaDoUong("DoUong.txt");
		else if (luaChon == 4) timKiemDoUong("DoUong.txt");
		else cout << "\n--> Lựa chọn không hợp lệ!" << endl;

		dungManHinh();
	}
}
