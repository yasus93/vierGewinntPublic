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
    Q_PROPERTY(QList<QString> nextOrder READ nextOrder WRITE setNextOrder NOTIFY orderChanged)
    Q_PROPERTY(QList<int> nextResult READ nextResult WRITE setNextResult NOTIFY resultChanged)

private:

    QOpenGLBuffer *m_vertexBuffer;
    QOpenGLBuffer *m_indexBuffer;
    QList<GLDisc *> redDiscs;
    QList<GLDisc *> yellowDiscs;
    GLBody *m_blender;
    QTimer * m_timer;
    Board *field;

    QList<QString> m_nextOrder = QList<QString>();
    QList<int> m_nextResult = QList<int>();

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

    QString m_staticPlayer1;
    QString m_staticPlayer2;

    QString m_nextPlayer;
    QString m_nextColor;

    bool redWins();
    bool redHasHorizontal();
    bool redHasVertical();
    bool redHasDiagonal();

    bool yellowWins();
    bool yellowHasHorizontal();
    bool yellowHasVertical();
    bool yellowHasDiagonal();

    void markWinnerHorizontal(QList<GLDisc *> disc, int minX, int maxX, int currentY);
    void markWinnerVertical(QList<GLDisc *> disc, int minY, int maxY, int currentX);
public:
    MyGlItem();

    virtual void setupGeometry() override;
    void paintUnderQmlScene() override;
    void paintOnTopOfQmlScene() override;

    Q_INVOKABLE QString nextPlayer(){return m_nextPlayer;}
    Q_INVOKABLE QString nextColor(){return m_nextColor;}
    Q_INVOKABLE QList<QString> nextOrder() {return m_nextOrder;}
    Q_INVOKABLE QList<int> nextResult() {return m_nextResult;}

    void setNextPlayer( QString next){m_nextPlayer = next;  emit playerChanged(next);}
    void setNextColor( QString color) {m_nextColor = color; emit colorChanged(color);}
    void setNextOrder (QList<QString> order) {m_nextOrder = order; emit orderChanged(order);}
    void setNextResult (QList<int> result) {m_nextResult = result; emit resultChanged(result);}

signals:
    void playerChanged(QString next);
    void colorChanged(QString color);
    void orderChanged(QList<QString> order);
    void resultChanged(QList<int> result);

public slots:
    void insertDisc(int buttonNumber);
    void doMouseClick(int x, int y);
    void newGame(QString player1, QString player2);
    void resetScore();
    void changeTheme(int theme);
    void timerSlot();
    void staticPlayers(QString p1, QString p2);
};

#endif // MYGLITEM_H
