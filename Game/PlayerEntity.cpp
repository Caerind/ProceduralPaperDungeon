#include "PlayerEntity.hpp"
#include <iostream>
#include "Projectile.hpp"

#include "../Engine/Core/World.hpp"
#include "../Engine/Application/Application.hpp"

PlayerEntity::PlayerEntity(oe::EntityManager& manager)
    : Entity(manager)
    , mAction(*this)

{
    // First load sprite
    mSprite.setTexture(mTilesetTexture);
    mSprite.setTextureRect(sf::IntRect(12, 5, 58, 70));
    mSprite.setPositionZ(10.0f);
    mSprite.setPosition(-26.5f, -65.0f);

    setPosition(512, 394);

    mLife = 100;
    mLifeMax = 0;
    mStrength = 10;
    mMovementSpeed = 200;
    mFireSpeed = 200.0f;
    mFireLimit = oe::seconds(0.1f);
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

void PlayerEntity::update(oe::Time dt)
{
    mFireCooldown += dt;

    oe::Vector2 mvt;
	bool moved = determineMovement(mvt);
	if (moved)
	{
		tryMove(dt, mvt);
	}
}

bool PlayerEntity::shoot()
{
    const oe::Vector2 pos = getApplication().getWindow().getCursorPositionView(getWorld().getRenderSystem().getView());
	if (mFireCooldown >= mFireLimit )
	{
        oe::Vector2 pos2 = getPosition() - oe::Vector2(18.0f, 18.0f);
		oe::Vector2 delta = pos - pos2;
		delta.normalize();

		getManager().createEntity<Projectile>(pos2, delta, mStrength, mFireSpeed);

		mFireCooldown = oe::Time::Zero;

		return true;
	}
	return false;
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
