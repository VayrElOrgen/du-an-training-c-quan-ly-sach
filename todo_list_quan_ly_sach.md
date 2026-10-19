# TO-DO LIST: XÂY DỰNG CHƯƠNG TRÌNH QUẢN LÝ SÁCH

## TỔNG QUAN TIẾN ĐỘ

| Giai đoạn | Nội dung công việc | Số đầu việc | Trạng thái |
| :---: | :--- | :---: | :---: |
| 1 | Phân tích đề tài và yêu cầu nghiệp vụ | 4 | [] |
| 2 | Thiết kế cấu trúc dữ liệu Sach | 3 | [] |
| 3 | Thiết kế menu và chương trình chính | 5 | [] |
| 4 | Lập trình thêm và hiển thị sách | 6 | [] |
| 5 | Lập trình tìm kiếm, cập nhật và xóa | 5 | [] |
| 6 | Lập trình các chức năng lọc sách | 10 | [] |
| 7 | Lập trình sắp xếp và thống kê | 2 | [] |
| 8 | Kiểm thử từng chức năng | 15 | [] |
| 9 | Tích hợp, hoàn thiện báo cáo và demo | 4 | [] |

## RÀNG BUỘC

| STT | Dữ liệu | Kiểu dữ liệu | Ràng buộc |
| :---: | :--- | :--- | :--- |
| 1 | Mã sách | char maSach[20] | Không rỗng, không trùng |
| 2 | Tên sách | char tenSach[100] | Không rỗng |
| 3 | Tác giả | char tacGia[100] | Không rỗng |
| 4 | Thể loại | char theLoai[50] | Không rỗng |
| 5 | Nhà xuất bản | char nhaXuatBan[100] | Không rỗng |
| 6 | Năm xuất bản | int namXuatBan | Năm hợp lệ, không vượt quá năm hiện tại |
| 7 | Giá sách | double giaSach | Không âm |
| 8 | Số lượng | int soLuong | Số nguyên không âm |

### Mức ưu tiên chức năng

| STT | Chức năng | Mức ưu tiên |
| :---: | :--- | :---: |
| 1 | Thêm sách | **BẮT BUỘC** |
| 2 | Hiển thị sách | **BẮT BUỘC** |
| 3 | Tìm kiếm sách | **BẮT BUỘC** |
| 4 | Lọc sách | **BẮT BUỘC** |
| 5 | Cập nhật sách | **BẮT BUỘC** |
| 6 | Xóa sách | **BẮT BUỘC** |
| 7 | Sắp xếp sách | Nên có |
| 8 | Thống kê sách | Nên có |
| 9 | Lưu dữ liệu | Nâng cao |
| 10 | Thoát chương trình | **BẮT BUỘC** |

Quy ước trong danh sách: **việc in đậm = thuộc chức năng Bắt buộc**; việc thường gắn nhãn `[Nên có]` hoặc `[Nâng cao]`.

---

## GIAI ĐOẠN 1: Phân tích đề tài và yêu cầu nghiệp vụ

**Kết quả cần đạt:** Danh sách chức năng và ràng buộc

- [ ] **Liệt kê 10 chức năng của chương trình và mức ưu tiên (mục 3.1)**
- [x] **Xác định 7 tiêu chí lọc sách: thể loại, tác giả, nhà xuất bản, khoảng giá, năm xuất bản, số lượng, lọc kết hợp (mục 3.2)**
- [x] **Ghi nhận 5 quy tắc nghiệp vụ của lọc: báo không tìm thấy khi không có kết quả; không thay đổi dữ liệu gốc; lọc kết hợp mặc định AND; giá tối thiểu không lớn hơn giá tối đa; dữ liệu nhập đúng kiểu và trong giới hạn**
- [x] **Tổng hợp ràng buộc của 8 trường dữ liệu (mục 4.1): không rỗng, không trùng mã, năm hợp lệ, giá và số lượng không âm**

---

## GIAI ĐOẠN 2: Thiết kế cấu trúc dữ liệu Sach

