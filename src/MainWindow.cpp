#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QtCore/QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , converter(new NumberConverter())
    , validator(new BaseValidator())
    , explainer(new StepByStepExplainer())
    , calculator(new ArithmeticCalculator())
{
    setupUI();
    setWindowTitle("Convertidor de Sistemas Numéricos");
    setMinimumSize(800, 600);
    resize(1200, 800);
}

MainWindow::~MainWindow()
{
    delete converter;
    delete validator;
    delete explainer;
    delete calculator;
}

void MainWindow::setupUI()
{
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    mainSplitter = new QSplitter(Qt::Horizontal, this);
    
    setupInputPanel();
    setupResultsPanel();
    
    mainSplitter->addWidget(inputPanel);
    mainSplitter->addWidget(resultsTabWidget);
    mainSplitter->setStretchFactor(0, 1);
    mainSplitter->setStretchFactor(1, 2);
    
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->addWidget(mainSplitter);
}

void MainWindow::setupInputPanel()
{
    inputPanel = new QWidget();
    QVBoxLayout* inputLayout = new QVBoxLayout(inputPanel);
    
    // Input group
    QGroupBox* inputGroup = new QGroupBox("Número de Entrada");
    QVBoxLayout* inputGroupLayout = new QVBoxLayout(inputGroup);
    
    // Number input
    QHBoxLayout* numberLayout = new QHBoxLayout();
    inputLineEdit = new QLineEdit();
    inputLineEdit->setPlaceholderText("Ingrese un número...");
    QLabel* baseLabel = new QLabel("Base:");
    inputBaseCombo = new QComboBox();
    
    // Populate base combo
    inputBaseCombo->addItem("Binario (2)", 2);
    inputBaseCombo->addItem("Ternario (3)", 3);
    inputBaseCombo->addItem("Octal (8)", 8);
    inputBaseCombo->addItem("Decimal (10)", 10);
    inputBaseCombo->addItem("Hexadecimal (16)", 16);
    inputBaseCombo->setCurrentIndex(3); // Default to decimal
    
    numberLayout->addWidget(inputLineEdit);
    numberLayout->addWidget(baseLabel);
    numberLayout->addWidget(inputBaseCombo);
    
    // Validation label
    validationLabel = new QLabel();
    validationLabel->setStyleSheet("QLabel { color: green; }");
    
    inputGroupLayout->addLayout(numberLayout);
    inputGroupLayout->addWidget(validationLabel);
    
    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    convertAllButton = new QPushButton("Convertir Todo");
    clearButton = new QPushButton("Limpiar");
    
    buttonLayout->addWidget(convertAllButton);
    buttonLayout->addWidget(clearButton);
    
    inputGroupLayout->addLayout(buttonLayout);
    
    // Operations group
    QGroupBox* operationsGroup = new QGroupBox("Operaciones");
    QVBoxLayout* operationsGroupLayout = new QVBoxLayout(operationsGroup);
    
    // Operation selection
    QHBoxLayout* opLayout = new QHBoxLayout();
    QLabel* opLabel = new QLabel("Operación:");
    operationCombo = new QComboBox();
    operationCombo->addItem("Suma", static_cast<int>(Operation::ADD));
    operationCombo->addItem("Resta", static_cast<int>(Operation::SUBTRACT));
    operationCombo->addItem("Multiplicación", static_cast<int>(Operation::MULTIPLY));
    
    opLayout->addWidget(opLabel);
    opLayout->addWidget(operationCombo);
    
    // Second operand
    QHBoxLayout* operand2Layout = new QHBoxLayout();
    QLabel* operand2Label = new QLabel("Operando 2:");
    operand2LineEdit = new QLineEdit();
    operand2LineEdit->setPlaceholderText("Segundo número...");
    operand2BaseCombo = new QComboBox();
    
    // Populate second operand base combo
    operand2BaseCombo->addItem("Binario (2)", 2);
    operand2BaseCombo->addItem("Ternario (3)", 3);
    operand2BaseCombo->addItem("Octal (8)", 8);
    operand2BaseCombo->addItem("Decimal (10)", 10);
    operand2BaseCombo->addItem("Hexadecimal (16)", 16);
    operand2BaseCombo->setCurrentIndex(3);
    
    operand2Layout->addWidget(operand2Label);
    operand2Layout->addWidget(operand2LineEdit);
    operand2Layout->addWidget(operand2BaseCombo);
    
    calculateButton = new QPushButton("Calcular");
    
    operationsGroupLayout->addLayout(opLayout);
    operationsGroupLayout->addLayout(operand2Layout);
    operationsGroupLayout->addWidget(calculateButton);
    
    inputLayout->addWidget(inputGroup);
    inputLayout->addWidget(operationsGroup);
    inputLayout->addStretch();
    
    // Connect signals
    connect(inputLineEdit, &QLineEdit::textChanged, this, &MainWindow::onInputChanged);
    connect(inputBaseCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onBaseChanged);
    connect(convertAllButton, &QPushButton::clicked, this, &MainWindow::onConvertAllClicked);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::onCalculateClicked);
    connect(operationCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onOperationChanged);
}

