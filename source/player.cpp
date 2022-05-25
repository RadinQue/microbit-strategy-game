#include "player.h"
#include "piece.h"
#include "scene.h"
#include "widgets/widget.h"
#include "widgets/w_piece_info.h"
#include "types/cast_types.h"
#include "combat.h"
#include "types/combat_types.h"
#include "cursor.h"

#include <algorithm>

Player::Player(Scene* scene, ESide playerSide)
{
    this->scene = scene;
    side = playerSide;
}

void Player::onButtonA()
{
    if(scene->InputTarget == EInputTarget::EIT_Widgets)
    {
        if(Widget* currWidget = scene->getCurrentWidget())
        {
            if(side == ESide::Pins)
                currWidget->onBack();
            else
                currWidget->onSelect();
        }

        return;
    }
    else if(scene->InputTarget == EInputTarget::EIT_Board)
    {
        if(side == ESide::Pins)
        {
            if(pickedUpPiece)
                dropPiece();
        }
        else
        {
            if(!pickedUpPiece)
            {
                tryPickUpPiece();
            }
            else
            {
                if(tryPutPiece(scene->getCursor()->getLocation()))
                {
                    passTurn();
                }
                else
                    dropPiece();
            }
        }
    }
}

void Player::onLongButtonA()
{
    if(scene->InputTarget == EInputTarget::EIT_Widgets)
    {
        if(Widget* currWidget = scene->getCurrentWidget())
        {
            if(side == ESide::Pins)
                currWidget->onLongBack();
            else
                currWidget->onLongSelect();
        }

        return;
    }
    else if(scene->InputTarget == EInputTarget::EIT_Board)
    {
        if(side == ESide::Pins)
        {
        }
        else
        {
            WPieceInfo* infoWidget = scene->createWidget<WPieceInfo>();

            FCastQuery castQuery;
            castQuery.filteredObjects.push_back(scene->getCursor());
            if(Object* foundObject = scene->getObjectAtLocation(scene->getCursor()->getLocation(), castQuery))
            {
                if(Piece* piece = static_cast<Piece*>(foundObject))
                {
                    infoWidget->init(piece);
                    infoWidget->pushToViewport();
                }
            }
        }
    }
}

void Player::onButtonB()
{
    if(scene->InputTarget == EInputTarget::EIT_Widgets)
    {
        if(Widget* currWidget = scene->getCurrentWidget())
        {
            if(side == ESide::Pins)
                currWidget->onSelect();
            else
                currWidget->onBack();
        }

        return;
    }
    else if(scene->InputTarget == EInputTarget::EIT_Board)
    {
        if(side == ESide::Pins)
        {
            if(!pickedUpPiece)
            {
                tryPickUpPiece();
            }
            else
            {
                if(tryPutPiece(scene->getCursor()->getLocation()))
                {
                    passTurn();
                }
                else
                    dropPiece();
            }

            // // todo: remove
            // FCastQuery castQuery;
            // castQuery.filteredObjects.push_back(scene->getCursor());

            // if(Object* foundObject = scene->getObjectAtLocation(scene->getCursor()->getLocation(), castQuery))
            // {
            //     foundObject->destroy();
            // }
        }
        else
        {
            if(pickedUpPiece)
                dropPiece();
        }
    }
}

void Player::onLongButtonB()
{
    if(scene->InputTarget == EInputTarget::EIT_Widgets)
    {
        if(Widget* currWidget = scene->getCurrentWidget())
        {
            if(side == ESide::Pins)
                currWidget->onLongSelect();
            else
                currWidget->onLongBack();
        }

        return;
    }
    else if(scene->InputTarget == EInputTarget::EIT_Board)
    {
        if(side == ESide::Pins)
        {
            WPieceInfo* infoWidget = scene->createWidget<WPieceInfo>();

            FCastQuery castQuery;
            castQuery.filteredObjects.push_back(scene->getCursor());
            if(Object* foundObject = scene->getObjectAtLocation(scene->getCursor()->getLocation(), castQuery))
            {
                if(Piece* piece = static_cast<Piece*>(foundObject))
                {
                    infoWidget->init(piece);
                    infoWidget->pushToViewport();
                }
            }
        }
        else
        {
        }
    }
}

void Player::addPiece(Piece* piece)
{
    ownedPieces.push_back(piece);
}

void Player::removePiece(Piece* piece)
{
    ownedPieces.erase(std::remove(ownedPieces.begin(), ownedPieces.end(), piece));
}

bool Player::tryPickUpPiece(Piece* pieceToPickUp)
{
    if(!pieceToPickUp)
        return false;

    if(pickedUpPiece)
        return false;

    pickUpPiece(pieceToPickUp);
    return true;
}

bool Player::tryPickUpPiece()
{
    if(pickedUpPiece)
        return false;

    FCastQuery castQuery;
    castQuery.filteredObjects.push_back(scene->getCursor());

    if(Object* foundObject = scene->getObjectAtLocation(scene->getCursor()->getLocation(), castQuery))
    {
        if(Piece* foundPiece = static_cast<Piece*>(foundObject))
        {
            return tryPickUpPiece(foundPiece);
        }
    }

    return false;
}

void Player::pickUpPiece(Piece* pieceToPickUp)
{
    if(!pieceToPickUp)
        return;

    if(pieceToPickUp->getOwner() != this)
        return;

    pieceToPickUp->setVisibility(false);
    pickedUpPiece = pieceToPickUp;
}

bool Player::tryPutPiece(const Point& location)
{
    if(!pickedUpPiece)
        return false;

    if(!pickedUpPiece->getScene())
        return false;

    Scene* scene = pickedUpPiece->getScene();

    if(scene->getCursor() == nullptr)
        return false;

    if(!pickedUpPiece->canMoveAtLocation(location))
        return false;

    FCastQuery castQuery;
    castQuery.filteredObjects.push_back(scene->getCursor());

    Object* foundObject = scene->getObjectAtLocation(location, castQuery);
    if(foundObject)
    {
        if(Piece* foundPiece = static_cast<Piece*>(foundObject))
        {
            if(foundPiece->getOwner() != pickedUpPiece->getOwner())
            {
                combatPieces(pickedUpPiece, foundPiece);
                return true;
            }
        }

        return false;
    }

    putPiece(location);
    return true;
}

void Player::putPiece(const Point& location)
{
    if(!pickedUpPiece)
        return;
        
    pickedUpPiece->move(location);
    pickedUpPiece->setVisibility(true);
    pickedUpPiece = nullptr;
}

void Player::dropPiece()
{
    if(!pickedUpPiece)
        return;
        
    pickedUpPiece->setVisibility(true);
    pickedUpPiece = nullptr;
}

void Player::combatPieces(Piece* own, Piece* other)
{
    Combat combat(own, other);
    ECombatResult result = combat.processCombat();

    switch (result)
    {
    case Tie:
        dropPiece();
        break;

    case AttackerWins:
        putPiece(scene->getCursor()->getLocation());
        break;

    default:
        break;
    }
}

void Player::passTurn()
{
    scene->switchTurnFrom(this);
}
