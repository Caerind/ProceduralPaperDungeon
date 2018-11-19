#include "PlayerEntity.hpp"
#include <iostream>
#include "Projectile.hpp"

#include "../Engine/Core/World.hpp"
#include "../Engine/Application/Application.hpp"

PlayerEntity::PlayerEntity(oe::EntityManager& manager)
    : Entity(manager)
    , mAction(*this)
    , mCurrentRoom(nullptr)

{
    // First load Tileset
    mSprite.setTexture(mTilesetTexture);
    // Then select sprite
    mSprite.setTextureRect(sf::IntRect(12, 5, 58, 70));
    // Priority of the sprite
    mSprite.setPositionZ(10.0f);
    // Adjust the position of the sprite
    mSprite.setPosition(-26.5f, -65.0f);

    // Position of the player entity at start
    setPosition(512, 394);

    // Stat of the player entity at start
    mLife = 100;                        // Life of the player can be healed
    mLifeMax = 100;                     // Max life of the player can be improve by chest and boss fight
    mStrength = 10;                     // Strengh of the player can be improve by chest and boss fight
    mMovementSpeed = 200;               // Movement speed of the player
    mFireSpeed = 200.0f;                // Speed of the projectile
    mFireLimit = oe::seconds(0.5f);     // Time between two shots
    mFireCooldown = mFireLimit;

    loadInputs();

    oe::ActionId shootAction = mAction.addAction("shoot");
    mAction.setInput(shootAction, &mShootInput);
    mAction.addOutput(shootAction, [this]() { shoot(); });
}

PlayerEntity::~PlayerEntity()
{
}

void PlayerEntity::loadInputs()
{
	mUp.setKey(sf::Keyboard::Z);
	mUp.setType(oe::ActionType::Hold);
	mUp2.setKey(sf::Keyboard::W);
	mUp2.setType(oe::ActionType::Hold);
	mLeft.setKey(sf::Keyboard::Q);
	mLeft.setType(oe::ActionType::Hold);
	mLeft2.setKey(sf::Keyboard::A);
	mLeft2.setType(oe::ActionType::Hold);
	mDown.setKey(sf::Keyboard::S);
	mDown.setType(oe::ActionType::Hold);
	mRight.setKey(sf::Keyboard::D);
	mRight.setType(oe::ActionType::Hold);
	mShootInput.setButton(sf::Mouse::Right);
	mShootInput.setType(oe::ActionType::Pressed);
}

void PlayerEntity::setCurrentRoom(Room* room)
{
    mCurrentRoom = room;
}

void PlayerEntity::update(oe::Time dt)
{
    mFireCooldown += dt;

    oe::Vector2 mvt;
	bool moved = determineMovement(mvt);
	if (moved)
	{
		moved = tryMove(dt, mvt);
		if (moved)
		{

		}
	}
    else
    {

    }
}

bool PlayerEntity::shoot()
{
    const oe::Vector2 pos = getApplication().getWindow().getCursorPositionView(getWorld().getRenderSystem().getView());
	if (mFireCooldown >= mFireLimit && mCurrentRoom != nullptr)
	{
        oe::Vector2 pos2 = getPosition() - oe::Vector2(18.0f, 18.0f);
		oe::Vector2 delta = pos - pos2;
		delta.normalize();

        mCurrentRoom->addEntity(getManager().createEntity<Projectile>(pos2, delta, mStrength, mFireSpeed));

		mFireCooldown = oe::Time::Zero;

		return true;
	}
	return false;
}

void PlayerEntity::increase()
{
    // TODO : Increase some stats randomly
}

bool PlayerEntity::determineMovement(oe::Vector2& mvt)
{
	bool moved = false;

	bool left = (sf::Keyboard::isKeyPressed(mLeft.getKey()) || sf::Keyboard::isKeyPressed(mLeft2.getKey()));
	bool right = sf::Keyboard::isKeyPressed(mRight.getKey());
	bool up = (sf::Keyboard::isKeyPressed(mUp.getKey()) || sf::Keyboard::isKeyPressed(mUp2.getKey()));
	bool down = sf::Keyboard::isKeyPressed(mDown.getKey());

	if (left && !right)
	{
		mvt.x--;
		moved = true;
	}
	else if (right && !left)
	{
		mvt.x++;
		moved = true;
	}

	if (up && !down)
	{
		mvt.y--;
		moved = true;
	}
	else if (down && !up)
	{
		mvt.y++;
		moved = true;
	}

	return moved;
}

oe::ActionInputKey PlayerEntity::mUp;
oe::ActionInputKey PlayerEntity::mUp2;
oe::ActionInputKey PlayerEntity::mLeft;
oe::ActionInputKey PlayerEntity::mLeft2;
oe::ActionInputKey PlayerEntity::mDown;
oe::ActionInputKey PlayerEntity::mRight;
oe::ActionInputMouse PlayerEntity::mShootInput;
