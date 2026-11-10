#include <iostream>
#include <string>
using namespace std;

// TravelRoute Class
class TravelRoute {
public:
    float travel_cost;

    TravelRoute(float cost) {
        travel_cost = cost;
    }
};

// StarSystem Class
class StarSystem {
public:
    int system_id;
    string name;
    int num_planets;

    float x;
    float y;
    float z;

    bool is_habitable;

    // Mary tree properties
    StarSystem** children;
    TravelRoute** routes;

    int child_count;
    int capacity;

    StarSystem(int id, string n, int planets,
               float xCoord, float yCoord, float zCoord,
               bool habitable, int M) {

        system_id = id;
        name = n;
        num_planets = planets;

        x = xCoord;
        y = yCoord;
        z = zCoord;

        is_habitable = habitable;
        capacity = M;
        child_count = 0;

        children = new StarSystem*[M];
        routes = new TravelRoute*[M];

        for (int i = 0; i < M; i++) {
            children[i] = nullptr;
            routes[i] = nullptr;
        }
    }
};

// Galaxy Class
class Galaxy {
private:
    int M;

    // Calculating total nodes in a subtree
    int subtree_size(StarSystem* x) const {

        if (x == nullptr)
            return 0;

        int size = 1;

        for (int i = 0; i < x->child_count; i++) {
            size += subtree_size(x->children[i]);
        }

        return size;
    }

    // Checking balance recursively
    bool check_balance(StarSystem* x) const {

        if (x == nullptr)
            return true;

        int minSize = -1;
        int maxSize = -1;

        for (int i = 0; i < x->child_count; i++) {
            StarSystem* child = x->children[i];

            // Every child subtree must also be balanced
            if (!check_balance(child))
                return false;

            int size = subtree_size(child);

            if (minSize == -1 || size < minSize)
                minSize = size;
            if (maxSize == -1 || size > maxSize)
                maxSize = size;
        }

        // Checking difference between child subtree sizes
        if (maxSize - minSize > 1)
            return false;

        return true;
    }

    // Deleting tree recursively
    void destroy(StarSystem* x) {

        if (x == nullptr)
            return;

        for (int i = 0; i < x->child_count; i++) {

            destroy(x->children[i]);

            delete x->routes[i];
        }

        delete[] x->children;
        delete[] x->routes;

        delete x;
    }

public:

    StarSystem* root;

    // Constructor 1: Without root
    Galaxy(int m) {
        M = m;
        root = nullptr;
    }

    // Constructor 2: With root
    Galaxy(int m, StarSystem* r) {

        M = m;
        root = r;
    }

    // Adding child to a StarSystem
    void add_child(StarSystem* parent,
                   StarSystem* child,
                   float cost) {

        if (parent == nullptr || child == nullptr)
            return;

        if (parent->child_count >= M) {
            cout << "Maximum children reached!" << endl;
            return;
        }

        int index = parent->child_count;
        parent->children[index] = child;
        parent->routes[index] = new TravelRoute(cost);
        parent->child_count++;
    }

    // Part (b): Check if tree is balanced
    bool is_balanced(StarSystem* x) const {

        return check_balance(x);
    }

    // Part (c): Count leaf nodes
    int count_leaves(StarSystem* x) const {

        if (x == nullptr)
            return 0;

        // A node with no children is a leaf
        if (x->child_count == 0)
            return 1;

        int count = 0;

        for (int i = 0; i < x->child_count; i++) {

            count += count_leaves(x->children[i]);
        }
        return count;
    }

    // Destructor
    ~Galaxy() {

        destroy(root);
    }
};

// Main Function
int main() {
    // Creating Galaxy with M = 3
    Galaxy galaxy(3);

    // Creating Star Systems
    StarSystem* A = new StarSystem(
        1, "Earth", 1, 0, 0, 0, true, 3
    );

    StarSystem* B = new StarSystem(
        2, "Mars", 0, 1, 2, 3, false, 3
    );

    StarSystem* C = new StarSystem(
        3, "Jupiter", 79, 2, 3, 4, false, 3
    );

    StarSystem* D = new StarSystem(
        4, "Saturn", 82, 3, 4, 5, false, 3
    );

    StarSystem* E = new StarSystem(
        5, "Venus", 0, 4, 5, 6, false, 3
    );

    StarSystem* F = new StarSystem(
        6, "Neptune", 14, 5, 6, 7, false, 3
    );

    // Set root
    galaxy.root = A;

    // Constructing M ary tree
    galaxy.add_child(A, B, 10.5);
    galaxy.add_child(A, C, 15.5);
    galaxy.add_child(A, D, 20.5);

    galaxy.add_child(B, E, 5.5);
    galaxy.add_child(C, F, 8.5);

    // Checking balance
    if (galaxy.is_balanced(galaxy.root)) {
        cout << "Galaxy tree is balanced." << endl;
    }
    else {
        cout << "Galaxy tree is NOT balanced." << endl;
    }

    // Counting leaf nodes
    cout << "Number of leaf nodes: "
         << galaxy.count_leaves(galaxy.root) << endl;

    return 0;
}