void MainWindow::setupResultsPanel()
{
    resultsTabWidget = new QTabWidget();
    
    // Conversions Tab
    conversionsTab = new QWidget();
    QVBoxLayout* conversionsLayout = new QVBoxLayout(conversionsTab);
    
    QLabel* titleLabel = new QLabel("Resultados de Conversión");
    titleLabel->setStyleSheet("QLabel { font-size: 14px; font-weight: bold; margin-bottom: 10px; }");
    conversionsLayout->addWidget(titleLabel);
    
    QGroupBox* resultsGroup = new QGroupBox("Conversiones");
    QGridLayout* resultsLayout = new QGridLayout(resultsGroup);
    
    // Create result labels
    resultsLayout->addWidget(new QLabel("Binario:"), 0, 0);
    binaryResult = new QLabel("---");
    binaryResult->setStyleSheet("QLabel { font-family: monospace; font-size: 12px; }");
    resultsLayout->addWidget(binaryResult, 0, 1);
    
    resultsLayout->addWidget(new QLabel("Ternario:"), 1, 0);
    ternaryResult = new QLabel("---");
    ternaryResult->setStyleSheet("QLabel { font-family: monospace; font-size: 12px; }");
    resultsLayout->addWidget(ternaryResult, 1, 1);
    
    resultsLayout->addWidget(new QLabel("Octal:"), 2, 0);
    octalResult = new QLabel("---");
    octalResult->setStyleSheet("QLabel { font-family: monospace; font-size: 12px; }");
    resultsLayout->addWidget(octalResult, 2, 1);
    
    resultsLayout->addWidget(new QLabel("Decimal:"), 3, 0);
    decimalResult = new QLabel("---");
    decimalResult->setStyleSheet("QLabel { font-family: monospace; font-size: 12px; }");
    resultsLayout->addWidget(decimalResult, 3, 1);
    
    resultsLayout->addWidget(new QLabel("Hexadecimal:"), 4, 0);
    hexResult = new QLabel("---");
    hexResult->setStyleSheet("QLabel { font-family: monospace; font-size: 12px; }");
    resultsLayout->addWidget(hexResult, 4, 1);
    
    resultsLayout->addWidget(new QLabel("Base 12:"), 5, 0);
    customResult = new QLabel("---");
    customResult->setStyleSheet("QLabel { font-family: monospace; font-size: 12px; }");
    resultsLayout->addWidget(customResult, 5, 1);
    
    conversionsLayout->addWidget(resultsGroup);
    conversionsLayout->addStretch();
    
    // Steps Tab
    stepsTab = new QWidget();
    QVBoxLayout* stepsLayout = new QVBoxLayout(stepsTab);
    
    QLabel* stepsTitle = new QLabel("Proceso Paso a Paso");
    stepsTitle->setStyleSheet("QLabel { font-size: 14px; font-weight: bold; margin-bottom: 10px; }");
    stepsLayout->addWidget(stepsTitle);
    
    stepsTextEdit = new QTextEdit();
    stepsTextEdit->setReadOnly(true);
    stepsTextEdit->setFont(QFont("monospace", 10));
    stepsLayout->addWidget(stepsTextEdit);
    
    // Operations Tab
    operationsTab = new QWidget();
    QVBoxLayout* operationsLayout = new QVBoxLayout(operationsTab);
    
    QLabel* operationsTitle = new QLabel("Operaciones Aritméticas");
    operationsTitle->setStyleSheet("QLabel { font-size: 14px; font-weight: bold; margin-bottom: 10px; }");
    operationsLayout->addWidget(operationsTitle);
    
    operationsTextEdit = new QTextEdit();
    operationsTextEdit->setReadOnly(true);
    operationsTextEdit->setFont(QFont("monospace", 10));
    operationsLayout->addWidget(operationsTextEdit);
    
    // Theory Tab
    setupTheoryTab();
    
    // Add tabs
    resultsTabWidget->addTab(conversionsTab, "🔢 Conversiones");
    resultsTabWidget->addTab(stepsTab, "📚 Proceso");
    resultsTabWidget->addTab(operationsTab, "🧮 Operaciones");
    resultsTabWidget->addTab(theoryTab, "📖 Teoría");
}

