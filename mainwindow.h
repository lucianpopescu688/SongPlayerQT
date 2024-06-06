#pragma once
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTableView>
#include <QListWidget>
#include <QStandardItemModel>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private:
    void setupUI();
    void connectUI();

    QPushButton *btnAdd, *btnDelete, *btnUpdate, *btnFilter, *btnPlay, *btnNext, *centerButton;
    QLineEdit *leTitle, *leArtist, *leDuration, *lePath;
    QListWidget *playlist;
    QTableView *songsTable;
    QStandardItemModel *model;

private slots:
    void onAddSong();
    void onDeleteSong();
    void onUpdateSong();
    void onFilterSongs();
    void onAddToPlaylist();
    void onPlay();
    void onNextSong();
};
