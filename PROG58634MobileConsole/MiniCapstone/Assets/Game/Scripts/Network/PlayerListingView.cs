using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerListingView : Photon.PunBehaviour
{
    [SerializeField]
    private GameObject listingPrefab;

    private List<PlayerListing> listings = new List<PlayerListing>();

    //private void Start()
    //{
    //    ClearListings();
    //    UpdatePlayerListing();
    //}

    private void OnEnable()
    {
        ClearListings();
        UpdatePlayerListing();
    }

    public override void OnJoinedRoom()
    {
        ClearListings();
        UpdatePlayerListing();
    }

    private void ClearListings()
    {
        foreach (var listing in listings)
        {
            Destroy(listing.gameObject);
        }

        listings.Clear();
    }

    private void UpdatePlayerListing()
    {
        PhotonPlayer[] players = PhotonNetwork.playerList;
        for (int i = 0; i < players.Length; i++)
        {
            PlayerJoinedRoom(players[i]);
        }
    }

    public override void OnPhotonPlayerConnected(PhotonPlayer newPlayer)
    {
        PlayerJoinedRoom(newPlayer);
    }

    public override void OnPhotonPlayerDisconnected(PhotonPlayer otherPlayer)
    {
        PlayerLeftRoom(otherPlayer);
    }

    private void PlayerJoinedRoom(PhotonPlayer player)
    {
        if (player == null)
        {
            Debug.LogWarning("Player joined room found to be null");
            return;
        }

        PlayerLeftRoom(player);

        if (listingPrefab == null)
        {
            throw new System.NullReferenceException("ListingPrefab must be set to use ListingView");
        }

        GameObject listing = Instantiate(listingPrefab);
        // set the parent to the list and don't keep its position (let the layout group set the correct position)s
        listing.transform.SetParent(transform, false);

        PlayerListing playerListing = listing.GetComponent<PlayerListing>();
        if (playerListing == null)
        {
            throw new System.NullReferenceException("ListingPrefab must have a PlayerListing component attached to it");
        }

        playerListing.SetupPhotonPlayer(player);
        listings.Add(playerListing);
    }

    private void PlayerLeftRoom(PhotonPlayer player)
    {
        int index = listings.FindIndex(item => item.PhotonPlayer.Equals(player));
        Debug.Log("Left Room Index: " + index);
        if (index != -1)
        {
            Destroy(listings[index].gameObject);
            listings.RemoveAt(index);
        }
    }

    public void UpdateCharacter(PhotonPlayer player, Character character)
    {
        int index = listings.FindIndex(item => item.PhotonPlayer.Equals(player));
        if (index != -1)
        {
            PlayerListing listing = listings[index];
            listing.UpdateCharacter(character);
        }
    }
}
