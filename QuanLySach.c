#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 1000
#define DAI 200

typedef struct {
    char maSach[20];
    char tenSach[100];
    char tacGia[100];
    char theLoai[50];
    char nhaXuatBan[100];
    int namXuatBan;
    double giaSach;
    int soLuongTon;
    int soLuongDangMuon;
} Sach;

Sach danhSach[MAX];
int soSach = 0;

/* ===================== NHAP DU LIEU ===================== */

void docDong(char s[], int size) {
    int len;
    if (fgets(s, size, stdin) == NULL) { 
        printf("\nKet thuc nhap lieu. Thoat chuong trinh.\n");
        exit(0);
    }
    len = (int)strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
}

int laRong(const char s[]) {
    int i;
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] != ' ') return 0;
    }
    return 1;
}

void docChuoi(const char cauHoi[], char s[], int size) {
    while (1) {
        printf("%s", cauHoi);
        docDong(s, size);
        if (!laRong(s)) return;
        printf("Loi: khong duoc de trong!\n");
    }
}

int docSoNguyen(const char cauHoi[], int min, int max) {
    char buf[DAI];
    char thua;
    int x;
    while (1) {
        printf("%s", cauHoi);
        docDong(buf, DAI);
        if (sscanf(buf, "%d %c", &x, &thua) != 1) {
            printf("Loi: phai nhap mot so nguyen!\n");
        } else if (x < min || x > max) {
            printf("Loi: gia tri phai tu %d den %d!\n", min, max);
        } else {
            return x;
        }
    }
}

double docSoThuc(const char cauHoi[], double min, double max) {
    char buf[DAI];
    char thua;
    double x;
    while (1) {
        printf("%s", cauHoi);
        docDong(buf, DAI);
        if (sscanf(buf, "%lf %c", &x, &thua) != 1) {
            printf("Loi: phai nhap mot so!\n");
        } else if (!(x >= min && x <= max)) {
            printf("Loi: gia tri phai tu %.2f den %.2f!\n", min, max);
        } else {
            return x;
        }
    }
}

int hoiCoKhong(const char cauHoi[]) {
    char buf[DAI];
    while (1) {
        printf("%s (y/n): ", cauHoi);
        docDong(buf, DAI);
        if (strcmp(buf, "y") == 0 || strcmp(buf, "Y") == 0) return 1;
        if (strcmp(buf, "n") == 0 || strcmp(buf, "N") == 0) return 0;
        printf("Loi: chi nhap y hoac n!\n");
    }
}

/* ===================== HAM HO TRO ===================== */

int layNamHienTai() {
    time_t t = time(NULL);
    struct tm now = *localtime(&t);
    return now.tm_year + 1900;
}


void layTinhTrang(Sach s, char ketQua[]) {
    if (s.soLuongTon > 0) {
        strcpy(ketQua, "Con sach");
    } else {
        strcpy(ketQua, "Het sach");
    }
}


int timViTriTheoMa(const char ma[]) {
    int i;
    for (i = 0; i < soSach; i++) {
        if (strcmp(danhSach[i].maSach, ma) == 0) return i;
    }
    return -1;
}

void chuyenThuong(const char nguon[], char dich[]) {
    int i;
    for (i = 0; nguon[i] != '\0'; i++) {
        char c = nguon[i];
        if (c >= 'A' && c <= 'Z') c = (char)(c + 32);
        dich[i] = c;
    }
    dich[i] = '\0';
}


int chuaChuoi(const char nguon[], const char tu[]) {
    char a[DAI], b[DAI];
    chuyenThuong(nguon, a);
    chuyenThuong(tu, b);
    return strstr(a, b) != NULL;
}

/* ===================== HIEN THI DANG BANG ===================== */

void inDuongKe() {
    int i;
    for (i = 0; i < 118; i++) putchar('-');
    putchar('\n');
}

void inTieuDe() {
    inDuongKe();
    printf("%-10s %-22s %-16s %-12s %-14s %-5s %12s %4s %4s %-10s\n",
           "Ma sach", "Ten sach", "Tac gia", "The loai", "NXB",
           "Nam", "Gia", "Ton", "Muon", "Tinh trang");
    inDuongKe();
}

void inSach(Sach s) {
    char tinhTrang[20];
    layTinhTrang(s, tinhTrang);
    printf("%-10.10s %-22.22s %-16.16s %-12.12s %-14.14s %5d %12.2f %4d %4d %-10s\n",
           s.maSach, s.tenSach, s.tacGia, s.theLoai, s.nhaXuatBan,
           s.namXuatBan, s.giaSach, s.soLuongTon, s.soLuongDangMuon, tinhTrang);
}

