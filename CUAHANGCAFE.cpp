#include <iostream>
#include <string>
#include <format>
#include <fstream>
#include <sstream>
#include <ctime>
#include "QuanLiDoUong.h"
#include "QuanLiDoAn.h"
#include "QuanLiTopping.h"
#include "CauHinhOrder.h"

using std::cout, std::cin, std::endl, std::to_string;
using std::string, std::ofstream, std::ifstream, std::ios;
using std::format, std::istringstream, std::getline, std::stoi;

const int TOI_DA = 100;

// =========================================================
// KHAI BÁO STRUCT
// =========================================================
struct DoUong;
struct DoAn;
struct Topping;
struct CauHinh;

struct Ban {
	int soBan = 0;
	int trangThai = 0;
};

struct ChiTietMon {
	string maMon, tenMon;
	int giaGoc = 0;
	string size = "S"; int giaSize = 0;
	string topping = "", maTopping = ""; int giaTopping = 0;
	int duong = 100, da = 100;
	int soLuong = 0;
	int thanhTien = 0;
};

struct HoaDon {
	string maHD, ngay;
	int soBan = 0;
	ChiTietMon dsMon[TOI_DA];
	int soMon = 0;
	int tongTien = 0;
	string ghiChu = "";
};

struct NguyenLieu {
	string ma, ten, donVi;
	int soLuong = 0;
	int giaNhap = 0;
};

struct PhieuNhap {
	string maPhieu, ngay, nguoiNhap;
	NguyenLieu dsNL[TOI_DA];
	int soNL = 0;
	int tongTien = 0;
};

// =========================================================
// HÀM TIỆN ÍCH CHUNG
// =========================================================
void veDuong(int doDai);
void veTieuDe(string tieuDe);
void dungManHinh();
bool xacNhan();
string tachData(string str, int index);
string layNgayHienTai();

// =========================================================
// QUẢN LÍ CƠ SỞ DỮ LIỆU
// =========================================================

// =========================================================
// I. QUẢN LÝ ĐỒ UỐNG
// =========================================================
DoUong docDoUong(string thongTin);
bool docFileDoUong(string tenFile, DoUong danhSach[], int& thuTu);
bool ghiFileDoUong(string tenFile, DoUong danhSach[], int& thuTu);
void xoaDongDoUong(DoUong danhSach[], int& thuTu, int i);
void capNhatDoUong(DoUong& mon);
void inMenuDoUong(DoUong danhSach[], int& thuTu);
void nhapDoUongMoi(DoUong& moi);
void themDoUong(string fileDoUong);
void xoaDoUong(string fileDoUong);
void suaDoUong(string fileDoUong);
void timKiemDoUong(string fileDoUong);
void quanLiDoUong();

// =========================================================
// II. QUẢN LÝ ĐỒ ĂN
// =========================================================
DoAn docDoAn(string thongTin);
bool docFileDoAn(string tenFile, DoAn danhSach[], int& thuTu);
bool ghiFileDoAn(string tenFile, DoAn danhSach[], int& thuTu);
void xoaDongDoAn(DoAn danhSach[], int& thuTu, int i);
void capNhatDoAn(DoAn& mon);
void inMenuDoAn(DoAn danhSach[], int& thuTu);
void nhapDoAnMoi(DoAn& moi);
void themDoAn(string fileDoAn);
void xoaDoAn(string fileDoAn);
void suaDoAn(string fileDoAn);
void timKiemDoAn(string fileDoAn);
void quanLiDoAn();

// =========================================================
// III. QUẢN LÝ TOPPING
// =========================================================
Topping docTopping(string thongTin);
bool docFileTopping(string tenFile, Topping danhSach[], int& thuTu);
bool ghiFileTopping(string tenFile, Topping danhSach[], int& thuTu);
void xoaDongTopping(Topping danhSach[], int& thuTu, int i);
void capNhatTopping(Topping& mon);
void inMenuTopping(Topping danhSach[], int& thuTu);
void nhapToppingMoi(Topping& moi);
void themTopping(string fileTopping);
void xoaTopping(string fileTopping);
void suaTopping(string fileTopping);
void timKiemTopping(string fileTopping);
void quanLiTopping();

// =========================================================
// IV. CẤU HÌNH ORDER
// =========================================================
CauHinh docCauHinh(string thongTin);
bool docFileCauHinh(string tenFile, CauHinh danhSach[], int& thuTu);
bool ghiFileCauHinh(string tenFile, CauHinh danhSach[], int& thuTu);
void xoaDongCauHinh(CauHinh danhSach[], int& thuTu, int i);
void capNhatCauHinh(CauHinh& mon);
void inCauHinh(CauHinh danhSach[], int& thuTu);
void nhapCauHinhMoi(CauHinh& moi);
void themSize(string fileCauHinh);
void xoaSize(string fileCauHinh);
void suaCauHinh(string fileCauHinh);
void cauHinhOrder();

