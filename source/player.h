#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

class Player
{
public:
    Player(/* args */);
    
    void addPiece(class Piece* piece);
    void removePiece(Piece* piece);

    std::vector<Piece*> getOwnedPieces() const { return ownedPieces; }

private:
    std::vector<Piece*> ownedPieces;
};

#endif