**Kết quả cần đạt:** Hoàn thiện mô hình dữ liệu

- [x] **Xác nhận kiểu dữ liệu của mã sách (xem mục "Lưu ý cần xác nhận")**
- [x] **Khai báo `typedef struct Sach` gồm 8 trường: mã sách, tên sách, tác giả, thể loại, nhà xuất bản, năm xuất bản, giá sách, số lượng**
- [x] **Khai báo `#define MAX 1000`, mảng `Sach danhSach[MAX]` và biến `int soSach = 0`**

---

## GIAI ĐOẠN 3: Thiết kế menu và chương trình chính

**Kết quả cần đạt:** Điều hướng được các chức năng

- [X] **`hienThiMenu()`: hiển thị menu chính gồm 10 lựa chọn**
- [x] **Viết vòng lặp menu chính trong `main()`: gọi hàm tương ứng với lựa chọn, quay lại menu cho đến khi người dùng chọn thoát**
- [ ] **Thiết kế nội dung menu lọc gồm 8 lựa chọn**
- [x] **Xử lý nhập lựa chọn menu không hợp lệ: thông báo và yêu cầu nhập lại**
- [x] **Chức năng 10, Thoát chương trình: kết thúc chương trình an toàn**

---

## GIAI ĐOẠN 4: Lập trình thêm và hiển thị sách

**Kết quả cần đạt:** Quản lý danh sách cơ bản

- [x] **`nhapSach()`: nhập thông tin một sách (tên có dấu cách phải nhận đủ chuỗi)**
- [x] **`kiemTraDuLieu()`: kiểm tra dữ liệu đầu vào (không rỗng, năm hợp lệ, giá và số lượng không âm)**
- [x] **`kiemTraMaSach()`: kiểm tra mã sách trùng**
- [x] **`themSach()`: thêm sách vào danh sách sau khi dữ liệu hợp lệ và mã không trùng**
- [x] **`hienThiDanhSach()`: hiển thị toàn bộ sách**
- [x] **Xử lý danh sách rỗng khi hiển thị: thông báo danh sách chưa có sách**

---

## GIAI ĐOẠN 5: Lập trình tìm kiếm, cập nhật và xóa

**Kết quả cần đạt:** Hoàn thiện CRUD

- [x] **`timSachTheoMa()`: tìm vị trí sách theo mã (báo không tìm thấy nếu mã không tồn tại)**
- [x] **`timSachTheoTen()`: tìm sách theo tên**
- [x] **`timSachTheoTacGia()`: tìm sách theo tác giả**
- [x] **`capNhatSach()`: cập nhật thông tin sách đã tồn tại (kiểm tra dữ liệu trước khi cập nhật)**
- [x] **`xoaSach()`: xóa sách theo mã (đúng ở đầu, giữa, cuối mảng; dồn mảng lại sau khi xóa)**

---

## GIAI ĐOẠN 6: Lập trình các chức năng lọc sách

**Kết quả cần đạt:** Lọc đơn và lọc kết hợp

- [ ] **`locSach()`: hiển thị menu lọc sách và gọi hàm lọc tương ứng**
- [ ] **`locTheoTheLoai()`: lọc sách theo thể loại**
- [ ] **`locTheoTacGia()`: lọc sách theo tác giả**
- [ ] **`locTheoNhaXuatBan()`: lọc sách theo nhà xuất bản**
- [ ] **`locTheoKhoangGia()`: lọc theo khoảng giá (giá tối thiểu không được lớn hơn giá tối đa)**
- [ ] **`locTheoNamXuatBan()`: lọc theo một năm hoặc khoảng năm**
- [ ] **`locTheoSoLuong()`: lọc sách còn hàng, hết hàng hoặc có số lượng dưới ngưỡng**
- [ ] **`locKetHop()`: lọc kết hợp nhiều điều kiện, mặc định tất cả phải thỏa mãn (AND)**
- [ ] **Đảm bảo mọi hàm lọc không làm thay đổi dữ liệu gốc**
- [ ] **Đảm bảo mọi hàm lọc thông báo không tìm thấy kết quả khi không có sách phù hợp, và không lỗi khi danh sách rỗng**

