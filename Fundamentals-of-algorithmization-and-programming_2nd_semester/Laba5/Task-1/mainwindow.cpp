#include "mainwindow.h"
#include <QApplication>
#include <QButtonGroup>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFontDatabase>
#include <QMessageBox>
#include <QPalette>
#include <QRadioButton>
#include <QSpinBox>
#include <QStyleFactory>
#include <QTextStream>
#include <QTimer>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
    ui_->setupUi(this);

    // apply dark theme
    applyDarkTheme();

    timer_ = new QTimer(this);
    const int thousand = 1000;
    timer_->setInterval(thousand);

    sampleTexts_["Deutsch"] =
        "Der schnelle braune Fuchs springt über den faulen Hund. Alle Menschen "
        "sind frei und gleich an Würde und Rechten geboren.";
    sampleTexts_["français"] =
        "Le rapide renard brun saute par-dessus le chien paresseux. Tous les "
        "êtres humains naissent libres et égaux en dignité et en droits.";
    sampleTexts_["العربية"] =
        "الثعلب البني السريع يقفز فوق الكلب الكسول. يولد جميع البشر أحراراً "
        "ومتساوين في الكرامة والحقوق.";
    sampleTexts_["中文"] =
        "快速的棕色狐狸跳过懒狗。人人生而自由，在尊严和权利上一律平等。";
    sampleTexts_["Беларускі"] =
        "Хуткі карычневы ліс скача праз гультайскага сабаку. Усе людзі "
        "нараджаюцца свабоднымі і роўнымі ў сваёй годнасці і правах.";
    sampleTexts_["עבריתעברית"] =
        "השועל החום המהיר קופץ מעל הכלב העצלן. כל בני האדם נולדו חופשיים "
        "ושווים בכבוד ובזכויות.";
    sampleTexts_["Русский"] =
        "Быстрая коричневая лиса прыгает через ленивую собаку. Все люди "
        "рождаются свободными и равными в своем достоинстве и правах.";
    sampleTexts_["English"] =
        "The quick brown fox jumps over the lazy dog. All human beings are "
        "born free and equal in dignity and rights.";


    languageWords_["Deutsch"] = {
        "und",	  "ich",	"zu",		"der",	 "die",	   "das",	"nicht",
        "mit",	  "sich",	"er",		"ein",	 "sie",	   "auch",	"auf",
        "für",	  "es",		"an",		"als",	 "können", "haben", "sein",
        "werden", "bei",	"durch",	"über",	 "wenn",   "nach",	"vor",
        "um",	  "unter",	"doch",		"hier",	 "mir",	   "nur",	"von",
        "wir",	  "mich",	"noch",		"zur",	 "du",	   "aus",	"gut",
        "dass",	  "mehr",	"schon",	"sehr",	 "alle",   "so",	"oder",
        "aber",	  "Mann",	"Zeit",		"Leben", "Frau",   "Land",	"Kind",
        "Welt",	  "Haus",	"Arbeit",	"Jahr",	 "Tag",	   "Teil",	"Stadt",
        "Recht",  "Seite",	"Mensch",	"Weg",	 "Fall",   "Ende",	"Frage",
        "Herr",	  "Stelle", "Beispiel", "Grund"};

    languageWords_["Русский"] = {
        "я",	   "и",		 "в",		"не",		 "на",		"что",
        "это",	   "он",	 "с",		"как",		 "а",		"то",
        "все",	   "она",	 "так",		"его",		 "но",		"да",
        "ты",	   "к",		 "у",		"же",		 "вы",		"за",
        "бы",	   "по",	 "только",	"ее",		 "мне",		"было",
        "вот",	   "от",	 "меня",	"еще",		 "нет",		"о",
        "из",	   "ему",	 "теперь",	"когда",	 "даже",	"ну",
        "вдруг",   "ли",	 "если",	"уже",		 "или",		"ни",
        "быть",	   "был",	 "него",	"до",		 "время",	"рука",
        "работа",  "слово",	 "место",	"дело",		 "жизнь",	"день",
        "человек", "вопрос", "лицо",	"глаз",		 "страна",	"мир",
        "случай",  "голова", "ребенок", "сила",		 "конец",	"вид",
        "система", "часть",	 "город",	"отношение", "женщина", "деньги",
        "земля",   "машина"};

    languageWords_["français"] = {
        "et",	 "à",	   "de",	 "je",		"est",		"pas",	  "le",
        "vous",	 "la",	   "tu",	 "que",		"un",		"il",	  "dans",
        "pour",	 "ce",	   "en",	 "du",		"une",		"qui",	  "elle",
        "nous",	 "des",	   "les",	 "ça",		"mais",		"on",	  "au",
        "plus",	 "mon",	   "sur",	 "ne",		"se",		"me",	  "quoi",
        "lui",	 "faire",  "avec",	 "tout",	"son",		"te",	  "bien",
        "si",	 "y",	   "même",	 "était",	"suis",		"comme",  "être",
        "ou",	 "temps",  "homme",	 "femme",	"jour",		"pays",	  "monde",
        "vie",	 "main",   "enfant", "premier", "travail",	"moment", "année",
        "porte", "fait",   "chose",	 "raison",	"regard",	"place",  "face",
        "façon", "maison", "gens",	 "mot",		"histoire", "ville",  "partie",
        "point"};

    languageWords_["Беларускі"] = {
        "і",	   "ў",		  "не",		 "на",	  "што",   "гэта",	 "я",
        "ён",	   "з",		  "як",		 "а",	  "тое",   "усе",	 "яна",
        "так",	   "яго",	  "але",	 "так",	  "ты",	   "да",	 "у",
        "ж",	   "вы",	  "за",		 "бы",	  "па",	   "толькі", "яе",
        "мне",	   "было",	  "вось",	 "ад",	  "мяне",  "яшчэ",	 "няма",
        "аб",	   "з",		  "яму",	 "цяпер", "калі",  "нават",	 "ну",
        "раптам",  "ці",	  "калі",	 "ужо",	  "або",   "ні",	 "быць",
        "час",	   "рука",	  "работа",	 "слова", "месца", "справа", "жыццё",
        "дзень",   "чалавек", "пытанне", "твар",  "вока",  "краіна", "свет",
        "выпадак", "галава",  "дзіця",	 "сіла",  "канец", "від",	 "сістэма",
        "частка",  "горад",	  "адносіны"};

    languageWords_["العربية"] = {
        "في",	"على",	 "أن",	 "إلى",	 "من",	  "هو",	  "و",	   "هي",
        "مع",	"عن",	 "لا",	 "ما",	 "كان",	  "هذا",  "أو",	   "كل",
        "إذا",	"كانت",	 "هذه",	 "ثم",	 "هناك",  "يكون", "واحد",  "بعد",
        "حول",	"حتى",	 "قبل",	 "تحت",	 "عندما", "له",	  "أنت",   "أنا",
        "الذي", "التي",	 "فوق",	 "هم",	 "لكن",	  "نحن",  "أين",   "لماذا",
        "كيف",	"يا",	 "ماذا", "لقد",	 "لديه",  "لك",	  "بين",   "شيء",
        "قد",	"اليوم", "وقت",	 "رجل",	 "امرأة", "يوم",  "بلد",   "عالم",
        "حياة", "يد",	 "طفل",	 "أول",	 "عمل",	  "لحظة", "سنة",   "باب",
        "فعل",	"شيء",	 "سبب",	 "نظرة", "مكان",  "وجه",  "طريقة", "منزل"};

    languageWords_["中文"] = {
        "的",  "一",   "是",   "不",   "了",   "在",   "人",   "我",   "有",
        "他",  "这",   "个",   "们",   "中",   "来",   "上",   "大",   "为",
        "和",  "国",   "地",   "到",   "以",   "说",   "时",   "要",   "就",
        "出",  "会",   "可",   "也",   "你",   "对",   "生",   "能",   "而",
        "子",  "那",   "得",   "于",   "着",   "下",   "自",   "之",   "年",
        "过",  "发",   "后",   "作",   "里",   "用",   "时间", "男人", "女人",
        "日",  "国家", "世界", "生活", "手",   "孩子", "第一", "工作", "时刻",
        "年",  "门",   "事实", "东西", "原因", "看",   "地方", "脸",   "方式",
        "房子"};

    languageWords_["עברית"] = {
        "אני",	"אתה",	 "הוא",	  "היא", "אנחנו", "אתם",  "הם",	   "זה",
        "לא",	"כן",	 "של",	  "עם",	 "את",	  "על",	  "יש",	   "אין",
        "מה",	"מי",	 "איפה",  "למה", "כמה",	  "ב",	  "ל",	   "מ",
        "כ",	"שלי",	 "שלך",	  "טוב", "רע",	  "גדול", "קטן",   "עכשיו",
        "אחר",	"יותר",	 "פחות",  "כל",	 "הרבה",  "מעט",  "רק",	   "גם",
        "אבל",	"או",	 "כי",	  "לא",	 "אולי",  "תודה", "בבקשה", "שלום",
        "זמן",	"איש",	 "אישה",  "יום", "ארץ",	  "עולם", "חיים",  "יד",
        "ילד",	"ראשון", "עבודה", "רגע", "שנה",	  "דלת",  "דבר",   "דבר",
        "סיבה", "מבט"};

    languageWords_["English"] = {
        "the",	"be",	 "to",	   "of",	 "and",		"a",	   "in",
        "that", "have",	 "I",	   "it",	 "for",		"not",	   "on",
        "with", "he",	 "as",	   "you",	 "do",		"at",	   "this",
        "but",	"his",	 "by",	   "from",	 "they",	"we",	   "say",
        "her",	"she",	 "or",	   "an",	 "will",	"my",	   "one",
        "all",	"would", "there",  "their",	 "what",	"so",	   "up",
        "out",	"if",	 "about",  "who",	 "get",		"which",   "go",
        "me",	"time",	 "man",	   "woman",	 "day",		"country", "world",
        "life", "hand",	 "child",  "first",	 "work",	"moment",  "year",
        "door", "fact",	 "thing",  "reason", "look",	"place",   "face",
        "way",	"house", "people", "word",	 "history", "city",	   "part"};

    // debug dicy
    for (const QString& lang :
         QStringList({"English", "Русский", "Deutsch", "français", "العربية",
                      "中文", "Беларускі", "עברית"})) {
        if (!languageWords_.contains(lang)) {
            qDebug() << "Error: Dictionary for" << lang << "not initialized!";
        } else {
            qDebug() << "Dictionary for" << lang << "contains"
                     << languageWords_[lang].size() << "words";
        }
    }

    // fill the language dropdown
    ui_->languageComboBox->addItem("English");
    ui_->languageComboBox->addItem("Русский");
    ui_->languageComboBox->addItem("Немецкий");
    ui_->languageComboBox->addItem("Французский");
    ui_->languageComboBox->addItem("Арабский");
    ui_->languageComboBox->addItem("Китайский");
    ui_->languageComboBox->addItem("Белорусский");
    ui_->languageComboBox->addItem("Иврит");
    ui_->languageComboBox->setVisible(true);

    QHBoxLayout* control_layout = new QHBoxLayout();

    //  refresh button
    QPushButton* refresh_btn =
        new QPushButton(QIcon::fromTheme("view-refresh"), "", this);
    refresh_btn->setStyleSheet(
        "background-color: #282C34; color: #56B6C2; border: none;");
    refresh_btn->setToolTip("Refresh");
    const int th = 30;
    refresh_btn->setMaximumWidth(th);

    // selection buttons
    QPushButton* words_btn = new QPushButton("words", this);
    words_btn->setStyleSheet(
        "background-color: #282C34; color: white; border: none;");
    words_btn->setCheckable(true);
    words_btn->setChecked(true);

    QPushButton* timed_btn = new QPushButton("timed", this);
    timed_btn->setStyleSheet(
        "background-color: #282C34; color: #ABB2BF; border: none;");
    timed_btn->setCheckable(true);

    // group  mode selection
    QButtonGroup* mode_group = new QButtonGroup(this);
    mode_group->addButton(words_btn, 0);
    mode_group->addButton(timed_btn, 1);

    //  number input fields
    QSpinBox* custom_word_count_input = new QSpinBox(this);
    const int fhundred = 500;
    const int twfive = 25;
    const int five = 5;
    custom_word_count_input->setRange(five, fhundred);
    custom_word_count_input->setValue(twfive);
    custom_word_count_input->setStyleSheet(
        "background-color: #282C34; color: #61AFEF; border: none; "
        "border-bottom: 1px solid #61AFEF;");
    custom_word_count_input->setPrefix("words: ");

    QSpinBox* time_limit_input = new QSpinBox(this);
    const int thrhundred = 300;
    const int sxteem = 60;
    const int fifrteen = 15;
    time_limit_input->setRange(fifrteen, thrhundred);
    time_limit_input->setValue(sxteem);
    time_limit_input->setSingleStep(fifrteen);
    time_limit_input->setStyleSheet(
        "background-color: #282C34; color: #61AFEF; border: none; "
        "border-bottom: 1px solid #61AFEF;");
    time_limit_input->setPrefix("seconds: ");
    time_limit_input->hide();

    // word count in layout
    QButtonGroup* word_count_group = new QButtonGroup(this);
    QHBoxLayout* word_count_layout = new QHBoxLayout();

    //  input fields in layout
    word_count_layout->addWidget(custom_word_count_input);
    word_count_layout->addWidget(time_limit_input);
    word_count_layout->addStretch();

    //  all controls to control layout
    control_layout->addWidget(refresh_btn);
    control_layout->addWidget(ui_->languageComboBox);
    const int twenty = 20;
    control_layout->addSpacing(twenty);
    control_layout->addWidget(words_btn);
    control_layout->addWidget(timed_btn);
    control_layout->addSpacing(twenty);
    control_layout->addLayout(word_count_layout);
    control_layout->addStretch();

    // find and modify  layout
    QVBoxLayout* main_layout = findChild<QVBoxLayout*>("verticalLayout");


    if (main_layout) {
        // create a new widget for the control panel and add it to the main layout
        QWidget* control_widget = new QWidget(this);
        control_widget->setLayout(control_layout);
        main_layout->insertWidget(0, control_widget);
    }

    // connect signals and slots
    connect(refresh_btn, &QPushButton::clicked, this, &MainWindow::resetGame);
    connect(mode_group, SIGNAL(idClicked(int)), this, SLOT(onModeChanged(int)));
    connect(custom_word_count_input, SIGNAL(valueChanged(int)), this,
            SLOT(onWordCountChanged(int)));
    connect(time_limit_input, SIGNAL(valueChanged(int)), this,
            SLOT(onTimeLimitChanged(int)));
    connect(ui_->languageComboBox, SIGNAL(currentIndexChanged(int)), this,
            SLOT(onLanguageChanged(int)));
    connect(ui_->inputLineEdit, SIGNAL(textChanged(const QString&)), this,
            SLOT(onInputChanged(const QString&)));
    connect(ui_->actionOpen, SIGNAL(triggered()), this, SLOT(onOpenFile()));
    connect(ui_->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(timer_, SIGNAL(timeout()), this, SLOT(updateTimerAndWPM()));

    // store references to controls
    wordCountButtonGroup_ = word_count_group;
    customWordCountInput_ = custom_word_count_input;
    timeLimitInput_ = time_limit_input;
    modeButtonGroup_ = mode_group;

    // initialize game
    resetGame();
}

