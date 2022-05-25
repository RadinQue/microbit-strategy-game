#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "fmath.h"

// this whole side thing was a bad idea and
// now i regret everything
// refactor if you can please
enum ESide : uint8_t
{
    Pins,
    Port
};

class Player
{
public:
    Player() {}
    Player(class Scene* scene, ESide playerSide);
    
    void addPiece(class Piece* piece);
    void removePiece(Piece* piece);

    std::vector<Piece*> getOwnedPieces() const { return ownedPieces; }

    bool tryPickUpPiece(Piece* pieceToPickUp);
    bool tryPickUpPiece();
    bool tryPutPiece(const Point& location);

    void onButtonA();
    void onLongButtonA();
    void onButtonB();
    void onLongButtonB();

    ESide side;

    void combatPieces(Piece* own, Piece* other);

    void passTurn();

private:
    Scene* scene;

    void pickUpPiece(Piece* pieceToPickUp);
    void putPiece(const Point& location);
    void dropPiece();

    std::vector<Piece*> ownedPieces;
    Piece* pickedUpPiece;
};

#endif