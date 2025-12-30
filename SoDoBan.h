#pragma once
#include "TienIchChung.h"

struct Ban {
	int soBan = 0;
	int trangThai = 0;
};

Ban docBan(string thongTin) {
	istringstream phanTach(thongTin);
	Ban b;
	string boNhoDem;
	getline(phanTach, boNhoDem, '|'); b.soBan = stoi(boNhoDem);
	getline(phanTach, boNhoDem); b.trangThai = stoi(boNhoDem);
	return b;
}

bool docFileBan(string tenFile, Ban dsBan[], int& soLuong) {
	ifstream docFile(tenFile, ios::in);
	if (!docFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	string boNhoDem;
	while (getline(docFile, boNhoDem)) {
		if (boNhoDem.length() < 1) continue;
		dsBan[soLuong] = docBan(boNhoDem);
		if (dsBan[soLuong].soBan != string::npos) soLuong++;
	}
	docFile.close();
	return true;
}

bool ghiFileBan(string tenFile, Ban dsBan[], int& soLuong) {
	ofstream ghiFile(tenFile, ios::out);
	if (!ghiFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	for (int i = 0; i < soLuong; i++) {
		ghiFile << dsBan[i].soBan << "|" << dsBan[i].trangThai << endl;
	}
	ghiFile.close();
	return true;
}

void inSoDoBan(Ban dsBan[], int soLuong) {
	veTieuDe("SƠ ĐỒ BÀN");
	veDuong(60);
	for (int i = 0; i < soLuong; i++) {
		string trangThai = (dsBan[i].trangThai == 0) ? "Trống" : "Có khách";
		cout << format("[{:02} - {:<8}]", dsBan[i].soBan, trangThai);
		if ((i + 1) % 5 == 0) cout << endl;
	}
	veDuong(60);
}