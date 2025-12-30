#include <iostream>
#include <string>
#include <format>
#include <fstream>
#include <sstream>
#include <ctime>

// Include các file header chứa Struct và hàm cơ bản
#include "TienIchChung.h"
#include "SoDoBan.h"
#include "QuanLiDoUong.h"
#include "QuanLiDoAn.h"
#include "QuanLiTopping.h"
#include "CauHinhOrder.h"
#include "MenuChiTiet.h"

using std::cout, std::cin, std::endl, std::to_string;
using std::string, std::ofstream, std::ifstream, std::ios;
using std::format, std::istringstream, std::getline, std::stoi;

// =========================================================
// KHAI BÁO STRUCT NỘI BỘ (Chỉ dùng cho Bán hàng & Kho)
// =========================================================

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
    ChiTietMon dsMon[100]; // Sử dụng số cố định thay vì TOI_DA để tránh lỗi
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
    NguyenLieu dsNL[100];
    int soNL = 0;
    int tongTien = 0;
};

// Struct tạm dùng để gộp Menu Đồ Ăn và Đồ Uống chung vào 1 danh sách hiển thị
struct MonMenu { 
    string ma, ten, loai; 
    int gia = 0; 
};

// =========================================================
// I. XỬ LÝ HÓA ĐƠN VÀ BÁN HÀNG
// =========================================================

ChiTietMon docChiTietMon(string thongTin) {
    istringstream phanTach(thongTin);
    ChiTietMon mon;
    string boNhoDem;
    getline(phanTach, mon.tenMon, '|');
    getline(phanTach, mon.size, '|');
    getline(phanTach, boNhoDem, '|'); mon.duong = (boNhoDem.empty() ? 0 : stoi(boNhoDem));
    getline(phanTach, boNhoDem, '|'); mon.da = (boNhoDem.empty() ? 0 : stoi(boNhoDem));
    getline(phanTach, mon.topping, '|');
    getline(phanTach, boNhoDem, '|'); mon.soLuong = (boNhoDem.empty() ? 0 : stoi(boNhoDem));
    getline(phanTach, boNhoDem); mon.thanhTien = (boNhoDem.empty() ? 0 : stoi(boNhoDem));
    return mon;
}

HoaDon docHoaDon(string thongTin) {
    istringstream phanTach(thongTin);
    HoaDon hd;
    string boNhoDem;
    getline(phanTach, hd.maHD, '|');
    getline(phanTach, hd.ngay, '|');
    getline(phanTach, boNhoDem, '|'); hd.soBan = (boNhoDem.empty() ? 0 : stoi(boNhoDem));
    getline(phanTach, boNhoDem, '|'); hd.soMon = (boNhoDem.empty() ? 0 : stoi(boNhoDem));
    getline(phanTach, boNhoDem, '|'); hd.tongTien = (boNhoDem.empty() ? 0 : stoi(boNhoDem));
    getline(phanTach, hd.ghiChu);
    return hd;
}

bool docFileHoaDon(string tenFile, HoaDon dsHD[], int& soLuong) {
    ifstream docFile(tenFile, ios::in);
    if (!docFile.is_open()) return false;
    
    string boNhoDem;
    soLuong = 0;
    while (getline(docFile, boNhoDem)) {
        if (boNhoDem.find("HD_START") != string::npos) {
            if (getline(docFile, boNhoDem)) {
                dsHD[soLuong] = docHoaDon(boNhoDem);
                int soMon = 0;
                while (getline(docFile, boNhoDem) && boNhoDem.find("HD_END") == string::npos) {
                    if (boNhoDem.find("MON|") != string::npos) {
                         // Logic đọc chi tiết món đơn giản hóa cho file log
                         // Lưu ý: Hàm này đang đọc file cấu trúc cũ, cần cẩn thận nếu format thay đổi
                    }
                    // Tạm thời bỏ qua chi tiết món khi đọc danh sách tổng để tránh lỗi parser phức tạp
                }
                soLuong++;
            }
        }
    }
    docFile.close();
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
        cout << "\n--> Đã xuất bill ra file '" << tenFile << "'\n";
    }
}

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