// =========================================================
// V. MENU CHI TIẾT
// =========================================================
void menuChiTiet();

// =========================================================
// QUẢN LÍ DỮ LIỆU PHÁT SINH
// =========================================================

// =========================================================
// I. QUẢN LÍ BÁN HÀNG VÀ ORDER
// =========================================================
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





ChiTietMon docChiTietMon(string thongTin) {
	istringstream phanTach(thongTin);
	ChiTietMon mon;
	string boNhoDem;
	getline(phanTach, mon.tenMon, '|');
	getline(phanTach, mon.size, '|');
	getline(phanTach, boNhoDem, '|'); mon.duong = stoi(boNhoDem);
	getline(phanTach, boNhoDem, '|'); mon.da = stoi(boNhoDem);
	getline(phanTach, mon.topping, '|');
	getline(phanTach, boNhoDem, '|'); mon.soLuong = stoi(boNhoDem);
	getline(phanTach, boNhoDem); mon.thanhTien = stoi(boNhoDem);
	return mon;
}

HoaDon docHoaDon(string thongTin) {
	istringstream phanTach(thongTin);
	HoaDon hd;
	string boNhoDem;
	getline(phanTach, hd.maHD, '|');
	getline(phanTach, hd.ngay, '|');
	getline(phanTach, boNhoDem, '|'); hd.soBan = stoi(boNhoDem);
	getline(phanTach, boNhoDem, '|'); hd.soMon = stoi(boNhoDem);
	getline(phanTach, boNhoDem, '|'); hd.tongTien = stoi(boNhoDem);
	getline(phanTach, hd.ghiChu);
	return hd;
}