void MainWindow::applyDarkTheme() {
    QApplication::setStyle(QStyleFactory::create("Fusion"));


    const int k_window_r = 40;
    const int k_window_g = 44;
    const int k_window_b = 52;

    const int k_base_r = 30;
    const int k_base_g = 34;
    const int k_base_b = 42;

    const int k_alternate_base_r = 50;
    const int k_alternate_base_g = 54;
    const int k_alternate_base_b = 62;

    const int k_link_r = 97;
    const int k_link_g = 175;
    const int k_link_b = 239;
    QPalette dark_palette;
    dark_palette.setColor(QPalette::Window,
                          QColor(k_window_r, k_window_g, k_window_b));
    dark_palette.setColor(QPalette::WindowText, Qt::white);
    dark_palette.setColor(QPalette::Base, QColor(k_base_r, k_base_g, k_base_b));
    dark_palette.setColor(
        QPalette::AlternateBase,
        QColor(k_alternate_base_r, k_alternate_base_g, k_alternate_base_b));
    dark_palette.setColor(QPalette::ToolTipBase, Qt::white);
    dark_palette.setColor(QPalette::ToolTipText, Qt::white);
    dark_palette.setColor(QPalette::Text, Qt::white);
    dark_palette.setColor(QPalette::Button,
                          QColor(k_window_r, k_window_g, k_window_b));
    dark_palette.setColor(QPalette::ButtonText, Qt::white);
    dark_palette.setColor(QPalette::BrightText, Qt::red);
    dark_palette.setColor(QPalette::Link, QColor(k_link_r, k_link_g, k_link_b));
    dark_palette.setColor(QPalette::Highlight,
                          QColor(k_link_r, k_link_g, k_link_b));
    dark_palette.setColor(QPalette::HighlightedText, Qt::black);


    QApplication::setPalette(dark_palette);

    qApp->setStyleSheet(
        "QMainWindow { background-color: #282C34; }"
        "QTextEdit { background-color: #282C34; color: #ABB2BF; border: none; }"
        "QLineEdit { background-color: #282C34; color: #ABB2BF; border: none; "
        "border-bottom: 1px solid #3E4451; }"
        "QPushButton { background-color: #3E4451; color: white; border: none; "
        "padding: 5px; }"
        "QPushButton:hover { background-color: #4B5363; }"
        "QComboBox { background-color: #3E4451; color: white; border: none; "
        "padding: 5px; }"
        "QLabel { color: #ABB2BF; }"
        "QMenuBar { background-color: #282C34; color: #ABB2BF; }"
        "QMenuBar::item:selected { background-color: #3E4451; }"
        "QMenu { background-color: #282C34; color: #ABB2BF; }"
        "QMenu::item:selected { background-color: #3E4451; }"
        "QStatusBar { background-color: #21252B; color: #ABB2BF; }");

    setWindowTitle("Typing Test");

    ui_->textDisplay->setFrameShape(QFrame::NoFrame);
    ui_->textDisplay->setStyleSheet(
        "QTextEdit { background-color: #282C34; color: #ABB2BF; border: none; "
        "font-size: 18px; }");
}