void hienThiDanhSach() {
    int i;
    if (soSach == 0) {
        printf("Danh sach chua co sach nao.\n");
        return;
    }
    inTieuDe();
    for (i = 0; i < soSach; i++) inSach(danhSach[i]);
    inDuongKe();
    printf("Tong cong: %d dau sach.\n", soSach);
}

/* ===================== THEM / SUA / XOA ===================== */

Sach nhapThongTinSach(const char ma[]) {
    Sach s;
    strcpy(s.maSach, ma);
    docChuoi("Ten sach: ", s.tenSach, 100);
    docChuoi("Tac gia: ", s.tacGia, 100);
    docChuoi("The loai: ", s.theLoai, 50);
    docChuoi("Nha xuat ban: ", s.nhaXuatBan, 100);
    s.namXuatBan = docSoNguyen("Nam xuat ban: ", 1000, layNamHienTai());
    s.giaSach = docSoThuc("Gia sach: ", 0, 99999999);
    s.soLuongTon = docSoNguyen("So luong ton: ", 0, 9999);
    s.soLuongDangMuon = 0;
    return s;
}

Sach nhapSach() {
    char ma[20];
    while (1) {
        docChuoi("Ma sach: ", ma, 20);
        if (timViTriTheoMa(ma) == -1) break;
        printf("Loi: ma sach \"%s\" da ton tai!\n", ma);
    }
    return nhapThongTinSach(ma);
}

void themSach() {
	
    do {
        if (soSach >= MAX) {
            printf("Loi: danh sach da day (%d sach), khong the them!\n", MAX);
            return;
        }
        danhSach[soSach] = nhapSach();
        soSach++;
        printf("Da them sach thanh cong.\n");
    } while (hoiCoKhong("Nhap tiep?"));
}

void capNhatSach() {
    char ma[20];
    int vt, dangMuon;
    docChuoi("Nhap ma sach can cap nhat: ", ma, 20);
    vt = timViTriTheoMa(ma);
    if (vt == -1) {
        printf("Khong tim thay sach co ma \"%s\".\n", ma);
        return;
    }
    inTieuDe();
    inSach(danhSach[vt]);
    printf("Nhap thong tin moi (ma sach khong doi):\n");
    dangMuon = danhSach[vt].soLuongDangMuon;
    danhSach[vt] = nhapThongTinSach(ma);
    danhSach[vt].soLuongDangMuon = dangMuon;
    printf("Da cap nhat sach.\n");
}

void xoaSach() {
    char ma[20];
    int vt, i;
    docChuoi("Nhap ma sach can xoa: ", ma, 20);
    vt = timViTriTheoMa(ma);
    if (vt == -1) {
        printf("Khong tim thay sach co ma \"%s\".\n", ma);
        return;
    }
    inTieuDe();
    inSach(danhSach[vt]);
    if (danhSach[vt].soLuongDangMuon > 0) {
        printf("Khong the xoa: con %d cuon dang duoc muon!\n", danhSach[vt].soLuongDangMuon);
        return;
    }
    if (!hoiCoKhong("Xac nhan xoa?")) {
        printf("Da huy xoa.\n");
        return;
    }
    for (i = vt; i < soSach - 1; i++) {
        danhSach[i] = danhSach[i + 1];
    }
    soSach--;
    printf("Da xoa sach.\n");
}

/* ===================== MUON / TRA SACH ===================== */

void muonSach() {
	
    char ma[20] = "";
    int viTriSach = 0;
	int soLuong = 0; 
	
    docChuoi("Nhap ma sach can muon: ", ma, 20);
    viTriSach = timViTriTheoMa(ma);
    
    if (viTriSach == -1) {
        printf("Khong tim thay sach co ma \"%s\".\n", ma);
    return;
    }
    
    inTieuDe();
    inSach(danhSach[viTriSach]);
    
    if (danhSach[viTriSach].soLuongTon == 0) {
        printf("Sach da het, khong the muon!\n");
    return;
    }
    
    soLuong = docSoNguyen("Nhap so luong muon: ", 1, danhSach[viTriSach].soLuongTon);
    danhSach[viTriSach].soLuongTon -= soLuong;
    danhSach[viTriSach].soLuongDangMuon += soLuong;
    
    printf("Muon thanh cong %d cuon sach \"%s\".\n", soLuong, danhSach[viTriSach].tenSach);
    printf("Con ton: %d | Dang muon: %d\n",danhSach[viTriSach].soLuongTon, danhSach[viTriSach].soLuongDangMuon);
	}

