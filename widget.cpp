#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QPushButton>
#include <QLabel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)

{
    ui->setupUi(this);



    connect(ui->button_1, &QPushButton::clicked, this, &Widget::switchpage_2);
    connect(ui->button_2, &QPushButton::clicked, this, &Widget::backtopage_0);
    connect(ui->button_4, &QPushButton::clicked, this, &Widget::backtopage_2);
    connect(ui->button_5, &QPushButton::clicked, this, &Widget::backtopage_2);
    connect(ui->button_6, &QPushButton::clicked, this, &Widget::backtopage_2);
    connect(ui->button_3, &QPushButton::clicked, this, &Widget::navigateToNextPage);
    connect(ui->button_7, &QPushButton::clicked, this, &Widget::backtopage_3);
    connect(ui->button_8, &QPushButton::clicked, this, &Widget::backtopage_4);
    connect(ui->button_9, &QPushButton::clicked, this, &Widget::backtopage_5);
    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::switchpage_2);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &Widget::backtopage_0);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Widget::switchpage_1);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &Widget::switchpage);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &Widget::backtopage_0);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &Widget::backtopage_0);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &Widget::switchtopage_9);
    connect(ui->save, &QPushButton::clicked, this, &Widget::saveDataToDatabase);
    connect(ui->searchButton, &QPushButton::clicked, this, &Widget::retrieveDataFromDatabase);
    connect(ui->updateButton, &QPushButton::clicked, this, &Widget::updateDataInDatabase);
    connect(ui->deleteButton, &QPushButton::clicked, this, &Widget::deleteDataFromDatabase);


    ui->label_10->installEventFilter(this);
    ui->label_21->installEventFilter(this);
    ui->label_7->installEventFilter(this);


}
void Widget::switchpage_1()
{
    ui->stackedWidget->setCurrentWidget(ui->page_1);
    QMessageBox::information(this, "Welcome", "Welcome to the application!");
}
void Widget::backtopage_0()
{
    ui->stackedWidget->setCurrentWidget(ui->page_0);
}
void Widget::switchtopage_9()
{
    ui->stackedWidget->setCurrentWidget(ui->page_9);
}
void Widget::switchpage()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}
void Widget::switchpage_2()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void Widget::backtopage_1()
{
    ui->stackedWidget->setCurrentWidget(ui->page_1);
}

void Widget::backtopage_2()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void Widget::backtopage_3()
{
     ui->stackedWidget->setCurrentWidget(ui->page_3);
}

void Widget::backtopage_4()
{
    ui->stackedWidget->setCurrentWidget(ui->page_4);
}

void Widget::backtopage_5()
{
    ui->stackedWidget->setCurrentWidget(ui->page_5);
}

// Implement the navigateToNextPage slot function
void Widget::navigateToNextPage()
{
    QString userInput = ui->lineEdit->text();

    if (!userInput.isEmpty())
    {
        if (userInput == "Asiga")
        {
            ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->page_3));

            // Set arbitrary temperature and humidity values
            double temperature = 25.5; // in Celsius
            double humidity = 50.0; // in percentage

            // Update QLabel objects with temperature and humidity values
            ui->label_9->setText(QString::number(temperature) + " °C");
            ui->label_17->setText(QString::number(humidity) + " %");

            ui->label_8->setText("LEGEND:");
            ui->label_29->setText("NORMAL");
            ui->label_30->setText("STAND BY");
            ui->label_31->setText("ALERT");

        }
        else if (userInput == "Andanan")
        {
            ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->page_4));
            QMessageBox::warning(this, "ALERT!", "HIGH WATER LEVEL!\n\nEVACUATE IMMEDIATELY!\nFor Emergencies Call: \n          09123456789\n          09876543211", QMessageBox::Ok);

            // Set arbitrary temperature and humidity values
            double temperature = 38.7; // in Celsius
            double humidity = 80.0; // in percentage

            // Update QLabel objects with temperature and humidity values
            ui->label_25->setText(QString::number(temperature) + " °C");
            ui->label_26->setText(QString::number(humidity) + " %");

            ui->label_32->setText("LEGEND:");
            ui->label_36->setText("NORMAL");
            ui->label_37->setText("STAND BY");
            ui->label_38->setText("ALERT");

        }

        else if (userInput == "Bislig")
        {
            ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->page_5));

            // Set arbitrary temperature and humidity values
            double temperature = 36.3; // in Celsius
            double humidity = 60.0; // in percentage

            // Update QLabel objects with temperature and humidity values
            ui->label_22->setText(QString::number(temperature) + " °C");
            ui->label_27->setText(QString::number(humidity) + " %");

            ui->label_39->setText("LEGEND:");
            ui->label_43->setText("NORMAL");
            ui->label_44->setText("STAND BY");
            ui->label_45->setText("ALERT");



        }
        else
        {
            QMessageBox::warning(this, "Invalid Place", "Please enter a valid place to proceed.");
        }
    }
    else
    {
        QMessageBox::warning(this, "Empty Input", "Please enter a place to proceed.");
    }
}

