#include "GameState.hpp"

#include "GameConfig.hpp"

GameState::GameState(oe::StateManager& manager, const std::string& seed)
	: oe::State(manager)
	, mWorld(manager.getApplication())
	, mFloorData(nullptr)
	, mCurrentRoom(nullptr)
{
    mSeed = seed;
    mLevel = 0;

	mWorld.getRenderSystem().setBackgroundColor(oe::Color::DarkGray);
	mWorld.getRenderSystem().setView(oe::View(0, 0, WINSIZEX, WINSIZEY));
	mWorld.play();

	mFloorData = FloorData::Ptr(new FloorData(mSeed, mLevel));

	mCurrentRoom = Room::Ptr(new Room(mWorld, mFloorData->getRoomData(0)));

	mWorld.update(oe::Time::Zero);
}

bool GameState::handleEvent(const sf::Event& event)
{
	//OE_PROFILE_FUNCTION("GameState::handleEvent");

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && mCurrentRoom->hasDoor(RoomData::Top))
    {
        unsigned int nextRoomIndex = mCurrentRoom->getRoomIndex(RoomData::Top);
        mCurrentRoom.reset();
        mCurrentRoom = Room::Ptr(new Room(mWorld, mFloorData->getRoomData(nextRoomIndex)));
        mWorld.getEntityManager().update();
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right && mCurrentRoom->hasDoor(RoomData::Right))
    {
        unsigned int nextRoomIndex = mCurrentRoom->getRoomIndex(RoomData::Right);
        mCurrentRoom.reset();
        mCurrentRoom = Room::Ptr(new Room(mWorld, mFloorData->getRoomData(nextRoomIndex)));
        mWorld.getEntityManager().update();
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && mCurrentRoom->hasDoor(RoomData::Bottom))
    {
        unsigned int nextRoomIndex = mCurrentRoom->getRoomIndex(RoomData::Bottom);
        mCurrentRoom.reset();
        mCurrentRoom = Room::Ptr(new Room(mWorld, mFloorData->getRoomData(nextRoomIndex)));
        mWorld.getEntityManager().update();
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left && mCurrentRoom->hasDoor(RoomData::Left))
    {
        unsigned int nextRoomIndex = mCurrentRoom->getRoomIndex(RoomData::Left);
        mCurrentRoom.reset();
        mCurrentRoom = Room::Ptr(new Room(mWorld, mFloorData->getRoomData(nextRoomIndex)));
        mWorld.getEntityManager().update();
    }

	// Screenshot
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1)
	{
		getWindow().screenshot();
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F2)
	{
		/*
		if (mProfiler.isVisible())
		{
			mProfiler.hide();
		}
		else
		{
			mProfiler.show();
		}
		*/
		if (mDataViewer.isVisible())
		{
			mDataViewer.hide();
		}
		else
		{
			mDataViewer.show();
		}
	}

	return false;
}

bool GameState::update(oe::Time dt)
{
	//OE_PROFILE_FUNCTION("GameState::update");

	mWorld.update(dt);

	mDataViewer.setData("Floor-Seed", mFloorData->getSeed());
	mDataViewer.setData("Room-Index", oe::toString(mCurrentRoom->getIndex()));

	mDataViewer.draw();

	//mProfiler.draw();

	return false;
}

void GameState::render(sf::RenderTarget& target)
{
	//OE_PROFILE_FUNCTION("GameState::render");

	mWorld.render(target);
}

const std::string& GameState::getSeed() const
{
    return mSeed;
}

oe::Window& GameState::getWindow()
{
	return getApplication().getWindow();
}

oe::View& GameState::getView()
{
	return mWorld.getRenderSystem().getView();
}
