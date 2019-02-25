#ifndef MYGLITEM_H
#define MYGLITEM_H

#include "glitem.h"
#include "gldisc.h"
#include <QOpenGLBuffer>
#include "board.h"
#include <QTimer>

class MyGlItem : public GLItem
{
    Q_OBJECT

    Q_PROPERTY(QString nextPlayer READ nextPlayer WRITE setNextPlayer NOTIFY playerChanged)
    Q_PROPERTY(QString nextColor READ nextColor WRITE setNextColor NOTIFY colorChanged)

private:

    QOpenGLBuffer *m_vertexBuffer;
    QOpenGLBuffer *m_indexBuffer;
    QList<GLDisc *> redDiscs;
    QList<GLDisc *> yellowDiscs;
    GLBody *m_blender;
    QTimer * m_timer;
    Board *field;

    QList<QString> *messages;

    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    int counter4 = 0;
    int counter5 = 0;
    int counter6 = 0;
    int counter7 = 0;

    int totalDiscs = 0;

    int currentTheme = 2;

    GLColorRgba color;

    QString m_player1;
    QString m_player2;

    QString m_nextPlayer;
    QString m_nextColor;

public:
    MyGlItem();

    virtual void setupGeometry() override;
    void paintUnderQmlScene() override;
    void paintOnTopOfQmlScene() override;

    Q_INVOKABLE QString nextPlayer()const{return m_nextPlayer;}
    Q_INVOKABLE QString nextColor()const{return m_nextColor;}

    void setNextPlayer(const QString next){m_nextPlayer = next;  emit playerChanged(next);}
    void setNextColor(const QString color) {m_nextColor = color; emit colorChanged(color);}

signals:
    void playerChanged(QString next);
    void colorChanged(QString color);

public slots:
    void insertDisc(int buttonNumber);
    void doMouseClick(int x, int y);
    void newGame(QString player1, QString player2);
    void changeTheme(int theme);
    void timerSlot();

};

#endif // MYGLITEM_H