void Widget::saveDataToDatabase()
{
    // Close the default connection if it's open
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        QSqlDatabase::removeDatabase("qt_sql_default_connection");
    }

    // Set up SQLite database
    QSqlDatabase sqlitedb = QSqlDatabase::addDatabase("QSQLITE");
    sqlitedb.setDatabaseName("C:/Users/bkeyw/Documents/QT/5-SqliteConnection/projectfinal/fdatabase.db");

    // Open the database
    if (!sqlitedb.open()) {
        QMessageBox::critical(this, "Error", "An error occurred while opening the database: " + sqlitedb.lastError().text());
        qDebug() << "Failed to open database.";
        return;

    }
    qDebug() << "Database opened successfully.";
    // Create users table if it doesn't exist
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS users ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name TEXT,"
                    "age INTEGER,"
                    "address TEXT"
                    ")")) {
        QMessageBox::critical(nullptr, "Error", "Failed to create table: " + query.lastError().text());
         qDebug() << "Failed to create table: " << query.lastError().text();
        return;
    } else {
        qDebug() << "Table users created successfully.";
    }

    // Retrieve data from input fields
    QString name = ui->name->text();
    QString age = ui->age->text();
    QString address = ui->address->text();

    // Check if data already exists
    query.prepare("SELECT COUNT(*) FROM users WHERE Name = :name AND Age = :age AND Address = :address");
    query.bindValue(":name", name);
    query.bindValue(":age", age);
    query.bindValue(":address", address);
    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this, "Database error", "Error checking for existing data: " + query.lastError().text());
        qDebug() << "Error checking for existing data: " << query.lastError().text();
        return;
    }
    int count = query.value(0).toInt();
    if (count > 0) {
        QMessageBox::warning(this, "Duplicate Data", "Data already exists in the database.");
        return;
    }

    // Insert data into the database
    query.prepare("INSERT INTO users (Name, Age, Address) VALUES (:name, :age, :address)");
    query.bindValue(":name", name);
    query.bindValue(":age", age);
    query.bindValue(":address", address);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database error", "Error inserting data: " + query.lastError().text());
        qDebug() << "Error inserting data: " << query.lastError().text();
    } else {
        qDebug() << "Data added to database.";
        QMessageBox::information(this, "Database added", "Data added to database");
        ui->name->clear();
        ui->age->clear();
        ui->address->clear();
    }
}

void Widget::labelClicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->page_6));

}
void Widget::labelClicked1()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->page_7));

}
void Widget::labelClicked2()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->page_8));

}

bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->label_10 && event->type() == QEvent::MouseButtonPress) {
        labelClicked();
        return true;
    }
    else if (obj == ui->label_21 && event->type() == QEvent::MouseButtonPress) {
        labelClicked1();
        return true;
    }
    else if (obj == ui->label_7 && event->type() == QEvent::MouseButtonPress) {
        labelClicked2();
        return true;
    }
    return QWidget::eventFilter(obj, event);
}