MainWindow::~MainWindow() {
    delete ui_;
}

void MainWindow::onLanguageChanged(int index) {
    currentLanguage_ = ui_->languageComboBox->itemText(index);
    qDebug() << "Language changed to:" << currentLanguage_;

    if (!languageWords_.contains(currentLanguage_)) {
        qDebug() << "Error: Dictionary for" << currentLanguage_ << "not found!";
        return;
    }

    qDebug() << "Dictionary found with" << languageWords_[currentLanguage_].size()
             << "words";

    // generate
    currentPos_ = 0;
    isTypingActive_ = false;
    timer_->stop();
    generateRandomText(wordCount_);
}

void MainWindow::loadTextForLanguage(const QString& language) {
    if (sampleTexts_.contains(language)) {
        currentFullText_ = sampleTexts_[language];
        updateTextDisplay();
    }
}

QString MainWindow::getRandomWord(const QString& language) {
    if (languageWords_.contains(language) &&
        !languageWords_[language].isEmpty()) {
        int random_index =
            QRandomGenerator::global()->bounded(languageWords_[language].size());
        return languageWords_[language].at(random_index);
    }
    return "test";
}

void MainWindow::generateRandomText(int wordCount) {
    if (currentLanguage_.isEmpty() || !languageWords_.contains(currentLanguage_)) {
        qDebug() << "No language selected or language dictionary not found";
        return;
    }

    QStringList words;


    for (int i = 0; i < wordCount; ++i) {
        words.append(getRandomWord(currentLanguage_));
    }

    currentFullText_ = words.join(" ");

    const int fifrty = 50;
    qDebug() << "Generated text:" << currentFullText_.left(fifrty) << "...";

    updateTextDisplay();

    if (!currentFullText_.isEmpty()) {
        ui_->textDisplay->setPlainText(currentFullText_);
        updateTextDisplay();
    } else {
        ui_->textDisplay->setPlainText("Error: No text generated.");
    }
}