void MainWindow::setupTheoryTab()
{
    theoryTab = new QWidget();
    QVBoxLayout* theoryLayout = new QVBoxLayout(theoryTab);
    
    QLabel* theoryTitle = new QLabel("Sistemas Numéricos - Conceptos");
    theoryTitle->setStyleSheet("QLabel { font-size: 14px; font-weight: bold; margin-bottom: 10px; }");
    theoryLayout->addWidget(theoryTitle);
    
    theoryTextEdit = new QTextEdit();
    theoryTextEdit->setReadOnly(true);
    theoryTextEdit->setHtml(
        "<h3>🔢 ¿Qué es un sistema numérico?</h3>"
        "<p>Un sistema numérico es un método para representar números usando un conjunto finito de símbolos.</p>"
        
        "<h3>🧮 Base del sistema</h3>"
        "<ul>"
        "<li><b>Base 2 (Binario):</b> Usa 2 símbolos (0,1)</li>"
        "<li><b>Base 8 (Octal):</b> Usa 8 símbolos (0-7)</li>"
        "<li><b>Base 10 (Decimal):</b> Usa 10 símbolos (0-9)</li>"
        "<li><b>Base 16 (Hexadecimal):</b> Usa 16 símbolos (0-9,A-F)</li>"
        "</ul>"
        
        "<h3>🔄 Valor posicional</h3>"
        "<p>Cada posición en un número tiene un valor que es una potencia de la base.</p>"
        "<p><b>Ejemplo:</b> 1011₂ = 1×2³ + 0×2² + 1×2¹ + 1×2⁰ = 8 + 0 + 2 + 1 = 11₁₀</p>"
        
        "<h3>🔀 Conversiones</h3>"
        "<p><b>Decimal a otra base:</b> División sucesiva por la base</p>"
        "<p><b>Otra base a decimal:</b> Suma de productos por potencias de la base</p>"
        "<p><b>Entre bases no decimales:</b> Conversión vía decimal</p>"
        
        "<h3>🎯 Aplicaciones</h3>"
        "<ul>"
        "<li><b>Informática:</b> Representación binaria de datos</li>"
        "<li><b>Electrónica:</b> Circuitos digitales</li>"
        "<li><b>Matemáticas:</b> Teoría de números</li>"
        "<li><b>Criptografía:</b> Algoritmos de cifrado</li>"
        "</ul>"
    );
    
    theoryLayout->addWidget(theoryTextEdit);
}

void MainWindow::onInputChanged()
{
    updateValidationStatus();
    updateAllConversions();
    updateStepByStepExplanation();
}

void MainWindow::onBaseChanged()
{
    updateValidationStatus();
    updateAllConversions();
    updateStepByStepExplanation();
}

void MainWindow::onConvertAllClicked()
{
    updateAllConversions();
    updateStepByStepExplanation();
}

void MainWindow::onClearClicked()
{
    inputLineEdit->clear();
    operand2LineEdit->clear();
    
    binaryResult->setText("---");
    ternaryResult->setText("---");
    octalResult->setText("---");
    decimalResult->setText("---");
    hexResult->setText("---");
    customResult->setText("---");
    
    stepsTextEdit->clear();
    operationsTextEdit->clear();
    validationLabel->clear();
}

void MainWindow::onCalculateClicked()
{
    updateOperationsTab();
}

void MainWindow::onOperationChanged()
{
    // Update operation tab if there's already content
    if (!operationsTextEdit->toPlainText().isEmpty()) {
        updateOperationsTab();
    }
}