void Widget::retrieveDataFromDatabase()
{
    QString name = ui->searchName->text();

    QSqlDatabase sqlitedb = QSqlDatabase::addDatabase("QSQLITE");
    sqlitedb.setDatabaseName("C:/Users/bkeyw/Documents/QT/5-SqliteConnection/projectfinal/fdatabase.db");

    if (!sqlitedb.open()) {
        QMessageBox::critical(this, "Database error", "Error opening the database: " + sqlitedb.lastError().text());
        qDebug() << "Error opening the database: " << sqlitedb.lastError().text();
        return;
    }
    // Query the database for the user with the given name
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE Name = :name");
    query.bindValue(":name", name);
    if (!query.exec()) {
        QMessageBox::critical(this, "Database error", "Error retrieving data: " + query.lastError().text());
        qDebug() << "Error retrieving data: " << query.lastError().text();
        return;
    }

    ui->dataTable->clearContents();
    ui->dataTable->setRowCount(0);


    // Set column headers
    QStringList headers;
    headers << "id" << "Name" << "Age" << "Address";
    ui->dataTable->setColumnCount(4);
    ui->dataTable->setHorizontalHeaderLabels(headers);

    // Populate the table with retrieved data
    int row = 0;
    while (query.next()) {
        ui->dataTable->insertRow(row);
        ui->dataTable->setItem(row, 0, new QTableWidgetItem(query.value("id").toString()));
        ui->dataTable->setItem(row, 1, new QTableWidgetItem(query.value("Name").toString()));
        ui->dataTable->setItem(row, 2, new QTableWidgetItem(query.value("Age").toString()));
        ui->dataTable->setItem(row, 3, new QTableWidgetItem(query.value("Address").toString()));
        row++;
    }
    if (row == 0) {
        QMessageBox::information(this, "Search Result", "No records found for the given name.");
    }

    // Resize columns to contents
    ui->dataTable->resizeColumnsToContents();
}

void Widget::updateDataInDatabase()
{
    int row = ui->dataTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Error", "Please select a row to update.");
        return;
    }

    QString id = ui->dataTable->item(row, 0)->text(); // Assuming id is stored in the first column
    QString name = ui->dataTable->item(row, 1)->text(); // Assuming name is stored in the second column
    QString age = ui->dataTable->item(row, 2)->text(); // Assuming age is stored in the third column
    QString address = ui->dataTable->item(row, 3)->text(); // Assuming address is stored in the fourth column

    QMessageBox::StandardButton confirmUpdate;
    confirmUpdate = QMessageBox::question(this, "Confirm Update", "Are you sure you want to update this record?",
                                          QMessageBox::Yes|QMessageBox::No);
    if (confirmUpdate == QMessageBox::No)
        return;
    // Update the data in the database for the specified id
    QSqlQuery query;
    query.prepare("UPDATE users SET Name = :name, Age = :age, Address = :address WHERE id = :id");
    query.bindValue(":name", name);
    query.bindValue(":age", age);
    query.bindValue(":address", address);
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database error", "Error updating data: " + query.lastError().text());
        qDebug() << "Error updating data: " << query.lastError().text();
        return;
    }

    QMessageBox::information(this, "Database updated", "Data updated successfully");
}

void Widget::deleteDataFromDatabase()
{
    int row = ui->dataTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Error", "Please select a row to delete.");
        return;
    }

    QString id = ui->dataTable->item(row, 0)->text(); // Assuming id is stored in the first column

    QMessageBox::StandardButton confirmDelete;
    confirmDelete = QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this record?",
                                          QMessageBox::Yes|QMessageBox::No);
    if (confirmDelete == QMessageBox::No)
        return;
    // Delete the data from the database for the specified id
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        QMessageBox::critical(this, "Database error", "Error deleting data: " + query.lastError().text());
        qDebug() << "Error deleting data: " << query.lastError().text();
        return;
    }

    QMessageBox::information(this, "Database updated", "Data deleted successfully");
}

Widget::~Widget()
{
    delete ui;
}





