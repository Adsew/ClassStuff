using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PersonalAStar : MonoBehaviour {

    public static PersonalAStar Instance { get; private set; }

    public Vector3 mapMinRange = new Vector3();
    public Vector3 mapMaxRange = new Vector3();

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
            previous = prev;

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

        if (position == destination) {

            return;
        }
        
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
            
            current = openList[0];

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
                    
                    EstablishPath(neighb, path);

                    return;
                }

                bool skip = false;

                // Ensure not already closed
                foreach (AStarPosition closed in closedList) {

                    if (closed.position == neighb.position && closed.f <= neighb.f) {
                        
                        skip = true;
                        break;
                    }
                }

                if (skip) {

                    continue;
                }
                
                // Reevaluate if found in open
                foreach (AStarPosition open in openList) {

                    if (open.position == neighb.position) {

                        if (open.f > neighb.f) {

                            openList.Remove(open);
                        }
                        else {

                            skip = true;
                        }
                        
                        break;
                    }
                }

                if (skip) {

                    continue;
                }

                openList.Add(neighb);
            }
        }

        // Dest not found, find lowest f and move to this point instead
        if (closedList.Count > 0) {

            current = closedList[0];

            for (int i = 1; i < closedList.Count; i++) {

                if (closedList[i].f < current.f) {

                    current = closedList[i];
                }
            }

            EstablishPath(current, path);
        }
    }

    // Get all eligable surrounding positions and return as a list
    private List<AStarPosition> GetNeighbours(AStarPosition currentPos, Vector3 destination) {

        List<AStarPosition> neighbours = new List<AStarPosition>();

        // Left
        Vector3 tempCheck = new Vector3(currentPos.position.x - 1, currentPos.position.y, currentPos.position.z);
        if (InBounds(tempCheck, mapMinRange, mapMaxRange)
            && !AStarPathfinding.PathFinding.Instance.CollisionMap.CheckCollision((int)tempCheck.x, (int)tempCheck.y * -1)) {

            neighbours.Add(new AStarPosition(tempCheck, currentPos, destination));
        }

        // Right
        tempCheck = new Vector3(currentPos.position.x + 1, currentPos.position.y, currentPos.position.z);
        if (InBounds(tempCheck, mapMinRange, mapMaxRange)
            && !AStarPathfinding.PathFinding.Instance.CollisionMap.CheckCollision((int)tempCheck.x, (int)tempCheck.y * -1)) {

            neighbours.Add(new AStarPosition(tempCheck, currentPos, destination));
        }

        // Up
        tempCheck = new Vector3(currentPos.position.x, currentPos.position.y - 1, currentPos.position.z);
        if (InBounds(tempCheck, mapMinRange, mapMaxRange)
            && !AStarPathfinding.PathFinding.Instance.CollisionMap.CheckCollision((int)tempCheck.x, (int)tempCheck.y * -1)) {

            neighbours.Add(new AStarPosition(tempCheck, currentPos, destination));
        }

        // Down
        tempCheck = new Vector3(currentPos.position.x, currentPos.position.y + 1, currentPos.position.z);
        if (InBounds(tempCheck, mapMinRange, mapMaxRange)
            && !AStarPathfinding.PathFinding.Instance.CollisionMap.CheckCollision((int)tempCheck.x, (int)tempCheck.y * -1)) {

            neighbours.Add(new AStarPosition(tempCheck, currentPos, destination));
        }

        return neighbours;
    }

    private void EstablishPath(AStarPosition finalPosition, List<Vector3> path) {

        while (finalPosition != null) {

            path.Insert(0, finalPosition.position);
            finalPosition = finalPosition.previous;
        }
    }

    // Inclusive bound checking
    public static bool InBounds(Vector3 x, Vector3 min, Vector3 max) {

        if (x.x >= min.x && x.x <= max.x
            && x.y >= min.y && x.y <= max.y
            && x.z >= min.z && x.z <= max.z) {

            return true;
        }

        return false;
    }

    // Default heuristic function
    public static float ManhattenDistance(Vector3 a, Vector3 b) {

        return Vector3.Magnitude(a - b);
    }
}