void traSach() {
    char ma[20];
    int viTriSach = 0;
	int soLuong = 0;
	
    docChuoi("Nhap ma sach can tra: ", ma, 20);
    viTriSach = timViTriTheoMa(ma);
    
    if (viTriSach == -1) {
        printf("Khong tim thay sach co ma \"%s\".\n", ma);
    return;
    }
    inTieuDe();
    inSach(danhSach[viTriSach]);
    
    if (danhSach[viTriSach].soLuongDangMuon == 0) {
        printf("Sach nay khong co cuon nao dang duoc muon!\n");
    return;
    }
    
    soLuong = docSoNguyen("Nhap so luong tra: ", 1, danhSach[viTriSach].soLuongDangMuon);
    danhSach[viTriSach].soLuongTon += soLuong;
    danhSach[viTriSach].soLuongDangMuon -= soLuong;
    
    printf("Tra thanh cong %d cuon sach \"%s\".\n", soLuong, danhSach[viTriSach].tenSach);
    printf("Con ton: %d | Dang muon: %d\n",danhSach[viTriSach].soLuongTon, danhSach[viTriSach].soLuongDangMuon);
	}

/* ===================== TIM KIEM / LOC ===================== */
void locSach(int chon){
	printf("1. The Loai\n"); 
	printf("2. Tac Gia\n"); 
	printf("3. Nha Xuat Ban\n"); 
	printf("4. Khoang Gia\n"); 
	printf("5. Nam Xuat Ban\n"); 
	printf("6. So Luong\n");
	printf("7. Ket Hop\n");
	printf("0. Thoat\n");
	printf("Nhap lua chon: "); 
	scanf("%d", &chon);
	
	switch(chon){
		case 1: locTheoTheLoai(); break;
		case 2: locTheoTacGia(); break;
		case 3: locTheoNhaXuatBan(); break;
		case 4: locTheoKhoangGia(); break;
		case 5: locTheoNamXuatBan(); break;
		case 6: locTheoSoLuong(); break;
		case 7: locKetHop(); break; 
		case 0: break;
		default: printf("Lua chon khong hop le!"); 
	} 
} 

void loctheoTheLoai(){
	int timThay = 0;
	printf("Nhap the loai: ");
	docDong(theLoai, sizeof(theLoai));
	
	for(int i = 0; i < soSach; i++){
		if(strcmp(danhSach[i].theLoai, theLoai == 0)){
			printf("\nMa sach: %s", danhSach[i].maSach);
			printf("\nTen sach: %s", danhSach[i].tenSach);
			printf("\nGia sach: %.2lf", danhSach[i].giaSach);
			printf("\nTac gia: %s", danhSach[i].tacGia);
			printf("\nThe loai: %s", danhSach[i].theLoai);
			timThay = 1;
		} 
	}
	
	if(!timThay){
		printf("Khong tim thay sach phu hop!\n");
	}
}

void locTheoTacGia(){
	int timThay = 0;
	printf("Nhap ten tac gia: ");
	docDong(tacGia, sizeof(tacGia));
	
	for(int i = 0; i < soSach; i++){
		if(strcmp(danhSach[i].tacGia, tacGia == 0)){
			printf("\nMa sach: %s", danhSach[i].maSach);
			printf("\nTen sach: %s", danhSach[i].tenSach);
			printf("\nGia sach: %.2lf", danhSach[i].giaSach);
			printf("\nTac gia: %s", danhSach[i].tacGia);
			printf("\nThe loai: %s", danhSach[i].theLoai);
			timThay = 1;
		} 
	}
	
	if(!timThay){
		printf("Khong tim thay sach phu hop!\n");
	} 
}

void locTheoNhaXuatBan(){
	int timThay = 0;
	printf("Nhap nha xuat ban: ");
	docDong(nhaXuatBan, sizeof(nhaXuatBan));
	
	for(int i = 0; i < soSach; i++){
		if(strcmp(danhSach[i].nhaXuatBan, nhaXuatBan == 0)){
			printf("\nMa sach: %s", danhSach[i].maSach);
			printf("\nTen sach: %s", danhSach[i].tenSach);
			printf("\nGia sach: %.2lf", danhSach[i].giaSach);
			printf("\nTac gia: %s", danhSach[i].tacGia);
			printf("\nThe loai: %s", danhSach[i].theLoai);
			timThay = 1;
		} 
	}
	
	if(!timThay){
		printf("Khong tim thay sach phu hop!\n");
	}
}