---

## GIAI ĐOẠN 7: Lập trình sắp xếp và thống kê

**Kết quả cần đạt:** Hoàn thiện chức năng mở rộng

- [ ] `[Nên có]` `sapXepSach()`: sắp xếp danh sách theo tên, giá hoặc số lượng
- [x] `[Nên có]` `thongKeSach()`: thống kê số đầu sách, tổng số cuốn và tổng giá trị kho


---

## GIAI ĐOẠN 8: Kiểm thử từng chức năng

**Kết quả cần đạt:** Phát hiện và sửa lỗi

- [ ] **TC1: Thêm sách với dữ liệu hợp lệ → Thêm thành công**
- [ ] **TC2: Thêm sách có mã trùng → Thông báo lỗi, không thêm**
- [ ] **TC3: Nhập giá âm hoặc số lượng âm → Từ chối dữ liệu không hợp lệ**
- [ ] **TC4: Hiển thị khi danh sách rỗng → Thông báo danh sách chưa có sách**
- [ ] **TC5: Tìm mã sách không tồn tại → Thông báo không tìm thấy**
- [ ] **TC6: Cập nhật sách theo mã hợp lệ → Thông tin được cập nhật**
- [ ] **TC7: Xóa sách ở đầu, giữa hoặc cuối mảng → Xóa đúng sách, danh sách được sắp lại**
- [ ] **TC8: Lọc theo thể loại có kết quả → Hiển thị đúng các sách phù hợp**
- [ ] **TC9: Lọc theo khoảng giá không có kết quả → Thông báo không có sách phù hợp**
- [ ] **TC10: Lọc kết hợp nhiều tiêu chí → Chỉ hiển thị sách thỏa mãn tất cả điều kiện**
- [ ] **TC11: Lọc khi danh sách rỗng → Không phát sinh lỗi**
- [ ] `[Nên có]` TC12: Sắp xếp theo tên hoặc giá → Danh sách đúng thứ tự
- [ ] `[Nâng cao]` TC13: Lưu và đọc dữ liệu từ file → Dữ liệu được khôi phục chính xác
- [ ] **TC14: Nhập lựa chọn menu không hợp lệ → Thông báo và yêu cầu nhập lại**
- [ ] **TC15: Nhập tên sách có dấu cách → Chương trình nhận đầy đủ chuỗi**

---

## GIAI ĐOẠN 9: Tích hợp, hoàn thiện báo cáo và demo

**Kết quả cần đạt:** Bản project hoàn chỉnh

- [ ] **Tích hợp các nhóm hàm (quản lý sách, xử lý danh sách, đọc ghi file) vào chương trình chính**
- [ ] **Đối chiếu chương trình với 9 tiêu chí hoàn thành bên dưới**
- [ ] **Hoàn thiện báo cáo kết quả kiểm thử**
- [ ] **Chuẩn bị demo: mỗi thành viên giải thích được hoạt động của các hàm chính**

---

## TIÊU CHÍ HOÀN THÀNH PROJECT

- [ ] 1. Các chức năng bắt buộc hoạt động chính xác.
- [ ] 2. Dữ liệu được kiểm tra trước khi thêm và cập nhật.
- [ ] 3. Mã sách không bị trùng.
- [ ] 4. Chức năng lọc trả về đúng kết quả, không thay đổi danh sách gốc.
- [ ] 5. Chương trình xử lý được danh sách rỗng và dữ liệu đầu vào sai.
- [ ] 6. Code được chia hàm hợp lý, dễ đọc và dễ bảo trì.
- [ ] 7. Chức năng đọc ghi file hoạt động nếu thuộc phạm vi yêu cầu.
- [ ] 8. Chương trình được kiểm thử và có báo cáo kết quả.
- [ ] 9. Nhóm có thể giải thích được các hoạt động của các hàm chính khi demo.
