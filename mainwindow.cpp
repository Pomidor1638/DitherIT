#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "orderedDithering.h"
#include "random.h"

//#define _DEBUG_

void MainWindow::disableForseWidgets()
{
    ui->forseParamsButton->setEnabled(false);
    ui->forseSizeButton->setEnabled(false);
    //ui->browseOutput->setEnabled(false);
}
void MainWindow::enableForseWidgets()
{
    ui->forseParamsButton->setEnabled(true);
    ui->forseSizeButton->setEnabled(true);
    //ui->browseOutput->setEnabled(true);
}

void MainWindow::initValues()
{

    ui->setupUi(this);

    listWidget = new DitherListWidget(this);
    listWidget->setMinimumWidth(300);
    ui->scrollArea->setWidget(listWidget);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    updateCurDither();
}

IDither* ditherByIndex(int index)
{

    switch (index) {
    case DITHERING_RANDOM:
        return new RandomDithering;
    case DITHERING_ORDERED:
        return new OrderedDithering;
    default:
        break;
    }
    return nullptr;
}

void MainWindow::onItemSelectionChanged()
{
    QList<QListWidgetItem*> selectedItems = listWidget->selectedItems();
    int selectedCount = selectedItems.count();
#ifdef _DEBUG_
    qDebug() << "Selected items:" << selectedCount;
#endif
    setCurDither(nullptr);
    curItemWidget = nullptr;
    clearCurImage();
    clearPathLabel();

    disableForseWidgets();

    if (selectedCount == 0) {
        return;
    }

    if (selectedCount > 1) {
        enableForseWidgets();
        const int index = ui->tabWidget->currentIndex();
        setCurDither(std::shared_ptr<IDither>(ditherByIndex(index)));
        return;
    }

    DitherItemWidget* item = listWidget->currentDitherItem();
    if (!item) {
#ifdef _DEBUG_
        qDebug() << "No current item widget";
#endif
        return;
    }

    curItemWidget = item;

    std::shared_ptr<IDither> d = item->getDither().lock();

    if (!d) {

#ifdef _DEBUG_
        qDebug() << "WARNING: Item without dither";

#endif
        return;
    }

    setCurDither(d);

    QImage image = item->getImage();
    if (image.isNull()) {

#ifdef _DEBUG_
        qDebug() << "WARNING: Item without image";
#endif
        return;
    }

    if (!setCurImage(image)) {

#ifdef _DEBUG_
        qDebug() << "WARNING: Can't load item image";
#endif
        return;
    }

    // Показываем путь
    if (outputPath.isEmpty()) {
#ifdef _DEBUG_
        qDebug() << "WARNING: item without output path";
#endif
        return;
    }

    setOutputPath(outputPath);
}