void taoOrderMoi() {
    Ban dsBan[100]; int slBan = 0; docFileBan("Ban.txt", dsBan, slBan);
    DoUong dsDU[100]; int slDU = 0; docFileDoUong("DoUong.txt", dsDU, slDU);
    DoAn dsDA[100]; int slDA = 0; docFileDoAn("DoAn.txt", dsDA, slDA);
    Topping dsTop[100]; int slTop = 0; docFileTopping("Topping.txt", dsTop, slTop);
    CauHinh dsSize[100]; int slSize = 0; docFileCauHinh("CauHinhOrder.txt", dsSize, slSize);

    MonMenu menu[200]; int slMenu = 0;
    for (int i = 0; i < slDU; i++) menu[slMenu++] = { dsDU[i].ma, dsDU[i].ten, "Do Uong", dsDU[i].giaGoc };
    for (int i = 0; i < slDA; i++) menu[slMenu++] = { dsDA[i].ma, dsDA[i].ten, "Do An", dsDA[i].giaGoc };

    veTieuDe("ORDER TẠI QUẦY"); inSoDoBan(dsBan, slBan);
    HoaDon hd; cout << "--> Số bàn (0=Mang ve): "; string s; getline(cin, s); 
    hd.soBan = (s == "") ? 0 : stoi(s);
    
    if (hd.soBan != 0) {
        for (int i = 0; i < slBan; i++) if (dsBan[i].soBan == hd.soBan && dsBan[i].trangThai == 1) {
            cout << "[!] Bàn bận. Tiếp tục ghi đè? (Y/N) "; if (!xacNhan()) return;
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
            cout << "--> SL: "; string sl; getline(cin, sl); 
            ct.soLuong = (sl == "") ? 1 : stoi(sl);
            ct.size = "S"; ct.giaSize = 0; ct.topping = ""; ct.giaTopping = 0;

            if (m.loai == "Do Uong") {
                cout << "\n-- SIZE: "; for (int k = 0; k < slSize; k++) cout << format("{} (+{}) | ", dsSize[k].size, dsSize[k].giaCongThem);
                cout << "\n--> Nhập tên Size: "; string sz; getline(cin, sz);
                // Chuyển size về chữ hoa để so sánh
                for (auto & c: sz) c = toupper(c);
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
        int tienKhach = (sk == "") ? 0 : stoi(sk);
        
        if (tienKhach >= hd.tongTien && xacNhan()) {
            luuDoanhThu(hd); xuatBillChoKhach(hd);
            if (hd.soBan != 0) {
                for (int i = 0; i < slBan; i++) if (dsBan[i].soBan == hd.soBan) dsBan[i].trangThai = 1;
                ghiFileBan("Ban.txt", dsBan, slBan);
            }
            cout << "--> DONE!\n";
        } else {
            cout << "--> Hủy thanh toán hoặc tiền không đủ!\n";
        }
    }
}

void donBan() {
    Ban ds[100]; int n; docFileBan("Ban.txt", ds, n); inSoDoBan(ds, n);
    cout << "--> Nhập bàn dọn (0 thoát): "; string s; getline(cin, s); 
    int b = (s == "") ? 0 : stoi(s);
    if (b != 0) {
        for (int i = 0; i < n; i++) if (ds[i].soBan == b) ds[i].trangThai = 0;
        ghiFileBan("Ban.txt", ds, n); cout << "--> Đã dọn!\n";
    }
}

void quanLiBanHangVaOrder() {
    while (true) {
        system("cls"); veTieuDe("QUẢN LÝ BÁN HÀNG");
        cout << "[1] Order & Pay\n[2] Dọn bàn\n[3] Sơ đồ bàn\n[4] In lại Bill cũ\n[0] Về\nChọn: ";
        string s; getline(cin, s); int c = (s == "") ? 0 : stoi(s);
        if (c == 0) break;
        if (c == 1) taoOrderMoi(); 
        else if (c == 2) donBan(); 
        else if (c == 4) inLaiHoaDonCu();
        else if (c == 3) { Ban ds[100]; int n; docFileBan("Ban.txt", ds, n); inSoDoBan(ds, n); }
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
    getline(phanTach, boNhoDem, '|'); nl.soLuong = (boNhoDem.empty() ? 0 : stoi(boNhoDem));
    getline(phanTach, boNhoDem); nl.giaNhap = (boNhoDem.empty() ? 0 : stoi(boNhoDem));

    return nl;
}

bool docFileNguyenLieu(string tenFile, NguyenLieu dsNL[], int& soLuong) {
    ifstream docFile(tenFile, ios::in);
    if (!docFile.is_open()) return false;

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
    if (!ghiFile.is_open()) return false;

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
    NguyenLieu dsNL[100];
    int soLuong = 0;
    if (docFileNguyenLieu("Kho.txt", dsNL, soLuong)) {
        inKho(dsNL, soLuong);
    } else {
        cout << "\n--> Kho trống hoặc chưa có dữ liệu!" << endl;
    }
}

void nhapKho() {
    system("cls");
    veTieuDe("NHẬP KHO");

    NguyenLieu dsNL[100];
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
        cout << "\nNhập mã nguyên liệu (0 để kết thúc): "; getline(cin, nl.ma);
        if (nl.ma == "0") break;

        cout << "Tên nguyên liệu: "; getline(cin, nl.ten);
        cout << "Đơn vị: "; getline(cin, nl.donVi);
        cout << "Số lượng nhập: "; string slStr; getline(cin, slStr); nl.soLuong = stoi(slStr);
        cout << "Giá nhập: "; string giaStr; getline(cin, giaStr); nl.giaNhap = stoi(giaStr);

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
            luuPhieu << phieu.maPhieu << "|" << phieu.ngay << "|" << phieu.nguoiNhap << "|" << phieu.soNL << "|" << phieu.tongTien << endl;
            for (int i = 0; i < phieu.soNL; i++) {
                luuPhieu << phieu.dsNL[i].ma << "|" << phieu.dsNL[i].ten << "|" << phieu.dsNL[i].donVi << "|" << phieu.dsNL[i].soLuong << "|" << phieu.dsNL[i].giaNhap << endl;
            }
            luuPhieu << "PN_END" << endl;
            luuPhieu.close();
        }
        cout << "\n--> [THÀNH CÔNG] Đã nhập kho và lưu phiếu nhập!" << endl;
    }
}

void xuatKho() {
    system("cls"); veTieuDe("XUẤT KHO");
    NguyenLieu dsNL[100]; int soLuong = 0;
    if (docFileNguyenLieu("Kho.txt", dsNL, soLuong)) { inKho(dsNL, soLuong); }

    cout << "\nNhập mã nguyên liệu cần xuất: "; string ma; getline(cin, ma);
    bool timThay = false;
    for (int i = 0; i < soLuong; i++) {
        if (dsNL[i].ma == ma) {
            timThay = true;
            cout << format("Nguyên liệu: {} - Tồn kho: {} {}", dsNL[i].ten, dsNL[i].soLuong, dsNL[i].donVi) << endl;
            cout << "Số lượng xuất: "; string slStr; getline(cin, slStr); int soLuongXuat = stoi(slStr);

            if (soLuongXuat > dsNL[i].soLuong) {
                cout << "\n--> [LỖI] Số lượng trong kho không đủ!" << endl;
            } else {
                dsNL[i].soLuong -= soLuongXuat;
                ghiFileNguyenLieu("Kho.txt", dsNL, soLuong);
                cout << "\n--> [THÀNH CÔNG] Đã xuất kho!" << endl;
            }
            break;
        }
    }
    if (!timThay) cout << "\n--> Không tìm thấy nguyên liệu!" << endl;
}

void quanLiKho() {
    while (true) {
        system("cls"); veTieuDe("[I.2] QUẢN LÝ KHO");
        cout << format("{:<60}", "[1] Xem kho") << endl;
        cout << format("{:<60}", "[2] Nhập kho") << endl;
        cout << format("{:<60}", "[3] Xuất kho") << endl;
        cout << format("{:<60}", "[0] Quay lại") << endl;
        veDuong(60); cout << " [*] CHỌN: ";

        string boNhoDem; getline(cin, boNhoDem);
        int luaChon = (boNhoDem != "") ? stoi(boNhoDem) : 0;
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
    cout << endl; veDuong(60);
    cout << format(" HÓA ĐƠN: {:<20} NGÀY: {:<15}", hd.maHD, hd.ngay) << endl;
    cout << format(" BÀN SỐ:  {:<20} TRẠNG THÁI: {}", (hd.soBan == 0 ? "Mang Ve" : to_string(hd.soBan)), "Da Thanh Toan") << endl;
    veDuong(60);
    cout << format("| {:<20} | {:<5} | {:<8} | {:<12} |", "TEN MON", "SL", "GIA", "THANH TIEN") << endl;
    veDuong(60);

    for (int i = 0; i < hd.soMon; i++) {
        // Tính giá đơn vị để in (Thành tiền / Số lượng)
        int donGia = (hd.dsMon[i].soLuong > 0) ? (hd.dsMon[i].thanhTien / hd.dsMon[i].soLuong) : 0;
        cout << format("| {:<20} | {:<5} | {:<8} | {:<12} |", hd.dsMon[i].tenMon, hd.dsMon[i].soLuong, donGia, hd.dsMon[i].thanhTien) << endl;
    }
    veDuong(60);
    cout << format(" TỔNG CỘNG: {:>42} VNĐ", hd.tongTien) << endl; veDuong(60);
}

void traCuuHoaDon() {
    system("cls"); veTieuDe("TRA CỨU HÓA ĐƠN");
    cout << "[1] Tra cứu hóa đơn chưa thanh toán\n[2] Tra cứu hóa đơn đã thanh toán\nChọn: ";
    string luaChon; getline(cin, luaChon);
    string tenFile = (luaChon == "1") ? "HoaDonChuaThanhToan.txt" : "HoaDonDaThanhToan.txt";

    HoaDon dsHD[100]; int soHD = 0;
    docFileHoaDon(tenFile, dsHD, soHD);

    if (soHD == 0) { cout << "\n--> Không có hóa đơn nào!" << endl; return; }

    cout << "\nNhập mã hóa đơn hoặc số bàn: "; string tuKhoa; getline(cin, tuKhoa);
    bool timThay = false;
    for (int i = 0; i < soHD; i++) {
        if (dsHD[i].maHD.find(tuKhoa) != string::npos || to_string(dsHD[i].soBan).find(tuKhoa) != string::npos) {
            system("cls"); inHoaDon(dsHD[i]); timThay = true; break;
        }
    }
    if (!timThay) cout << "\n--> Không tìm thấy hóa đơn!" << endl;
}

void traCuuGiaoDich() {
    while (true) {
        system("cls"); veTieuDe("[I.3] TRA CỨU DỮ LIỆU GIAO DỊCH");
        cout << format("{:<60}", "[1] Tra cứu hóa đơn") << endl;
        cout << format("{:<60}", "[0] Quay lại") << endl;
        veDuong(60); cout << " [*] CHỌN: ";
        string boNhoDem; getline(cin, boNhoDem);
        int luaChon = (boNhoDem != "") ? stoi(boNhoDem) : 0;
        if (luaChon == 0) break;
        system("cls");
        if (luaChon == 1) traCuuHoaDon();
        else cout << "\n--> Lựa chọn không hợp lệ!" << endl;
        dungManHinh();
    }
}

// =========================================================
// IV. BÁO CÁO THỐNG KÊ
// =========================================================

void thongKeBanHang() {
    system("cls"); veTieuDe("THỐNG KÊ BÁN HÀNG");
    HoaDon dsHD[100]; int soHD = 0;
    docFileHoaDon("HoaDonDaThanhToan.txt", dsHD, soHD);

    if (soHD == 0) { cout << "\n--> Chưa có dữ liệu bán hàng!" << endl; return; }

    int tongDoanhThu = 0; int tongSoMon = 0;
    cout << "\n=== DANH SÁCH HÓA ĐƠN ĐÃ THANH TOÁN ===" << endl; veDuong(75);
    cout << format("| {:<15} | {:<12} | {:<10} | {:<12} | {:<10} |", "MÃ HĐ", "NGÀY", "BÀN", "TỔNG TIỀN", "SỐ MÓN") << endl; veDuong(75);

    for (int i = 0; i < soHD; i++) {
        cout << format("| {:<15} | {:<12} | {:<10} | {:<12} | {:<10} |", dsHD[i].maHD, dsHD[i].ngay, (dsHD[i].soBan == 0 ? "Mang về" : to_string(dsHD[i].soBan)), dsHD[i].tongTien, dsHD[i].soMon) << endl;
        tongDoanhThu += dsHD[i].tongTien; tongSoMon += dsHD[i].soMon;
    }
    veDuong(75);
    cout << "\n=== THỐNG KÊ TỔNG QUAN ===" << endl;
    cout << format("Tổng số hóa đơn: {}", soHD) << endl;
    cout << format("Tổng doanh thu: {} VNĐ", tongDoanhThu) << endl;
    cout << format("Tổng số món đã bán: {}", tongSoMon) << endl;
    cout << format("Doanh thu trung bình/hóa đơn: {} VNĐ", (soHD > 0 ? tongDoanhThu / soHD : 0)) << endl;
}

void thongKeMonBanChay() {
    // Để đơn giản, hàm này tạm thời thông báo đang phát triển vì logic phân tích món phức tạp
    // khi đọc từ file log dạng text.
    cout << "Chức năng đang được hoàn thiện..." << endl;
}

// =========================================================
// MAIN & INCLUDE HAM CHUC NANG CHINH
// =========================================================

// Include file chứa menu chính (HamChucNangChinh.h)
// Lưu ý: File này phải được include SAU KHI các hàm quanLiBanHangVaOrder... đã được định nghĩa
#include "HamChucNangChinh.h"

int main() {
    // Thiết lập font tiếng Việt nếu cần (trên Windows)
    system("chcp 65001 > nul");

    while (true) {
        system("cls");
        veTieuDe("CỬA HÀNG CÀ PHÊ");
        cout << format("{:<60}", "[1] QUẢN LÍ CƠ SỞ DỮ LIỆU") << endl;
        cout << format("{:<60}", "[2] QUẢN LÍ DỮ LIỆU PHÁT SINH") << endl;
        cout << format("{:<60}", "[3] BÁO CÁO THỐNG KÊ") << endl;
        cout << format("{:<60}", "[0] THOÁT CỬA HÀNG") << endl;
        veDuong(60);
        cout << " [*] CHỌN: ";

        string boNhoDem; getline(cin, boNhoDem);
        int luaChon = (boNhoDem != "") ? stoi(boNhoDem) : 0;
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
