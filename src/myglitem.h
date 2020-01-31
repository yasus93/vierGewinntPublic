#ifndef MYGLITEM_H
#define MYGLITEM_H

#include "glitem.h"
#include "gldisc.h"
#include <QOpenGLBuffer>
#include "board.h"
#include <QTimer>

/**
 * @brief This class is used for representing the game process.
 *
 * Q_Properties are used to bind values targeting attributes of qml components.
 * It contains wincondition for horizontal, vertical and diagonal.
 *
 */
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
    /**
     * @brief redDiscs
     * @brief yellowDiscs
     *
     * containing total ammount of inserted discs.
     */
    QList<GLDisc *> redDiscs;
    QList<GLDisc *> yellowDiscs;
    /**
     * @brief m_blender
     *
     * Objectmodel for the game created in blender.
     */
    GLBody *m_blender;
    /**
     * @brief color
     *
     * displayed color of a disc
     */
    GLColorRgba color;
    /**
     * @brief currentTheme
     *
     * a flag representing the chosen theme to be drawn.
     */
    int currentTheme = 2;
    /**
     * @brief m_timer
     *
     * triggers timerSlot for animating disc.
     */
    QTimer * m_timer;
    /**
     * @brief field
     *
     * grid used for the positioning of discs.
     */
    Board *field;

    /**
     * @brief m_player1
     * @brief m_player2
     *
     * player of the current round
     */
    QString m_player1;
    QString m_player2;

    /**
     * @brief m_staticPlayer1
     * @brief m_staticPlayer2
     *
     * player of the current game
     */
    QString m_staticPlayer1;
    QString m_staticPlayer2;

    /**
     * @brief m_nextPlayer
     * @brief m_nextColor
     * @brief m_nextOrder
     * @brief m_nextResult
     *
     * Containing the valid attributes for the corresponding qml components
     */
    QString m_nextPlayer;
    QString m_nextColor;
    QList<QString> m_nextOrder = QList<QString>();
    QList<int> m_nextResult = QList<int>();

    /**
     * @brief messages
     *
     * A simple List containing some prepared texts
     */
    QList<QString> *messages;

    /**
     * @brief counter1
     * @brief counter2
     * @brief counter3
     * @brief counter4
     * @brief counter5
     * @brief counter6
     * @brief counter7
     *
     * counting discs in y-direction
     */
    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    int counter4 = 0;
    int counter5 = 0;
    int counter6 = 0;
    int counter7 = 0;

    /**
     * @brief totalDiscs
     *
     * should count up to magic number.
     */
    int totalDiscs = 0;

    /**
     * @brief redWins
     * @return true if red wins
     */
    bool redWins();
    /**
     * @brief redHasHorizontal
     * @return true if red wins horizontal
     */
    bool redHasHorizontal();
    /**
     * @brief redHasVertical
     * @return true if red wins vertical
     */
    bool redHasVertical();
    /**
     * @brief redHasDiagonal
     * @return true if red wins diagonal
     */
    bool redHasDiagonal();

    /**
     * @brief yellowWins
     * @return true if yellow wins
     */
    bool yellowWins();
    /**
     * @brief yellowHasHorizontal
     * @return true if yellow wins horizontal
     */
    bool yellowHasHorizontal();
    /**
     * @brief yellowHasVertical
     * @return true if yellow wins vertical
     */
    bool yellowHasVertical();
    /**
     * @brief yellowHasDiagonal
     * @return true if yellow wins diagonal
     */
    bool yellowHasDiagonal();

    /**
     * @brief markWinnerHorizontal
     * @param disc
     * @param minX
     * @param maxX
     * @param currentY
     *
     * Sets color of horizontal winning discs to white
     */
    void markWinnerHorizontal(QList<GLDisc *> disc, int minX, int maxX, int currentY);
    /**
     * @brief markWinnerVertical
     * @param disc
     * @param minY
     * @param maxY
     * @param currentX
     *
     * Sets color of vertical winning disc to white
     */
    void markWinnerVertical(QList<GLDisc *> disc, int minY, int maxY, int currentX);
    bool gameRunning;
public:
    MyGlItem();

    /**
     * @brief setupGeometry
     *
     * setup blendermodel and field
     */
    virtual void setupGeometry() override;
    /**
     * @brief paintUnderQmlScene
     *
     * paint underQML is not used
     */
    void paintUnderQmlScene() override;
    /**
     * @brief paintOnTopOfQmlScene
     *
     * object will be painted on top of qml scene
     */
    void paintOnTopOfQmlScene() override;
    void keyPressEvent(QKeyEvent *ev) override;

    /**
     * Invokable Methods for qml meta object system
     *
     */
    Q_INVOKABLE QString nextPlayer(){return m_nextPlayer;}
    Q_INVOKABLE QString nextColor(){return m_nextColor;}
    Q_INVOKABLE QList<QString> nextOrder() {return m_nextOrder;}
    Q_INVOKABLE QList<int> nextResult() {return m_nextResult;}

    /**
     * @brief setNextPlayer
     * @param next
     *
     * simple setter which also emits playerChanged Signal
     */
    void setNextPlayer( QString next){m_nextPlayer = next;  emit playerChanged(next);}
    /**
     * @brief setNextColor
     * @param color
     *
     * simple setter which also emits colorChanged Signal
     */
    void setNextColor( QString color) {m_nextColor = color; emit colorChanged(color);}
    /**
     * @brief setNextOrder
     * @param order
     *
     * simple setter which also emits orderChanged Signal
     */
    void setNextOrder (QList<QString> order) {m_nextOrder = order; emit orderChanged(order);}
    /**
     * @brief setNextResult
     * @param result
     *
     * simple setter which also emits resultChanged Signal
     */
    void setNextResult (QList<int> result) {m_nextResult = result; emit resultChanged(result);}

signals:
    /**
     * @brief playerChanged
     * @param next = next Player
     *
     * signal emitted when player is changed
     */
    void playerChanged(QString next);
    /**
     * @brief colorChanged
     * @param color = next color
     *
     * signal emitted when color is changed
     */
    void colorChanged(QString color);
    /**
     * @brief orderChanged
     * @param order = next order
     *
     * signal emitted when order is changed
     */
    void orderChanged(QList<QString> order);
    /**
     * @brief resultChanged
     * @param result = next result
     *
     * signal emitted when result is changed
     */
    void resultChanged(QList<int> result);

public slots:
    /**
     * @brief insertDisc
     * @param buttonNumber = id of the clicked button representing the column
     *
     * inserts disc and checks if it is a winning disc
     */
    void insertDisc(int buttonNumber);
    /**
     * @brief doMouseClick
     * @param x
     * @param y
     *
     * simple function for debugging qml scene
     */
    void doMouseClick(int x, int y);
    /**
     * @brief newGame
     * @param player1 = name of first player
     * @param player2 = name of second player
     *
     * sets the name of the players for the next round
     */
    void newGame(QString player1, QString player2);
    /**
     * @brief resetScore
     * simple slot for resetting current score
     */
    void resetScore();
    /**
     * @brief changeTheme
     * @param theme = flag in form of an integer
     *
     * selects the corresponding theme to the id
     */
    void changeTheme(int theme);
    /**
     * @brief timerSlot
     *
     * slot for updating the window
     */
    void timerSlot();
    /**
     * @brief staticPlayers
     * @param p1 = name of first player
     * @param p2 = name of second player
     *
     * sets the name of the players for the game
     */
    void staticPlayers(QString p1, QString p2);
};

#endif // MYGLITEM_H
