#include "player.h"

#include <algorithm>

Player::Player(/* args */)
{
}

void Player::addPiece(Piece* piece)
{
    ownedPieces.push_back(piece);
}

void Player::removePiece(Piece* piece)
{
    ownedPieces.erase(std::remove(ownedPieces.begin(), ownedPieces.end(), piece));
}