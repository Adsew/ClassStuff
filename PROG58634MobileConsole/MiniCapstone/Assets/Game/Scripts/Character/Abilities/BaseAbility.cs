using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class BaseAbility : Photon.PunBehaviour
{
    public abstract void Execute();
    public virtual void Finish() { }

    public virtual void ApplyDamage(GameCharacter gameCharacter) { }
}
