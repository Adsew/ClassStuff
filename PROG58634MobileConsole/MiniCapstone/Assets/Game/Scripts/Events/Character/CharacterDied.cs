using UnityEngine;
using System.Collections;

public class CharacterDied : EventHandler.Event
{
    public GameCharacter Character { get; private set; }

    public CharacterDied(GameCharacter gameCharacter)
    {
        Character = gameCharacter;
    }
}