void MainWindow::updateValidationStatus()
{
    QString input = inputLineEdit->text();
    if (input.isEmpty()) {
        validationLabel->clear();
        return;
    }
    
    int base = inputBaseCombo->currentData().toInt();
    bool isValid = validator->isValidNumber(input.toStdString(), base);
    
    if (isValid) {
        validationLabel->setText("✓ Número válido");
        validationLabel->setStyleSheet("QLabel { color: green; }");
    } else {
        QString error = QString::fromStdString(validator->getValidationError(input.toStdString(), base));
        validationLabel->setText("❌ " + error);
        validationLabel->setStyleSheet("QLabel { color: red; }");
    }
}

void MainWindow::updateAllConversions()
{
    QString input = inputLineEdit->text();
    if (input.isEmpty()) {
        return;
    }
    
    int base = inputBaseCombo->currentData().toInt();
    
    if (!validator->isValidNumber(input.toStdString(), base)) {
        return;
    }
    
    try {
        int decimal = converter->baseToDecimal(input.toStdString(), base);
        
        binaryResult->setText(QString::fromStdString(converter->decimalToBase(decimal, 2)));
        ternaryResult->setText(QString::fromStdString(converter->decimalToBase(decimal, 3)));
        octalResult->setText(QString::fromStdString(converter->decimalToBase(decimal, 8)));
        decimalResult->setText(QString::fromStdString(converter->decimalToBase(decimal, 10)));
        hexResult->setText(QString::fromStdString(converter->decimalToBase(decimal, 16)));
        customResult->setText(QString::fromStdString(converter->decimalToBase(decimal, 12)));
        
    } catch (const std::exception& e) {
        validationLabel->setText("❌ Error: " + QString::fromStdString(e.what()));
        validationLabel->setStyleSheet("QLabel { color: red; }");
    }
}

void MainWindow::updateStepByStepExplanation()
{
    QString input = inputLineEdit->text();
    if (input.isEmpty()) {
        stepsTextEdit->clear();
        return;
    }
    
    int base = inputBaseCombo->currentData().toInt();
    
    if (!validator->isValidNumber(input.toStdString(), base)) {
        stepsTextEdit->setText("Ingrese un número válido para ver el proceso paso a paso.");
        return;
    }
    
    try {
        int decimal = converter->baseToDecimal(input.toStdString(), base);
        
        QString explanation;
        if (base != 10) {
            explanation += QString::fromStdString(explainer->explainBaseToDecimal(input.toStdString(), base));
            explanation += "\n" + QString(50, '=') + "\n\n";
        }
        
        explanation += QString::fromStdString(explainer->explainDecimalToBase(decimal, 2));
        explanation += "\n" + QString(50, '=') + "\n\n";
        explanation += QString::fromStdString(explainer->explainDecimalToBase(decimal, 16));
        
        stepsTextEdit->setText(explanation);
        
    } catch (const std::exception& e) {
        stepsTextEdit->setText("Error al generar explicación: " + QString::fromStdString(e.what()));
    }
}

void MainWindow::updateOperationsTab()
{
    QString input1 = inputLineEdit->text();
    QString input2 = operand2LineEdit->text();
    
    if (input1.isEmpty() || input2.isEmpty()) {
        operationsTextEdit->setText("Ingrese ambos operandos para realizar la operación.");
        return;
    }
    
    int base1 = inputBaseCombo->currentData().toInt();
    int base2 = operand2BaseCombo->currentData().toInt();
    
    if (!validator->isValidNumber(input1.toStdString(), base1) || 
        !validator->isValidNumber(input2.toStdString(), base2)) {
        operationsTextEdit->setText("Ambos números deben ser válidos para sus respectivas bases.");
        return;
    }
    
    try {
        Operation op = static_cast<Operation>(operationCombo->currentData().toInt());
        QString result;
        
        switch (op) {
            case Operation::ADD:
                result = QString::fromStdString(calculator->add(input1.toStdString(), base1, 
                                                               input2.toStdString(), base2, 10));
                break;
            case Operation::SUBTRACT:
                result = QString::fromStdString(calculator->subtract(input1.toStdString(), base1, 
                                                                    input2.toStdString(), base2, 10));
                break;
            case Operation::MULTIPLY:
                result = QString::fromStdString(calculator->multiply(input1.toStdString(), base1, 
                                                                    input2.toStdString(), base2, 10));
                break;
        }
        
        QString explanation = QString::fromStdString(calculator->getLastCalculationSteps());
        operationsTextEdit->setText(explanation);
        
    } catch (const std::exception& e) {
        operationsTextEdit->setText("Error en el cálculo: " + QString::fromStdString(e.what()));
    }
}