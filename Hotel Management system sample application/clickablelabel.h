#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>

class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~ClickableLabel() override;

    ClickableLabel(const ClickableLabel& other) = delete;             // disable copy construction
    ClickableLabel& operator=(const ClickableLabel& other) = delete;  // disable assignment

    ClickableLabel(const ClickableLabel&& other) = delete;
    ClickableLabel& operator=(const ClickableLabel&& other) = delete;

signals:
    void clicked();

protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
};

#endif // CLICKABLELABEL_H
