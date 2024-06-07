#include "fdanhsachkichban_old.h"
#include "Form/ui_fdanhsachkichban_old.h"
#include "../maxcare/interactsql.h"
#include "../Utils/Utils.h"
#include "qmenu.h"
fDanhSachKichBan_Old::fDanhSachKichBan_Old(QString kichBan,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fDanhSachKichBan_Old), kichBan(kichBan)
{
    ui->setupUi(this);
    ui->dtgvKichBan->hideColumn(1);
    ui->dtgvhanhDong->hideColumn(1);
    connect(ui->dtgvhanhDong, &QTableWidget::customContextMenuRequested, this, &fDanhSachKichBan_Old::showContextMenuHanhDong);
    connect(ui->dtgvKichBan, &QTableWidget::customContextMenuRequested, this, &fDanhSachKichBan_Old::showContextMenuKichBan);
    ui->dtgvhanhDong->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->dtgvKichBan->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->dtgvhanhDong->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->dtgvhanhDong->setSelectionMode(QTableWidget::SingleSelection);
    ui->dtgvKichBan->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->dtgvhanhDong->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->dtgvKichBan->setContextMenuPolicy(Qt::CustomContextMenu);
    LoadKichBan(kichBan);
}

fDanhSachKichBan_Old::~fDanhSachKichBan_Old()
{
    delete ui;
}
void fDanhSachKichBan_Old::LoadKichBan(QString kichban){
    ui->dtgvKichBan->clearContents();
    QVariantList allKichBan = *InteractSQL::GetAllKichBan();
    ui->dtgvKichBan->setRowCount(allKichBan.size());
    if(allKichBan.size() >0){
        ui->dtgvKichBan->setRowCount(allKichBan.size());
        for(int i =0; i<allKichBan.size();i++){
            auto rowMap = allKichBan[i].toMap();
            ui->dtgvKichBan->setItem(i,0, new QTableWidgetItem(i+1));
            ui->dtgvKichBan->setItem(i,1, new QTableWidgetItem(rowMap["Id_KichBan"].toString()));
            ui->dtgvKichBan->setItem(i,2, new QTableWidgetItem(rowMap["TenKichBan"].toString()));
        }
    }
    if(kichban != ""){
        for(int j =0; j<ui->dtgvKichBan->rowCount();j++){
            auto check = ui->dtgvKichBan->item(j,2)->text();
            if(ui->dtgvKichBan->item(j,2)->text() == kichban){
                ui->dtgvKichBan->selectRow(j);
                break;
            }
        }
    }
    LoadHanhDong();
}
void fDanhSachKichBan_Old::LoadHanhDong(){
    try {
        ui->dtgvhanhDong->clearContents();
        if(ui->dtgvKichBan->rowCount()!=0){
            int row = ui->dtgvKichBan->selectedItems().first()->row();
            QVariantList allHanhDongByKichBan = *InteractSQL::GetAllHanhDongByKichBan(ui->dtgvKichBan->item(row,1)->text());
            ui->dtgvhanhDong->setRowCount(allHanhDongByKichBan.size());
            for (int i = 0; i < allHanhDongByKichBan.count(); i++)
            {
                auto rowMap = allHanhDongByKichBan[i].toMap();
                ui->dtgvhanhDong->setItem(i,0, new QTableWidgetItem(i+1));
                ui->dtgvhanhDong->setItem(i,1, new QTableWidgetItem(rowMap["Id_HanhDong"].toString()));
                ui->dtgvhanhDong->setItem(i,2, new QTableWidgetItem(rowMap["TenHanhDong"].toString()));
                ui->dtgvhanhDong->setItem(i,3, new QTableWidgetItem(rowMap["MoTa"].toString()));
            }
        }
    } catch (...) {
    }
}

void fDanhSachKichBan_Old::showContextMenuHanhDong(const QPoint &pos){
    QMenu contextMenu(this);

    QAction *themHanhDong = new QAction(QIcon(":/img/img/plus.png"), "Thêm hành động", this);
    QAction *suaHanhDong = new QAction(QIcon(":/img/img/pen.png"),"Sửa hành động", this);
    QAction *xoaHanhDong = new QAction(QIcon(":/img/img/delete-file.png"),"Xóa hành động", this);
    QAction *nhanBanHanhDong = new QAction(QIcon(":/img/img/copy.png"),"Nhân bản", this);
    contextMenu.addAction(themHanhDong);
    contextMenu.addAction(suaHanhDong);
    contextMenu.addAction(xoaHanhDong);
    contextMenu.addAction(nhanBanHanhDong);
    contextMenu.exec(ui->dtgvhanhDong->viewport()->mapToGlobal(pos));
}
void fDanhSachKichBan_Old::showContextMenuKichBan(const QPoint &pos){
    QMenu contextMenu(this);
    QAction *themKichBan = new QAction(QIcon(":/img/img/add-button.png"), "Thêm kịch bản", this);
    QAction *suaKichBan = new QAction(QIcon(":/img/img/pencil.png"),"Sửa kịch bản", this);
    QAction *xoaKichBan = new QAction(QIcon(":/img/img/delete-file-yellow.png"),"Xóa kịch bản", this);
    QAction *nhanBanKichBan = new QAction(QIcon(":/img/img/copy-yellow.png"),"Nhân bản", this);
    contextMenu.addAction(themKichBan);
    contextMenu.addAction(suaKichBan);
    contextMenu.addAction(xoaKichBan);
    contextMenu.addAction(nhanBanKichBan);
    contextMenu.exec(ui->dtgvKichBan->viewport()->mapToGlobal(pos));
}

void fDanhSachKichBan_Old::on_dtgvKichBan_cellClicked(int row, int column)
{
    LoadHanhDong();
}


void fDanhSachKichBan_Old::on_button5_clicked()
{
    auto selectedItems = ui->dtgvhanhDong->selectedItems();
    if (!selectedItems.isEmpty()) {
        int selectedRow = selectedItems.first()->row();
        if (selectedRow > 0) { // Ensure the selected row is not the first row
            for (int col = 0; col < ui->dtgvhanhDong->columnCount(); ++col) {
                QTableWidgetItem* currentItem = ui->dtgvhanhDong->takeItem(selectedRow, col);
                QTableWidgetItem* aboveItem = ui->dtgvhanhDong->takeItem(selectedRow - 1, col);

                ui->dtgvhanhDong->setItem(selectedRow - 1, col, currentItem);
                ui->dtgvhanhDong->setItem(selectedRow, col, aboveItem);
            }
            ui->dtgvhanhDong->selectRow(selectedRow - 1);
        }
    }
}


void fDanhSachKichBan_Old::on_button4_clicked()
{
    auto selectedItems = ui->dtgvhanhDong->selectedItems();
    if (!selectedItems.isEmpty()) {
        int selectedRow = selectedItems.first()->row();
        if (selectedRow < ui->dtgvhanhDong->rowCount()-1) { // Ensure the selected row is not the first row
            for (int col = 0; col < ui->dtgvhanhDong->columnCount(); ++col) {
                QTableWidgetItem* currentItem = ui->dtgvhanhDong->takeItem(selectedRow, col);
                QTableWidgetItem* belowItem = ui->dtgvhanhDong->takeItem(selectedRow + 1, col);

                ui->dtgvhanhDong->setItem(selectedRow + 1, col, currentItem);
                ui->dtgvhanhDong->setItem(selectedRow, col, belowItem);
            }
            ui->dtgvhanhDong->selectRow(selectedRow + 1);
        }
    }
}