void locTheoKhoangGia(){
	double minGia = 0;
	double maxGia = 0;
	int timThay = 0;
	printf("Nhap khoang gia thap nhat: ");
	scanf("%d", &minGia);
	printf("Nhap khoang gia cao nhat: ");
	scanf("%d", &maxGia);
	getchar();
	
	for(int i = 0; i < soSach; i++){
		if(strcmp(danhSach[i].giaSach >= minGia && danhSach[i].giaSach <= maxGia)){
			printf("\nMa sach: %s", danhSach[i].maSach);
			printf("\nTen sach: %s", danhSach[i].tenSach);
			printf("\nGia sach: %.2lf", danhSach[i].giaSach);
			printf("\nTac gia: %s", danhSach[i].tacGia);
			printf("\nThe loai: %s", danhSach[i].theLoai);
			timThay = 1;
		} 
	}
	
	if(!timThay){
		printf("Khong tim thay sach phu hop!\n");
	}
}

void ketThucLoc(int dem) {
    if (dem == 0) {
        printf("Khong tim thay sach phu hop.\n");
    } else {
        inDuongKe();
        printf("Tim thay %d sach.\n", dem);
    }
}

void timKiem() {
    int chon;
    printf("1. Theo ma sach\n2. Theo ten sach (chua tu khoa)\n0. Quay lai\n");
    chon = docSoNguyen("Chon: ", 0, 2);
    if (chon == 1) {
        char ma[20];
        int vt;
        docChuoi("Nhap ma sach: ", ma, 20);
        vt = timViTriTheoMa(ma);
        if (vt == -1) {
            printf("Khong tim thay sach co ma \"%s\".\n", ma);
        } else {
            inTieuDe();
            inSach(danhSach[vt]);
            ketThucLoc(1);
        }
    } else if (chon == 2) {
        char tu[100];
        int dem = 0, i;
        docChuoi("Nhap ten sach (hoac 1 phan): ", tu, 100);
        for (i = 0; i < soSach; i++) {
            if (chuaChuoi(danhSach[i].tenSach, tu)) {
                if (dem == 0) inTieuDe();
                inSach(danhSach[i]);
                dem++;
            }
        }
        ketThucLoc(dem);
    }
}

/* ===================== SAP XEP / THONG KE ===================== */

void thongKeSach() {
    int tongTon = 0, tongMuon = 0, soHetSach = 0, i;
    double tongGiaTri = 0;
    for (i = 0; i < soSach; i++) {
        tongTon += danhSach[i].soLuongTon;
        tongMuon += danhSach[i].soLuongDangMuon;
        if (danhSach[i].soLuongTon == 0) soHetSach++;
        tongGiaTri += danhSach[i].giaSach * (danhSach[i].soLuongTon + danhSach[i].soLuongDangMuon);
    }
    printf("So dau sach              : %d\n", soSach);
    printf("Tong so cuon tren ke     : %d\n", tongTon);
    printf("Tong so cuon dang muon   : %d\n", tongMuon);
    printf("So dau sach da het       : %d\n", soHetSach);
    printf("Tong gia tri sach        : %.2f\n", tongGiaTri);
}

/* ===================== MENU ===================== */

void hienThiMenu() {
    printf("\n========== QUAN LY SACH THU VIEN ==========\n");
    printf(" 1. Them sach\n");
    printf(" 2. Hien thi danh sach\n");
    printf(" 3. Tim kiem sach\n");
    printf(" 4. Cap nhat sach\n");
    printf(" 5. Xoa sach\n");
    printf(" 6. Muon sach\n");
    printf(" 7. Tra sach\n");
    printf(" 8. Thong ke\n");
    printf(" 0. Thoat\n");
    printf("===========================================\n");
}

int main() {
    int chon;
    do {
        hienThiMenu();
        chon = docSoNguyen("Chon chuc nang: ", 0, 8);
        switch (chon) {
            case 1: themSach(); break;
            case 2: hienThiDanhSach(); break;
            case 3: timKiem(); break;
            case 4: capNhatSach(); break;
            case 5: xoaSach(); break;
            case 6: muonSach(); break;
            case 7: traSach(); break;
            case 8: thongKeSach(); break;
            case 0: printf("Tam biet!\n"); break;
        }
    } while (chon != 0);
    return 0;
}
