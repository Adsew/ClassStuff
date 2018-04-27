using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CharacterPicker : Photon.PunBehaviour
{
    public Text characterName;
    public Image characterImage;
    public PlayerListingView listing;

    [SerializeField]
    private List<Character> characters = new List<Character>();
    private int currentIndex;

    private void OnEnable()
    {
        currentIndex = 0;
        UpdateCharacter();
    }

    public void Left()
    {
        currentIndex--;
        if (currentIndex < 0)
        {
            currentIndex = characters.Count - 1;
        }

        UpdateCharacter();
    }

    public void Right()
    {
        currentIndex++;
        if (currentIndex > characters.Count - 1)
        {
            currentIndex = 0;
        }

        UpdateCharacter();
    }

    public Character GetCurrentCharacter()
    {
        if (currentIndex < 0 && currentIndex >= characters.Count)
        {
            return null;
        }

        return characters[currentIndex];
    }

    private void UpdateCharacter()
    {
        if (currentIndex < 0 && currentIndex >= characters.Count)
        {
            return;
        }

        if (characterName == null)
        {
            throw new System.NullReferenceException("Cannot update CharacterName without a valid reference");
        }

        if (characterImage == null)
        {
            throw new System.NullReferenceException("Cannot update CharacterImage witout a valid reference");
        }

        Character character = characters[currentIndex];
        LobbyManager.Instance.SelectedCharacter = character;
        characterName.text = character.characterName;
        characterImage.sprite = character.image;

        listing.UpdateCharacter(PhotonNetwork.player, character);

        var photonView = PhotonView.Get(this);
        photonView.RPC("RPC_CharacterChanged", PhotonTargets.Others, PhotonNetwork.player, character.characterName);
    }

    public override void OnPhotonPlayerConnected(PhotonPlayer newPlayer)
    {
        SendCurrentCharacter(newPlayer);
    }

    public void SendCurrentCharacter(PhotonPlayer newPlayer)
    {
        if (currentIndex >= 0 && currentIndex < characters.Count)
        {
            Character character = characters[currentIndex];
            var photonView = PhotonView.Get(this);
            photonView.RPC("RPC_CharacterChanged", newPlayer, PhotonNetwork.player, character.characterName);
        }
    }

    [PunRPC]
    public void RPC_CharacterChanged(PhotonPlayer player, string characterName)
    {
        Character character = characters.Find(item => item.characterName.Equals(characterName));
        if (character != null)
        {
            listing.UpdateCharacter(player, character);
        }
    }
}
