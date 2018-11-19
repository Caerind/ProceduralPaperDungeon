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

	mPlayerHandle = mWorld.getEntityManager().createEntity<PlayerEntity>();

	mWorld.update(oe::Time::Zero);

	goToNextFloor();
}

bool GameState::handleEvent(const sf::Event& event)
{
	mWorld.handleEvent(event);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && mCurrentRoom->hasDoor(RoomData::Top))
    {
        unsigned int nextRoomIndex = mCurrentRoom->getRoomIndex(RoomData::Top);
        goToNextRoom(nextRoomIndex, mPlayerHandle->getPosition());
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right && mCurrentRoom->hasDoor(RoomData::Right))
    {
        unsigned int nextRoomIndex = mCurrentRoom->getRoomIndex(RoomData::Right);
        goToNextRoom(nextRoomIndex, mPlayerHandle->getPosition());
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && mCurrentRoom->hasDoor(RoomData::Bottom))
    {
        unsigned int nextRoomIndex = mCurrentRoom->getRoomIndex(RoomData::Bottom);
        goToNextRoom(nextRoomIndex, mPlayerHandle->getPosition());
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left && mCurrentRoom->hasDoor(RoomData::Left))
    {
        unsigned int nextRoomIndex = mCurrentRoom->getRoomIndex(RoomData::Left);
        goToNextRoom(nextRoomIndex, mPlayerHandle->getPosition());
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LControl)
    {
        goToNextFloor();
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
        goToNextFloor();
    }
}

void GameState::checkPlayerAndDoors()
{
    if (mDoorsRects[0].contains(oe::toSF(mPlayerHandle->getPosition())))
    {
        unsigned int nextRoomIndex = mCurrentRoom->getRoomIndex(RoomData::Top);
        goToNextRoom(nextRoomIndex, oe::Vector2(512, 648));
    }
    else if (mDoorsRects[1].contains(oe::toSF(mPlayerHandle->getPosition())))
    {
        unsigned int nextRoomIndex = mCurrentRoom->getRoomIndex(RoomData::Right);
        goToNextRoom(nextRoomIndex, oe::Vector2(160, 384));

    }
    else if (mDoorsRects[2].contains(oe::toSF(mPlayerHandle->getPosition())))
    {
        unsigned int nextRoomIndex = mCurrentRoom->getRoomIndex(RoomData::Bottom);
        goToNextRoom(nextRoomIndex, oe::Vector2(512, 120));
    }
    else if (mDoorsRects[3].contains(oe::toSF(mPlayerHandle->getPosition())))
    {
        unsigned int nextRoomIndex = mCurrentRoom->getRoomIndex(RoomData::Left);
        goToNextRoom(nextRoomIndex, oe::Vector2(874, 384));
    }
}

void GameState::goToNextRoom(unsigned int index, const oe::Vector2& playerPosition)
{
    if (mCurrentRoom != nullptr)
    {
        mCurrentRoom->clear();
    }
    mCurrentRoom.reset();
    mCurrentRoom = Room::Ptr(new Room(mWorld, mFloorData->getRoomData(index), mPlayerHandle));
    mWorld.getEntityManager().spawnEntities();
    generateDoorsRects();
    PlayerEntity* playerEntity = mPlayerHandle->getAs<PlayerEntity>();
    if (playerEntity != nullptr)
    {
        playerEntity->setPosition(playerPosition);
        playerEntity->setCurrentRoom(mCurrentRoom.get());
    }
}

void GameState::goToNextFloor()
{
    mLevel++;
	mFloorData = FloorData::Ptr(new FloorData(mSeed, mLevel));
	goToNextRoom(0, mPlayerHandle->getPosition());
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
