# DSA_DT15_Josephus

Đề tài ĐT15: Trò chơi loại trừ vòng tròn và chọn người may mắn (bài toán Josephus), cài đặt bằng danh sách liên kết vòng (Circular Linked List) bằng C++.

## Thành viên nhóm 5

| STT | Họ tên | Phần phụ trách |
|---|---|---|
| 1 | Trần Phương Nghị | Kiểm thử, rò rỉ bộ nhớ, demo, Chương 4 |
| 2 |Phan Xuân Phúc| Node và danh sách liên kết vòng, Chương 2 |
| 3 | Nguyễn Khả Nhật Phi | Thuật toán Josephus, Chương 1 |
| 4 | Trịnh Quốc Nam | Menu console, Chương 3 |
| 5 | Lê Thành Nhân | Đọc/ghi file, tổng hợp báo cáo |

## Cách biên dịch và chạy

g++ main.cpp -o josephus
./josephus

## Cấu trúc thư mục

- CircularList.h: Node và danh sách vòng (thêm, hiển thị, giải phóng)
- Josephus.h: thuật toán loại trừ Josephus
- Menu.h: menu console
- FileIO.h: đọc/ghi file danh sách người chơi và lịch sử
- main.cpp: chương trình chính
