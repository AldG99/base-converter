#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QSplitter>

#include "NumberConverter.h"
#include "BaseValidator.h"
#include "StepByStepExplainer.h"
#include "ArithmeticCalculator.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onInputChanged();
    void onBaseChanged();
    void onConvertAllClicked();
    void onClearClicked();
    void onCalculateClicked();
    void onOperationChanged();

private:
    void setupUI();
    void setupInputPanel();
    void setupResultsPanel();
    void updateValidationStatus();
    void updateAllConversions();
    void updateStepByStepExplanation();
    void updateOperationsTab();
    void setupTheoryTab();
    
    // Core functionality
    NumberConverter* converter;
    BaseValidator* validator;
    StepByStepExplainer* explainer;
    ArithmeticCalculator* calculator;
    
    // UI Components - Input Panel
    QWidget* inputPanel;
    QLineEdit* inputLineEdit;
    QComboBox* inputBaseCombo;
    QLabel* validationLabel;
    QPushButton* convertAllButton;
    QPushButton* clearButton;
    
    // UI Components - Operations
    QComboBox* operationCombo;
    QLineEdit* operand2LineEdit;
    QComboBox* operand2BaseCombo;
    QPushButton* calculateButton;
    
    // UI Components - Results Panel
    QTabWidget* resultsTabWidget;
    
    // Results tabs
    QWidget* conversionsTab;
    QWidget* stepsTab;
    QWidget* operationsTab;
    QWidget* theoryTab;
    
    // Results display
    QLabel* binaryResult;
    QLabel* ternaryResult;
    QLabel* octalResult;
    QLabel* decimalResult;
    QLabel* hexResult;
    QLabel* customResult;
    QTextEdit* stepsTextEdit;
    QTextEdit* operationsTextEdit;
    QTextEdit* theoryTextEdit;
    
    // Layout
    QSplitter* mainSplitter;
};

#endif // MAINWINDOW_H