bool docFileHoaDon(string tenFile, HoaDon dsHD[], int& soLuong) {
	ifstream docFile(tenFile, ios::in);
	if (!docFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	string boNhoDem;
	while (getline(docFile, boNhoDem)) {
		if (boNhoDem.find("HD_START") != string::npos) {
			getline(docFile, boNhoDem);
			dsHD[soLuong] = docHoaDon(boNhoDem);

			int soMon = 0;
			while (getline(docFile, boNhoDem) && boNhoDem.find("HD_END") == string::npos) {
				if (boNhoDem.length() > 5) {
					dsHD[soLuong].dsMon[soMon] = docChiTietMon(boNhoDem);
					soMon++;
				}
			}
			soLuong++;
		}
	}
	docFile.close();
	return true;
}

bool ghiFileHoaDon(string tenFile, HoaDon dsHD[], int soLuong) {
	ofstream ghiFile(tenFile, ios::out);
	if (!ghiFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}

	for (int i = 0; i < soLuong; i++) {
		ghiFile << "HD_START" << endl;
		ghiFile << dsHD[i].maHD << "|" << dsHD[i].ngay << "|"
			<< dsHD[i].soBan << "|" << dsHD[i].soMon << "|"
			<< dsHD[i].tongTien << "|" << dsHD[i].ghiChu << endl;

		for (int j = 0; j < dsHD[i].soMon; j++) {
			ghiFile << dsHD[i].dsMon[j].tenMon << "|"
				<< dsHD[i].dsMon[j].size << "|"
				<< dsHD[i].dsMon[j].duong << "|"
				<< dsHD[i].dsMon[j].da << "|"
				<< dsHD[i].dsMon[j].topping << "|"
				<< dsHD[i].dsMon[j].soLuong << "|"
				<< dsHD[i].dsMon[j].thanhTien << endl;
		}
		ghiFile << "HD_END" << endl;
	}

	ghiFile.close();
	return true;
}

void luuDoanhThu(HoaDon hd) {
	ofstream f("HoaDonDaThanhToan.txt", ios::app);
	if (f.is_open()) {
		f << "HD_START" << endl;
		f << format("{}|{}|{}|{}", hd.maHD, hd.ngay, hd.soBan, hd.tongTien) << endl;
		for (int i = 0; i < hd.soMon; i++) {
			ChiTietMon m = hd.dsMon[i];
			f << format("MON|{}|{}|{}|{}|{}", m.maMon, m.tenMon, m.giaGoc, m.soLuong, m.giaGoc * m.soLuong) << endl;
			if (m.size != "S")
				f << format("SZ|SZ_{}|Size {}|{}|{}|{}", m.size, m.size, m.giaSize, m.soLuong, m.giaSize * m.soLuong) << endl;
			if (!m.topping.empty())
				f << format("TP|{}|{}|{}|{}|{}", m.maTopping, m.topping, m.giaTopping, m.soLuong, m.giaTopping * m.soLuong) << endl;
		}
		f << "HD_END" << endl;
		f.close();
	}
}

// Hàm 2: Xuất Bill khách
void xuatBillChoKhach(HoaDon hd) {
	string tenFile = "PhieuInHoaDon.txt";
	ofstream f(tenFile);
	if (f.is_open()) {
		f << "==================================================" << endl;
		f << "              CUA HANG CA PHE ABC                 " << endl;
		f << "==================================================" << endl;
		f << format(" SO HD: {:<18} NGAY: {:<10}", hd.maHD, hd.ngay) << endl;
		f << format(" BAN:   {:<18}", (hd.soBan == 0 ? "Mang Ve" : to_string(hd.soBan))) << endl;
		f << "--------------------------------------------------" << endl;
		f << format(" {:<28} {:^4} {:>14} ", "TEN", "SL", "THANH TIEN") << endl;
		f << "--------------------------------------------------" << endl;
		for (int i = 0; i < hd.soMon; i++) {
			ChiTietMon m = hd.dsMon[i];
			f << format(" {:<28} {:^4} {:>14} ", m.tenMon, m.soLuong, m.giaGoc * m.soLuong) << endl;
			if (m.size != "S") f << format(" {:<28} {:^4} {:>14} ", " + Size " + m.size, "", m.giaSize * m.soLuong) << endl;
			if (!m.topping.empty()) f << format(" {:<28} {:^4} {:>14} ", " + " + m.topping, "", m.giaTopping * m.soLuong) << endl;
			f << " - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
		}
		f << "--------------------------------------------------" << endl;
		f << format(" TONG CONG: {:>36} VND ", hd.tongTien) << endl;
		f << "==================================================" << endl;
		f.close();
		// string lenh = "notepad.exe " + tenFile; system(lenh.c_str());
	}
}

// Hàm 3: In lại bill cũ
void inLaiHoaDonCu() {
	veTieuDe("IN LẠI HÓA ĐƠN CŨ");
	cout << "--> Nhập MÃ HÓA ĐƠN (VD: HD170501): "; string maTim; getline(cin, maTim);
	ifstream f("HoaDonDaThanhToan.txt");
	if (!f.is_open()) { cout << "Lỗi mở file!\n"; return; }

	string line; bool timThay = false; HoaDon hd; int idx = -1;
	while (getline(f, line)) {
		if (line.find(maTim) != string::npos && line.find("HD_START") == string::npos) {
			timThay = true;
			hd.maHD = tachData(line, 0); hd.ngay = tachData(line, 1);
			string sb = tachData(line, 2); hd.soBan = (sb == "Mang Ve") ? 0 : stoi(sb);
			hd.tongTien = stoi(tachData(line, 3)); hd.soMon = 0; idx = -1;

			while (getline(f, line)) {
				if (line == "HD_END") break;
				if (line.find("MON|") == 0) {
					idx++; hd.soMon++;
					hd.dsMon[idx].maMon = tachData(line, 1);
					hd.dsMon[idx].tenMon = tachData(line, 2);
					hd.dsMon[idx].giaGoc = stoi(tachData(line, 3));
					hd.dsMon[idx].soLuong = stoi(tachData(line, 4));
					hd.dsMon[idx].size = "S"; hd.dsMon[idx].topping = ""; // Reset
				}
				else if (line.find("SZ|") == 0) {
					string sFull = tachData(line, 2);
					hd.dsMon[idx].size = sFull.substr(5);
					hd.dsMon[idx].giaSize = stoi(tachData(line, 3));
				}
				else if (line.find("TP|") == 0) {
					hd.dsMon[idx].topping = tachData(line, 2);
					hd.dsMon[idx].giaTopping = stoi(tachData(line, 3));
				}
			}
			break;
		}
	}
	f.close();
	if (timThay) xuatBillChoKhach(hd); else cout << "Không tìm thấy!\n";
}

// Hàm 4: Tạo Order (Full tính năng)
void taoOrderMoi() {
	Ban dsBan[TOI_DA]; int slBan = 0; docFileBan("Ban.txt", dsBan, slBan);
	DoUong dsDU[TOI_DA]; int slDU = 0; docFileDoUong("DoUong.txt", dsDU, slDU);
	DoAn dsDA[TOI_DA]; int slDA = 0; docFileDoAn("DoAn.txt", dsDA, slDA);
	Topping dsTop[TOI_DA]; int slTop = 0; docFileTopping("Topping.txt", dsTop, slTop);
	CauHinh dsSize[TOI_DA]; int slSize = 0; docFileCauHinh("CauHinhOrder.txt", dsSize, slSize);

	MonMenu menu[200]; int slMenu = 0;
	for (int i = 0; i < slDU; i++) menu[slMenu++] = { dsDU[i].ma, dsDU[i].ten, "Do Uong", dsDU[i].giaGoc };
	for (int i = 0; i < slDA; i++) menu[slMenu++] = { dsDA[i].ma, dsDA[i].ten, "Do An", dsDA[i].giaGoc };

	veTieuDe("ORDER TẠI QUẦY"); inSoDoBan(dsBan, slBan);
	HoaDon hd; cout << "--> Số bàn (0=Mang ve): "; string s; getline(cin, s); hd.soBan = (s == "") ? 0 : stoi(s);
	if (hd.soBan != 0) {
		for (int i = 0; i < slBan; i++) if (dsBan[i].soBan == hd.soBan && dsBan[i].trangThai == 1) {
			cout << "[!] Bàn bận. Tiếp tục? (Y/N) "; if (!xacNhan()) return;
		}
	}
	hd.maHD = "HD" + to_string(time(0)); hd.ngay = layNgayHienTai(); hd.soMon = 0; hd.tongTien = 0;

	while (true) {
		system("cls"); veTieuDe(format("BÀN {} - TỔNG: {}", hd.soBan, hd.tongTien));
		cout << format("| {:<10} | {:<30} | {:<10} |", "MA", "TEN", "GIA") << endl; veDuong(58);
		for (int i = 0; i < slMenu; i++) cout << format("| {:<10} | {:<30} | {:<10} |", menu[i].ma, menu[i].ten, menu[i].gia) << endl;
		veDuong(58); cout << "\n--> Nhập MÃ (0 Thanh Toán): "; string ma; getline(cin, ma); if (ma == "0") break;

		bool found = false; MonMenu m;
		for (int i = 0; i < slMenu; i++) if (menu[i].ma == ma) { m = menu[i]; found = true; break; }

		if (found) {
			ChiTietMon ct; ct.maMon = m.ma; ct.tenMon = m.ten; ct.giaGoc = m.gia;
			cout << "--> SL: "; string sl; getline(cin, sl); ct.soLuong = (sl == "") ? 1 : stoi(sl);
			ct.size = "S"; ct.giaSize = 0; ct.topping = ""; ct.giaTopping = 0;

			if (m.loai == "Do Uong") {
				cout << "\n-- SIZE: "; for (int k = 0; k < slSize; k++) cout << format("{} (+{}) | ", dsSize[k].size, dsSize[k].giaCongThem);
				cout << "\n--> Nhập tên Size: "; string sz; getline(cin, sz);
				for (auto& c : sz) c = toupper(c);
				for (int k = 0; k < slSize; k++) if (dsSize[k].size == sz) { ct.size = sz; ct.giaSize = dsSize[k].giaCongThem; break; }

				cout << "\n-- TOPPING: "; for (int k = 0; k < slTop; k++) cout << format("{} (+{}) | ", dsTop[k].ma, dsTop[k].giaGoc);
				cout << "\n--> Nhập MÃ Top: "; string mt; getline(cin, mt);
				for (int k = 0; k < slTop; k++) if (dsTop[k].ma == mt) { ct.topping = dsTop[k].ten; ct.maTopping = dsTop[k].ma; ct.giaTopping = dsTop[k].giaGoc; break; }
			}
			ct.thanhTien = (ct.giaGoc + ct.giaSize + ct.giaTopping) * ct.soLuong;
			hd.dsMon[hd.soMon++] = ct; hd.tongTien += ct.thanhTien;
		}
	}

	if (hd.soMon > 0) {
		cout << "\n--> TỔNG: " << hd.tongTien << ". Khách đưa: "; string sk; getline(cin, sk);
		if (stoi(sk) >= hd.tongTien && xacNhan()) {
			luuDoanhThu(hd); xuatBillChoKhach(hd);
			if (hd.soBan != 0) {
				for (int i = 0; i < slBan; i++) if (dsBan[i].soBan == hd.soBan) dsBan[i].trangThai = 1;
				ghiFileBan("Ban.txt", dsBan, slBan);
			}
			cout << "--> DONE!\n";
		}
	}
}

void donBan() {
	Ban ds[TOI_DA]; int n; docFileBan("Ban.txt", ds, n); inSoDoBan(ds, n);
	cout << "--> Nhập bàn dọn (0 thoát): "; string s; getline(cin, s); int b = stoi(s);
	if (b != 0) {
		for (int i = 0; i < n; i++) if (ds[i].soBan == b) ds[i].trangThai = 0;
		ghiFileBan("Ban.txt", ds, n); cout << "--> Đã dọn!\n";
	}
}

struct MonMenu { string ma, ten, loai; int gia = 0; };

void quanLiBanHangVaOrder() {
	while (true) {
		system("cls"); veTieuDe("QUẢN LÝ BÁN HÀNG");
		cout << "[1] Order & Pay\n[2] Dọn bàn\n[3] Sơ đồ bàn\n[4] In lại Bill cũ\n[0] Về\nChọn: ";
		string s; getline(cin, s); int c = (s == "") ? 0 : stoi(s);
		if (c == 0) break;
		if (c == 1) taoOrderMoi(); else if (c == 2) donBan(); else if (c == 4) inLaiHoaDonCu();
		else if (c == 3) { Ban ds[100]; int n; docFileBan("Ban.txt", ds, n); inSoDoBan(ds, n); }
		dungManHinh();
	}
}

// =========================================================
// CÁC HÀM HỖ TRỢ ORDER 
// =========================================================

// Struct tạm dùng để gộp Menu Đồ Ăn và Đồ Uống chung vào 1 danh sách
struct MonMenu {
	string ma, ten, loai;
	int gia = 0;
};

// Hàm ghi nối tiếp (Append) hóa đơn mới vào file
void ghiOrderVaoFile(HoaDon hd) {
	ofstream ghiFile("HoaDonChuaThanhToan.txt", ios::app); // ios::app để không xóa dữ liệu cũ
	if (ghiFile.is_open()) {
		ghiFile << "HD_START" << endl;
		ghiFile << format("{}|{}|{}|{}|{}|{}",
			hd.maHD, hd.ngay, hd.soBan, hd.soMon, hd.tongTien, hd.ghiChu) << endl;

		for (int i = 0; i < hd.soMon; i++) {
			ghiFile << format("{}|{}|{}|{}|{}|{}|{}",
				hd.dsMon[i].tenMon, hd.dsMon[i].size, hd.dsMon[i].duong,
				hd.dsMon[i].da, hd.dsMon[i].topping, hd.dsMon[i].soLuong, hd.dsMon[i].thanhTien) << endl;
		}
		ghiFile << "HD_END" << endl;
		ghiFile.close();
	}
}



void quanLiBanHangVaOrder() {
	while (true) {
		system("cls");
		veTieuDe("[I] QUẢN LÝ BÁN HÀNG VÀ ORDER");
		cout << format("{:<60}", "[1] Tạo order mới") << endl;
		cout << format("{:<60}", "[2] Cập nhật order (Đang bảo trì)") << endl;
		cout << format("{:<60}", "[3] Xử lý hóa đơn (Đang bảo trì)") << endl;
		cout << format("{:<60}", "[4] Xem sơ đồ bàn") << endl;
		cout << format("{:<60}", "[5] Danh sách hóa đơn (Đang bảo trì)") << endl;
		cout << format("{:<60}", "[0] Quay lại") << endl;
		veDuong(60);
		cout << " [*] CHỌN: ";

		string boNhoDem;
		getline(cin, boNhoDem);
		int luaChon = 0;
		if (boNhoDem != "") luaChon = stoi(boNhoDem);
		if (luaChon == 0) break;

		system("cls");
		if (luaChon == 1) taoOrderMoi();
		else if (luaChon == 2) capNhatOrder();    
		else if (luaChon == 3) xuLyHoaDon();     
		else if (luaChon == 4) {
			Ban dsBan[TOI_DA]; int soBan = 0;
			docFileBan("Ban.txt", dsBan, soBan);
			inSoDoBan(dsBan, soBan);
		}
		else if (luaChon == 5) xemDanhSachHoaDon(); <-- Tạm ẩn
		else cout << "\n--> Chức năng đang phát triển hoặc lựa chọn sai!" << endl;

		dungManHinh();
	}
}




// =========================================================
// II. QUẢN LÍ KHO
// =========================================================
NguyenLieu docNguyenLieu(string thongTin) {
	istringstream phanTach(thongTin);
	NguyenLieu nl;
	string boNhoDem;

	getline(phanTach, nl.ma, '|');
	getline(phanTach, nl.ten, '|');
	getline(phanTach, nl.donVi, '|');
	getline(phanTach, boNhoDem, '|'); nl.soLuong = stoi(boNhoDem);
	getline(phanTach, boNhoDem); nl.giaNhap = stoi(boNhoDem);

	return nl;
}

bool docFileNguyenLieu(string tenFile, NguyenLieu dsNL[], int& soLuong) {
	ifstream docFile(tenFile, ios::in);
	if (!docFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}

	string boNhoDem;
	while (getline(docFile, boNhoDem)) {
		if (boNhoDem.length() < 5) continue;
		dsNL[soLuong] = docNguyenLieu(boNhoDem);
		if (dsNL[soLuong].ma != "") soLuong++;
	}
	docFile.close();
	return true;
}

bool ghiFileNguyenLieu(string tenFile, NguyenLieu dsNL[], int soLuong) {
	ofstream ghiFile(tenFile, ios::out);
	if (!ghiFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}

	for (int i = 0; i < soLuong; i++) {
		ghiFile << dsNL[i].ma << "|"
			<< dsNL[i].ten << "|"
			<< dsNL[i].donVi << "|"
			<< dsNL[i].soLuong << "|"
			<< dsNL[i].giaNhap << endl;
	}
	ghiFile.close();
	return true;
}

void inKho(NguyenLieu dsNL[], int soLuong) {
	veDuong(85);
	cout << format("| {:<10} | {:<25} | {:<10} | {:<10} | {:<12} |",
		"MÃ", "TÊN NGUYÊN LIỆU", "ĐƠN VỊ", "SỐ LƯỢNG", "GIÁ NHẬP") << endl;
	veDuong(85);
	for (int i = 0; i < soLuong; i++) {
		cout << format("| {:<10} | {:<25} | {:<10} | {:<10} | {:<12} |",
			dsNL[i].ma, dsNL[i].ten, dsNL[i].donVi,
			dsNL[i].soLuong, dsNL[i].giaNhap) << endl;
	}
	veDuong(85);
}

void xemKho() {
	system("cls");
	veTieuDe("DANH SÁCH NGUYÊN LIỆU TRONG KHO");

	NguyenLieu dsNL[TOI_DA];
	int soLuong = 0;

	if (docFileNguyenLieu("Kho.txt", dsNL, soLuong)) {
		inKho(dsNL, soLuong);
	}
	else {
		cout << "\n--> Kho trống hoặc chưa có dữ liệu!" << endl;
	}
}

void nhapKho() {
	system("cls");
	veTieuDe("NHẬP KHO");

	NguyenLieu dsNL[TOI_DA];
	int soLuong = 0;
	docFileNguyenLieu("Kho.txt", dsNL, soLuong);

	PhieuNhap phieu;
	phieu.maPhieu = "PN" + to_string(time(0));
	phieu.ngay = layNgayHienTai();
	phieu.soNL = 0;
	phieu.tongTien = 0;

	cout << "Người nhập: ";
	getline(cin, phieu.nguoiNhap);

	while (true) {
		NguyenLieu nl;
		cout << "\nNhập mã nguyên liệu (0 để kết thúc): ";
		getline(cin, nl.ma);

		if (nl.ma == "0") break;

		cout << "Tên nguyên liệu: ";
		getline(cin, nl.ten);

		cout << "Đơn vị: ";
		getline(cin, nl.donVi);

		cout << "Số lượng nhập: ";
		string slStr;
		getline(cin, slStr);
		nl.soLuong = stoi(slStr);

		cout << "Giá nhập: ";
		string giaStr;
		getline(cin, giaStr);
		nl.giaNhap = stoi(giaStr);

		bool timThay = false;
		for (int i = 0; i < soLuong; i++) {
			if (dsNL[i].ma == nl.ma) {
				dsNL[i].soLuong += nl.soLuong;
				dsNL[i].giaNhap = nl.giaNhap;
				timThay = true;
				break;
			}
		}

		if (!timThay) {
			dsNL[soLuong] = nl;
			soLuong++;
		}

		phieu.dsNL[phieu.soNL] = nl;
		phieu.soNL++;
		phieu.tongTien += nl.soLuong * nl.giaNhap;

		cout << "\n--> Đã thêm vào phiếu nhập!" << endl;
	}

	if (phieu.soNL > 0) {
		ghiFileNguyenLieu("Kho.txt", dsNL, soLuong);

		ofstream luuPhieu("PhieuNhap.txt", ios::app);
		if (luuPhieu.is_open()) {
			luuPhieu << "PN_START" << endl;
			luuPhieu << phieu.maPhieu << "|" << phieu.ngay << "|"
				<< phieu.nguoiNhap << "|" << phieu.soNL << "|"
				<< phieu.tongTien << endl;

			for (int i = 0; i < phieu.soNL; i++) {
				luuPhieu << phieu.dsNL[i].ma << "|"
					<< phieu.dsNL[i].ten << "|"
					<< phieu.dsNL[i].donVi << "|"
					<< phieu.dsNL[i].soLuong << "|"
					<< phieu.dsNL[i].giaNhap << endl;
			}
			luuPhieu << "PN_END" << endl;
			luuPhieu.close();
		}

		cout << "\n--> [THÀNH CÔNG] Đã nhập kho và lưu phiếu nhập!" << endl;
	}
}

void xuatKho() {
	system("cls");
	veTieuDe("XUẤT KHO");

	NguyenLieu dsNL[TOI_DA];
	int soLuong = 0;

	if (docFileNguyenLieu("Kho.txt", dsNL, soLuong)) {
		inKho(dsNL, soLuong);
	}

	cout << "\nNhập mã nguyên liệu cần xuất: ";
	string ma;
	getline(cin, ma);

	bool timThay = false;
	for (int i = 0; i < soLuong; i++) {
		if (dsNL[i].ma == ma) {
			timThay = true;
			cout << format("Nguyên liệu: {} - Tồn kho: {} {}",
				dsNL[i].ten, dsNL[i].soLuong, dsNL[i].donVi) << endl;

			cout << "Số lượng xuất: ";
			string slStr;
			getline(cin, slStr);
			int soLuongXuat = stoi(slStr);

			if (soLuongXuat > dsNL[i].soLuong) {
				cout << "\n--> [LỖI] Số lượng trong kho không đủ!" << endl;
			}
			else {
				dsNL[i].soLuong -= soLuongXuat;
				ghiFileNguyenLieu("Kho.txt", dsNL, soLuong);
				cout << "\n--> [THÀNH CÔNG] Đã xuất kho!" << endl;
			}
			break;
		}
	}

	if (!timThay) {
		cout << "\n--> Không tìm thấy nguyên liệu!" << endl;
	}
}

void quanLiKho() {
	while (true) {
		system("cls");
		veTieuDe("[I.2] QUẢN LÝ KHO");
		cout << format("{:<60}", "[1] Xem kho") << endl;
		cout << format("{:<60}", "[2] Nhập kho") << endl;
		cout << format("{:<60}", "[3] Xuất kho") << endl;
		cout << format("{:<60}", "[0] Quay lại") << endl;
		veDuong(60);
		cout << " [*] CHỌN: ";

		string boNhoDem;
		getline(cin, boNhoDem);
		int luaChon = 0;
		if (boNhoDem != "") luaChon = stoi(boNhoDem);
		if (luaChon == 0) break;

		system("cls");
		if (luaChon == 1) xemKho();
		else if (luaChon == 2) nhapKho();
		else if (luaChon == 3) xuatKho();
		else cout << "\n--> Lựa chọn không hợp lệ!" << endl;

		dungManHinh();
	}
}


// =========================================================
// III. TRA CỨU DỮ LIỆU GIAO DỊCH
// =========================================================
void inHoaDon(HoaDon hd) {
	cout << endl;
	veDuong(60);
	cout << format(" HÓA ĐƠN: {:<20} NGÀY: {:<15}", hd.maHD, hd.ngay) << endl;
	cout << format(" BÀN SỐ:  {:<20} TRẠNG THÁI: {}",
		(hd.soBan == 0 ? "Mang Ve" : to_string(hd.soBan)),
		"Da Thanh Toan") << endl;
	veDuong(60);
	cout << format("| {:<20} | {:<5} | {:<8} | {:<12} |", "TEN MON", "SL", "GIA", "THANH TIEN") << endl;
	veDuong(60);

	for (int i = 0; i < hd.soMon; i++) {
		// Tính giá đơn vị để in (Thành tiền / Số lượng)
		int donGia = (hd.dsMon[i].soLuong > 0) ? (hd.dsMon[i].thanhTien / hd.dsMon[i].soLuong) : 0;

		cout << format("| {:<20} | {:<5} | {:<8} | {:<12} |",
			hd.dsMon[i].tenMon,
			hd.dsMon[i].soLuong,
			donGia,
			hd.dsMon[i].thanhTien) << endl;
	}
	veDuong(60);
	cout << format(" TỔNG CỘNG: {:>42} VNĐ", hd.tongTien) << endl;
	veDuong(60);
}

void traCuuHoaDon() {
	system("cls");
	veTieuDe("TRA CỨU HÓA ĐƠN");

	cout << "[1] Tra cứu hóa đơn chưa thanh toán" << endl;
	cout << "[2] Tra cứu hóa đơn đã thanh toán" << endl;
	cout << "Chọn: ";

	string luaChon;
	getline(cin, luaChon);

	string tenFile = (luaChon == "1") ? "HoaDonChuaThanhToan.txt" : "HoaDonDaThanhToan.txt";

	HoaDon dsHD[TOI_DA];
	int soHD = 0;
	docFileHoaDon(tenFile, dsHD, soHD);

	if (soHD == 0) {
		cout << "\n--> Không có hóa đơn nào!" << endl;
		return;
	}

	cout << "\nNhập mã hóa đơn hoặc số bàn: ";
	string tuKhoa;
	getline(cin, tuKhoa);

	bool timThay = false;
	for (int i = 0; i < soHD; i++) {
		if (dsHD[i].maHD.find(tuKhoa) != string::npos ||
			to_string(dsHD[i].soBan).find(tuKhoa) != string::npos) {
			system("cls");
			inHoaDon(dsHD[i]);
			timThay = true;
			break;
		}
	}

	if (!timThay) {
		cout << "\n--> Không tìm thấy hóa đơn!" << endl;
	}
}

void traCuuGiaoDich() {
	while (true) {
		system("cls");
		veTieuDe("[I.3] TRA CỨU DỮ LIỆU GIAO DỊCH");
		cout << format("{:<60}", "[1] Tra cứu hóa đơn") << endl;
		cout << format("{:<60}", "[0] Quay lại") << endl;
		veDuong(60);
		cout << " [*] CHỌN: ";

		string boNhoDem;
		getline(cin, boNhoDem);
		int luaChon = 0;
		if (boNhoDem != "") luaChon = stoi(boNhoDem);
		if (luaChon == 0) break;

		system("cls");
		if (luaChon == 1) traCuuHoaDon();
		else cout << "\n--> Lựa chọn không hợp lệ!" << endl;

		dungManHinh();
	}
}

// =========================================================
// BÁO CÁO THỐNG KÊ
// =========================================================
void thongKeBanHang() {
	system("cls");
	veTieuDe("THỐNG KÊ BÁN HÀNG");

	HoaDon dsHD[TOI_DA];
	int soHD = 0;
	docFileHoaDon("HoaDonDaThanhToan.txt", dsHD, soHD);

	if (soHD == 0) {
		cout << "\n--> Chưa có dữ liệu bán hàng!" << endl;
		return;
	}

	int tongDoanhThu = 0;
	int tongSoMon = 0;

	cout << "\n=== DANH SÁCH HÓA ĐƠN ĐÃ THANH TOÁN ===" << endl;
	veDuong(75);
	cout << format("| {:<15} | {:<12} | {:<10} | {:<12} | {:<10} |",
		"MÃ HĐ", "NGÀY", "BÀN", "TỔNG TIỀN", "SỐ MÓN") << endl;
	veDuong(75);

	for (int i = 0; i < soHD; i++) {
		cout << format("| {:<15} | {:<12} | {:<10} | {:<12} | {:<10} |",
			dsHD[i].maHD, dsHD[i].ngay,
			(dsHD[i].soBan == 0 ? "Mang về" : to_string(dsHD[i].soBan)),
			dsHD[i].tongTien, dsHD[i].soMon) << endl;

		tongDoanhThu += dsHD[i].tongTien;
		tongSoMon += dsHD[i].soMon;
	}
	veDuong(75);

	cout << "\n=== THỐNG KÊ TỔNG QUAN ===" << endl;
	cout << format("Tổng số hóa đơn: {}", soHD) << endl;
	cout << format("Tổng doanh thu: {} VNĐ", tongDoanhThu) << endl;
	cout << format("Tổng số món đã bán: {}", tongSoMon) << endl;
	cout << format("Doanh thu trung bình/hóa đơn: {} VNĐ",
		(soHD > 0 ? tongDoanhThu / soHD : 0)) << endl;
}

void thongKeMonBanChay() {
	system("cls");
	veTieuDe("THỐNG KÊ MÓN BÁN CHẠY");

	HoaDon dsHD[TOI_DA];
	int soHD = 0;
	docFileHoaDon("HoaDonDaThanhToan.txt", dsHD, soHD);

	if (soHD == 0) {
		cout << "\n--> Chưa có dữ liệu bán hàng!" << endl;
		return;
	}

	string dsMon[TOI_DA];
	int soLuongBan[TOI_DA];
	int soMon = 0;

	for (int i = 0; i < soHD; i++) {
		for (int j = 0; j < dsHD[i].soMon; j++) {
			bool timThay = false;
			for (int k = 0; k < soMon; k++) {
				if (dsMon[k] == dsHD[i].dsMon[j].tenMon) {
					soLuongBan[k] += dsHD[i].dsMon[j].soLuong;
					timThay = true;
					break;
				}
			}

			if (!timThay) {
				dsMon[soMon] = dsHD[i].dsMon[j].tenMon;
				soLuongBan[soMon] = dsHD[i].dsMon[j].soLuong;
				soMon++;
			}
		}
	}

	for (int i = 0; i < soMon - 1; i++) {
		for (int j = i + 1; j < soMon; j++) {
			if (soLuongBan[i] < soLuongBan[j]) {
				int tempSL = soLuongBan[i];
				soLuongBan[i] = soLuongBan[j];
				soLuongBan[j] = tempSL;

				string tempMon = dsMon[i];
				dsMon[i] = dsMon[j];
				dsMon[j] = tempMon;
			}
		}
	}

	veDuong(60);
	cout << format("| {:<5} | {:<35} | {:<12} |", "TOP", "TÊN MÓN", "SỐ LƯỢNG") << endl;
	veDuong(60);

	for (int i = 0; i < soMon && i < 10; i++) {
		cout << format("| {:<5} | {:<35} | {:<12} |", i + 1, dsMon[i], soLuongBan[i]) << endl;
	}
	veDuong(60);
}

// =========================================================
// CÁC HÀM CHỨC NĂNG CHÍNH
// =========================================================
void quanLiCoSoDuLieu();
void quanLiDuLieuPhatSinh();
void baoCaoThongKe();

// =========================================================
// MAIN
// =========================================================
int main() {
	while (true) {
		system("cls");
		veTieuDe("CỬA HÀNG CÀ PHÊ");
		cout << format("{:<60}", "[1] QUẢN LÍ CƠ SỞ DỮ LIỆU") << endl;
		cout << format("{:<60}", "[2] QUẢN LÍ DỮ LIỆU PHÁT SINH") << endl;
		cout << format("{:<60}", "[3] BÁO CÁO THỐNG KÊ") << endl;
		cout << format("{:<60}", "[0] THOÁT CỬA HÀNG") << endl;
		veDuong(60);
		cout << " [*] CHỌN: ";

		string boNhoDem;
		getline(cin, boNhoDem);
		int luaChon = 0;
		if (boNhoDem != "") luaChon = stoi(boNhoDem);
		if (luaChon == 0) break;

		system("cls");
		if (luaChon == 1) quanLiCoSoDuLieu();
		else if (luaChon == 2) quanLiDuLieuPhatSinh();
		else if (luaChon == 3) baoCaoThongKe();
		else cout << "\n--> Lựa chọn không hợp lệ!" << endl;

		dungManHinh();
	}
	cout << "\n=== CẢM ƠN QUÝ KHÁCH! ===" << endl;
	cout << "Hẹn gặp lại! *_*" << endl;
	return 0;
}