void MainWindow::onWordCountChanged(int count) {
    wordCount_ = count;
    // if message from spinbox, all buttons dont use
    if (sender() == customWordCountInput_) {
        QAbstractButton* checked_button = wordCountButtonGroup_->checkedButton();


        if (checked_button) {
            checked_button->setChecked(false);
        }
    }
    generateRandomText(wordCount_);
}

void MainWindow::onModeChanged(int modeId) {
    // mode 0 = words, mode 1 = timed
    isTimedMode_ = (modeId == 1);


    if (isTimedMode_) {
        // show time limit input, hide word count input
        customWordCountInput_->hide();
        timeLimitInput_->show();

        // generate a large number of words for timed mode
        const int thundred = 200;
        wordCount_ = thundred;
        generateRandomText(wordCount_);
    } else {
        // show word count input, hide time limit input
        customWordCountInput_->show();
        timeLimitInput_->hide();

        // revert to prev word count
        wordCount_ = customWordCountInput_->value();
        generateRandomText(wordCount_);
    }
}

void MainWindow::onTimeLimitChanged(int seconds) {
    timeLimit_ = seconds;
}

void MainWindow::updateTextDisplay() {
    if (currentFullText_.isEmpty()) {
        qDebug() << "Error: currentFullText_ is empty!?!";
        ui_->textDisplay->setPlainText(
            "Error: No text available. Please select a language and press ");
        return;
    }

    QString html_text;

    for (int i = 0; i < currentFullText_.length(); ++i) {
        QChar c = currentFullText_.at(i);


        if (i < currentPos_) {
            // typed symbol - light grey
            html_text +=
                QString("<span style='color:#AAAAAA;'>%1</span>").arg(c);
        } else if (i == currentPos_) {
            // color curr symbol
            html_text += QString(
                             "<span style='color:#000000; "
                             "background-color:#FFFF00;'>%1</span>")
                             .arg(c);
        } else {
            // all other
            html_text +=
                QString("<span style='color:#ABB2BF;'>%1</span>").arg(c);
        }
    }

    ui_->textDisplay->setHtml(html_text);
    ui_->textDisplay->show();
    ui_->textDisplay->repaint();
}

