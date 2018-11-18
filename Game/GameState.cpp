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

	mPlayerHandle = mWorld.getEntityManager().createEntity<PlayerEntity>();

	mCurrentRoom = Room::Ptr(new Room(mWorld, mFloorData->getRoomData(0), mPlayerHandle));

	mWorld.update(oe::Time::Zero);

    generateDoorsRects();
}

bool GameState::handleEvent(const sf::Event& event)
{
	mWorld.handleEvent(event);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && mCurrentRoom->hasDoor(RoomData::Top))
    {
        unsigned int nextRoomIndex = mCurrentRoom->getRoomIndex(RoomData::Top);
        mCurrentRoom.reset();
        mCurrentRoom = Room::Ptr(new Room(mWorld, mFloorData->getRoomData(nextRoomIndex), mPlayerHandle));
        mWorld.getEntityManager().update();
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right && mCurrentRoom->hasDoor(RoomData::Right))
    {
        unsigned int nextRoomIndex = mCurrentRoom->getRoomIndex(RoomData::Right);
        mCurrentRoom.reset();
        mCurrentRoom = Room::Ptr(new Room(mWorld, mFloorData->getRoomData(nextRoomIndex), mPlayerHandle));
        mWorld.getEntityManager().update();
        generateDoorsRects();
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && mCurrentRoom->hasDoor(RoomData::Bottom))
    {
        unsigned int nextRoomIndex = mCurrentRoom->getRoomIndex(RoomData::Bottom);
        mCurrentRoom.reset();
        mCurrentRoom = Room::Ptr(new Room(mWorld, mFloorData->getRoomData(nextRoomIndex), mPlayerHandle));
        mWorld.getEntityManager().update();
        generateDoorsRects();
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left && mCurrentRoom->hasDoor(RoomData::Left))
    {
        unsigned int nextRoomIndex = mCurrentRoom->getRoomIndex(RoomData::Left);
        mCurrentRoom.reset();
        mCurrentRoom = Room::Ptr(new Room(mWorld, mFloorData->getRoomData(nextRoomIndex), mPlayerHandle));
        mWorld.getEntityManager().update();
        generateDoorsRects();
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LControl)
    {
         // TODO : Go to higher floor
        printf("go\n");
    }

	// Screenshot
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1)
	{
		getWindow().screenshot();
	}

	return false;
}

bool GameState::update(oe::Time dt)
{
	mWorld.update(dt);

	checkPlayerAndRoom();
    checkPlayerAndDoors();

	return false;
}

void GameState::render(sf::RenderTarget& target)
{
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

void GameState::checkPlayerAndRoom()
{
	if (mCurrentRoom != nullptr && mCurrentRoom->update())
    {
        // TODO : Go to higher floor
        printf("go\n");
    }
}

void GameState::checkPlayerAndDoors()
{
    if (mDoorsRects[0].contains(oe::toSF(mPlayerHandle->getPosition())))
    {
        unsigned int nextRoomIndex = mCurrentRoom->getRoomIndex(RoomData::Top);
        mCurrentRoom.reset();
        mCurrentRoom = Room::Ptr(new Room(mWorld, mFloorData->getRoomData(nextRoomIndex), mPlayerHandle));
        mWorld.getEntityManager().update();
        mPlayerHandle->setPosition(512, 648);
        generateDoorsRects();
    }
    else if (mDoorsRects[1].contains(oe::toSF(mPlayerHandle->getPosition())))
    {
        unsigned int nextRoomIndex = mCurrentRoom->getRoomIndex(RoomData::Right);
        mCurrentRoom.reset();
        mCurrentRoom = Room::Ptr(new Room(mWorld, mFloorData->getRoomData(nextRoomIndex), mPlayerHandle));
        mWorld.getEntityManager().update();
        mPlayerHandle->setPosition(160, 384);
        generateDoorsRects();

    }
    else if (mDoorsRects[2].contains(oe::toSF(mPlayerHandle->getPosition())))
    {
        unsigned int nextRoomIndex = mCurrentRoom->getRoomIndex(RoomData::Bottom);
        mCurrentRoom.reset();
        mCurrentRoom = Room::Ptr(new Room(mWorld, mFloorData->getRoomData(nextRoomIndex), mPlayerHandle));
        mWorld.getEntityManager().update();
        mPlayerHandle->setPosition(512, 120);
        generateDoorsRects();
    }
    else if (mDoorsRects[3].contains(oe::toSF(mPlayerHandle->getPosition())))
    {
        unsigned int nextRoomIndex = mCurrentRoom->getRoomIndex(RoomData::Left);
        mCurrentRoom.reset();
        mCurrentRoom = Room::Ptr(new Room(mWorld, mFloorData->getRoomData(nextRoomIndex), mPlayerHandle));
        mWorld.getEntityManager().update();
        mPlayerHandle->setPosition(874, 384);
        generateDoorsRects();
    }
}

void GameState::generateDoorsRects()
{
    if (mCurrentRoom == nullptr)
    {
        return;
    }

    if (mCurrentRoom->hasDoor(RoomData::Top))
    {
        mDoorsRects[0] = sf::FloatRect(482, 80, 60, 30);
    }
    else
    {
        mDoorsRects[0] = sf::FloatRect(0, 0, 0, 0);
    }
    if (mCurrentRoom->hasDoor(RoomData::Right))
    {
        mDoorsRects[1] = sf::FloatRect(904, 354, 40, 60);
    }
    else
    {
        mDoorsRects[1] = sf::FloatRect(0, 0, 0, 0);
    }
    if (mCurrentRoom->hasDoor(RoomData::Bottom))
    {
        mDoorsRects[2] = sf::FloatRect(482, 658, 60, 30);
    }
    else
    {
        mDoorsRects[2] = sf::FloatRect(0, 0, 0, 0);
    }
    if (mCurrentRoom->hasDoor(RoomData::Left))
    {
        mDoorsRects[3] = sf::FloatRect(80, 354, 40, 60);
    }
    else
    {
        mDoorsRects[3] = sf::FloatRect(0, 0, 0, 0);
    }
}
