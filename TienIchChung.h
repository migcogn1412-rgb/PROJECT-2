#pragma once
#include <iostream>
#include <string>
#include <format>
#include <fstream>
#include <sstream>
#include <ctime>

using std::cout, std::cin, std::endl, std::to_string;
using std::string, std::ofstream, std::ifstream, std::ios;
using std::format, std::istringstream, std::getline, std::stoi;

void veDuong(int doDai) {
	cout << string(doDai, '-') << endl;
}

void veTieuDe(string tieuDe) {
	cout << endl;
	veDuong(60);
	cout << format("|-{:^56}-|", tieuDe) << endl;
	veDuong(60);
	cout << endl;
}

void dungManHinh() {
	cout << endl << "--> Nhấn [ENTER] để quay lại...";
	string rac;
	getline(cin, rac);
}

bool xacNhan() {
	string xacNhan;
	cout << " [*] XÁC NHẬN (Y/N): ";
	getline(cin, xacNhan);
	if (xacNhan == "N" || xacNhan == "n") return false;
	if (xacNhan == "Y" || xacNhan == "y") return true;
}

string tachData(string str, int index) {
	istringstream ss(str); string segment; int i = 0;
	while (getline(ss, segment, '|')) {
		if (i == index) return segment;
		i++;
	}
	return "";
}

string layNgayHienTai() {
	time_t bayGio = time(0);
	tm ltm;
	localtime_s(&ltm, &bayGio);
	return format("{:02}/{:02}/{}", ltm.tm_mday, 1 + ltm.tm_mon, 1900 + ltm.tm_year);

}