#include "MainWindow.h"
#include <QApplication>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
    setupUI();
    connectUI();
}

void MainWindow::setupUI() {
    this->setWindowTitle("Playlist Qt");
    this->resize(800, 400);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    QVBoxLayout* leftLayout = new QVBoxLayout();
    QLabel* allSongsLabel = new QLabel("All songs");
    leftLayout->addWidget(allSongsLabel);

    songsTable = new QTableView();
    songsTable->setMinimumSize(400, 150);

    model = new QStandardItemModel();
    model->setHorizontalHeaderLabels({ "Title", "Artist", "Duration", "Path" });
    songsTable->setModel(model);

    leftLayout->addWidget(songsTable);

    QGridLayout* formLayout = new QGridLayout();
    formLayout->addWidget(new QLabel("Title:"), 0, 0);
    leTitle = new QLineEdit();
    formLayout->addWidget(leTitle, 0, 1);

    formLayout->addWidget(new QLabel("Artist:"), 1, 0);
    leArtist = new QLineEdit();
    formLayout->addWidget(leArtist, 1, 1);

    formLayout->addWidget(new QLabel("Duration:"), 2, 0);
    leDuration = new QLineEdit();
    formLayout->addWidget(leDuration, 2, 1);

    formLayout->addWidget(new QLabel("Path:"), 3, 0);
    lePath = new QLineEdit();
    formLayout->addWidget(lePath, 3, 1);

    leftLayout->addLayout(formLayout);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    btnAdd = new QPushButton("Add");
    btnDelete = new QPushButton("Delete");
    btnUpdate = new QPushButton("Update");
    btnFilter = new QPushButton("Filter");
    buttonLayout->addWidget(btnAdd);
    buttonLayout->addWidget(btnDelete);
    buttonLayout->addWidget(btnUpdate);
    buttonLayout->addWidget(btnFilter);
    leftLayout->addLayout(buttonLayout);

    QVBoxLayout* centerButtonLayout = new QVBoxLayout();
    centerButton = new QPushButton(">");
    centerButton->setFixedSize(40, 40);
    centerButtonLayout->addWidget(centerButton);
    centerButtonLayout->setAlignment(centerButton, Qt::AlignCenter);

    QVBoxLayout* rightLayout = new QVBoxLayout();
    QLabel* playlistLabel = new QLabel("Playlist");
    rightLayout->addWidget(playlistLabel);

    playlist = new QListWidget();
    playlist->setMinimumSize(200, 250);
    rightLayout->addWidget(playlist);

    QVBoxLayout* playbackLayout = new QVBoxLayout();
    btnPlay = new QPushButton("Play");
    btnNext = new QPushButton("Next");
    playbackLayout->addWidget(btnPlay);
    playbackLayout->addWidget(btnNext);
    rightLayout->addLayout(playbackLayout);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(centerButtonLayout);
    mainLayout->addLayout(rightLayout);
}

void MainWindow::connectUI() {
    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::onAddSong);
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::onDeleteSong);
    connect(btnUpdate, &QPushButton::clicked, this, &MainWindow::onUpdateSong);
    connect(btnFilter, &QPushButton::clicked, this, &MainWindow::onFilterSongs);
    connect(centerButton, &QPushButton::clicked, this, &MainWindow::onAddToPlaylist);
    connect(btnPlay, &QPushButton::clicked, this, &MainWindow::onPlay);
    connect(btnNext, &QPushButton::clicked, this, &MainWindow::onNextSong);
}

void MainWindow::onAddSong() {
    QList<QStandardItem*> items;
    items.append(new QStandardItem(leTitle->text()));
    items.append(new QStandardItem(leArtist->text()));
    items.append(new QStandardItem(leDuration->text()));
    items.append(new QStandardItem(lePath->text()));

    model->appendRow(items);

    leTitle->clear();
    leArtist->clear();
    leDuration->clear();
    lePath->clear();
}

void MainWindow::onDeleteSong() {
    int selectedRow = songsTable->currentIndex().row();

    if (selectedRow >= 0) {
        model->removeRow(selectedRow);
    }
}

void MainWindow::onUpdateSong() {
    int selectedRow = songsTable->currentIndex().row();

    if (selectedRow >= 0) {
        model->setItem(selectedRow, 0, new QStandardItem(leTitle->text()));
        model->setItem(selectedRow, 1, new QStandardItem(leArtist->text()));
        model->setItem(selectedRow, 2, new QStandardItem(leDuration->text()));
        model->setItem(selectedRow, 3, new QStandardItem(lePath->text()));

        leTitle->clear();
        leArtist->clear();
        leDuration->clear();
        lePath->clear();
    }
}

void MainWindow::onFilterSongs() {
    QString titleFilter = leTitle->text();
    QString artistFilter = leArtist->text();
    QString durationFilter = leDuration->text();
    QString pathFilter = lePath->text();

    for (int row = 0; row < model->rowCount(); ++row) {
        bool match = true;

        if (!titleFilter.isEmpty() && !model->item(row, 0)->text().contains(titleFilter, Qt::CaseInsensitive)) {
            match = false;
        }
        if (!artistFilter.isEmpty() && !model->item(row, 1)->text().contains(artistFilter, Qt::CaseInsensitive)) {
            match = false;
        }
        if (!durationFilter.isEmpty() && !model->item(row, 2)->text().contains(durationFilter, Qt::CaseInsensitive)) {
            match = false;
        }
        if (!pathFilter.isEmpty() && !model->item(row, 3)->text().contains(pathFilter, Qt::CaseInsensitive)) {
            match = false;
        }

        songsTable->setRowHidden(row, !match);
    }
}

void MainWindow::onAddToPlaylist() {
    int selectedRow = songsTable->currentIndex().row();

    if (selectedRow >= 0) {
        QStandardItem* titleItem = model->item(selectedRow, 0);
        QStandardItem* artistItem = model->item(selectedRow, 1);

        QString songDescription = QString("%1 - %2").arg(titleItem->text(), artistItem->text());

        playlist->addItem(new QListWidgetItem(songDescription));
    }
}

void MainWindow::onPlay() {
    if (playlist->count() > 0) {
        QListWidgetItem* currentItem = playlist->item(0);
        if (currentItem) {
            QString song = currentItem->text();
            qDebug() << "Playing: " << song;
        }
    }
}

void MainWindow::onNextSong() {
    if (playlist->count() > 1) {
        delete playlist->takeItem(0);
        onPlay();
    }
}
