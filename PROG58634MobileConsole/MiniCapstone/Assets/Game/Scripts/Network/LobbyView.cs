using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LobbyView : Photon.PunBehaviour
{
    [SerializeField]
    private GameObject listingPrefab;

    private List<RoomListing> listings = new List<RoomListing>();

    //private void Start()
    //{
    //    UpdateRoomListings();
    //}

    private void OnEnable()
    {
        UpdateRoomListings();
    }

    public override void OnReceivedRoomListUpdate()
    {
        UpdateRoomListings();
    }

    /// <summary>
    /// Update the listings of rooms in the lobby
    /// </summary>
    private void UpdateRoomListings()
    {
        RoomInfo[] rooms = PhotonNetwork.GetRoomList();
        Debug.Log("Rooms Count: " + rooms.Length);

        for (int i = 0; i < rooms.Length; i++)
        {
            CreateRoomListing(rooms[i]);

        }
    }

    /// <summary>
    /// Create room if it is a room that is enterable.
    /// </summary>
    /// <param name="roomInfo">info about a photon room.</param>
    private void CreateRoomListing(RoomInfo roomInfo)
    {
        if (roomInfo == null)
        {
            return;
        }

        int index = listings.FindIndex(item => item.RoomName == roomInfo.Name);
        if (index == -1)
        {
            // check that the room is connectable
            if (roomInfo.IsVisible && roomInfo.PlayerCount < roomInfo.MaxPlayers)
            {
                GameObject listing = Instantiate(listingPrefab);
                // set the parent to the lobby view and let the layout group set the position of the listing
                listing.transform.SetParent(transform, false);

                RoomListing roomListing = listing.GetComponent<RoomListing>();
                if (roomListing == null)
                {
                    throw new System.NullReferenceException("Cannot Instantiate a room listing without RoomListing component attached");
                }

                roomListing.SetRoomName(roomInfo.Name);
                listings.Add(roomListing);
                // set that this room has been touched (i.e. is active/connectable)
                roomListing.Valid = true;
            }
        }
        else
        {
            RoomListing listing = listings[index];
            // set that this room has been touched (i.e. is active/connectable)
            listing.Valid = true;
        }
    }

    /// <summary>
    /// Remove any listings that were not in the rooms list
    /// </summary>
    private void RemoveOldRooms()
    {
        for (int i = 0; i < listings.Count; i++)
        {
            if (listings[i].Valid == false)
            {
                Destroy(listings[i].gameObject);
                listings.RemoveAt(i);
            }
            else
            {
                listings[i].Valid = false;
            }
        }
    }
}
