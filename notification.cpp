#include "notification.h"
#include "ui_notification.h"

notification::notification(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::notification)
{
    ui->setupUi(this);
    connect(ui->btnGrantPermission, &QPushButton::clicked, this, &notification::on_btnGrantPermission_clicked);
    connect(ui->btnDenyPermission, &QPushButton::clicked, this, &notification::on_btnDenyPermission_clicked);
}

notification::~notification()
{
    delete ui;
}
void notification::on_btnGrantPermission_clicked()
{
    emit permissionGranted();
    close();
}

void notification::on_btnDenyPermission_clicked()
{
    emit permissionDenied();
    close();
}
