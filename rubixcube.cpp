#include "rubixcube.h"

RubixCube::RubixCube(QGLWidget *widget)
{
    int idx = 0;

    for(int w = 1; w >= -1; w--)
        for(int j = 1; j >= -1; j--)
            for(int i = -1; i <= 1; i++)
                pieces[idx++] = new CubePiece(widget, RUBIX_DISTANCE_OF_PEICES, i, j, w);

    vecx = QVector3D(1,0,0);
    vecy = QVector3D(0,1,0);
    vecz = QVector3D(0,0,1);

    mv.finalAngle = 0;
    mv.type = Rubix::noMove;
    mv.speed = 0;

    this->widget = widget;

    timer = NULL;
}

RubixCube::~RubixCube()
{
    for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ ) {
        delete pieces[i];
        pieces[i] = NULL;
    }
}

void RubixCube::rotate(float angle, const QVector3D &vec)
{
    for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
        pieces[i]->rotate(angle, vec);

    QMatrix4x4 operation;
    operation.setToIdentity();
    operation.rotate(angle, vec);

    vecx = operation * vecx;
    vecy = operation * vecy;
    vecz = operation * vecz;
}

void RubixCube::translate(const QVector3D &vec)
{
    for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
        pieces[i]->translate(vec);
}

void RubixCube::set_pMatrix(QMatrix4x4 pMatrix)
{
    for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
        pieces[i]->set_pMatrix(pMatrix);
}

void RubixCube::set_vMatrix(QMatrix4x4 vMatrix)
{
    for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
        pieces[i]->set_vMatrix(vMatrix);
}

void RubixCube::drawObject()
{
    for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
        pieces[i]->drawObject();
}

void RubixCube::rotateR(float angle)
{
    for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
        if( pieces[i]->idxx() == 1 )
            pieces[i]->rotate(angle, vecx);
}

void RubixCube::rotateL(float angle)
{
    for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
        if( pieces[i]->idxx() == -1 )
            pieces[i]->rotate(angle, vecx);
}

void RubixCube::rotateB(float angle)
{
    for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
        if( pieces[i]->idxz() == -1 )
            pieces[i]->rotate(angle, vecz);
}

void RubixCube::rotateD(float angle)
{
    for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
        if( pieces[i]->idxy() == -1 )
            pieces[i]->rotate(angle, vecy);
}

void RubixCube::rotateF(float angle)
{
    for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
        if( pieces[i]->idxz() == 1 )
            pieces[i]->rotate(angle, vecz);
}

void RubixCube::rotateU(float angle)
{
    for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
        if( pieces[i]->idxy() == 1 )
            pieces[i]->rotate(angle, vecy);
}

void RubixCube::movement(const Rubix::MoveType move)
{
    //TODO: Implements other movements like SHUFFLE and ROTATE

    if(timer == NULL)
    {
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(timerInterrupt()));
        timer->start(RUBIX_TIMER_TIMEOUT_MS);

        mv.type = move;
        mv.finalAngle = 90;
        mv.speed = 180;
    }
}

