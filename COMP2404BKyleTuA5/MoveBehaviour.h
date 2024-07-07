#ifndef MOVEBEHAVIOUR_H
#define MOVEBEHAVIOUR_H

class MoveBehaviour {
public:
    virtual ~MoveBehaviour() {}
    virtual void move(int oldRow, int oldCol, int& newRow, int& newCol) = 0;
};

#endif