void MainWindow::onInputChanged(const QString& text) {
    if (!isTypingActive_ && text.length() > 0) {
        // auto start
        startGame();
        return;
    }


    if (!isTypingActive_) {
        return;
    }

    if (text.length() > 0) {
        // check last symbol
        QChar last_char = text.at(text.length() - 1);

        if (currentPos_ < currentFullText_.length()) {
            if (last_char == currentFullText_.at(currentPos_)) {
                // correct char
                correctChars_++;
                currentPos_++;
            } else {
                // wrong red color
                incorrectChars_++;
                QString html_text;
                for (int i = 0; i < currentFullText_.length(); ++i) {
                    QChar c = currentFullText_.at(i);


                    if (i < currentPos_) {
                        // okay smbl grey
                        html_text +=
                            QString("<span style='color:#AAAAAA;'>%1</span>")
                                .arg(c);
                    } else if (i == currentPos_) {
                        // !okay red
                        html_text += QString(
                                         "<span style='color:#FF0000; "
                                         "background-color:#FFFF00;'>%1</span>")
                                         .arg(c);
                    } else {
                        html_text +=
                            QString("<span style='color:#ABB2BF;'>%1</span>")
                                .arg(c);
                    }
                }
                ui_->textDisplay->setHtml(html_text);
            }
        }

        totalTypedChars_++;

        QSignalBlocker blocker(ui_->inputLineEdit);
        ui_->inputLineEdit->clear();
        if (currentPos_ >= currentFullText_.length() ||
            (isTimedMode_ && timeIsUp_)) {
            timer_->stop();
            isTypingActive_ = false;
            updateTimerAndWPM();
            const int hundred = 100;
            QMessageBox::information(
                this, "Finished!",
                QString("WPM: %1\nAccuracy: %2%")
                    .arg(ui_->wpmLabel->text().split(": ")[1])
                    .arg(qRound((double)correctChars_ / totalTypedChars_ *
                                hundred)));
        } else {
            updateTextDisplay();
        }
    }
}