void RubixCube::commitMovement(const Rubix::MoveType move)
{
//    int idx = 0;

//    for(int w = 1; w >= -1; w--)
//        for(int j = 1; j >= -1; j--)
//            for(int i = -1; i <= 1; i++)
//                pieces[idx++]->setidx(i,j,w);

//    vecx = QVector3D(1,0,0);
//    vecy = QVector3D(0,1,0);
//    vecz = QVector3D(0,0,1);

    QMatrix4x4 operation;
    QVector3D vec;

    switch(move) {

        case Rubix::Rmove:

            operation.rotate(90, vecx);

            for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
            {
                if( pieces[i]->idxx() == 1 )
                {
                    vec.setX(pieces[i]->idxx());
                    vec.setY(pieces[i]->idxy());
                    vec.setZ(pieces[i]->idxz());

                    vec = operation * vec;

                    pieces[i]->setidx(vec.x(), vec.y(), vec.z());
                }
            }
            break;

        case Rubix::rmove:

            operation.rotate(-90, vecx);

            for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
            {
                if( pieces[i]->idxx() == 1 )
                {
                    vec.setX(pieces[i]->idxx());
                    vec.setY(pieces[i]->idxy());
                    vec.setZ(pieces[i]->idxz());

                    vec = operation * vec;

                    pieces[i]->setidx(vec.x(), vec.y(), vec.z());
                }
            }
            break;

        case Rubix::Lmove:

            operation.rotate(90, vecx);

            for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
            {
                if( pieces[i]->idxx() == -1 )
                {
                    vec.setX(pieces[i]->idxx());
                    vec.setY(pieces[i]->idxy());
                    vec.setZ(pieces[i]->idxz());

                    vec = operation * vec;

                    pieces[i]->setidx(vec.x(), vec.y(), vec.z());
                }
            }
            break;

        case Rubix::lmove:

            operation.rotate(-90, vecx);

            for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
            {
                if( pieces[i]->idxx() == -1 )
                {
                    vec.setX(pieces[i]->idxx());
                    vec.setY(pieces[i]->idxy());
                    vec.setZ(pieces[i]->idxz());

                    vec = operation * vec;

                    pieces[i]->setidx(vec.x(), vec.y(), vec.z());
                }
            }
            break;

        case Rubix::Bmove:

            operation.rotate(90, vecz);

            for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
            {
                if( pieces[i]->idxz() == -1 )
                {
                    vec.setX(pieces[i]->idxx());
                    vec.setY(pieces[i]->idxy());
                    vec.setZ(pieces[i]->idxz());

                    vec = operation * vec;

                    pieces[i]->setidx(vec.x(), vec.y(), vec.z());
                }
            }
            break;

        case Rubix::bmove:

            operation.rotate(-90, vecz);

            for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
            {
                if( pieces[i]->idxz() == -1 )
                {
                    vec.setX(pieces[i]->idxx());
                    vec.setY(pieces[i]->idxy());
                    vec.setZ(pieces[i]->idxz());

                    vec = operation * vec;

                    pieces[i]->setidx(vec.x(), vec.y(), vec.z());
                }
            }
            break;

        case Rubix::Dmove:

            operation.rotate(90, vecy);

            for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
            {
                if( pieces[i]->idxy() == -1 )
                {
                    vec.setX(pieces[i]->idxx());
                    vec.setY(pieces[i]->idxy());
                    vec.setZ(pieces[i]->idxz());

                    vec = operation * vec;

                    pieces[i]->setidx(vec.x(), vec.y(), vec.z());
                }
            }
            break;

        case Rubix::dmove:

            operation.rotate(-90, vecy);

            for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
            {
                if( pieces[i]->idxy() == -1 )
                {
                    vec.setX(pieces[i]->idxx());
                    vec.setY(pieces[i]->idxy());
                    vec.setZ(pieces[i]->idxz());

                    vec = operation * vec;

                    pieces[i]->setidx(vec.x(), vec.y(), vec.z());
                }
            }
            break;

        case Rubix::Fmove:

            operation.rotate(90, vecz);

            for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
            {
                if( pieces[i]->idxz() == 1 )
                {
                    vec.setX(pieces[i]->idxx());
                    vec.setY(pieces[i]->idxy());
                    vec.setZ(pieces[i]->idxz());

                    vec = operation * vec;

                    pieces[i]->setidx(vec.x(), vec.y(), vec.z());
                }
            }
            break;

        case Rubix::fmove:

            operation.rotate(-90, vecz);

            for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
            {
                if( pieces[i]->idxz() == 1 )
                {
                    vec.setX(pieces[i]->idxx());
                    vec.setY(pieces[i]->idxy());
                    vec.setZ(pieces[i]->idxz());

                    vec = operation * vec;

                    pieces[i]->setidx(vec.x(), vec.y(), vec.z());
                }
            }
            break;

        case Rubix::Umove:

            operation.rotate(90, vecy);

            for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
            {
                if( pieces[i]->idxy() == 1 )
                {
                    vec.setX(pieces[i]->idxx());
                    vec.setY(pieces[i]->idxy());
                    vec.setZ(pieces[i]->idxz());

                    vec = operation * vec;

                    pieces[i]->setidx(vec.x(), vec.y(), vec.z());
                }
            }
            break;

        case Rubix::umove:

            operation.rotate(-90, vecy);

            for( int i = 0; i < RUBIX_NUMBER_OF_PIECES; i++ )
            {
                if( pieces[i]->idxy() == 1 )
                {
                    vec.setX(pieces[i]->idxx());
                    vec.setY(pieces[i]->idxy());
                    vec.setZ(pieces[i]->idxz());

                    vec = operation * vec;

                    pieces[i]->setidx(vec.x(), vec.y(), vec.z());
                }
            }
            break;

        default:
            break;
    }
}

void RubixCube::timerInterrupt()
{
    static float angle_acc = 0;

    switch(mv.type) {

        case Rubix::Rmove:
            rotateR(mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3);
            angle_acc += mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3;
            break;

        case Rubix::rmove:
            rotateR(-mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3);
            angle_acc += mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3;
            break;

        case Rubix::Lmove:
            rotateL(mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3);
            angle_acc += mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3;
            break;

        case Rubix::lmove:
            rotateL(-mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3);
            angle_acc += mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3;
            break;

        case Rubix::Bmove:
            rotateB(mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3);
            angle_acc += mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3;
            break;

        case Rubix::bmove:
            rotateB(-mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3);
            angle_acc += mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3;
            break;

        case Rubix::Dmove:
            rotateD(mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3);
            angle_acc += mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3;
            break;

        case Rubix::dmove:
            rotateD(-mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3);
            angle_acc += mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3;
            break;

        case Rubix::Fmove:
            rotateF(mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3);
            angle_acc += mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3;
            break;

        case Rubix::fmove:
            rotateF(-mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3);
            angle_acc += mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3;
            break;

        case Rubix::Umove:
            rotateU(mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3);
            angle_acc += mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3;
            break;

        case Rubix::umove:
            rotateU(-mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3);
            angle_acc += mv.speed*RUBIX_TIMER_TIMEOUT_MS*1e-3;
            break;

        default:
            break;
    }

    if( angle_acc == mv.finalAngle )
    {
        angle_acc = 0;

        commitMovement(mv.type);

        delete timer;
        timer = NULL;

        mv.finalAngle = 0;
        mv.speed = 0;
        mv.type = Rubix::noMove;
    }

    widget->updateGL();
}
