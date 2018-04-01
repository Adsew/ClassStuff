using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PersonalAStar : MonoBehaviour {

    public static PersonalAStar Instance { get; private set; }

    public Vector3 mapXRange = new Vector3();
    public Vector3 mapYRange = new Vector3();

    private void Start() {
        
        if (Instance == null) {

            Instance = this;
        }
    }

    // Holds all of the information for one part of a path
    private class AStarPosition {

        public int g;
        public float h;
        public float f;

        public Vector3 position;
        public AStarPosition previous;

        public AStarPosition(Vector3 pos, AStarPosition prev, Vector3 dest) {

            position = pos;
            prev = previous;

            if (prev != null) {

                g = prev.g + 1;
            }
            else {

                g = 0;
            }

            h = PersonalAStar.ManhattenDistance(position, dest);
            f = g + h;
        }
    }

    // Pathfinding returns path through path variable
	public void AStarPath(Vector3 position, Vector3 destination, List<Vector3> path) {

        bool destinationFound = false;

        // Setup required variables
        List<AStarPosition> openList = new List<AStarPosition>();
        List<AStarPosition> closedList = new List<AStarPosition>();

        if (path == null) {

            path = new List<Vector3>();
        }

        path.Clear();

        // Add first position as start of path
        AStarPosition current = new AStarPosition(position, null, destination);
        openList.Add(current);

        // Begin checking all possible paths on loop
        while (openList.Count > 0) {

            if (destinationFound) {

                break;
            }

            // Find lowest f to work with
            foreach (AStarPosition p in openList) {

                if (p.f < current.f) {

                    current = p;
                }
            }

            openList.Remove(current);
            closedList.Add(current);

            // Evaluate neighbours
            List<AStarPosition> neighbours = GetNeighbours(current, destination);

            foreach (AStarPosition neighb in neighbours) {

                // If we found destination, break, we're done
                if (neighb.position == destination) {

                    destinationFound = true;

                    break;
                }

                // Ensure not already closed
                bool skip = false;

                foreach (AStarPosition closed in closedList) {

                    if (closed.position == neighb.position) {

                        skip = true;
                    }
                }

                if (skip) {

                    continue;
                }

                // Reevaluate if found in open
                foreach (AStarPosition open in openList) {

                    if (open.position == neighb.position && open.f > neighb.f) {

                        openList.Remove(open);
                        break;
                    }
                }

                openList.Add(neighb);
            }
        }

        EstablishPath(closedList[0], path);
    }

    // Get all eligable surrounding positions and return as a list
    private List<AStarPosition> GetNeighbours(AStarPosition currentPos, Vector3 destination) {

        List<AStarPosition> neighbours = new List<AStarPosition>();

        // Left
        Vector3 tempCheck = new Vector3(currentPos.position.x - 1, currentPos.position.y, currentPos.position.z);
        if (!AStarPathfinding.PathFinding.Instance.CollisionMap.CheckCollision((int)tempCheck.x, (int)tempCheck.y)) {

            neighbours.Add(new AStarPosition(tempCheck, currentPos, destination));
        }

        // Right
        tempCheck = new Vector3(currentPos.position.x + 1, currentPos.position.y, currentPos.position.z);
        if (!AStarPathfinding.PathFinding.Instance.CollisionMap.CheckCollision((int)tempCheck.x, (int)tempCheck.y)) {

            neighbours.Add(new AStarPosition(tempCheck, currentPos, destination));
        }

        // Up
        tempCheck = new Vector3(currentPos.position.x, currentPos.position.y - 1, currentPos.position.z);
        if (!AStarPathfinding.PathFinding.Instance.CollisionMap.CheckCollision((int)tempCheck.x, (int)tempCheck.y)) {

            neighbours.Add(new AStarPosition(tempCheck, currentPos, destination));
        }

        // Down
        tempCheck = new Vector3(currentPos.position.x, currentPos.position.y + 1, currentPos.position.z);
        if (!AStarPathfinding.PathFinding.Instance.CollisionMap.CheckCollision((int)tempCheck.x, (int)tempCheck.y)) {

            neighbours.Add(new AStarPosition(tempCheck, currentPos, destination));
        }

        return neighbours;
    }

    private void EstablishPath(AStarPosition finalPosition, List<Vector3> path) {

        while (finalPosition.previous != null) {

            path.Add(finalPosition.position);
            finalPosition = finalPosition.previous;
        }
    }

    // Default heuristic function
    public static float ManhattenDistance(Vector3 a, Vector3 b) {

        return Vector3.Magnitude(a - b);
    }
}