void MainWindow::startGame() {


    if (!isTypingActive_) {
        isTypingActive_ = true;
        startTime_ = QDateTime::currentMSecsSinceEpoch();
        timer_->start();
        timeIsUp_ = false;
        ui_->inputLineEdit->setFocus();
    }
}

void MainWindow::resetGame() {
    timer_->stop();
    isTypingActive_ = false;
    correctChars_ = 0;
    incorrectChars_ = 0;
    totalTypedChars_ = 0;
    currentPos_ = 0;
    startTime_ = 0;
    timeIsUp_ = false;

    // check lang
    if (currentLanguage_.isEmpty() && ui_->languageComboBox->count() > 0) {
        currentLanguage_ = ui_->languageComboBox->itemText(0);
        ui_->languageComboBox->setCurrentText(currentLanguage_);
    }

    generateRandomText(wordCount_);

    ui_->timerLabel->setText("Time: 00:00");
    ui_->wpmLabel->setText("WPM: 0");
    ui_->inputLineEdit->clear();
    ui_->inputLineEdit->setFocus();
}

void MainWindow::updateTimerAndWPM() {


    if (!isTypingActive_ || startTime_ == 0) {
        return;
    }

    qint64 current_time = QDateTime::currentMSecsSinceEpoch();
    qint64 elapsed_ms = current_time - startTime_;

    const int tousand = 1000;
    const int sixtн = 60;
    const int ten = 10;
    // time in format: MM:SS
    int seconds = (elapsed_ms / tousand) % sixtн;
    int minutes = (elapsed_ms / tousand) / sixtн;

    QString time_string = QString("Time: %1:%2")
                              .arg(minutes, 2, ten, QChar('0'))
                              .arg(seconds, 2, ten, QChar('0'));
    ui_->timerLabel->setText(time_string);

    // check if time limit expired in timed mode
    if (isTimedMode_ && (minutes * sixtн + seconds) >= timeLimit_) {
        timeIsUp_ = true;
    }

    // WPM (5 chars == 1 word)
    double minutes_elapsed = elapsed_ms / double(tousand) / double(sixtн);

    const double five = 5.0;


    if (minutes_elapsed > 0) {
        double wpm = (correctChars_ / five) / minutes_elapsed;
        ui_->wpmLabel->setText(QString("WPM: %1").arg(qRound(wpm)));
    }
}

void MainWindow::onOpenFile() {
    QString file_name = QFileDialog::getOpenFileName(
        this, "Open txt", "", "Txt (*.txt);;All files (*.*)");

    if (file_name.isEmpty()) {
        return;
    }

    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error",
                             "Cant open file: " + file.errorString());
        return;
    }

    QTextStream in(&file);
    //in.setCodec("UTF-8");

    currentFullText_ = in.readAll();
    file.close();

    resetGame();
}
