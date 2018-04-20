#include "GameCore.h"
#include "InputController.h"
#include "GameObjectManager.h"
#include "Transform.h"

IMPLEMENT_DYNAMIC_CLASS(InputController)

void InputController::update(float deltaTime)
{
    Component::update(deltaTime);

    if (NetworkServer::Instance().isServer())
    {
        return;
    }

    clicked = false;

    if (InputManager::Instance().mouseReleased(sf::Mouse::Button::Left))
    {
        mousePosition = InputManager::Instance().getMousePosition();
        clicked = true;
        //TODO: Create a Bitstream and call writeGameObjectUpdate in the GameObjectManager (don't forget to send the BS!)

    }
}

void InputController::writeUpdate(RakNet::BitStream& bs) const
{
    Component::writeUpdate(bs);
    std::cout << "C: I exist always";
    // Since updates are called on the server and we only want to send data from the Client, make sure you only write the
    // mouse position when we are a client
    if (NetworkClient::Instance().isClient())
    {
        bs.Write(mousePosition);
        bs.Write(clicked);
        std::cout << "C: I exist";
    }
}

void InputController::readUpdate(RakNet::BitStream& bs)
{
	Component::readUpdate(bs);
    std::cout << "S: I exist always";
	// Since updates are called on the server and we only want to send data from the Client, make sure you only read the
	// mouse position when we are a server
    if (NetworkServer::Instance().isServer())
    {
        bs.Read(mousePosition);
        bs.Read(clicked);
        std::cout << "S: I exist";
        if (clicked)
        {
            // Finally we need to determine how to detect a collision with the raindrops.
            // Where should this be done?
            std::list<GameObject *> gObjList = GameObjectManager::Instance().GetAllRootGameObjects();

            for (auto iter = gObjList.begin(); iter != gObjList.end(); ++iter)
            {
                Transform *trans = (Transform *)(*iter)->GetComponentByType(Transform::getClassName());

                if (trans != NULL)
                {
                    // Once you figure where you want to do the collision test, determine if the click was on a RainDrop and if so
                    // destroy that raindrop
                    float dist = sqrt(pow(mousePosition.x - trans->getPosition().x, 2) + pow(mousePosition.y - trans->getPosition().y, 2));

                    std::cout << "Mouse: " << mousePosition.x << ", " << mousePosition.y << " Drop: " << trans->getPosition().x << ", " << trans->getPosition().y << " Dist: " << dist;

                    if (dist < 20.0f)
                    {
                        GameObjectManager::Instance().DestroyGameObject(*iter);
                    }
                }
            }
        }
    }
}
