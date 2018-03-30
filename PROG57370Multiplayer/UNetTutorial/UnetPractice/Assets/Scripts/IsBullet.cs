﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsBullet : MonoBehaviour {

    private void OnCollisionEnter(Collision collision) {

        Health health = collision.gameObject.GetComponent<Health>();

        if (health != null) {

            health.TakeDamage(10);
        }

        Destroy(gameObject);
    }
}
