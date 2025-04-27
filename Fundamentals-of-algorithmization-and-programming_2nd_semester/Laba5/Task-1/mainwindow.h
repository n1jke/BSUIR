#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QButtonGroup>
#include <QMainWindow>
#include <QMap>
#include <QRandomGenerator>
#include <QSpinBox>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
    static const int kTwentyfive = 25;

   public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

   private slots:
    void onLanguageChanged(int index);
    void onInputChanged(const QString& text);
    void updateTimerAndWPM();
    void onOpenFile();
    void startGame();
    void resetGame();
    void loadTextForLanguage(const QString& language);
    void updateTextDisplay();
    void generateRandomText(int wordCount = kTwentyfive);
    void onWordCountChanged(int count);
    void onModeChanged(int modeId);
    void onTimeLimitChanged(int seconds);

   private:
    Ui::MainWindow* ui_;
    QTimer* timer_;
    QMap<QString, QString> sampleTexts_;
    QMap<QString, QStringList> languageWords_;	//word  dictionary for language
    qint64 startTime_ = 0;
    int correctChars_ = 0;
    int incorrectChars_ = 0;
    int totalTypedChars_ = 0;
    int currentPos_ = 0;
    QString currentLanguage_;
    QString currentFullText_;
    bool isTypingActive_ = false;
    const int twentyfive_ = 25;
    int wordCount_ = twentyfive_;
    void applyDarkTheme();
    QString getRandomWord(const QString& language);

    //new input game
    bool isTimedMode_ = false;
    bool timeIsUp_ = false;
    const int kSixteen_ = 60;
    int timeLimit_ = kSixteen_;	 // default
    QButtonGroup* wordCountButtonGroup_ = nullptr;
    QSpinBox* customWordCountInput_ = nullptr;
    QSpinBox* timeLimitInput_ = nullptr;
    QButtonGroup* modeButtonGroup_ = nullptr;
};
#endif	// MAINWINDOW_H
