using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerListing : MonoBehaviour
{

    public PhotonPlayer PhotonPlayer { get; private set; }

    [SerializeField] Image characterImage;
    [SerializeField] Text playerName;


    public void UpdateCharacter(Character character)
    {
        Debug.Assert(character != null && character.image != null, "Cannot update character without valid parameters");
        if (character != null && character.image != null)
        {
            characterImage.sprite = character.image;
        }
    }

    public void SetupPhotonPlayer(PhotonPlayer player)
    {
        string prefix = "";
        if (PhotonNetwork.player == player)
        {
            prefix = "(You) ";
        }
        PhotonPlayer = player;
        playerName.text = prefix + player.NickName;
    }
}
