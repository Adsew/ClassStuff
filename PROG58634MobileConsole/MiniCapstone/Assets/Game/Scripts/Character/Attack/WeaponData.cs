using UnityEngine;

[CreateAssetMenu(fileName = "New Weapon Data", menuName = "Weapon/Data", order = 1)]
public class WeaponData : ScriptableObject
{
    public string weaponName;
    public int damage;
}
