#include "clickablelabel.h"

/*****************ClickableLabel************************
 ******************Constructor************************
 * @param parent QObject
 * @return none
 ****************************************************/
ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags)
    : QLabel(parent)
{

}

/*****************ClickableLabel************************
 ******************Destructor************************
 * @param parent QObject
 * @return none
 ****************************************************/
ClickableLabel::~ClickableLabel()
{

}

/*****************ClickableLabel************************
 ******************mousePressEvent************************
 * @param  event
 * @return none
 ****************************************************/
void ClickableLabel::mousePressEvent(QMouseEvent*)
{
    emit clicked();
}
