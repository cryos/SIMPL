#ifndef _searchlineedit_h_
#define _searchlineedit_h_



#include <QLineEdit>
#include <QAbstractButton>

#include "SIMPLib/Common/SIMPLibSetGetMacros.h"
#include "SVWidgetsLib/SVWidgetsLib.h"


class SearchLineEditPrivate;

/**
 * @brief The IconButton class
 */
class SVWidgetsLib_EXPORT IconButton : public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(float iconOpacity READ iconOpacity WRITE setIconOpacity)
    Q_PROPERTY(bool autoHide READ hasAutoHide WRITE setAutoHide)
    Q_PROPERTY(QPixmap pixmap READ pixmap WRITE setPixmap)
  public:
    explicit IconButton(QWidget* parent = 0);
    void paintEvent(QPaintEvent* event);
    void setPixmap(const QPixmap& pixmap) { m_pixmap = pixmap; update(); }
    QPixmap pixmap() const { return m_pixmap; }
    float iconOpacity() { return m_iconOpacity; }
    void setIconOpacity(float value) { m_iconOpacity = value; update(); }
    void animateShow(bool visible);

    void setAutoHide(bool hide) { m_autoHide = hide; }
    bool hasAutoHide() const { return m_autoHide; }
  private:
    float         m_iconOpacity;
    bool          m_autoHide;
    QPixmap       m_pixmap;
};

/**
    @brief A line edit with an embedded pixmap on one side that is connected to
    a menu.

    Additionally, it can display a grayed hintText (like "Type Here to")
    when not focused and empty. When connecting to the changed signals and
    querying text, one has to be aware that the text is set to that hint
    text if isShowingHintText() returns true (that is, does not contain
    valid user input).
 */
class SVWidgetsLib_EXPORT QtSLineEdit : public QLineEdit
{
    Q_OBJECT
    Q_ENUMS(Side)

  public:
    enum Side {Left = 0, Right = 1};

    explicit QtSLineEdit(QWidget* parent = 0);
    ~QtSLineEdit();

    QPixmap buttonPixmap(Side side) const;
    void setButtonPixmap(Side side, const QPixmap& pixmap);

    QMenu* buttonMenu(Side side) const;
    void setButtonMenu(Side side, QMenu* menu);

    void setButtonVisible(Side side, bool visible);
    bool isButtonVisible(Side side) const;

    void setButtonDisabled(Side side, bool disabled);
    void setButtonEnabled(Side side, bool enabled);
    bool isButtonEnabled(Side side) const;

    void setButtonToolTip(Side side, const QString&);
    void setButtonFocusPolicy(Side side, Qt::FocusPolicy policy);

    // Set whether tabbing in will trigger the menu.
    void setMenuTabFocusTrigger(Side side, bool v);
    bool hasMenuTabFocusTrigger(Side side) const;

    // Set if icon should be hidden when text is empty
    void setAutoHideButton(Side side, bool h);
    bool hasAutoHideButton(Side side) const;

    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);

  signals:
    void buttonClicked(QtSLineEdit::Side side);
    void leftButtonClicked();
    void rightButtonClicked();
    void fileDropped(const QString& file);

  private slots:
    void checkButtons(const QString&);
    void iconClicked();

  protected:
    virtual void resizeEvent(QResizeEvent* e);

  private:

    void updateMargins();
    void updateButtonPositions();
    friend class SearchLineEditPrivate;

    SearchLineEditPrivate* d;
    QString m_OldText;
};


#endif // _SearchLineEdit_H_