void MainWindow::connectSlots()
{
    // Imgs lists
    connect(listWidget, &DitherListWidget::itemSelectionChanged, this, &MainWindow::onItemSelectionChanged);

    // Dither params

    // common params
    connect(ui->  widthSpinBox,  QOverload<   int>::of(&QSpinBox::      valueChanged), this, &MainWindow::updateCommonParams);
    connect(ui->  heightSpinBox, QOverload<   int>::of(&QSpinBox::      valueChanged), this, &MainWindow::updateCommonParams);
    connect(ui->  brightSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::updateCommonParams);
    connect(ui->contrastSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::updateCommonParams);
    connect(ui->     colourFlag, &QCheckBox::toggled, this, &MainWindow::updateCommonParams);
    connect(ui->    inverseFlag, &QCheckBox::toggled, this, &MainWindow::updateCommonParams);

    // ordered params
    connect(ui->orderedColorDepthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::updateOrderedPararms);
    connect(ui->orderedLevelSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::updateOrderedPararms);
    connect(ui->orderedThresholdSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::updateOrderedPararms);
    connect(ui->orderedInverseMatrixFlag, &QCheckBox::toggled, this, &MainWindow::updateOrderedPararms);

    connect(ui->randomColorDepthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::updateRandomPararms);
    connect(ui->randomThresholdSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::updateRandomPararms);

    // Dither Type
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &::MainWindow::updateCurDither);
}




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , listWidget(nullptr)
    , curItemWidget(nullptr)
    , curDither(nullptr)
    , scene(nullptr)
{
    initValues();
    connectSlots();
    onItemSelectionChanged();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::setCurImage(const QImage& image)
{
    clearCurImage();
    if (image.isNull())
        return false;

    QPixmap pixmap = QPixmap::fromImage(image);

    scene->addPixmap(pixmap);
    scene->setSceneRect(pixmap.rect());

    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    return true;
}

std::weak_ptr<IDither> MainWindow::getCurDither() const
{
    return std::weak_ptr<IDither>(curDither);
}



void MainWindow::updateCommonParams()
{
    if (!curDither) {
#ifdef _DEBUG_
        qDebug() << "WARNING: " << __func__ << " - curDither is nullptr ";
#endif
        return;
    }

    CommonParams params;
    params.width = ui->widthSpinBox->value();
    params.height = ui->heightSpinBox->value();
    params.brightness = ui->brightSpinBox->value() / 100.0f;
    params.contrast = ui->contrastSpinBox->value() / 100.0f;
    params.colour = ui->colourFlag->isChecked();
    params.inverse = ui->inverseFlag->isChecked();

    curDither->setCommonParams(params);
}


void MainWindow::updateRandomPararms()
{
    std::shared_ptr<RandomDithering> rand = std::dynamic_pointer_cast<RandomDithering>(curDither);

    if (!rand)
    {

#ifdef _DEBUG_
        qDebug() << "ERROR: " << __func__ << " - can't cast cur dither to RandomDithering";
#endif
        return;
    }

    if (ui->tabWidget->currentIndex() != DITHERING_RANDOM)
    {
#ifdef _DEBUG_
        qDebug() << "WARNING: " << __func__ << " - wrong tab for RandomDithering";
#endif
        return;
    }

    rand->setColorDepth(ui->randomColorDepthSpinBox->value());
    rand->setThreshold(ui->randomThresholdSpinBox->value() / 100.0f);
}
// void MainWindow::updateFloydPararms()
// {

// }

void MainWindow::updateOrderedPararms()
{
    std::shared_ptr<OrderedDithering> od = std::dynamic_pointer_cast<OrderedDithering>(curDither);

    if (!od)
    {

#ifdef _DEBUG_
        qDebug() << "ERROR: " << __func__ << " - can't cast cur dither to OrderedDithering";
#endif
        return;
    }

    if (ui->tabWidget->currentIndex() != DITHERING_ORDERED)
    {
#ifdef _DEBUG_
        qDebug() << "WARNING: " << __func__ << " - wrong tab for OrderedDithering";
#endif
        return;
    }

    od->setColorDepth(ui->orderedColorDepthSpinBox->value());
    od->setThreshold(ui->orderedThresholdSpinBox->value() / 100.0f);
    od->setLevel(ui->orderedLevelSpinBox->value());
    od->setInvert(ui->orderedInverseMatrixFlag->checkState());

}

void MainWindow::updateCurDither()
{
    const int index = ui->tabWidget->currentIndex();
    DitheringType newType = static_cast<DitheringType>(index);

    CommonParams commonParams;
    if (curDither) {
        commonParams = curDither->getCommonParams();
    }

    auto newDither = std::shared_ptr<IDither>(ditherByIndex(index));
    if (!newDither)
        return;

    newDither->setCommonParams(commonParams);

    if (curItemWidget) {
        curItemWidget->setDither(newDither);
    }

    setCurDither(newDither);

    switch (newType) {
    case DITHERING_RANDOM:
        updateRandomPararms();
        break;
    case DITHERING_ORDERED:
        updateOrderedPararms();
        break;
    default:
        break;
    }
}


void MainWindow::updateCurDitherWidgets()
{
    if (!curDither) {
        return;
    }

    CommonParams params = curDither->getCommonParams();

    ui->widthSpinBox->blockSignals(true);
    ui->heightSpinBox->blockSignals(true);
    ui->brightSpinBox->blockSignals(true);
    ui->contrastSpinBox->blockSignals(true);
    ui->colourFlag->blockSignals(true);
    ui->inverseFlag->blockSignals(true);

    ui->widthSpinBox->setValue(params.width);
    ui->heightSpinBox->setValue(params.height);
    ui->brightSpinBox->setValue(params.brightness * 100.0f);
    ui->contrastSpinBox->setValue(params.contrast * 100.0f);
    ui->colourFlag->setCheckState(params.colour ? Qt::Checked : Qt::Unchecked);
    ui->inverseFlag->setCheckState(params.inverse ? Qt::Checked : Qt::Unchecked);

    ui->widthSpinBox->blockSignals(false);
    ui->heightSpinBox->blockSignals(false);
    ui->brightSpinBox->blockSignals(false);
    ui->contrastSpinBox->blockSignals(false);
    ui->colourFlag->blockSignals(false);
    ui->inverseFlag->blockSignals(false);

    switch (curDither->getDitherType()) {
    case DITHERING_ORDERED: {
        std::shared_ptr<OrderedDithering> od = std::dynamic_pointer_cast<OrderedDithering>(curDither);
        if (!od) {
#ifdef _DEBUG_
            qDebug() << "ERROR: " << __func__ << " - can't cast " << curDither->getDitherName();
#endif
            return;
        }

        ui->orderedColorDepthSpinBox->blockSignals(true);
        ui->orderedThresholdSpinBox->blockSignals(true);
        ui->orderedLevelSpinBox->blockSignals(true);
        ui->orderedInverseMatrixFlag->blockSignals(true);

        ui->orderedColorDepthSpinBox->setValue(od->getColorDepth());
        ui->orderedThresholdSpinBox->setValue(od->getThreshold() * 100.0f);
        ui->orderedLevelSpinBox->setValue(od->getLevel());
        ui->orderedInverseMatrixFlag->setCheckState(od->getInvert() ? Qt::Checked : Qt::Unchecked);

        ui->orderedColorDepthSpinBox->blockSignals(false);
        ui->orderedThresholdSpinBox->blockSignals(false);
        ui->orderedLevelSpinBox->blockSignals(false);
        ui->orderedInverseMatrixFlag->blockSignals(false);

        break;
    }
    case DITHERING_RANDOM: {
        std::shared_ptr<RandomDithering> rd = std::dynamic_pointer_cast<RandomDithering>(curDither);
        if (!rd) {
#ifdef _DEBUG_
            qDebug() << "ERROR: " << __func__ << " - can't cast " << curDither->getDitherName();
#endif
            return;
        }

        ui->randomColorDepthSpinBox->blockSignals(true);
        ui->randomThresholdSpinBox->blockSignals(true);

        ui->randomColorDepthSpinBox->setValue(rd->getColorDepth());
        ui->randomThresholdSpinBox->setValue(rd->getThreshold() * 100.0f);

        ui->randomColorDepthSpinBox->blockSignals(false);
        ui->randomThresholdSpinBox->blockSignals(false);

        break;
    }
    default:
        break;
    }
}

void MainWindow::setCurDither(std::shared_ptr<IDither> dither)
{
    if (curDither == dither) {
        return;
    }

    curDither = dither;

    if (!dither) {
#ifdef _DEBUG_
        qDebug() << "ERROR: " << __func__ << " - dither is nullptr";
#endif
        return;
    }

    updateCurDitherWidgets();
}

bool MainWindow::clearCurImage()
{
    if (scene)
    {
        scene->clear();
        return true;
    }
    return false;
}


void MainWindow::on_addButton_clicked()
{

    QStringList inputs = QFileDialog::getOpenFileNames(this, "Выбрать изображения");

    for (const QString& input : inputs) {
        listWidget->addDitherItem(input, ditherByIndex(ui->tabWidget->currentIndex()));
    }

    ui->imgsCountLabel->setText(QString("Images: %1").arg(listWidget->count()));
}

void MainWindow::on_deleteButton_clicked()
{
    QList<QListWidgetItem*> marked = listWidget->selectedItems();

    if (marked.isEmpty())
        return;

    for (QListWidgetItem* item : marked) {
        delete listWidget->takeItem(listWidget->row(item));
    }

    ui->imgsCountLabel->setText(QString("Images: %1").arg(listWidget->count()));
}

void MainWindow::onDitherItemAddError(const QString& input) {
    QMessageBox::information(this, "Error", "Can't load " + input);
}

void MainWindow::on_selectAllButton_clicked()
{
    if (!listWidget)
        return;

    QItemSelectionModel* selectionModel = listWidget->selectionModel();
    bool hasSelectedItems = selectionModel->hasSelection();

    if (hasSelectedItems)
    {
        selectionModel->clearSelection();
    } else
    {
        selectionModel->select(QItemSelection(
                                   listWidget->model()->index(0, 0),
                                   listWidget->model()->index(listWidget->count() - 1, 0)
                                   ), QItemSelectionModel::Select);
    }
}

void MainWindow::on_DitherIT_clicked()
{

    ui->DitherIT->setEnabled(false);


    if (outputPath.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Set output path");
        ui->DitherIT->setEnabled(true);
        return;
    }



    ui->currentImageProgressBar->setRange(0, 100);
    ui->commonProgressBar->setRange(0, 100);

    ui->currentImageProgressBar->setValue(0);
    ui->commonProgressBar->setValue(0);

    size_t count = 0;
    size_t common = listWidget->count();

    if(!common)
    {
        ui->DitherIT->setEnabled(true);
        return;
    }

    for (QListWidgetItem* item : listWidget->findItems("*", Qt::MatchWildcard)) {

        DitherItemWidget* widget = qobject_cast<DitherItemWidget*>(listWidget->itemWidget(item));

        if (!widget)
            continue;

        if (widget->getDither().expired())
        {
#ifdef _DEBUG_
            qDebug() << "WARNING: " << __func__ << " - item without dither";
#endif
            continue;
        }


        QImage image = widget->getDither().lock()->ditherImage(widget->getImage());
        count++;

        //setCurImage(image);

        ui->commonProgressBar->setValue(100.0f * count / common);



        QString fullPath = QDir(outputPath).filePath(widget->getFilename() + ".png");

        if (!image.save(fullPath, "PNG")) {
            QMessageBox::warning(this, "Error",
                                 QString("Can't save image as PNG to %1.\nError: %2")
                                     .arg(fullPath)
                                     .arg(image.isNull() ? "Image is null" : "Save failed"));
        }

        QCoreApplication::processEvents();
    }

    ui->currentImageProgressBar->setValue(100);
    ui->commonProgressBar->setValue(100);

    //clearCurImage();

    ui->DitherIT->setEnabled(true);

}

void MainWindow::setOutputPath(const QString& s)
{
    outputPath = s;
    ui->outputPath->setText(s);
}
void MainWindow::clearPathLabel()
{
    ui->outputPath->clear();
}


void MainWindow::on_forseParamsButton_clicked()
{
    if (!curDither) {
        return;
    }

    disableForseWidgets();

    const CommonParams& sourceParams = curDither->getCommonParams();

    const int itemCount = listWidget->count();
    for (int i = 0; i < itemCount; ++i) {
        QListWidgetItem* listItem = listWidget->item(i);
        if (!listItem) {
            continue;
        }

        DitherItemWidget* itemWidget = qobject_cast<DitherItemWidget*>(
            listWidget->itemWidget(listItem));
        if (!itemWidget) {
            continue;
        }

        auto ditherPtr = itemWidget->getDither().lock();
        if (!ditherPtr) {
            continue;
        }

        const CommonParams originalParams = ditherPtr->getCommonParams();
        const int originalWidth = originalParams.width;
        const int originalHeight = originalParams.height;

        CommonParams newParams = sourceParams;
        newParams.width = originalWidth;
        newParams.height = originalHeight;

        std::shared_ptr<IDither> ditherCopy(curDither->copy());
        ditherCopy->setCommonParams(newParams);

        itemWidget->setDither(ditherCopy);
    }

    enableForseWidgets();
}

void MainWindow::on_browseOutput_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(
        this,
        tr("Выберите папку для сохранения изображений"),
        QDir::homePath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );

    if (!folderPath.isEmpty())
    {
        setOutputPath(folderPath);
    }
}


void MainWindow::on_forseSizeButton_clicked()
{
    if (!curDither) {
        return;
    }

    disableForseWidgets();

    const CommonParams& sourceParams = curDither->getCommonParams();
    const int targetWidth = sourceParams.width;
    const int targetHeight = sourceParams.height;

    const int itemCount = listWidget->count();
    for (int i = 0; i < itemCount; ++i) {
        QListWidgetItem* listItem = listWidget->item(i);
        if (!listItem) {
            continue;
        }

        DitherItemWidget* itemWidget = qobject_cast<DitherItemWidget*>(
            listWidget->itemWidget(listItem));
        if (!itemWidget) {
            continue;
        }

        auto ditherPtr = itemWidget->getDither().lock();
        if (!ditherPtr) {
            continue;
        }

        CommonParams params = ditherPtr->getCommonParams();
        params.width = targetWidth;
        params.height = targetHeight;
        ditherPtr->setCommonParams(params);
    }

    enableForseWidgets();
}
